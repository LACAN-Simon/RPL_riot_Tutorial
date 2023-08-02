# READ_ME
## Introduction
In this github, you will find how to create a RPL network with nodes of the Iot-Lab and send data like temperature or luminosity in real time. It also creates a fake battery parameter on eatch nodes to see how the battery will evolve during the experiment. 
The aplication will create automatically the network, you will just have to choose the root node.
You have in the application 3 modes of rooting. 

## Modes
### Mode 1
This mode creates a  RPL network and assigns each node a rank depending of how far the node is to the base. All paths communication are choosen only with the rank parameter. To launch an experiment with this mode, put 0 in the second parameter of the fonction "go".

### Modes 2 and 3
This two modes create also a RPL network like the mode 1 but both are using the battery parameter to assign communication paths. The difference between the two modes is that the mode 2 use the rank to choose paths and update all of the paths with battery parameter every minute when the mode 3 initializes the network with ranks and after uses only the battery to define paths.
To launch an experiment with the mode 2, put 1 in the second parameter of the fonction "go". Put 2 if you want to test mode 3.

## Launch experiments and analyse results
To launch an experiment with the firmware sensors.elf and analyse your results with a Jupyther Notebook, you just have to folow the instructions of Notebooks experiment.ipynb and analyze.ipynb.

You will maybe have some problems with the values of the luminosity. Some nodes have issues with this sensor. Just take other nodes.

The application was created with the OS riot. In the directory "sources", you can find the main.c of the application and also all of the RIOT files which have been modified.

If you encounter a problem or have any questions, you can contact me by email at simon.lacan@gmail.com 




