#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hNamedPipe;//命名管道句柄
void ServerR()
{ 	
	char buffer[100];
	DWORD dwRead;
	if(!ReadFile(hNamedPipe,buffer,100,&dwRead,NULL))
	{
		cout<<"读取数据失败..."<<endl;
		return;
	}
	cout<<"读取数据成功：    "<<buffer<<endl;//输出   
} 
void ServerW()
{   
	DWORD dwWrite;   
	char* buffer = "服务端数据发送中。。。";   
	if(!WriteFile(hNamedPipe, buffer, strlen(buffer)+1, &dwWrite, NULL))  //写入数据
	{        
		cout<<"写入数据失败 ..."<<endl;    
		return;  
	}  
	cout<<"写入数据成功：    "<<buffer<<endl;
}
void main()
{
	HANDLE hEvent;
	OVERLAPPED ovlpd;     
	hNamedPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\namedpipe"),//创建命名管道         
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,//双向模式且重叠模式       
		0, 1, 1024, 1024, 0, NULL);     
	if(INVALID_HANDLE_VALUE == hNamedPipe)    
	{        
		hNamedPipe = NULL;        
		cout<<"创建命名管道失败。。。"<<endl;        
		return;    
	}
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);   //创建事件对象
	if(!hEvent)    
	{        
		cout<<"创建事件失败。。。"<<endl;        
		return;    
	}     
	memset(&ovlpd, 0, sizeof(OVERLAPPED));  //初始化为0  
	ovlpd.hEvent = hEvent;  //赋值
	if(!ConnectNamedPipe(hNamedPipe, &ovlpd))  //连接客户端   
	{        
		if(ERROR_IO_PENDING != GetLastError())        
		{           
			CloseHandle(hNamedPipe);    
			CloseHandle(hEvent);    
			cout<<"等待客户端连接失败 ..."<<endl;     
			return;       
		}    
	}
	if(WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE)) //等待事件状态
	{    
		CloseHandle(hNamedPipe);    //关闭命名管道
		CloseHandle(hEvent);     //关闭事件
		cout<<"等待对象失败 ..."<<endl;   
		return;   
	}    
	CloseHandle(hEvent);//关闭事件
	while(1)
	{
		cout<<"服务端操作，读/写：0-读，1-写"<<endl;
		int choose;
		cin>>choose;
		switch(choose)
		{
		case 0:
			ServerR();//读
			break;
		case 1:
			ServerW();//写
			break;
		default:
			break;
		}
	}
} 