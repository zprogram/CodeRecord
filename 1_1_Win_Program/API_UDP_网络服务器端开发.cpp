#pragma comment(lib,"Ws2_32.lib")
#include <Winsock2.h>
#include <iostream>
using namespace std;

void main()
{
	cout<<"---------基于UDP的聊天程序-----------"<<endl;
	cout<<"------------服务端开发(客户端先说）--"<<endl;
	WORD wVersionRequested;          //版本号
	WSADATA wsaData;                 //记录WinSockDLL信息
	wVersionRequested=MAKEWORD(2,2); //计算版本号
	SOCKET ss;             //服务端套接字
	SOCKADDR_IN addrS;     //地址
	int len=sizeof(sockaddr);//长度
	SOCKADDR_IN addrC;       //客户端地址
	char recvBuf[128];       //接收
	char sendBuf[128];       //发送
	char tempBuf[128];       //临时
	if(WSAStartup(wVersionRequested,&wsaData)!=0)
	{
		cout<<"初始化DLL失败"<<endl;
		return;
	}
	ss=socket(AF_INET,SOCK_DGRAM,0);   //创建套接字
	addrS.sin_family=AF_INET;
	addrS.sin_port=htons(5000);        //端口
	addrS.sin_addr.s_addr=INADDR_ANY;  //对任意IP通信
	bind(ss,(sockaddr*)&addrS,len);    //绑定套接字	
	while(1)
	{
		recvfrom(ss,recvBuf,128,0,(sockaddr*)&addrC,&len);//接收
		char *c_ip=inet_ntoa(addrC.sin_addr);
		sprintf(tempBuf,"%s 说: %s\n",c_ip,recvBuf);      //附加信息
		cout<<tempBuf;       //输出
		gets_s(sendBuf,20);  //获取服务端发送数据
		sendto(ss,sendBuf,strlen(sendBuf)+1,0,(sockaddr*)&addrC,len);//发送
	}
	closesocket(ss);  //关闭
	WSACleanup();     //清理
}