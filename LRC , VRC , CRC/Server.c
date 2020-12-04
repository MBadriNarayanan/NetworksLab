#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int VRC(char *s){
 int cnt=0;
 for(int i=0;s[i]!='\0';i++){
 if(s[i]=='1')
 cnt++;
 }
 if(cnt%2==0){
 printf("NO error \n ");
 return 1;
 }
 else{
 printf("Error in transmission, Parity mismatch ");
 return 0;
 }
}
int LRC(char *s){
 for(int i=0;i<4;i++){
 int cnt=0;
 if(s[i]=='1')
 cnt++;
 if(s[i+4]=='1')
 cnt++;
 if(s[i+8]=='1')
 cnt++;
 if(s[i+12]=='1'){
 if(cnt%2==0){
 printf("Error in the %dth column",i+1);
 return 0;
 }

 }
 else if(s[i+12]=='0'){
 if(cnt%2==1){
 printf("Error in the %dth column",i+1);
 return 0;
 }
 }
 }
 printf("NO error");
 return 1;
}
int CRC(char *s){
 int temp[10],gen[5]={1,1,0,0,1};
 for(int i=0;i<10;i++)
 temp[i]=s[i]-48;
 for(int i=0;i<6;i++){
 if (gen[0]==temp[i]){
 for(int j=0,k=i;j<5;j++,k++)
 if(!(temp[k]^gen[j]))
 temp[k]=0; 
 else
 temp[k]=1;
 }
 }
 for(int i=0;i<4;i++){
 if(temp[6+i]!=0){
 printf(" Error in transmission \n ");
 return 0;
 }
 }
 printf("NO error \n");
 return 1;
}

int main(int argc, char const *argv[])
{
 int server_fd, new_socket, valread;
 struct sockaddr_in address;
 int opt = 1;
 int addrlen = sizeof(address);
 char buffer[1024] = {0};
 char msg[20];
 server_fd = socket(AF_INET, SOCK_STREAM, 0);
 setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,&opt, sizeof(opt));
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = INADDR_ANY;
 address.sin_port = htons( PORT );
 bind(server_fd, (struct sockaddr *)&address,sizeof(address));
 listen(server_fd, 3);
 new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
 valread = read( new_socket , buffer, 1024);
 printf("The message sent from client is :%s\n",buffer );
 
 
 int choice;
 printf("Do you want to change the message received? \n Yes 1 \nNo 0 ");
 scanf("%d",&choice);
 
 if(choice == 1)
    {
    printf("\nEnter the changed message : \n");
    gets(buffer);
    }
 
 
 
 int k;
 printf("Enter : \n 1 for VRC \n 2 for LRC \n 3 for CRC\n");
 scanf("%d",&k);
 if(k==1){
 if(VRC(buffer))
 strcpy(msg,"VALID");
 else
 strcpy(msg,"INVALID");
 }
 else if(k==2){
 if(LRC(buffer))
 strcpy(msg,"VALID");
 else
 strcpy(msg,"INVALID");
 }
 else{
 if(CRC(buffer))
 strcpy(msg,"VALID");
 else
 strcpy(msg,"INVALID");
 }
 send(new_socket , msg , 20 , 0 );
 return 0;
}
