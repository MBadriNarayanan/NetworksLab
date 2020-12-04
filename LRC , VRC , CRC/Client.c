#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
 int sock = 0, valread;
 struct sockaddr_in serv_addr;
 char msg[20];
 printf("IF VRC message(15 bits) followed by parity(1 bit) \nIF LRC 3 blocks of 4 bit data(12 bits) 1 block of parity (4 bits)\nIF CRC 6 bit message followed by 4 bit remainder when divided by the generator 11001 (10 bits)\n");
 scanf("%s",msg);
 char buffer[1024] = {0};
 sock = socket(AF_INET, SOCK_STREAM, 0);
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_port = htons(PORT);
 inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
 connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
 send(sock , msg , 20 , 0 );
 valread = read( sock , buffer, 1024);
 printf("The message sent from server is : %s\n",buffer );
 return 0;
}
