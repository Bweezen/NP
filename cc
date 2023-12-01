Server.c
 
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
	setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&b,sizeof(b));
	bzero(&serv,sizeof(serv));
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr = inet_addr("255.255.255.255");
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
 
 Client.c
 
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
while(1)
{
bzero(str,100);
recvfrom(sock,str,100,0,NULL,NULL);
printf("Received data is : %s ",str);
}
close(sock);
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
