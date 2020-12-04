#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

int main(int argc, char *argv[])
{
	int serv_sock,portno;
    char recv_msg[256];
    char send_msg[250];
    struct sockaddr_in server_address,cliaddr;
    int len,n;
    
    if(argc<2)
    {
    fprintf(stderr,"No Port Provided \n");
    exit(1);
    }
 	portno=atoi(argv[1]);    
    
	serv_sock=socket(AF_INET,SOCK_DGRAM,0);
    
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(portno);
    server_address.sin_addr.s_addr=INADDR_ANY;
    
    bind(serv_sock,(struct sockaddr*) &server_address,sizeof(server_address));
    
	n = recvfrom(serv_sock, &recv_msg,sizeof(recv_msg),  
                MSG_WAITALL, (struct sockaddr *) &cliaddr, 
                &len); 
	printf("The message sent by the client is: %s\n",recv_msg);
    
	printf("Enter the message to be sent \n");
    gets(send_msg);
    
    sendto(serv_sock, send_msg, sizeof(send_msg), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,  
            sizeof(server_address));
	
	return 0;
}
