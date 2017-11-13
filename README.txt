/*

• Implemented the network emulator on Unix with C as programming language. 

• Implemented to emulate the functionalities of networking devices such as switches and routers. 

• Added functionalities such as stations sending/receiving Ethernet data frames, broadcasting of data frames by bridges, self-learning function of bridges, ARP protocol, stations sending/receiving IP packets, IP packet forwarding, stations handling sending/receiving data frames and user input concurrently, connecting/disconnecting stations/routers at any time.


*/






*************************** Sharing of information between server and client ******************************************

In the project description, it was mentioned that sharing of information between client and server can be implemented in ways other than mentioned in the project description. Therefore, I used the following approach for sharing information between client and server.

In my project, sharing of information is done through files lanaddr.txt and lanport.txt. Whenever, a bridge starts, it stores its ip address and port number in the files lanaddr.txt and lanport.txt respectively. 

A Bridge stores its ip address in the file lanaddr.txt in the following format:

.lan-name.addr

For example: Bridge cs1, when started, stores ip address in the file lanaddr.txt in the following format:

.cs1.linprog3


A Bridge stores its portnumber in the file lanport.txt in the following format:

.lan-name.port


For example: Bridge cs1, when started, stores portnumber in the file lanport.txt in the following format:

.cs1.34930



************************************ Station side functionality ********************************************************

As soon as a station is connected to bridge, type the following to send a message:

<destination> <message> //send message to a destination host

For example, in order to send message "Hello how are you" to station B, type the following:

B Hello how are you

Commands:       

In order to show routing table, type the following:

rout 

In order to show ARP cache, type the following:

ach

In order to show name/address mappings, type the following:

host


In order to show interface table, type the following:

ift 


************************************** Router side functionality ***************************************************

Commands:

In order to show routing table, type the following:

rout 

In order to show ARP cache, type the following:

ach

In order to show name/address mappings, type the following:

host


In order to show interface table, type the following:

ift 


*************************************** Bridge side functionality ****************************************************


In order to show the contents of self-learning table, type the following:

swt



