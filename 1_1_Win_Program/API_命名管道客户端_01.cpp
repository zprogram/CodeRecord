#include <Windows.h>
#include <iostream> 
using namespace std; 
    
HANDLE hNamedPipe; //命名管道句柄 

void ClientR()//读
{    
	char buffer[100];
	DWORD dwRead;
	if(!ReadFile(hNamedPipe,buffer,100,&dwRead,NULL))//读数据失败
	{
		cout<<"客户端读取数据失败。。。"<<endl;
		return;
	}
	cout<<"客户端读取数据成功："<<buffer<<endl;//输出  
}
void ClientW()//写
{ 
	DWORD dwWrite;   
	char* buffer = "客户端发送数据到服务端";   
	if(!WriteFile(hNamedPipe, buffer, strlen(buffer)+1, &dwWrite, NULL))  //写入数据
	{        
		cout<<"客户端写入数据失败。。。"<<endl;    
		return;  
	}  
	cout<<"客户端写入数据成功："<<buffer<<endl;
}
void main()
{    
	if(!WaitNamedPipe(TEXT("\\\\.\\pipe\\namedpipe"), NMPWAIT_WAIT_FOREVER))//等待连接命名管道  
	{     
		cout<<"命名管道实例不存在。。。"<<endl;     
		return;  
	} 
	hNamedPipe = CreateFile(TEXT("\\\\.\\pipe\\namedpipe"), GENERIC_READ | GENERIC_WRITE,     
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //打开命名管道 
	if(INVALID_HANDLE_VALUE == hNamedPipe)  
	{     
		cout<<"打开命名管道失败。。。"<<endl<<endl;   
		return; 
	}
	while(1)
	{
		cout<<"客户端操作，读/写：0-读，1-写"<<endl;
		int choose;
		cin>>choose;
		switch(choose)
		{
		case 0:
			ClientR();//读
			break;
		case 1:
			ClientW();//写
			break;
		default:
			break;
		}
	}
}  