/*

Course: CNT 5505 Data and Computer Communications

Semester: Spring 2016

Name: Jatin Singh Saluja


*/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/times.h>
#include <time.h>
#include <pthread.h>

char addr[5][40];
int switchsock[5];
pthread_t id[5];

void *worker(void *i)
 {
    int a = *((int *) i);
    
     sleep(60);
  
   if((strcmp(addr[a],"NULL")!=0) && (switchsock[a]>0))
   {
    printf("\nEntry in self learning table timed out:\n");

    printf("MAC address: %s",addr[a]);

    printf("                      Sockfd: %d\n",switchsock[a]);
     }

        strcpy(addr[a],"NULL");
        switchsock[a] = 0;
        
        free(i);
   

   return(NULL);     /* Thread exits (dies) */
 }





int main(int argc, char* argv[]) {


 pthread_t  tid;






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


    struct ether{
 
   int flag;
   char srcmac[40];
   char destmac[40];
   struct pyload pyld;


   };

   struct ether eth;
  
    char checkstr[50];
    FILE * fp = fopen("lanaddr.txt", "a+");

   fseek(fp, 0, SEEK_END);
   size_t size = ftell(fp);

   //printf("File size is: %d\n", size);

   
   
   if(size!=0)
   {

       FILE * fp1 = fopen("lanaddr.txt", "r");
       //printf("File processing Starts\n");


   while( fgets ( checkstr, sizeof(checkstr), fp1 ) != NULL  )
   {

    
    //printf("%s", checkstr);      
   

    const char* val1 = strtok(checkstr, ".");

    if (strcmp(argv[1], val1) == 0) 
    {
       fprintf(stderr, "LAN name already exists. Try again\n");
       exit(1);

        }

    memset(checkstr, 0, sizeof(checkstr));

    } 
    fclose(fp1);
   // printf("File processing is completed\n");

     }

 
     
    fclose(fp);
   
  int num_ports = atoi(argv[2]);


   char* switchtable[5][2];
  //char addr[5][40];
  //int switchsock[5];
  int addrcounter = 0;

   for(int i1=0;i1<5;i1++)
   {
     strcpy(addr[i1],"NULL");

     }

  for(int i1=0;i1<5;i1++)
   {
     switchsock[i1] =0;

     }




   

   char server_message1[256] = "accept";

   char server_message2[256] = "reject";


   char console_message[256];

   char hostname[256];
   
	


	
     int server_socket;
    struct addrinfo hints; 

   struct addrinfo *servinfo;

   struct addrinfo *p;
   struct sockaddr_storage ca; // connector's address information
    
    
    int rv;

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    hints.ai_protocol=IPPROTO_TCP;

    if ((rv = getaddrinfo(NULL, "0", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((server_socket = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (bind(server_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(server_socket);
            perror("server: bind");
            continue;
        }

        break;
    }




         listen(server_socket, 5);



        gethostname(hostname, sizeof(hostname));
        //printf("My hostname: %s\n", hostname);

       struct sockaddr_storage my_addr;
     socklen_t len = sizeof(my_addr);
     if (getsockname(server_socket, (struct sockaddr *)&my_addr, &len) == -1)
     perror("getsockname");
     else
     {
      //printf("port number %d\n", ntohs(server_address.sin_port));

       char serv[256];
       char host[256];

    if (getnameinfo((const struct sockaddr *) &my_addr, len,host,sizeof(host),
                    serv, sizeof(serv), 0) == 0)
    {
                 FILE *fp2;

                 fp2 = fopen("lanaddr.txt", "a+");

                FILE *fp3 = fopen("lanport.txt", "a+");

                if (fp2 == NULL)
                {
                    printf("Error opening file!\n");
                    exit(1);
                          }

               if (fp3 == NULL)
                {
                    printf("Error opening file!\n");
                    exit(1);
                          }


                 fprintf(fp2, ".%s.%s\n", argv[1],hostname);
                 fclose(fp2);

                 fprintf(fp3, ".%s.%s\n", argv[1],serv);
                 fclose(fp3);

                 printf("admin: started server on '%s' at '%s'\n",hostname, serv);
    }


         }

//client_socket = accept(server_socket, (struct sockaddr *)&ca, &calen);
// send the message
//send(client_socket, server_message, sizeof(server_message), 0);

int client_socket;
socklen_t calen;
char client_message[256];

int clients[10];
int max;
int ret;

for(int i=0;i<10;i++)
{
    clients[i] = 0;
    }

fd_set readset;
struct sockaddr_storage cl_addr1;
socklen_t len2 = sizeof(cl_addr1);
struct sockaddr_storage cl_addr2;
socklen_t len3 = sizeof(cl_addr2);
      
     

int cfd = 0;

while(1)
{
    FD_ZERO(&readset);

    FD_SET(cfd,&readset);

    FD_SET(server_socket,&readset);
    max = server_socket;



    for(int j=0;j<10;j++)
    {
         
       if(clients[j]>0)
       {

         FD_SET(clients[j],&readset);

         if(clients[j]>max)
         {
             max = clients[j];

          }   // end of inner if
        }     //end of outer if

      }       // end of for loop



select(max+1,&readset,NULL,NULL,NULL);


if(FD_ISSET(cfd,&readset))
   {

    int cst = read(cfd,(void*)console_message,255);

   if(strcmp(strtok(console_message, "\n"), "swt") == 0)
    { 
       int swfound = 0;

          for(int k=0;k<5;k++)
          {
            if(switchsock[k] !=0)
             {
               swfound = 1;
               printf("%s",addr[k]);
               printf("  %d\n",switchsock[k]);
               
              
                }

            }
       
       if(swfound == 0)
      {
         printf("Switch table is empty\n");
      }




     }



} // end of cfd isset

if(FD_ISSET(server_socket,&readset))
{
  
      
client_socket = accept(server_socket, (struct sockaddr *)&ca, &calen);

// send message to newly connected client



if (getpeername(client_socket, (struct sockaddr *)&cl_addr2, &len3) == -1)
               perror("getpeername");
               else
              {
                char serv3[256];
                char host3[256];

                  if (getnameinfo((const struct sockaddr *) &cl_addr2, len3,host3,sizeof(host3),
                    serv3, sizeof(serv3), 0) == 0)

    {          if(num_ports>0)
               {
               printf("admin: connect from '%s' at '%s'\n",host3,serv3);
               send(client_socket, server_message1, sizeof(server_message1), 0);
               num_ports = num_ports - 1;

               }

              else
             {     
               
               printf("No of ports is less than zero\n");
               send(client_socket, server_message2, sizeof(server_message2), 0);
               //printf("rejection sent\n");
               
               }
               

         
  
     
       
    }


         }


//send(client_socket, server_message, sizeof(server_message), 0);



   for(int k=0;k<10;k++)
   {
     if(clients[k]==0)
     {
       clients[k] = client_socket;
       break; 
     
         } // end of if
    } // end of for loop

 




 }  // end of if





for(int m=0;m<10;m++)
{
  if(clients[m]>0)
  {

     if(FD_ISSET(clients[m],&readset))
     {
       

       memset((void*)client_message,0,sizeof(client_message));

        int ret = recv(clients[m],(struct ether*)&eth,sizeof(struct ether),0);

        //int ret = recv(clients[m],client_message,sizeof(client_message),0);

     

         

          if(ret>0)
          { //printf("Frame received\n");
            //printf("Flag is %d \n",eth.flag);
            
                if(strcmp(eth.destmac,"ff:ff:ff:ff:ff:ff") ==0)
                {
                     //printf("Source mac address is %s\n",eth.pyld.arpreq.srcmac);
                     //printf("DEST mac address is %s\n",eth.pyld.arpreq.destmac);
               
                             int flagsrcmac = 0;
    //printf("Entering to find source mac address in switchtable\n");
     for(int i=0;i<5;i++)
      {

          if(strcmp(addr[i],eth.srcmac) == 0)
          {
            int *arg2 = malloc(sizeof(*arg2));
            *arg2 = i; 


            // printf("Source mac addres found in switch table\n");
            // printf("Source mac address is %s\n",addr[i]);
             flagsrcmac = 1;

             pthread_create(&id[i],0, worker, arg2);
             //printf("Timer updated\n");


             break;
             }

        }

if(flagsrcmac ==0)

    {

      //printf("Source mac addres not found in switch table\n");

      
      for(int k=0;k<5;k++)
      {
           int *arg1 = malloc(sizeof(*arg1));
           *arg1 = k;

            if(switchsock[k] ==0)
             {
               strcpy(addr[k],eth.srcmac);
               switchsock[k] = clients[m];

               pthread_create(&tid, 0, worker, arg1);
               id[k] = pthread_self();
               

               break;
                }

     }
   }


           

                    for(int x1=0;x1<10;x1++)
                    { 

                    if(clients[x1]>0 && clients[x1]!=clients[m])
                    {
                        send(clients[x1], (struct ether*)&eth, sizeof(struct ether), 0);

                         } // end of if

                   } // end of for 



               }


             



         /* if(frame1.flag == 2)
          {
              frame1.arpreq.sockfd = clients[m];

                for(int x1=0;x1<10;x1++)
                { 

                    if(clients[x1]>0 && clients[x1]!=clients[m])
                    {
                        send(clients[x1], (struct bigfrm*)&frame1, sizeof(struct bigfrm), 0);

                         } // end of if

                   } // end of for 

            } // end of if */







               if(strcmp(eth.destmac,"ff:ff:ff:ff:ff:ff") !=0)
              {


               strcpy(client_message, eth.pyld.ipp.c1);
               


               if (getpeername(clients[m], (struct sockaddr *)&cl_addr1, &len2) == -1)
               perror("getpeername");
               else
              {
                char serv2[256];
                char host2[256];

                  if (getnameinfo((const struct sockaddr *) &cl_addr1, len2,host2,sizeof(host2),
                    serv2, sizeof(serv2), 0) == 0)

    {   
        
     //printf("%s(%s): %s\n",host2,serv2,client_message);
     


for(int k=0;k<5;k++)
  {
    //printf("Address %d is %s\n",k,addr[k]);


     }

   int flagsrcmac = 0;
    //printf("Entering to find source mac address in switchtable\n");
     for(int i=0;i<5;i++)
      {

          if(strcmp(addr[i],eth.srcmac) == 0)
          {

              int *arg3 = malloc(sizeof(*arg3));
              *arg3 = i;


             //printf("Source mac addres found in switch table\n");
             //printf("Source mac address is %s\n",addr[i]);
             flagsrcmac = 1;

             pthread_create(&id[i],0, worker, arg3);
             //printf("Timer updated\n");

             break;
             }

        }

if(flagsrcmac ==0)

    {

      //printf("Source mac addres not found in switch table\n");

      
      for(int k=0;k<5;k++)
      {

          int *arg4 = malloc(sizeof(*arg4));
          *arg4 = k;


            if(switchsock[k] ==0)
             {
               strcpy(addr[k],eth.srcmac);
               switchsock[k] = clients[m];

              pthread_create(&tid, 0, worker, arg4);
              id[k] = pthread_self(); 


               break;
                }

     }
   }



   int flagdestmac = 0;
   //printf("Entering to find if dest mac address exists in switchtable\n");


      for(int i=0;i<5;i++)
      {

          if(strcmp(addr[i],eth.destmac) == 0)
          {   

              //printf("Destination mac address found in switchtable\n");
              //printf("Dest mac address is %s\n",addr[i]);

              flagdestmac = 1;


             send(switchsock[i],(struct ether*)&eth, sizeof(struct ether), 0);
             break;

             }


        }

    if(flagdestmac == 0)

      {

       // printf("Destination mac address not found in switchtable\n");

        for(int x1=0;x1<10;x1++)

               { 

                  if(clients[x1]>0 && clients[x1]!=clients[m])

                  {
                     
                     send(clients[x1], (struct ether*)&eth, sizeof(struct ether), 0);



                           } // end of if


                        } // end of for 


        

        }








//printf("Printng records\n");

/*for(int k=0;k<5;k++)
  {
    printf("Address of %d is %s and sockfd is %d\n",k,addr[k],switchsock[k]);


     }*/






       
    }


         }






           //printf("\n%s(%s)\n",host2,serv2,client_message);
               
     
    

 /*printf("Source mac address is %s\n",frame1.srcmac);
        printf("Dest mac address is %s\n",frame1.destmac);
   int flagsrcmac = 0;
    printf("Entering to find source mac address in switchtable\n");
     for(int i=0;i<5;i++)
      {

          if(strcmp(switchtable[i][1],frame1.srcmac) == 0)
          {

             printf("Source mac addres found in switch table\n");
             printf("Source mac address is %s\n",switchtable[i][1]);
             flagsrcmac = 1;
             break;
             }

        }
     
    if(flagsrcmac ==0)
    {
      printf("Source mac addres not found in switch table\n");

       for(int i=0;i<5;i++)
      {
          if(switchtable[i][0] == 0)
          {
            printf("Entering to insert src mac addr and sockfd in switchtable\n");
              
             switchtable[i][0] = clients[m];
             switchtable[i][1] = frame1.srcmac;
             printf("Entered src mac addr is %s\n",switchtable[i][1]);
             break;
             }

        }



            }


     int flagdestmac = 0;

    printf("Entering to find if dest mac address exists in switchtable\n");

      for(int i=0;i<5;i++)
      {
          if(strcmp(switchtable[i][1],frame1.destmac) == 0)
          {   
              printf("Destination mac address found in switchtable\n");
              printf("Dest mac address is %s\n",switchtable[i][1]);
              flagdestmac = 1;

             send(switchtable[i][0], frame1.c1, sizeof(frame1.c1), 0);
             break;
             }

        }

       if(flagdestmac == 0)
      {
        printf("Destination mac address not found in switchtable\n");
         for(int i=0;i<5;i++)
         {
          if(switchtable[i][0] >0 && switchtable[i][0]!=clients[m])
          {
             send(switchtable[i][0], frame1.c1, sizeof(frame1.c1), 0);
             
             }

          }
        }


   printf("Addresses in switching table:\n");


  for(int i=0;i<5;i++)
  {
    printf("Address %d is %s\n",i,switchtable[i][1]);


     }*/








              } // end of if

                } //end of if

          if(ret==0)
          {

            struct sockaddr_storage cl_addr;
           socklen_t len1 = sizeof(cl_addr);
      
     if (getpeername(clients[m], (struct sockaddr *)&cl_addr, &len1) == -1)
     perror("getpeername");
     else
     {
      

       char serv1[256];
       char host1[256];

    if (getnameinfo((const struct sockaddr *) &cl_addr, len1,host1,sizeof(host1),
                    serv1, sizeof(serv1), 0) == 0)

    {   
        printf("disconnect from  '%s(%s)'\n", host1,serv1);

        //printf("client service: %s\n", serv1);
    }


         }



            close(clients[m]);
            clients[m] = 0;

                 }


          }


        }



}// end of for loop

 



} // end of while



































//memset((void*)client_message,0,sizeof(client_message));

//recv(client_socket,client_message,sizeof(client_message),0);

//printf("\n Message from client: %s\n",client_message);




	// close the socket
	close(server_socket);
	
	return 0;
}
