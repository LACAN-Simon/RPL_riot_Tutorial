#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "ztimer.h"
#include "shell.h"
#include "mutex.h"
#include "lpsxxx.h"
#include "lpsxxx_params.h"
#include "lsm303dlhc.h"
#include "lsm303dlhc_params.h"
#include "l3g4200d.h"
#include "l3g4200d_params.h"
#include "isl29020.h"
#include "isl29020_params.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "random.h"
#include <sys/time.h>
#include <unistd.h>
#include "thread.h"
#include "shell.h"
#include "msg.h"
#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"
#include "net/gnrc.h"
#include "net/gnrc/ipv6.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/netif/hdr.h"
#include "net/gnrc/udp.h"
#include "net/gnrc/pktdump.h"
#include "net/gnrc/pktbuf.h"
#include "timex.h"
#include "utlist.h"
#include "xtimer.h"
#include "pktbuf_static.h"
#include "pktbuf_internal.h"

#include "net/gnrc/rpl.h"
#include "net/gnrc/rpl/dodag.h"
#include "net/gnrc/rpl/structs.h"


#define SERVER_MSG_QUEUE_SIZE   (8U)
#define SERVER_PRIO             (THREAD_PRIORITY_MAIN - 1)
#define SERVER_STACKSIZE        (THREAD_STACKSIZE_MAIN)
#define SERVER_RESET            (0x8fae)


static gnrc_netreg_entry_t server = GNRC_NETREG_ENTRY_INIT_PID(0, KERNEL_PID_UNDEF);
static char server_stack[SERVER_STACKSIZE];
static msg_t server_queue[SERVER_MSG_QUEUE_SIZE];
static kernel_pid_t server_pid = KERNEL_PID_UNDEF;


static int q=1;
static int id;


static lpsxxx_t lpsxxx ; 
static isl29020_t isl29020;


/*fonction for send a message
addr_srt   destination address
port_str   UDP port 
donne      data send  
*/
static void send(char *addr_str, char *port_str,char *donne)
{
    gnrc_netif_t *netif = NULL;
    char *iface;
    uint16_t port;
    ipv6_addr_t addr;
    size_t data_len;
    iface = ipv6_addr_split_iface(addr_str);
    if ((!iface) && (gnrc_netif_numof() == 1)) {
        netif = gnrc_netif_iter(NULL);
    }
    else if (iface) {
        netif = gnrc_netif_get_by_pid(atoi(iface));
    }
    /* parse destination address */
    if (ipv6_addr_from_str(&addr, addr_str) == NULL) {
        puts("Error: unable to parse destination address");
        return;
    }
    /* parse port */
    port = atoi(port_str);
    if (port == 0) {
        puts("Error: unable to parse destination port");
        return;
    }

    data_len = strlen(donne);



        gnrc_pktsnip_t *payload, *udp, *ip;
        /* allocate payload */
        payload = gnrc_pktbuf_add(NULL, NULL, data_len, GNRC_NETTYPE_UNDEF);
        if (payload == NULL) {
            puts("Error: unable to copy data to packet buffer");
            return;
        }
        memcpy(payload->data, donne, strlen(donne));
        /* allocate UDP header, set source port := destination port */
        udp = gnrc_udp_hdr_build(payload, port, port);
        if (udp == NULL) {
            puts("Error: unable to allocate UDP header");
            gnrc_pktbuf_release(payload);
            return;
        }
        /* allocate IPv6 header */
        ip = gnrc_ipv6_hdr_build(udp, NULL, &addr);
        if (ip == NULL) {
            puts("Error: unable to allocate IPv6 header");
            gnrc_pktbuf_release(udp);
            return;
        }
        /* add netif header, if interface was given */
        if (netif != NULL) {
            gnrc_pktsnip_t *netif_hdr = gnrc_netif_hdr_build(NULL, 0, NULL, 0);

            if (netif_hdr == NULL) {
                puts("Error: unable to allocate NETIF header");
                gnrc_pktbuf_release(ip);
                return;
            }
            gnrc_netif_hdr_set_netif(netif_hdr->data, netif);
            ip = gnrc_pkt_prepend(ip, netif_hdr);
        }
        /* send packet */
        if (!gnrc_netapi_dispatch_send(GNRC_NETTYPE_UDP, GNRC_NETREG_DEMUX_CTX_ALL, ip)) {
            puts("Error: unable to locate UDP thread");
            gnrc_pktbuf_release(ip);
            return;
        }

}

/*loop for the udp server*/
static void *_eventloop(void *arg)
{
    (void)arg;
    msg_t msg;
    gnrc_pktsnip_t *snip;
    /* setup the message queue */
    msg_init_queue(server_queue, SERVER_MSG_QUEUE_SIZE);
    while (1) {
        msg_receive(&msg);

        switch (msg.type) {
            case GNRC_NETAPI_MSG_TYPE_RCV:                
                    snip = (gnrc_pktsnip_t *)msg.content.ptr;
                    if (snip && snip->data && snip->size > 0) {
                        if(q==0){printf("Packet from : %.*s\n", snip->size, (char *)snip->data);
                        }
                    }
                gnrc_pktbuf_release(msg.content.ptr);
                break;

            case SERVER_RESET:
                break;
            default:
                break;
        }
    }

    /* never reached */
    return NULL;
}

/*udp server fonction
port_str   udp port
*/
static void start_server(char *port_str)
{
    uint16_t port;

    /* check if server is already running */
    if (server.target.pid != KERNEL_PID_UNDEF) {
        printf("Error: server already running on port %" PRIu32 "\n",
               server.demux_ctx);
        return;
    }
    /* parse port */
    port = atoi(port_str);
    if (port == 0) {
        puts("Error: invalid port specified");
        return;
    }
    if (server_pid <= KERNEL_PID_UNDEF) {
        /* start server */
        server_pid = thread_create(server_stack, sizeof(server_stack), SERVER_PRIO,
                                   THREAD_CREATE_STACKTEST, _eventloop, NULL, "UDP server");
        if (server_pid <= KERNEL_PID_UNDEF) {
            puts("Error: can not start server thread");
            return;
        }
    }
    /* register server to receive messages from given port */
    gnrc_netreg_entry_init_pid(&server, port, server_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UDP, &server);
    if(q==0){printf("Success: started UDP server on port %" PRIu16 "\n", port);}
}

/*fontion for build a message
addr    destination address
port    udp port
id      id of the sensor
*/
static void build_mess(char *addr,char *port, int id){
        
        int16_t lux = isl29020_read(&isl29020);
        int16_t temp = 0;
        lpsxxx_read_temp(&lpsxxx, &temp);
        // printf("%d %d\n",lux,temp);
        char idu[12];
        snprintf(idu,sizeof(idu),"%d %d %d",id,lux,temp/100);
        // snprintf(idu,sizeof(idu),"%d",id);
        send(addr,port,idu);
}

/*loop to send data
a   destination address
mode   mode of rooting
*/
static void *loop(char *a, char *mode){    
    int m = atoi(mode);
    if(m>1){
        gnrc_rpl_instances[0].dodag.new_p = 1;}
    
    if (gnrc_rpl_instances[0].dodag.nb_childs !=0){printf("nb child %d\n",gnrc_rpl_instances[0].dodag.nb_childs);}
    char *b = "4567";
    gnrc_rpl_instances[0].dodag.met = MET_BASE;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned int seed = tv.tv_sec + tv.tv_usec;
    srand(seed);
    id = rand() % 1000;
    printf("ID = %d\n",id);
    xtimer_sleep(10);

    while(1){
        for(int cmp=0;cmp<10;cmp++){
            if (gnrc_rpl_instances[0].dodag.met - (gnrc_rpl_instances[0].dodag.nb_childs*2)+2<5){gnrc_rpl_instances[0].dodag.met=0;}
            else {gnrc_rpl_instances[0].dodag.met = gnrc_rpl_instances[0].dodag.met - ((gnrc_rpl_instances[0].dodag.nb_childs*2)+2);
                build_mess(a,b,id);}
            if (gnrc_rpl_instances[0].dodag.met<1){
                gnrc_rpl_dodag_remove_all_parents(&gnrc_rpl_instances[0].dodag);
                gnrc_rpl_leaf_operation(&gnrc_rpl_instances[0].dodag);
                printf("sensor dead\n");
                break; }
            
            xtimer_sleep(1);
        }
        if (m==1){gnrc_rpl_instances[0].dodag.new_p = 1;}
        gnrc_rpl_instances[0].dodag.nb_childs=0;
        ipv6_addr_t null_addr; 
        memset(&null_addr, 0, sizeof(ipv6_addr_t));
        for (int j = 0; j < 10; j++) {
        memcpy(&gnrc_rpl_instances[0].dodag.childs[j], &null_addr, sizeof(ipv6_addr_t));
        }
        xtimer_sleep(10);
        for(int j=0;j<100;j++){
            gnrc_rpl_send_DAO(&gnrc_rpl_instances[0],&gnrc_rpl_instances[0].dodag.parents->addr,0);}
        xtimer_sleep(20);
        if (m==1){gnrc_rpl_instances[0].dodag.new_p = 0;}
        if (gnrc_rpl_instances[0].dodag.nb_childs !=0){printf("nb childs = %d\n",gnrc_rpl_instances[0].dodag.nb_childs);}
        printf("bat = %d\n", gnrc_rpl_instances[0].dodag.met); 
    }
    
    return NULL;
}

   

static int test_handler(int argc, char *argv[]){
    if (argc < 3 || argc > 3) {
        printf("<ipv6 adresse> <mode>/n");
        return -1;}
    if(q==1){
        server_pid = thread_create(server_stack, sizeof(server_stack), SERVER_PRIO,
                                   THREAD_CREATE_STACKTEST, loop(argv[1],argv[2]), NULL, "UDP server");
    }
    return 1;
}

static int serv_handler(int argc, char *argv[]){
    if (argc < 2 || argc > 2) {
        printf("<udp port>");
        return -1;}
    start_server(argv[1]);
    q = 0;
    return 0;
}

static const shell_command_t commands[] = {
    {"go","send a message", test_handler},
    {"ser","create server", serv_handler},
    { NULL, NULL, NULL}
};





int main(void)
{
    lpsxxx_init(&lpsxxx, &lpsxxx_params[0]);
    
    isl29020_init(&isl29020, &isl29020_params[0]);

    /* Everything is ready, let's start the shell now */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    
    
    return 0;
}