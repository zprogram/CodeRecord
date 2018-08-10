#pragma comment(lib,"Ws2_32.lib")
#include <Winsock2.h>
#include <iostream>
using namespace std;

void main()
{
	cout<<"---------基于UDP的聊天程序-----------"<<endl;
	cout<<"------------客户端开发(客户端先说）--"<<endl;
	WORD wVersionRequested;         //版本号
	WSADATA wsaData;                //记录WinSockDLL信息
	wVersionRequested=MAKEWORD(2,2);//计算版本号
	SOCKET cs;                //客户端套接字
	SOCKADDR_IN addr;         //客户端地址
	char recvBuf[128];        //接收
	char sendBuf[128];        //发送
	int len=sizeof(sockaddr); //长度
	if(WSAStartup(wVersionRequested,&wsaData)!=0)
	{
		cout<<"初始化DLL失败"<<endl;
		return;
	}
	cs=socket(AF_INET,SOCK_DGRAM,0);
	addr.sin_family=AF_INET;
	addr.sin_port=htons(5000);                      //端口
	addr.sin_addr.s_addr=inet_addr("192.168.14.45");//服务端IP
	while(1)
	{
		gets_s(sendBuf,20);                         //获取数据
		sendto(cs,sendBuf,strlen(sendBuf)+1,0,(sockaddr*)&addr,len);//发送
		recvfrom(cs,recvBuf,128,0,(sockaddr*)&addr,&len);           //获取
		char *s_ip=inet_ntoa(addr.sin_addr);                        //转换
		cout<<s_ip<<"说:"<<recvBuf<<endl;                           //输出
	}
	closesocket(cs);
	WSACleanup();
}