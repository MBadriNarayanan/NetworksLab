#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc, char *argv[])
{
    int net_sock;
    int portno;
    char recv_msg[256];
    char send_msg[250];
    struct sockaddr_in server_address;
    int connection_status;
    
    if(argc < 2)
    {
        fprintf(stderr," Port Was Not Provided !!!! \n");
        exit(1);
    }

 	portno = atoi(argv[1]);    
    
	net_sock = socket(AF_INET, SOCK_STREAM , 0);
    
    server_address.sin_family = AF_INET;

    server_address.sin_port = htons(portno);

    server_address.sin_addr.s_addr = INADDR_ANY;

    connection_status = connect(net_sock , (struct sockaddr *) &server_address , sizeof(server_address));
   
    if(connection_status == -1)
    {
        printf(" There was an error making a connection to the remote socket !!!! \n");
    }
    
    recv(net_sock , &recv_msg, sizeof(recv_msg) , 0);

    printf(" Message From Server : %s \n" , recv_msg);
    
    printf(" Enter Message To Be Sent To Server : ");

    gets(send_msg);

    send(net_sock , send_msg , sizeof(send_msg) , 0);   
   
    close(net_sock);
    
    return 0;
}
