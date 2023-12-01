Server.c
 
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#define err_log(log) do{perror(log); exit(1);}while(0)
#define N 128
int main(int argc, const char *argv[])
{
int sockfd;
struct sockaddr_in broadcastaddr;
char buf[N] = {0};
if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
{
err_log("fail to socket");
}
broadcastaddr.sin_family = AF_INET;
broadcastaddr.sin_addr.s_addr = inet_addr("192.168.1.255"); //Broadcast address
broadcastaddr.sin_port = htons(10000);
int optval = 1;
if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int)) < 0)
{
err_log("fail to setsockopt");
}
while(1)
{
printf("Input > ");
fgets(buf, N, stdin);
if(sendto(sockfd,buf, N, 0, (struct sockaddr *)&broadcastaddr, sizeof(broadcastaddr)) < 0)
{
err_log("fail to sendto");
}
}
return 0;
}
 
 
CLIENT.C
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#define err_log(log) do{perror(log); exit(1);}while(0)
#define N 128
int main(int argc, const char *argv[])
{
int sockfd;
char buf[N];
struct sockaddr_in broadcastaddr, srcaddr;
if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
{
err_log("fail to socket");
}
broadcastaddr.sin_family = AF_INET;
broadcastaddr.sin_addr.s_addr = inet_addr("192.168.1.255"); //Broadcast address
broadcastaddr.sin_port = htons(10000);
if(bind(sockfd, (struct sockaddr*)&broadcastaddr, sizeof(broadcastaddr)) < 0)
{
err_log("fail to bind");
}
socklen_t addrlen = sizeof(struct sockaddr);
while(1)
{
if(recvfrom(sockfd,buf, N, 0, (struct sockaddr *)&srcaddr, &addrlen) < 0)
{
err_log("fail to sendto");
}
printf("buf:%s ---> %s %d\n", buf, inet_ntoa(srcaddr.sin_addr), ntohs(srcaddr.sin_port));
}
return 0;
}
 
MULTICASTTTTTTTTTTTTTTTT
 
#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main(){
 
	int sock,b=1;
	char str[100],str2[10];
	struct sockaddr_in serv;
	sock=socket(AF_INET,SOCK_DGRAM,0);
	//setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&b,sizeof(b));
	bzero(&serv,sizeof(serv));
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr = inet_addr("227.0.0.3");
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr=inet_addr("227.0.0.3");
	mreq.imr_interface.s_addr=INADDR_ANY;
	setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	while(1){
 
		printf("Do you want to broadcast?");
		fgets(str2,10,stdin);
		if(strncmp(str2,"yes",3)==0)
		{	printf("Enter the Message");
			fgets(str,10,stdin);
			sendto(sock,str,strlen(str),0,(struct sockaddr *)&serv,sizeof(serv));
		}
else
{
break;
}
}
close(sock);
}
 
 
 
 
#include<stdio.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
int sock,r=1;
char str[100];
struct sockaddr_in serv;
bzero(&serv,sizeof(serv));
sock=socket(AF_INET,SOCK_DGRAM,0);
setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&r,sizeof(r));
serv.sin_port=htons(12345);
serv.sin_family=AF_INET;
serv.sin_addr.s_addr=INADDR_ANY;
bind(sock,(struct sockaddr*)&serv , sizeof(serv));
struct ip_mreq mreq;
mreq.imr_multiaddr.s_addr=inet_addr("227.0.0.3");
mreq.imr_interface.s_addr=INADDR_ANY;
setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
while(1)
{
bzero(str,100);
recvfrom(sock,str,100,0,NULL,NULL);
printf("Received data is : %s ",str);
}
close(sock);
}
