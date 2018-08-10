#pragma comment(lib,"Ws2_32.lib")
#include <Winsock2.h>
#include <iostream>
using namespace std;

void main()
{
	cout<<"--------客户端开发---------"<<endl;
	SOCKET sock;                              //套接字
	struct sockaddr_in add;                   //地址信息
	int servport = 5000;                      //端口号
	char buff[256];                           //缓冲区
	int len;                                  //缓冲区长度
	WSADATA ws;                               //DLL信息
	WORD wVersionRequested;                   //版本号
	wVersionRequested=MAKEWORD(2,2);          //计算版本号
	if(WSAStartup(wVersionRequested,&ws)!=0)  //初始DLL失败
	{
		cout<<"初始化DLL失败"<<endl;
		return;
	}
	sock=socket(AF_INET,SOCK_STREAM,0);              //创建套接字
	memset(&add,0,sizeof(add));                      //初始化地结构为0
	add.sin_family=AF_INET;                          //赋值
	add.sin_port=htons(servport);                    //赋值端口信息
	add.sin_addr.s_addr = inet_addr("192.168.14.45");//IP地址
	connect(sock,(const sockaddr*)&add,sizeof(add)); //连接服务器
	memset(buff,0,sizeof(buff));       //初始缓冲区
	len=recv(sock,buff,sizeof(buff),0);//接收数据
	cout<<buff<<endl;                  //输出数据
	closesocket(sock);                 //关闭套接字
	WSACleanup();                      //清理资源
}