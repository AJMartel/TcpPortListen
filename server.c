#include<winsock2.h>
#include<windows.h>
#include<string.h>
#include<stdio.h>
#define BUFFSIZE 2000

void errorOutput(char *);
void infoOutput(char *);
int main (int argc,char *argv[]){
	WSADATA wsaData; 
	WSAStartup( 0x101 , &wsaData);
	char buff[BUFFSIZE];
	int ser_SocketNum;
	int cli_SocketNum;
	int listen_PortNum;
	struct sockaddr_in ser_info;
	struct sockaddr_in cli_info;
	ser_info.sin_family=AF_INET;
	infoOutput(argv[1]);
	listen_PortNum=atoi(argv[1]);
	printf("[INFO]:listen_PortNum is :%d\n",listen_PortNum);
	ser_info.sin_port=htons(listen_PortNum);
	ser_info.sin_addr.s_addr=INADDR_ANY;
	ser_SocketNum=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(ser_SocketNum==INVALID_SOCKET)
	{
		errorOutput("Create Socket failed!");
		return 1;
	}
	else
	{
		infoOutput("Create Socket successfully!");
	}
	if(bind(ser_SocketNum,(struct sockaddr*)&ser_info,sizeof(ser_info))<0)
	{
		errorOutput("Bind Port failed!");
		return 1;
	}
	else
	{
		infoOutput("Bind Port successfully!");
	}
	if(listen(ser_SocketNum,10)<0)
	{
		errorOutput("Create listen for Tcp Port failed!");
		return 1;
	}
	else
	{
		infoOutput("Tcp Port listen was created successfully!");
	}
	infoOutput("Waiting for client connection");
		int clientLen=sizeof(cli_info);
		cli_SocketNum=accept(ser_SocketNum,(struct sockaddr*)&cli_info,&clientLen);
	while(recv(cli_SocketNum,buff,BUFFSIZE,0)>0)
	{
		
		if(cli_SocketNum<0)
		{
			errorOutput("Accept for client connection failed!");
			return 1;
		}
		else
		{
			infoOutput("Accept for client successfully!");
		}
		
			printf("[RECV]:%s\n",buff);
		


	}
	infoOutput("Bye");
	closesocket(ser_SocketNum);
	WSACleanup();
	return 0;

}
void errorOutput( char *p)
{
	printf("[ERROR]:%s\n",p);
}
void infoOutput( char *s)
{
	printf("[INFO]:%s\n",s);
}