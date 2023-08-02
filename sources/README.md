# Sources of the code 

In this repersitory, you will find the main.c of the sensors.elf application, the makefile and all of the files of Riot I changed. 

If you want to modify the main.c and after make a new application, you just have to download this repersitory and put it in your ssh server. 

For this, do $git clone https://github.com/LACAN-Simon/RPL_riot_Tutorial.git

Do not forget to replace all of the Riot files modified and work with Riot set up for Iot-Lab apps. The best way is to work in the JupyterLab give by Iot-Lab. Here is the list with the path for each. 

- sys/include/net/gnrc/rpl/structs.h
- sys/include/net/gnrc/rpl.h 
- sys/net/gnrc/routing/rpl/gnrc_rpl.c
- sys/net/gnrc/routing/rpl/of0.c 
- sys/net/gnrc/routing/rpl/gnrc_rpl_control_messages.c

  If you have some issues with this part, send an email to simon.lacan@gmail.com

