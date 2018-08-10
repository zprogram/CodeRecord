#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
using namespace std;

//打印容器的值

void main()
{
	vector<int> v(4,1);  //创建vector容器对象

	deque<float>deq;     //创建deque容器对象
	deq.push_back(1);    //加入一个元素到队列
	deq.push_back(2);    //加入另一个元素
	deq.pop_back();      //删除最后一个元素
	deq.push_front(3);   //加到第一个元素位置
	list<int> l;         //创建list容器对象
	l.push_back(1);
	set<short>_set;      //创建set容器对象
	_set.insert(1);
	_set.insert(1);
	_set.insert(2);
	multiset<short>_mset;//创建multiset容器对象
	_mset.insert(1);
	_mset.insert(1);
	_mset.insert(2);
	map<string,string>_map;//创建map容器对象
	_map.insert(pair<string,string>("1","1"));
	_map.insert(pair<string,string>("1","2"));
	multimap<string,string>_mmap;//创建multimap容器
	_mmap.insert(pair<string,string>("1","1"));
	_mmap.insert(pair<string,string>("1","2"));

	list<int>::iterator lit;  //list的迭代器，用于读取元素
	set<short>::iterator iset;//创建set的迭代器
	multiset<short>::iterator mul;
	map<string,string>::iterator mit;//创建map的迭代器
	multimap<string,string>::iterator mulm;
	cout<<"vector容器中各元素的值：";
	for(int i=0;i<v.size();i++)
		cout<<v.at(i)<<" ";
	cout<<endl;
	cout<<"deque容器中各元素的值：";
	for(int i=0;i<deq.size();i++)
		cout<<deq.at(i)<<" ";
	cout<<endl;
	cout<<"list容器中各元素的值：";
	for(lit=l.begin();lit!=l.end();lit++)
		cout<<*lit<<" ";
	cout<<endl;
	cout<<"set容器中各元素的值：";
	for(iset=_set.begin();iset!=_set.end();iset++)
		cout<<*iset<<" ";
	cout<<endl;
	cout<<"multiset容器中各元素的值：";
	for(mul=_mset.begin();mul!=_mset.end();mul++)
		cout<<*mul<<" ";
	cout<<endl;
	cout<<"map容器中各元素的值：";
	for(mit=_map.begin();mit!=_map.end();mit++)
		cout<<mit->first<<" "<<mit->second<<" ";
	cout<<endl;
	cout<<"multimap容器中各元素的值：";
	for(mulm=_mmap.begin();mulm!=_mmap.end();mulm++)
		cout<<mulm->first<<" "<<mulm->second<<" ";
	cout<<endl;
}