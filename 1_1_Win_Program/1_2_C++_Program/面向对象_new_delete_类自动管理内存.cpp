// 类自动化管理内存
// 相对程序员手动分配和释放内存块，系统自动完成这些任务。
// 示例以一维整型内存为例演示自动化的内存管理。
// new开辟内存、delete删除内存

#include <iostream>
using namespace std;

class memory
{
public:
	memory(int length)
	{
		_length=length;
		memo=new int[_length];            //申请一维内存
		for(int i=0;i<_length;i++)
			memo[i]=0;                    //初始化
		cout<<"内存分配成功！"<<endl;
	}
	~memory()
	{
		delete []memo;                    //释放内存
		if(memo!=NULL)
			memo=NULL;                    //释放指针
		cout<<"内存释放成功！"<<endl;
	}
	void output()                         //输出初始值
	{
		for(int i=0;i<_length;i++)
			cout<<memo[i]<<" ";
		cout<<endl;
	}
private:
	int *memo;                            //一维内存
	int _length;                          //内存长度
};
void main()
{
	memory _mem(20);                      //申请内存长度为20
	_mem.output();                        //调用输出函数
}