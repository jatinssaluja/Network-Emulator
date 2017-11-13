/*

Course: CNT 5505 Data and Computer Communications

Semester: Spring 2016

Name: Jatin Singh Saluja


*/



#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/times.h>
#include <resolv.h>
#include <arpa/nameser.h>
#include <string.h>
#include <sys/select.h>

unsigned long int conv(char []);

int main(int argc, char* argv[]) {


 if(strcmp(argv[1],"-no") == 0)
 {
   printf("This is a station\n");

 char* p2;

 


 
 char subnetrec[10][16];
 char netprefix[10][16];
 char nxthoprec[10][16];
 char rtifacerec[10][40];
 char lanrec[10][10];


int socrec[10];
 char srcmacrec[10][40];
 char srciprec[10][40];
 char ifacerec[10][40]; 

char riface[40];




  
 int netflag = 0;
 
 char str6[100];

for(int i=0;i<10;i++)
 {
    strcpy(lanrec[i],"NULL");
    strcpy(srcmacrec[i],"NULL");
    strcpy(srciprec[i],"NULL");
    strcpy(ifacerec[i],"NULL");
    socrec[i] = 0;
 
    

    }




 for(int i=0;i<10;i++)
 {

    strcpy(subnetrec[i],"NULL");
    strcpy(netprefix[i],"NULL");
    strcpy(nxthoprec[i],"NULL");
    strcpy(rtifacerec[i],"NULL");
   }

 FILE * fp6 = fopen(argv[3], "r"); // rtable file
  int rcounter = 0;
   while(fgets (str6, sizeof(str6), fp6)!=NULL)
   {
        if(strspn(str6, " \r\n\t") == strlen(str6))
        {
            break;
           }


    //printf("%s\n", str6); 
    char* ptr1 = strtok(str6, " "); // gives the network prefix
    strcpy(netprefix[rcounter],ptr1);
    //printf("Network prefix is %s\n",netprefix[rcounter]);
    char* ptr2 = strtok(NULL, " "); // gives the next hop
    strcpy(nxthoprec[rcounter],ptr2);
    //printf("Next hop station is %s\n",nxthoprec[rcounter]);
    char* ptr3 = strtok(NULL, " "); // gives the subnet
    strcpy(subnetrec[rcounter],ptr3);
    //printf("Subnet is %s\n",subnetrec[rcounter]);
    char* ptr4 = strtok(NULL, " \n");  // gives the interface name

    strcpy(rtifacerec[rcounter],ptr4);
    //printf("Interface is %s\n",rtifacerec[rcounter]);

    memset(str6, 0, sizeof(str6));
    rcounter++;

    }

 
 struct arprequest{
 
       
       char srcmac[40];
       char srcip[40];
       char destmac[40];
       char destip[40];
       int type;

     };





  struct ippack{

   char srcip[40];
   char destip[40];
   char c1[256];
   };

struct pyload{

   struct ippack ipp;
   struct arprequest arpreq;
   };

 struct ippack tempque[5];

 struct ippack temp;

 for(int x=0;x<5;x++)
 {
  struct ippack temp1;
  

  strcpy(temp1.srcip,"NULL");
  strcpy(temp1.destip,"NULL");
  strcpy(temp1.c1,"NULL");
  
  tempque[x] = temp1;

   }




  

  char server_response[256];

   struct ether{
 
   int flag;
   char srcmac[40];
   char destmac[40];
   struct pyload pyld;

   };



  struct ether eth;


  FILE * fp5 = fopen(argv[4], "r");
   char str5[100];
   char arpcacheip[25][40];
   char arpcachemac[25][40];


  for(int i=0;i<25;i++)
 {

    strcpy(arpcacheip[i],"NULL");
    strcpy(arpcachemac[i],"NULL");
   }

    int ik=0;
  
   while(fgets ( str5, sizeof(str5), fp5)!=NULL)
   {
        if(strspn(str5, " \r\n\t") == strlen(str5))
        {
            break;
           }



     char* ptr13 = strtok(str5, " \t");// gives the station name 
     char* ptr14 = strtok(NULL, " \n"); // gives the ip address of station
     //char* ptr15 = strtok(NULL, " \n"); // gives the mac address of station


    
     strcpy(arpcacheip[ik],ptr14);
     strcpy(arpcachemac[ik],"NULL");
     ik++;

    }

  /*printf("Printing arp cache ip addresses:\n");

  for(int i=0;i<25;i++)
  {

    printf("Address is %s\n",arpcacheip[i]);
    }*/



  const char* ptr7; // Bridge address
  const char* ptr9; // Bridge port
 
  int sockfd, n;
  struct addrinfo hints, *res;
    char* ptr1;
    char* ptr2;
    char* ptr3;
    char* ptr4;
    char* xyz;


    char str1[100];
    char str2[100];
    char str3[100];
  FILE * fp1 = fopen(argv[2], "r"); // interface file

  int g=0;

  int findic = 0;

 while( fgets (str1, sizeof(str1), fp1) != NULL)
     {

          if(strspn(str1, " \r\n\t") == strlen(str1))
        {
            break;
           }

         


   //printf("Creating the socket\n");
	
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family=AF_UNSPEC;
  hints.ai_socktype=SOCK_STREAM;
  hints.ai_protocol=IPPROTO_TCP;


 

    
    //printf("%s\n", str1);
    ptr1 = strtok(str1, " ");
    ptr2 = strtok(NULL, " "); // gives the source ip address
    ptr3 = strtok(NULL, " ");
    ptr4 = strtok(NULL, " "); // gives the source mac address
    const char* a = strtok(NULL, " \n");  // gives the lan name
    xyz ="hello";

    

    
    //printf("%s\n", ptr1);     // print what we got
    //printf("%s\n", ptr2);
    //printf("Source mac address is %s\n", ptr4); 
    



   FILE * fp3 = fopen("lanaddr.txt", "r");
   FILE * fp4 = fopen("lanport.txt", "r");

  while( fgets ( str2, sizeof(str2), fp3) != NULL)
     {

    //printf("%s\n", str2); 
    const char* b = strtok(str2, ".");// gives the lan name
    ptr7 = strtok(NULL, " \n"); // gives the ip address
    //printf("%s\n", b);     // print what we got
   // printf("%s\n", ptr7);
  //printf("LAN name is %s\n", b);


   if(strcmp(a,b) == 0)
   {
      //printf("Equal lan names\n");

   
       // printf("IP address of %s is %s\n",b, ptr7);
       
         break;

      }

   memset(str2, 0, sizeof(str2));
    
        
    }


while( fgets ( str3, sizeof(str3), fp4) != NULL)
     {

    //printf("%s\n", str3);
    char* ptr8 = strtok(str3, "."); // gives the lan name
    ptr9 = strtok(NULL, " \n"); //  gives the port number
    //printf("%s\n", ptr8);     // print what we got
    //printf("%s\n", ptr9);
 


   if(strcmp(ptr8, a) == 0)
   {

      //printf("Equal lan names\n");

      //printf("Port number is %s\n",ptr9);
        
       
         break;

      }

   memset(str3, 0, sizeof(str3));
    
        
    }
//printf("Value of g is %d\n",g);
   //printf(" Value of ptr7 is %s\n",ptr7);
  //printf("Value of ptr9 is %s\n",ptr9);
 //printf("Value of ptr1 is %s\n",ptr1);
 //printf("Value of a is %s\n",a);
 //printf("Value of xyz is %s\n",xyz);
//printf("MAC Address is %s\n",ptr4);


  if((n=getaddrinfo(ptr7, ptr9, &hints, &res))!=0)
    printf("getaddrinfo error for %s, %s; %s", ptr7,ptr9, gai_strerror(n));

  //ressave=res;

  do{
   sockfd=socket(res->ai_family, res->ai_socktype, res->ai_protocol);
 
   if(sockfd<0)
     continue;  /*ignore this returned Ip addr*/
  
   if(connect(sockfd, res->ai_addr, res->ai_addrlen)==0)
    { 
      //printf("connection ok!\n"); /* success*/

    int rets = recv(sockfd, &server_response, sizeof(server_response), 0);

     //printf("\n>>> %s\n",server_response);

      if(strcmp(server_response,"reject") == 0)
      {

        printf("Connection rejected\n");
        close(sockfd);
        exit(1);

	
        //break;

        }

      socrec[g] = sockfd;
      strcpy(srcmacrec[g],ptr4); 
      //printf("MAC Address is %s\n",srcmacrec[g]);
      strcpy(srciprec[g],ptr2); 
      //printf("IP Address  is %s\n",srciprec[g]);
   
      strcpy(lanrec[g],a);
      strcpy(ifacerec[g],ptr1);

      //printf("LAN name is%s\n", lanrec[g]);
      //printf("Interface is%s\n", ifacerec[g]);




      //int pq = send(sockfd, (struct message*)&msg, sizeof(struct message), 0);

      struct sockaddr_storage my_addr;
      socklen_t len = sizeof(my_addr);
     if (getsockname(sockfd, (struct sockaddr *)&my_addr, &len) == -1)
     perror("getsockname");
     else
     {
      //printf("port number %d\n", ntohs(server_address.sin_port));

       char serv[256];
       char host[256];

    if (getnameinfo((const struct sockaddr *) &my_addr, len,host,sizeof(host),
                    serv, sizeof(serv), 0) == 0)
    {
         //int rets = recv(sockfd, &server_response, sizeof(server_response), 0);

          //printf("\n>>> %s\n",server_response);

        printf("admin: connected to server on '%s' at '%s' thru '%s'\n",ptr7,ptr9, serv);
    }


         }








      break;
    }
   else  {
     perror("connecting stream socket");
   }


   
  } while ((res=res->ai_next)!= NULL);


 g++;

  }




	//receive data from the server

    

    char client_response[256];

int fd,max;
 fd=0;

 max =0;

int ret;


fd_set readset;

 while(1)
 {
     FD_ZERO(&readset);

     FD_SET(fd,&readset);
     

      for(int j1=0;j1<10;j1++)
     {
         
       if(socrec[j1]>0)
       {

         FD_SET(socrec[j1],&readset);

         if(socrec[j1]>max)
         {
             max = socrec[j1];

          }   // end of inner if
        }     //end of outer if

      }       // end of for loop







    memset((void*)client_response,0,256);

    select(max+1,&readset,NULL,NULL,NULL);

   if(FD_ISSET(fd,&readset))
   {

    ret = read(fd,(void*)client_response,255);

      

      if(strcmp(strtok(client_response, "\n"), "host") == 0)
      { 


           FILE * fhost = fopen(argv[4], "r"); // hosts file 

                char fh1[100];
             
               while( fgets ( fh1, sizeof(fh1), fhost) != NULL)
              {


                        printf("%s\n", fh1);
                 }

        } 



   if(strcmp(strtok(client_response, "\n"), "ift") == 0)
    { 


    FILE * fi = fopen(argv[2], "r"); // interface file
    char fti[100];
  
         while(fgets (fti, sizeof(fti), fi)!=NULL)
         {
               printf("%s\n", fti); 

            } 
    
     }


    if(strcmp(strtok(client_response, "\n"), "rout") == 0)
    { 

          // printf("condition satisfied\n");

           FILE * fr = fopen(argv[3], "r"); // rtable file
           char rst[100];
  
          while(fgets (rst, sizeof(rst), fr)!=NULL)
         {
               printf("%s\n", rst);     

            }

      }
    
   
    
   if(strcmp(strtok(client_response, "\n"), "ach") == 0)
   { 
      //printf("condition satisfied\n");
      int arpfound = 0;

   for(int i=0;i<25;i++)
   {
     
     if(strcmp(arpcachemac[i],"NULL")!=0)
     {
          arpfound = 1;
          printf("%s",arpcacheip[i]);
          printf("  %s\n",arpcachemac[i]);

      }

    }
  
  if(arpfound == 0)
  {
      printf("Arp cache is empty\n");
    }


  }

 if( (strcmp(strtok(client_response, "\n"), "ach") != 0) && (strcmp(strtok(client_response, "\n"), "rout") != 0) && (strcmp(strtok(client_response, "\n"), "ift") != 0) && (strcmp(strtok(client_response, "\n"), "host") != 0)   )
{
   

     FILE * fp2 = fopen(argv[4], "r"); // hosts file 

    char* p1 = strtok(client_response, " ");
    p2 = strtok(NULL, "\n");

   //printf("First argument is %s\n",p1);
   //printf("Second argument is %s\n",p2);
   char str4[100];
   char* ptr10;
   char* ptr11;
   char iprouter[16];
   int found = 0;
   while( fgets ( str4, sizeof(str4), fp2) != NULL)
     {

            if(strspn(str4, " \r\n\t") == strlen(str4))
           {
            break;
           }



    //printf("%s\n", str4);  
    ptr10 = strtok(str4, " \t");// gives the station name 
    ptr11 = strtok(NULL, " \n"); // gives the ip address of station
    //char* ptr12 = strtok(NULL, " \n"); // gives the mac address of station

    
    


   if(strcmp(p1, ptr10) == 0)
   {
         //printf("Equal station names names\n");

     struct ippack ftemp;

     temp = ftemp;
     
      
     for(int k=0;k<10;k++)
     {

        if(strcmp(subnetrec[k],"NULL")!=0)
        {
           char t1[16];
           char t2[16];
           char t3[16];

          strcpy(t1,subnetrec[k]);
          strcpy(t2,netprefix[k]);
          strcpy(t3,ptr11);
          unsigned long int n1=conv(t3);
          //printf("Before subnet is %s\n",t1);
          unsigned long int n2=conv(t1);
          //printf("After subnet is %s\n",subnetrec[k]);
          //printf(" Before Net prefix is %s\n",t2);
          unsigned long int n3=conv(t2);
          //printf(" After Net prefix is %s\n",netprefix[k]);
            
          unsigned long int n4 = n1&n2;

          if(n3 == n4)
          { found = 1;

            strcpy(riface,rtifacerec[k]);

            //printf("Next hop router found\n");
            //printf("Net prefix is %s\n",netprefix[k]);
            //printf("Next hop station is %s\n",nxthoprec[k]);
            //printf("Interface through which routing to occur is %s\n",rtifacerec[k]);
           
              if(strcmp(nxthoprec[k],"0.0.0.0") == 0)
              {
                 //printf("packet is to be routed in the same network\n");
                 //frame1.rout = 0;
                   netflag = 0;
                  }

               else
               {
                 netflag = 1;
                 //frame1.rout = 1;
                 //printf("packet is to be routed to a different network\n");
                 strcpy(iprouter,nxthoprec[k]);
                 //printf("IP address of router is %s\n",iprouter);
                 }


            break;
            }
         }
      }

    } // end of if

   if(found ==1)
   {
      //printf("Break out of while loop\n");
      break;
    }

   memset(str4, 0, sizeof(str4));
    
        
    } // end of while

    if(netflag == 0)
    {
       // printf("Starting the arp thing for a packet to be routed in the same network\n");


      //printf("Checking ip and mac address in arp cache\n");

      for(int i=0;i<25;i++)
      {
         if(strcmp(arpcacheip[i],ptr11) == 0)
         {
           if(strcmp(arpcachemac[i],"NULL")!=0)
            {
               //printf("ARP cache mac address found\n");
               //printf("Address is %s\n",arpcachemac[i]);
               
             // frame1.flag = 1; for ethernet frame
              eth.flag = 1;// for ip packet.
           
           for(int f=0;f<g;f++)
            {     
               if(strcmp(riface,ifacerec[f]) == 0)
               {  

              strcpy(temp.srcip,srciprec[f]);
              strcpy(temp.destip,ptr11);
              strcpy(temp.c1,p2);

              strcpy(eth.srcmac, srcmacrec[f]);
              strcpy(eth.destmac, arpcachemac[i]);
              strcpy(eth.pyld.ipp.srcip, temp.srcip);
              strcpy(eth.pyld.ipp.destip, temp.destip);
              strcpy(eth.pyld.ipp.c1, p2);
              send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
              break;

               }
            }

            //printf("Ip address is %s\n",ptr11);
            //printf("Mac address is %s\n",ptr12);
             break;
               }

            else
            {

              // printf("ARP cache mac address not found\n");


               eth.flag = 2; // for arprequest frame

              for(int f=0;f<g;f++)
               {     
                  if(strcmp(riface,ifacerec[f]) == 0)
                  {
                        strcpy(temp.srcip,srciprec[f]);
                        strcpy(temp.destip,ptr11);
                        strcpy(temp.c1,p2);


               eth.pyld.arpreq.type = 1;
               strcpy(eth.srcmac, srcmacrec[f]);
               strcpy(eth.destmac, "ff:ff:ff:ff:ff:ff");
               strcpy(eth.pyld.arpreq.srcmac, srcmacrec[f]);
               strcpy(eth.pyld.arpreq.srcip, srciprec[f]);
               strcpy(eth.pyld.arpreq.destmac, "00:00:00:00:00:00");
               strcpy(eth.pyld.arpreq.destip, ptr11);
             

             for(int d=0;d<5;d++)              
             {
                 if(strcmp(tempque[d].srcip,"NULL") ==0)
                 {
                         tempque[d] = temp;
                         break;
                   }
               }

            send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);


               break;
          }
       }

         break;      

               }// end of else

             } // end of first if after for loop

           } // end of for loop

         } // end of if for netflag

       if(netflag == 1)
    {
        //printf("Starting the arp thing for a packet to be routed to a different network\n");


      //printf("Checking ip and mac address of router in arp cache\n");

      for(int i=0;i<25;i++)
      {
         if(strcmp(arpcacheip[i],iprouter) == 0)
         {
           if(strcmp(arpcachemac[i],"NULL")!=0)
            {
               //printf("ARP cache mac address found\n");
               //printf("Address is %s\n",arpcachemac[i]);
               
              eth.flag = 1;// for ip packet

             for(int f=0;f<g;f++)
            {     
               if(strcmp(riface,ifacerec[f]) == 0)
               { 
                       strcpy(temp.srcip,srciprec[f]);
                        strcpy(temp.destip,ptr11);
                        strcpy(temp.c1,p2);


              strcpy(eth.srcmac, srcmacrec[f]);
              strcpy(eth.destmac, arpcachemac[i]);
              strcpy(eth.pyld.ipp.srcip, temp.srcip);
              strcpy(eth.pyld.ipp.destip, temp.destip);
              strcpy(eth.pyld.ipp.c1, temp.c1);

             send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
             break;
          }
       }




            //printf("Ip address is %s\n",ptr11);
            //printf("Mac address is %s\n",ptr12);
             break;
               }

            else
            {

               //printf("ARP cache mac address not found\n");


               eth.flag = 2; // for arprequest frame
               eth.pyld.arpreq.type = 1;
             
           for(int f=0;f<g;f++)
               {     
                 if(strcmp(riface,ifacerec[f]) == 0)
                 { 
                        strcpy(temp.srcip,srciprec[f]);
                        strcpy(temp.destip,ptr11);
                        strcpy(temp.c1,p2);



               strcpy(eth.srcmac, srcmacrec[f]);
               strcpy(eth.destmac, "ff:ff:ff:ff:ff:ff");
               strcpy(eth.pyld.arpreq.srcmac, srcmacrec[f]);
               strcpy(eth.pyld.arpreq.srcip, srciprec[f]);
               strcpy(eth.pyld.arpreq.destmac, "00:00:00:00:00:00");
               strcpy(eth.pyld.arpreq.destip, iprouter);
              // printf("Dest ip address in arpreq is %s\n",eth.pyld.arpreq.destip);
             
              for(int d=0;d<5;d++)              
             {
                 if(strcmp(tempque[d].srcip,"NULL") ==0)
                 {
                         tempque[d] = temp;
                         break;
                   }
               }

               send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
               break;
            }
         }


               break;

               

               }// end of else

             } // end of first if after for loop

           } // end of for loop

         } // end of if for netflag

       //  } // end of if

   //memset(str4, 0, sizeof(str4));
    
        
   // } // end of while









    //printf("\n ret = %d\n",ret);

    if(ret==0)
    {
         //close the socket

	for(int j1=0;j1<g;j1++)
     {
         
       if(socrec[j1]>0)
       {


	close(socrec[j1]);
        }

      }

        break;

         }
        
     

     /*if(ret>0)
     { printf("Sending frame\n");
       //printf("\n client_response = %s\n",client_response);
       int r = send(sockfd,(struct ether*)&eth, sizeof(struct ether), 0);

       if(r>0)
       {
         printf("\n Frame sent : %d \n",r);
         //printf("Message to send: %s\n",frame1.arpreq.c1);

           }
      }*/

  } // end of else

    }// end of isset if




for(int j2=0;j2<10;j2++)
{
  if(socrec[j2]>0)
  {




   if(FD_ISSET(socrec[j2],&readset))
   {


int rets = recv(socrec[j2],(struct ether*)&eth, sizeof(struct ether), 0);

        if(rets>0)
        {
           //printf("frame received\n");
           //printf("Flag is %d\n",eth.flag);


        int mfound = 0;


           for(int f=0;f<g;f++)
                    {
                  
                       if(strcmp(srcmacrec[f],eth.destmac) == 0)
                       {
                          mfound = 1;
                          //printf("Mac address matched\n");
                         }
                      }
                          






        if(mfound == 1)
        {

           if(eth.flag == 1)
           {


                 FILE * fpr = fopen(argv[4], "r"); // hosts file 

    
                  char stc[100];
                  char* stc2;
                  char* stc3;
               while( fgets ( stc, sizeof(stc), fpr) != NULL)
              {

               
                        stc2 = strtok(stc, " \t");// gives the station name 
                        stc3 = strtok(NULL, " \n"); // gives the ip address of station
    
                        if(strcmp(stc3, eth.pyld.ipp.srcip) == 0)
                        {
                              
                             printf("\nMessage from %s>>> %s\n",stc2,eth.pyld.ipp.c1);
                             break;

                           }
                  }


              
              }

           if(eth.flag == 2)
           {
              //printf("Station receiving a frame of type arp\n");

              if(eth.pyld.arpreq.type == 2)
              {
                  //printf("Station receiving a frame of type arp response\n");

                 for(int i=0;i<25;i++)
                 {
                    if(strcmp(arpcacheip[i],eth.pyld.arpreq.srcip) == 0)
                    {
                     strcpy(arpcachemac[i],eth.pyld.arpreq.srcmac);
                     break;
                      }
                }

                  //printf("Constructing a frame of type ip\n");
                  int rfound = 0;

                  eth.flag = 1; // for ip packet

                
                       for(int e=0;e<10;e++)
                      {
                         if(strcmp(nxthoprec[e],eth.pyld.arpreq.srcip) == 0)
                         {
                              rfound = 1;
                              for(int d=0;d<5;d++)              
                              {
                                 if(strcmp(tempque[d].srcip,"NULL") !=0)
                                 {
                                       if(strcmp(subnetrec[e],"NULL")!=0)
                                      {
                                              char t1[16];
                                              char t2[16];
                                              char t3[16];

                                         strcpy(t1,subnetrec[e]);
                                         strcpy(t2,netprefix[e]);
                                         strcpy(t3,tempque[d].destip);
                                         unsigned long int n1=conv(t3);
                                        // printf("Before subnet is %s\n",t1);
                                         unsigned long int n2=conv(t1);
                                         //printf("After subnet is %s\n",subnetrec[e]);
                                         //printf(" Before Net prefix is %s\n",t2);
                                         unsigned long int n3=conv(t2);
                                        //printf(" After Net prefix is %s\n",netprefix[e]);
            
                                         unsigned long int n4 = n1&n2;
                                         
                                        if(n3 == n4)
                                        {
                                          strcpy(eth.srcmac, eth.pyld.arpreq.destmac);
                                          strcpy(eth.destmac, eth.pyld.arpreq.srcmac); 
                                          strcpy(eth.pyld.ipp.srcip, tempque[d].srcip);
                                          strcpy(eth.pyld.ipp.destip, tempque[d].destip);
                                          strcpy(eth.pyld.ipp.c1, tempque[d].c1);

                                          //printf("Construction of ip packet completed\n");


                                           for(int f=0;f<g;f++)
                                          {
                                               if(socrec[f] == socrec[j2])
                                               {
          
                                                    strcpy(eth.srcmac, srcmacrec[f]);

                                          send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
                                          //printf("Ip packet sent\n");
                              
                                          strcpy(tempque[d].srcip,"NULL");
                                          strcpy(tempque[d].destip,"NULL");
                                          strcpy(tempque[d].c1,"NULL");

                                           break;
                                        }
                                   }



                                                }



                                }
                                     
                   

                     }

                    }
                  break;
                   }

                }


          if(rfound == 0)
          {
              for(int d=0;d<5;d++)              
              {
                 if(strcmp(tempque[d].srcip,"NULL") !=0)
                  {
                    if(strcmp(tempque[d].destip,eth.pyld.arpreq.srcip) == 0)
                     {
                                strcpy(eth.srcmac, eth.pyld.arpreq.destmac);
                                strcpy(eth.destmac, eth.pyld.arpreq.srcmac);
                                strcpy(eth.pyld.ipp.srcip, tempque[d].srcip);
                                strcpy(eth.pyld.ipp.destip, tempque[d].destip);
                                strcpy(eth.pyld.ipp.c1, tempque[d].c1);

                                //printf("Construction of ip packet completed\n");


                        for(int f=0;f<g;f++)
                                 {
                                    if(socrec[f] == socrec[j2])
                                     {
          
                                           strcpy(eth.srcmac, srcmacrec[f]);


                                send(socrec[j2],(struct ether*)&eth, sizeof(struct ether), 0);
                                //printf("Ip packet sent\n");
                              
                                strcpy(tempque[d].srcip,"NULL");
                                strcpy(tempque[d].destip,"NULL");
                                strcpy(tempque[d].c1,"NULL");
                                break;
                              }
                          }
                               
                         }
                      }
                   }
                }

             }
 
          } // end of if for flag 2
     } // end of if eth.destmac
      

       if(strcmp(eth.destmac, "ff:ff:ff:ff:ff:ff") == 0)
        {

           if(eth.flag == 2)
           {
               // printf("Station receiving a frame of type arp\n");


      if(eth.pyld.arpreq.type == 1)
      {
        //printf("Station receiving a frame of type arp request\n");

                for(int i=0;i<25;i++)
                {
                  if(strcmp(arpcacheip[i],eth.pyld.arpreq.srcip) == 0)
                  {
                      if(strcmp(arpcachemac[i],"NULL")==0)
                      {
                         strcpy(arpcachemac[i], eth.pyld.arpreq.srcmac);
                         break;

                          }
                      }
                   }

               

                 for(int f=0;f<g;f++)
                 {


                 if(strcmp(srciprec[f],eth.pyld.arpreq.destip) == 0)
                     {
                         char srcipq1[40];
                         char srcmacq2[40];
                         char destipq3[40];
                    
                        strcpy(srcipq1,eth.pyld.arpreq.srcip);
                        strcpy(srcmacq2,eth.pyld.arpreq.srcmac);
                        strcpy(destipq3,eth.pyld.arpreq.destip);

                         //printf("Ip address matched\n");
                           
                         eth.pyld.arpreq.type = 2;
                       
                       
                         strcpy(eth.destmac, eth.srcmac);    
                         strcpy(eth.srcmac, srcmacrec[f]);
                        
                         strcpy(eth.pyld.arpreq.srcmac, srcmacrec[f]);
                         strcpy(eth.pyld.arpreq.srcip, destipq3);
                         strcpy(eth.pyld.arpreq.destmac, srcmacq2);
                         strcpy(eth.pyld.arpreq.destip, srcipq1);


                         send(socrec[j2],(struct ether*)&eth, sizeof(struct ether), 0);
                         break;
                                
                           }
                     }

          }
        }
       }

        
      

           /* printf("Constructing ethernet frame\n");
            //printf("Message to send: %s\n",frame1.arpreq.c1);


             for(int i=0;i<9;i++)
              {
                 if(strcmp(arpcacheip[i],frame1.arpreq.destip) == 0)
                 {
                     strcpy(arpcachemac[i],frame1.arpreq.destmac);
                     break;
                    }
                }

   
            frame1.flag = 1;// for ethernet frame
            strcpy(frame1.eth.srcmac, ptr4);
            strcpy(frame1.eth.destmac, frame1.arpreq.destmac);
            strcpy(frame1.eth.c1, frame1.arpreq.c1);

             send(sockfd,(struct bigfrm*)&frame1, sizeof(struct bigfrm), 0);

             } // end of if    */
                    
         
          /*if(frame1.flag == 2)
          {
                for(int i=0;i<9;i++)
                {
                  if(strcmp(arpcacheip[i],frame1.arpreq.srcip) == 0)
                  {
                      if(strcmp(arpcachemac[i],"NULL")==0)
                      {
                         strcpy(arpcachemac[i], frame1.arpreq.srcmac);
                         break;

                          }
                      }
                   }

                  
                     if(strcmp(ptr2,frame1.arpreq.destip) == 0)
                     {
                         printf("Ip address matched\n");
                          frame1.flag = 3;// for arp response
                          strcpy(frame1.arpreq.destmac, ptr4);
                           send(sockfd,(struct bigfrm*)&frame1, sizeof(struct bigfrm), 0);
                                
                           }
                        
                     
               }// end of if*/


           }// end of if for rets>0 


       if(rets==0)
       {
         //close the socket
        printf("\n error: server died \n");

       close(socrec[j2]);
       socrec[j2] = 0;

      int filled = 0;

    for(int v1=0;v1<g;v1++)
    {
       if( socrec[v1] ==0)
       {
          filled++;
         }

     }

     if(g == filled)
     {
        findic = 1;

       }         

        break;

         }
        
     





     } // end of isset if

  }

 } // end of for loop


if(findic == 1)
 {
   break;


 }





     } // end of while




    }// end of big if

   
  if(strcmp(argv[1],"-route") == 0)
  {
    printf("THIS is a router\n");

    char* p2;
    
 
 char subnetrec[10][16];
 char netprefix[10][16];
 char nxthoprec[10][16];
 char rtifacerec[10][40];
 char lanrec[10][10];


 

 int socrec[10];
 char srcmacrec[10][40];
 char srciprec[10][40];
 char ifacerec[10][40]; 

 char riface[40];
 
 char str6[100];

 for(int i=0;i<10;i++)
 {
    strcpy(lanrec[i],"NULL");
    strcpy(srcmacrec[i],"NULL");
    strcpy(srciprec[i],"NULL");
    strcpy(ifacerec[i],"NULL");
    socrec[i] = 0;
 
    

    }

 for(int i=0;i<10;i++)
 {

    strcpy(subnetrec[i],"NULL");
    strcpy(netprefix[i],"NULL");
    strcpy(nxthoprec[i],"NULL");
    strcpy(rtifacerec[i],"NULL");
   }

 FILE * fp6 = fopen(argv[3], "r"); // rtable file
  int rcounter = 0;
   while(fgets (str6, sizeof(str6), fp6)!=NULL)
   {

         if(strspn(str6, " \r\n\t") == strlen(str6))
        {
            break;
           }


    //printf("%s\n", str6);  
    char* ptr1 = strtok(str6, " "); // gives the network prefix
    strcpy(netprefix[rcounter],ptr1);
    //printf("Network prefix is %s\n",netprefix[rcounter]);
    char* ptr2 = strtok(NULL, " "); // gives the next hop
    strcpy(nxthoprec[rcounter],ptr2);
    //printf("Next hop station is %s\n",nxthoprec[rcounter]);
    char* ptr3 = strtok(NULL, " "); // gives the subnet
    strcpy(subnetrec[rcounter],ptr3);
    //printf("Subnet is %s\n",subnetrec[rcounter]);
    char* ptr4 = strtok(NULL, " \n");  // gives the interface name
    strcpy(rtifacerec[rcounter],ptr4);
   // printf("Interface is %s\n",rtifacerec[rcounter]);

    memset(str6, 0, sizeof(str6));
    rcounter++;

    }

   
   struct arprequest{
 
       
       char srcmac[40];
       char srcip[40];
       char destmac[40];
       char destip[40];
       int type;

     };



  struct ippack{

   char srcip[40];
   char destip[40];
   char c1[256];
   };

 struct pyload{

   struct ippack ipp;
   struct arprequest arpreq;
   };


 struct ippack tempque[5]; 

 for(int x=0;x<5;x++)
 {
  struct ippack temp1;

  strcpy(temp1.srcip,"NULL");
  strcpy(temp1.destip,"NULL");
  strcpy(temp1.c1,"NULL");
  
  tempque[x] = temp1;

   }






   char server_response[256];

   struct ether{
 
   int flag;
   char srcmac[40];
   char destmac[40];
   struct pyload pyld;


   };

 

  struct ether eth;

  FILE * fp5 = fopen(argv[4], "r");
   char str5[100];
   char arpcacheip[25][40];
   char arpcachemac[25][40];

 for(int i=0;i<25;i++)
 {

    strcpy(arpcacheip[i],"NULL");
    strcpy(arpcachemac[i],"NULL");
   }

    int ik=0;
  

  
   while(fgets ( str5, sizeof(str5), fp5)!=NULL)
   {

        if(strspn(str5, " \r\n\t") == strlen(str5))
        {
            break;
           }


    
     char* ptr13 = strtok(str5, " \t");// gives the station name 
     char* ptr14 = strtok(NULL, " \n"); // gives the ip address of station
     //char* ptr15 = strtok(NULL, " \n"); // gives the mac address of station


    
     strcpy(arpcacheip[ik],ptr14);
     strcpy(arpcachemac[ik],"NULL");
     ik++;

    }

  /*printf("Printing arp cache ip addresses:\n");


  for(int i=0;i<25;i++)
  {

    printf("Address is %s\n",arpcacheip[i]);
    }*/




  const char* ptr7; // Bridge address
  const char* ptr9; // Bridge port
  int sockfd, n;
  struct addrinfo hints, *res;
    char* ptr1;
    char* ptr2;
    char* ptr3;
    char* ptr4;
    char* xyz;
    char str1[100];
    char str2[100];
    char str3[100];
   FILE * fp1 = fopen(argv[2], "r"); // interface file

  int g=0;

  int findic = 0;

 while( fgets (str1, sizeof(str1), fp1) != NULL)
 {
     if(strspn(str1, " \r\n\t") == strlen(str1))
        {
            break;
           }
         


  //printf("Creating the socket\n");
	
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family=AF_UNSPEC;
  hints.ai_socktype=SOCK_STREAM;
  hints.ai_protocol=IPPROTO_TCP;

   // fgets (str1, sizeof(str1), fp1);
   // printf("%s\n", str1);   
    ptr1 = strtok(str1, " ");
    ptr2 = strtok(NULL, " "); // gives the source ip address
    ptr3 = strtok(NULL, " ");
    ptr4 = strtok(NULL, " "); // gives the source mac address
    const char* a = strtok(NULL, " \n");  // gives the lan name
   xyz ="hello";
    
   
    
    
    //printf("%s\n", ptr1);     // print what we got
    //printf("%s\n", ptr2);
   // printf("Source mac address is %s\n", ptr4); 
    

  
   FILE * fp3 = fopen("lanaddr.txt", "r");
   FILE * fp4 = fopen("lanport.txt", "r");

  while( fgets ( str2, sizeof(str2), fp3) != NULL)
     {

    //printf("%s\n", str2); 
    const char* b = strtok(str2, ".");// gives the lan name
    ptr7 = strtok(NULL, " \n"); // gives the ip address
   // printf("%s\n", b);     // print what we got
    //printf("%s\n", ptr7);
  //printf("LAN name is %s\n", b);


   if(strcmp(a,b) == 0)
   {
      //printf("Equal lan names\n");
       
         break;

      }

   memset(str2, 0, sizeof(str2));
    
        
    }


while( fgets ( str3, sizeof(str3), fp4) != NULL)
     {

   // printf("%s\n", str3);   
    char* ptr8 = strtok(str3, "."); // gives the lan name
    ptr9 = strtok(NULL, " \n"); //  gives the port number
   // printf("%s\n", ptr8);     // print what we got
   // printf("%s\n", ptr9);
 


   if(strcmp(ptr8, a) == 0)
   {

      //printf("Equal lan names\n");
     
         break;

      }

   memset(str3, 0, sizeof(str3));
    
        
    }

   //memset(str1, 0, sizeof(str1));
   //printf("Value of g is %d\n",g);
   //printf(" Value of ptr7 is %s\n",ptr7);
  //printf("Value of ptr9 is %s\n",ptr9);
 //printf("Value of ptr1 is %s\n",ptr1);
 //printf("Value of a is %s\n",a);
 //printf("Value of xyz is %s\n",xyz);
//printf("MAC Address is %s\n",ptr4);

if((n=getaddrinfo(ptr7, ptr9, &hints, &res))!=0)

    printf("getaddrinfo error for %s, %s; %s", ptr7,ptr9, gai_strerror(n));

  //ressave=res;

  do{
   sockfd=socket(res->ai_family, res->ai_socktype, res->ai_protocol);
   
 
   if(sockfd<0)
     continue;  //ignore this returned Ip addr



  

   if(connect(sockfd, res->ai_addr, res->ai_addrlen)==0)

    { 

      //printf("connection ok!\n"); /* success*/


     int rets = recv(sockfd, &server_response, sizeof(server_response), 0);

     //printf("\n>>> %s\n",server_response);

      if(strcmp(server_response,"reject") == 0)
      {

        printf("Connection rejected\n");
        close(sockfd);
        exit(1);

	
        //break;

        }









      socrec[g] = sockfd;
      strcpy(srcmacrec[g],ptr4); 
      //printf("MAC Address is %s\n",srcmacrec[g]);
      strcpy(srciprec[g],ptr2); 
      //printf("IP Address  is %s\n",srciprec[g]);

      strcpy(lanrec[g],a);
      strcpy(ifacerec[g],ptr1);

     //printf("LAN name is%s\n", lanrec[g]);
     //printf("Interface is%s\n", ifacerec[g]);




      //int pq = send(sockfd, (struct message*)&msg, sizeof(struct message), 0);

      struct sockaddr_storage my_addr;
      socklen_t len = sizeof(my_addr);
     if (getsockname(sockfd, (struct sockaddr *)&my_addr, &len) == -1)
     perror("getsockname");
     else
     {
      //printf("port number %d\n", ntohs(server_address.sin_port));

       char serv[256];
       char host[256];

    if (getnameinfo((const struct sockaddr *) &my_addr, len,host,sizeof(host),
                    serv, sizeof(serv), 0) == 0)
    {
        printf("admin: connected to server on '%s' at '%s' thru '%s'\n",ptr7,ptr9, serv);
    }


         }








      break;
    }
   else  {
     perror("connecting stream socket");
   }


   
  } while ((res=res->ai_next)!= NULL);




 g++;




   }

 


	//receive data from the server

   

    char client_response[256];

int max;
 
 max =0;
int ret;

int fd=0;



fd_set readset;

 while(1)
 {
     FD_ZERO(&readset);
     FD_SET(fd,&readset);

   
   
    for(int j1=0;j1<10;j1++)
    {
         
       if(socrec[j1]>0)
       {

         FD_SET(socrec[j1],&readset);

         if(socrec[j1]>max)
         {
             max = socrec[j1];

          }   // end of inner if
        }     //end of outer if

      }       // end of for loop


     

    memset((void*)client_response,0,256);

    select(max+1,&readset,NULL,NULL,NULL);



if(FD_ISSET(fd,&readset))
   {

    int retr = read(fd,(void*)client_response,255);


   if(strcmp(strtok(client_response, "\n"), "host") == 0)
      { 


           FILE * fhost = fopen(argv[4], "r"); // hosts file 

                char fh1[100];
             
               while( fgets ( fh1, sizeof(fh1), fhost) != NULL)
              {

                        printf("%s\n", fh1);
                 }

        } 






   if(strcmp(strtok(client_response, "\n"), "ift") == 0)
    { 


    FILE * fi = fopen(argv[2], "r"); // interface file
    char fti[100];
  
         while(fgets (fti, sizeof(fti), fi)!=NULL)
         {
               printf("%s\n", fti);     

            } 
    
     }


    if(strcmp(strtok(client_response, "\n"), "rout") == 0)
    { 

          // printf("condition satisfied\n");

           FILE * fr = fopen(argv[3], "r"); // rtable file
           char rst[100];
  
          while(fgets (rst, sizeof(rst), fr)!=NULL)
         {
               printf("%s\n", rst);      

            }

      }
    
   
    
   if(strcmp(strtok(client_response, "\n"), "ach") == 0)
   { 
      //printf("condition satisfied\n");
      int arpfound = 0;

   for(int i=0;i<25;i++)
   {
     
     if(strcmp(arpcachemac[i],"NULL")!=0)
     {
          arpfound = 1;
          printf("%s",arpcacheip[i]);
          printf("  %s\n",arpcachemac[i]);

      }

    }
  
  if(arpfound == 0)
  {
      printf("Arp cache is empty\n");
    }


  }


}



 for(int j2=0;j2<10;j2++)
{
  if(socrec[j2]>0)
  {

     if(FD_ISSET(socrec[j2],&readset))
     {



       int rets = recv(socrec[j2],(struct ether*)&eth, sizeof(struct ether), 0);
         //int rets = recv(socrec[j2],&server_response, sizeof(server_response), 0);

        if(rets>0)
        {  int netflag = 0;
           //printf("frame received\n");
          
          //printf("Flag is %d\n",eth.flag);

         
           
             int mfound = 0;
             

                    for(int f=0;f<g;f++)
                    {
                  
                       if(strcmp(srcmacrec[f],eth.destmac) == 0)
                       {
                          mfound = 1;
                          //printf("Mac address matched\n");
                         }
                      }
                          

               if(mfound == 1)
              {  
                 if(eth.flag == 1)
                 {
                
                // printf("Frame accepted\n");
                // printf("Router processing of ethernet frame begins\n");
                 //printf("\n>>> %s\n",eth.pyld.ipp.c1);
                // printf("Destination ip address is %s\n",eth.pyld.ipp.destip);

                  char z1[40];
                  char iprouter[16];
            
            strcpy(z1,eth.pyld.ipp.destip);
            //printf("Destination ip address is %s\n",z1);

       for(int k=0;k<10;k++)
       {

        if(strcmp(subnetrec[k],"NULL")!=0)
        {
           char t1[16];
           char t2[16];
           char t3[40];

          strcpy(t1,subnetrec[k]);
          strcpy(t2,netprefix[k]);
          strcpy(t3,z1);
          unsigned long int n1=conv(t3);
          //printf("Before subnet is %s\n",t1);
          unsigned long int n2=conv(t1);
          //printf("After subnet is %s\n",subnetrec[k]);
          //printf(" Before Net prefix is %s\n",t2);
          unsigned long int n3=conv(t2);
          //printf(" After Net prefix is %s\n",netprefix[k]);
            
          unsigned long int n4 = n1&n2;

          if(n3 == n4)
          {
            strcpy(riface,rtifacerec[k]);

            //printf("Next hop router found\n");
           // printf("Net prefix is %s\n",netprefix[k]);
            //printf("Next hop station is %s\n",nxthoprec[k]);
           // printf("Interface through which routing to occur is %s\n",rtifacerec[k]);
           
              if(strcmp(nxthoprec[k],"0.0.0.0") == 0)
              {
                 //printf("packet is to be routed in the same network\n");
                 //frame1.rout = 0;
                  }

               else
               {
                 netflag = 1;
                 //frame1.rout = 1;
                 //printf("packet is to be routed to a different network\n");
                 strcpy(iprouter,nxthoprec[k]);
                 //printf("IP address of router is %s\n",iprouter);
                 }


            break;
            }
         }
      }


    if(netflag == 0)
    {
        //printf("Starting the arp thing for a packet to be routed in the same network\n");


     // printf("Checking ip and mac address in arp cache\n");

      for(int i=0;i<25;i++)
      {
         if(strcmp(arpcacheip[i],z1) == 0)
         {
           if(strcmp(arpcachemac[i],"NULL")!=0)
            {
               //printf("ARP cache mac address found\n");
              // printf("Address is %s\n",arpcachemac[i]);
               
              eth.flag = 1;// for ip packet

            for(int f=0;f<g;f++)
            {     
               if(strcmp(riface,ifacerec[f]) == 0)
               { 
                   strcpy(eth.srcmac, srcmacrec[f]);
                   strcpy(eth.destmac, arpcachemac[i]);
               
                   send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
                  
                   break;
                 }

              }
              
              //strcpy(frame1.eth.c1, p2);
            //printf("Ip address is %s\n",ptr11);
            //printf("Mac address is %s\n",ptr12);
             break;
               }

            else
            {

               //printf("ARP cache mac address not found\n");


               eth.flag = 2; // for arprequest frame
               for(int f=0;f<g;f++)
               {     
                    if(strcmp(riface,ifacerec[f]) == 0)
                    {
                         eth.pyld.arpreq.type = 1;
                         strcpy(eth.srcmac, srcmacrec[f]);
                         strcpy(eth.destmac, "ff:ff:ff:ff:ff:ff");
                         strcpy(eth.pyld.arpreq.srcmac,srcmacrec[f]);
                         strcpy(eth.pyld.arpreq.srcip, srciprec[f]);
                         strcpy(eth.pyld.arpreq.destmac, "00:00:00:00:00:00");
                         strcpy(eth.pyld.arpreq.destip, z1);
 
                         struct ippack temp;
     
                         strcpy(temp.srcip,eth.pyld.ipp.srcip);
                         strcpy(temp.destip,eth.pyld.ipp.destip);
                         strcpy(temp.c1,eth.pyld.ipp.c1);

                         strcpy(eth.pyld.ipp.srcip,"NULL");
                         strcpy(eth.pyld.ipp.destip,"NULL");
                         strcpy(eth.pyld.ipp.c1,"NULL");
                          
                         
                         for(int d=0;d<5;d++)              
                         {
                             if(strcmp(tempque[d].srcip,"NULL") ==0)
                             {
                                      tempque[d] = temp;
                                      break;
                                  }
                           }
                


                         send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
                        
                         //strcpy(frame1.arpreq.c1, p2);
                         break;
                        }
                  }
               break;

               }// end of else

             } // end of first if after for loop

           } // end of for loop

         } // end of if for netflag

       if(netflag == 1)
    {
        //printf("Starting the arp thing for a packet to be routed to a different network\n");


     // printf("Checking ip and mac address of router in arp cache\n");

      for(int i=0;i<25;i++)
      {
         if(strcmp(arpcacheip[i],iprouter) == 0)
         {
           if(strcmp(arpcachemac[i],"NULL")!=0)
            {
               //printf("ARP cache mac address found\n");
              // printf("Address is %s\n",arpcachemac[i]);
               
              eth.flag = 1;// for ip packet
             for(int f=0;f<g;f++)
            {     
               if(strcmp(riface,ifacerec[f]) == 0)
               { 
                   strcpy(eth.srcmac, srcmacrec[f]);
                   strcpy(eth.destmac, arpcachemac[i]);
                   send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
                   break;
                  }
              }
              //strcpy(frame1.eth.c1, p2);
            //printf("Ip address is %s\n",ptr11);
            //printf("Mac address is %s\n",ptr12);
             break;
               }

            else
            {

              // printf("ARP cache mac address not found\n");


               eth.flag = 2; // for arprequest frame
               eth.pyld.arpreq.type = 1;
               for(int f=0;f<g;f++)
               {     
                 if(strcmp(riface,ifacerec[f]) == 0)
                 {   
                     strcpy(eth.srcmac, srcmacrec[f]);
                     strcpy(eth.destmac, "ff:ff:ff:ff:ff:ff");
                     strcpy(eth.pyld.arpreq.srcmac, srcmacrec[f]);
                     strcpy(eth.pyld.arpreq.srcip, srciprec[f]);
                     strcpy(eth.pyld.arpreq.destmac, "00:00:00:00:00:00");
                     strcpy(eth.pyld.arpreq.destip, iprouter);


                         struct ippack temp;
     
                         strcpy(temp.srcip,eth.pyld.ipp.srcip);
                         strcpy(temp.destip,eth.pyld.ipp.destip);
                         strcpy(temp.c1,eth.pyld.ipp.c1);

                         strcpy(eth.pyld.ipp.srcip,"NULL");
                         strcpy(eth.pyld.ipp.destip,"NULL");
                         strcpy(eth.pyld.ipp.c1,"NULL");
                          
                       
                         for(int d=0;d<5;d++)              
                         {
                             if(strcmp(tempque[d].srcip,"NULL") ==0)
                             {
                                      tempque[d] = temp;
                                      break;
                                  }
                           }
                
    


                     send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);
                     //strcpy(frame1.arpreq.c1, p2);
                     break;
                   }
                 }

               break;

               

               }// end of else

             } // end of first if after for loop

           } // end of for loop

         } // end of if for netflag

        







        } // end of if for flag 1



            
             
      

           if(eth.flag == 2)
           {
             //printf("Router receiving a frame of type arp\n");
             
             
              if(eth.pyld.arpreq.type == 2)
              {
                  //printf("Router receiving a frame of type arp response\n");

                   for(int i=0;i<25;i++)
                   {
                       if(strcmp(arpcacheip[i],eth.pyld.arpreq.srcip) == 0)
                       {
                            strcpy(arpcachemac[i],eth.pyld.arpreq.srcmac);
                            break;
                         }
                     }

                     //printf("Constructing a frame of type ip\n");

                     int rfound = 0;
                    eth.flag = 1; // for ip packet


                      for(int e=0;e<10;e++)
                      {
                         if(strcmp(nxthoprec[e],eth.pyld.arpreq.srcip) == 0)
                         {
                              rfound = 1;
                              for(int d=0;d<5;d++)              
                              {
                                 if(strcmp(tempque[d].srcip,"NULL") !=0)
                                 {
                                       if(strcmp(subnetrec[e],"NULL")!=0)
                                      {
                                              char t1[16];
                                              char t2[16];
                                              char t3[16];

                                         strcpy(t1,subnetrec[e]);
                                         strcpy(t2,netprefix[e]);
                                         strcpy(t3,tempque[d].destip);
                                         unsigned long int n1=conv(t3);
                                         //printf("Before subnet is %s\n",t1);
                                         unsigned long int n2=conv(t1);
                                        // printf("After subnet is %s\n",subnetrec[e]);
                                        // printf(" Before Net prefix is %s\n",t2);
                                         unsigned long int n3=conv(t2);
                                        //printf(" After Net prefix is %s\n",netprefix[e]);
            
                                         unsigned long int n4 = n1&n2;
                                         
                                        if(n3 == n4)
                                        {
                                            //strcpy(riface,rtifacerec[e]);

                                          strcpy(eth.srcmac, eth.pyld.arpreq.destmac);
                                          strcpy(eth.destmac, eth.pyld.arpreq.srcmac);
                                          strcpy(eth.pyld.ipp.srcip, tempque[d].srcip);
                                          strcpy(eth.pyld.ipp.destip, tempque[d].destip);
                                          strcpy(eth.pyld.ipp.c1, tempque[d].c1);

                                          //printf("Construction of ip packet completed\n");
                                          for(int f=0;f<g;f++)
                                          {
                                               if(socrec[f] == socrec[j2])
                                               {
          
                                                   strcpy(eth.srcmac, srcmacrec[f]);
                                                   send(socrec[f],(struct ether*)&eth, sizeof(struct ether), 0);

                                                  // printf("Ip packet sent\n");
                                                   strcpy(tempque[d].srcip,"NULL");
                                                   strcpy(tempque[d].destip,"NULL");
                                                   strcpy(tempque[d].c1,"NULL");
                                                   break;
                                                  }
                                             }



                                          
                                          }



                                }
                                     
                   

                     }

                    }
                  break;
                   }

                }



              if(rfound == 0)
              {
              for(int d=0;d<5;d++)              
              {
                 if(strcmp(tempque[d].srcip,"NULL") !=0)
                  {
                    if(strcmp(tempque[d].destip,eth.pyld.arpreq.srcip) == 0)
                     {
                                strcpy(eth.srcmac, eth.pyld.arpreq.destmac);
                                strcpy(eth.destmac, eth.pyld.arpreq.srcmac);
                                strcpy(eth.pyld.ipp.srcip, tempque[d].srcip);
                                strcpy(eth.pyld.ipp.destip, tempque[d].destip);
                                strcpy(eth.pyld.ipp.c1, tempque[d].c1);

                                //printf("Construction of ip packet completed\n");
                                 for(int f=0;f<g;f++)
                                 {
                                    if(socrec[f] == socrec[j2])
                                     {
          
                                           strcpy(eth.srcmac, srcmacrec[f]);
                                           send(socrec[j2],(struct ether*)&eth, sizeof(struct ether), 0);

                                           // printf("Ip packet sent\n");
                                            strcpy(tempque[d].srcip,"NULL");
                                            strcpy(tempque[d].destip,"NULL");
                                            strcpy(tempque[d].c1,"NULL");
                                            break;
                                          }
                                     }
                               
                         }
                      }
                   }
                }

             }

           } // end of if for flag2

      } // end of if for mfound == 1 
     


          if(strcmp(eth.destmac,"ff:ff:ff:ff:ff:ff") ==0)
          {
            if(eth.flag == 2)
            {

              // printf("Router receiving a frame of type arp \n");

             if(eth.pyld.arpreq.type == 1)
             {
                 //printf("Router receiving a frame of type arp request\n");

               
               /*printf("Dest ip address is %s\n",eth.pyld.arpreq.destip);
               printf("Ip addresses of router are:\n");
              for(int v=0;v<g;v++)
             { 
                printf("Address %d is %s\n",v,srciprec[v]);
                printf("sockfd %d is %d\n",v,socrec[v]);
                printf("MAc Address %d is %s\n",v,srcmacrec[v]);
               }*/


                for(int i=0;i<25;i++)
                {
                  if(strcmp(arpcacheip[i],eth.pyld.arpreq.srcip) == 0)
                  {
                      if(strcmp(arpcachemac[i],"NULL")==0)
                      {
                         strcpy(arpcachemac[i], eth.pyld.arpreq.srcmac);

                         break;

                          }
                      }
                   }

                    for(int f=0;f<g;f++)
                    {
                  
                       if(strcmp(srciprec[f],eth.pyld.arpreq.destip) == 0)
                       {

                           char srcipq1[40];
                           char srcmacq2[40];
                           char destipq3[40];
                    
                        strcpy(srcipq1,eth.pyld.arpreq.srcip);
                        strcpy(srcmacq2,eth.pyld.arpreq.srcmac);
                        strcpy(destipq3,eth.pyld.arpreq.destip);




                         // printf("Ip address matched\n");
                       
                          eth.pyld.arpreq.type = 2;
 
                         strcpy(eth.destmac, eth.srcmac);    
                         strcpy(eth.srcmac, srcmacrec[f]);

                         strcpy(eth.pyld.arpreq.srcmac, srcmacrec[f]);
                         strcpy(eth.pyld.arpreq.srcip, destipq3);
                         strcpy(eth.pyld.arpreq.destmac, srcmacq2);
                         strcpy(eth.pyld.arpreq.destip, srcipq1);


                         
                          send(socrec[j2],(struct ether*)&eth, sizeof(struct ether), 0);
                        
                          break;      
                           }

                       }
                   }
               }     
                     
               }// end of if


       























            /*printf("Constructing ethernet frame\n");
            //printf("Message to send: %s\n",frame1.arpreq.c1);


             for(int i=0;i<9;i++)
              {
                 if(strcmp(arpcacheip[i],frame1.arpreq.destip) == 0)
                 {
                     strcpy(arpcachemac[i],frame1.arpreq.destmac);
                     break;
                    }
                }

   
            frame1.flag = 1;// for ethernet frame
           for(int f=0;f<2;f++)
           {
              if(socrec[f] == socrec[j2])
              {
          
                    strcpy(frame1.eth.srcmac, srcmacrec[f]);
                    strcpy(frame1.eth.destmac, frame1.arpreq.destmac);
                    strcpy(frame1.eth.c1, frame1.arpreq.c1);
                   send(socrec[j2],(struct bigfrm*)&frame1, sizeof(struct bigfrm), 0);
                    break;
                  }
             }

             } // end of if    
                    
         
          if(frame1.flag == 2)
          {
               printf("Router enters the flag 2 condition\n");
               printf("Dest ip address is %s\n",frame1.arpreq.destip);
               printf("Ip addresses of router are:\n");
              for(int v=0;v<2;v++)
             { 
                printf("Address %d is %s\n",v,srciprec[v]);
                printf("sockfd %d is %d\n",v,socrec[v]);
                printf("MAc Address %d is %s\n",v,srcmacrec[v]);
               }


                for(int i=0;i<9;i++)
                {
                  if(strcmp(arpcacheip[i],frame1.arpreq.srcip) == 0)
                  {
                      if(strcmp(arpcachemac[i],"NULL")==0)
                      {
                         strcpy(arpcachemac[i], frame1.arpreq.srcmac);
                         break;

                          }
                      }
                   }

                    for(int f=0;f<2;f++)
                    {
                  
                       if(strcmp(srciprec[f],frame1.arpreq.destip) == 0)
                       {
                          printf("Ip address matched\n");
                          frame1.flag = 3;// for arp response
                          strcpy(frame1.arpreq.destmac, srcmacrec[f]);
                          send(socrec[j2],(struct bigfrm*)&frame1, sizeof(struct bigfrm), 0);
                          printf("Packet sent to same bridge\n");
                          break;      
                           }

                       }
                        
                     
               }// end of if */


           }// end of if for rets>0 


       if(rets==0)
       {
         //close the socket
        printf("\n error: server died \n");

	close(socrec[j2]);
        socrec[j2] = 0;


        int filled = 0;

    for(int v1=0;v1<g;v1++)
    {
       if( socrec[v1] ==0)
       {
          filled++;
         }

     }

    if(g == filled)
    {
        findic = 1;

    }






        break;

         }
        
     





     } // end of isset if

   } 

 } // end of for loop


 if(findic == 1)
 {
   break;


 }

     } // end of while












      } // end of big else















 

	return 0;
}



unsigned long int conv(char ipadr[])
{
 unsigned long int num=0,val;
 char *tok,*ptr;
 tok=strtok(ipadr,".");
 while( tok != NULL)
 {
  val=strtoul(tok,&ptr,0);
  num=(num << 8) + val;
  tok=strtok(NULL,".");
 }
 return(num);
}




