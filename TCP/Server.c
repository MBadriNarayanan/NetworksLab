#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(int argc , char *argv[])
{
    char serv_msg[256];
    int portno;
    int serv_sock;
    struct sockaddr_in server_address;
    int cl_sock;
    
    if(argc<2)
    {
        fprintf(stderr," Port Was Not Provided !!!! \n");
        exit(1);
    }
    
    printf(" Enter Message To Be Sent To Client : ");

    gets(serv_msg);

    printf("\n");
    
    portno = atoi(argv[1]);

    serv_sock = socket(AF_INET , SOCK_STREAM , 0);

    server_address.sin_family = AF_INET;

    server_address.sin_port = htons(portno);

    server_address.sin_addr.s_addr = INADDR_ANY;
    
    bind(serv_sock , (struct sockaddr*) &server_address , sizeof(server_address));
    
    listen(serv_sock , 5);
    
    cl_sock = accept(serv_sock , NULL , NULL);

    send(cl_sock , serv_msg , sizeof(serv_msg) , 0);

    recv(cl_sock ,&serv_msg , sizeof(serv_msg) , 0);
    
    printf(" Message Sent By Client : %s\n",serv_msg);
    
	close(serv_sock);
    
	return 0; 
}
