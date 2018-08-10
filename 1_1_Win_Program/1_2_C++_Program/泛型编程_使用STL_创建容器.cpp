#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
using namespace std;

//STL是一种模版类。使用容器可以更方便地处理各种类型的数据。
//本例子实现使用STL创建容器，并对容器的各元素进行初始化。最后输出各个容器的大小。


void main()
{
	vector<int> v(4,1);  
	//创建vector容器对象
	deque<float>deq;   //创建deque容器对象
	deq.push_back(1);  //加入一个元素到队列
	deq.push_back(2);  //加入另一个元素
	deq.pop_back();    //删除最后一个元素
	deq.push_front(3); //加到第一个元素位置
	list<int> l;       //创建list容器对象
	l.push_back(1);
	set<short>_set;    //创建set容器对象
	_set.insert(1);
	_set.insert(1);
	_set.insert(2);
	multiset<short>_mset;//创建multiset容器对象
	_mset.insert(1);
	_mset.insert(1);
	_mset.insert(2);
	map<string,string>_map;                     //创建map容器对象
	_map.insert(pair<string,string>("1","1"));
	_map.insert(pair<string,string>("1","2"));
	multimap<string,string>_mmap;               //创建multimap<
	_mmap.insert(pair<string,string>("1","1"));
	_mmap.insert(pair<string,string>("1","2"));
	cout<<"此vector的大小："<<v.size()<<endl;
	cout<<"此deque的大小："<<deq.size()<<endl;
	cout<<"此list的大小："<<l.size()<<endl;
	cout<<"此set的大小："<<_set.size()<<endl;
	cout<<"此multiset的大小："<<_mset.size()<<endl;
	cout<<"此map的大小："<<_map.size()<<endl;
	cout<<"此multimap的大小："<<_mmap.size()<<endl;
}