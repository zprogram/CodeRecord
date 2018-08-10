#pragma comment(lib,"Ws2_32.lib")
#include <Winsock2.h>
#include <iostream>
using namespace std;

void main()
{
	cout<<"--------服务端开发---------"<<endl;
	SOCKET sersock,clisock;     //服务器与客户端套接字
	struct sockaddr_in add;     //服务器信息
	struct sockaddr_in cliaddr; //客户端信息
	int serport = 5000;         //端口号
	char buff[256];             //缓冲区
	WSADATA ws;                             //记录WinSock DLL信息
	int len;                                //缓冲区长度过	
	WORD wVersionRequested;                 //版本号
	wVersionRequested=MAKEWORD(2,2);        //计算版本号
	if(WSAStartup(wVersionRequested,&ws)!=0)//初始化Winsock
	{
		cout<<"初始化DLL失败!"<<endl;
		return;
	}
	cout<<"创建套接字中..."<<endl;
	sersock=socket(AF_INET,SOCK_STREAM,0);   //创建套接字
	memset(&add,0,sizeof(add));              //初始化地址信息
	add.sin_family=AF_INET;
	add.sin_port=htons(serport);
	add.sin_addr.s_addr = INADDR_ANY;        //对任意IP通信
	
	cout<<"正在绑定中..."<<endl;
	if(bind(sersock,(const sockaddr*)&add,sizeof(add))!=0)//绑定套接字
	{
		cout<<"绑定失败"<<WSAGetLastError()<<endl;
		return;
	}
	cout<<"正在监听中..."<<endl;
	if(listen(sersock,5)!=0)        //监听有错误
	{
		cout<<"监听失败"<<WSAGetLastError()<<endl;
		return;
	}
	cout<<"等待连接请求中..."<<endl;//等待连接请求
	len=sizeof(cliaddr);
	clisock=accept(sersock,(struct sockaddr*)&cliaddr,&len);//接受连接请求
	cout<<"接受客户端连接请求"<<inet_ntoa(cliaddr.sin_addr)
		<<ntohs(cliaddr.sin_port)<<endl;
	sprintf(buff,"大家好%s",inet_ntoa(cliaddr.sin_addr));//附加IP地址信息
	send(clisock,buff,strlen(buff),0);//发送数据
	closesocket(clisock);             //关闭客户端套接字
	closesocket(sersock);             //关闭服务器套接字
	WSACleanup();                     //清理资源
}