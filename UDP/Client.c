#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

int main(int argc, char *argv[])
{
	int net_sock,portno;
    char recv_msg[256];
    char send_msg[250];
    struct sockaddr_in server_address;
    int len,n;
    
    if(argc<2)
    {
    fprintf(stderr,"No Port Provided \n");
    exit(1);
    }
 	portno=atoi(argv[1]);    
    
	net_sock=socket(AF_INET,SOCK_DGRAM,0);
    
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(portno);
    server_address.sin_addr.s_addr=INADDR_ANY;
    
    printf("Enter the message to be sent \n");
    gets(send_msg);
    
    sendto(net_sock, send_msg, sizeof(send_msg), 
        MSG_CONFIRM, (const struct sockaddr *) &server_address,  
            sizeof(server_address));
            
    n = recvfrom(net_sock, &recv_msg,sizeof(recv_msg),  
                MSG_WAITALL, (struct sockaddr *) &server_address, 
                &len); 
	 printf("The message sent by the server is: %s\n",recv_msg);
	
	return 0;
}
