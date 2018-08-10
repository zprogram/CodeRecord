//代码重点：寻路算法
// 模拟走迷宫原理，实现该算法。已知道迷宫布局，其中1表示不可通行，0为可通行。
// 由用户输入出入口位置，经过算法处理，输出路径。

// 输出效果：
//
// 显示迷宫10*10：
// 1111111111
// 1000000001
// 1010101001
// 1001011101
// 1101011000
// 1000001001
// 1111111011
// 1101011001
// 1000001101
// 1111111111
// 请输入迷宫入口行：1
// 请输入迷宫入口列：1
// 请输入迷宫出口行：8
// 请输入迷宫出口列：8
// 
// 显示路径：
// 1111111111
// 1********1
// 1 1 1 1 *1
// 1  1 111*1
// 11 1 11 *
// 1     1**1
// 1111111*11
// 11 1 11**1
// 1     11*1
// 1111111111



#include <iostream>
using namespace std;

#define M 10
#define N 10
class Maze
{
public:
	Maze();                         // 构造函数
	~Maze(){}                       // 析构函数
	void PrintMaze();               // 打印迷宫
	void GetPos();                  // 获取出入口位置
	void SearchMaze();              // 获取迷宫路径
	bool EvaluateMaze(int i,int j); // 判断当前点是否可行
private:
	int maze[M][N];                 // 迷宫
	int start_row;                  // 入口行
	int start_col;                  // 入口列
	int end_row;                    // 出口行
	int end_col;                    // 出口列
	bool succeed;                   // 是否找到出口
};
Maze::Maze()
{
	int copy[M][N]={{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,0,1,0,0,1},
	{1,0,0,1,0,1,1,1,0,1},
	{1,1,0,1,0,1,1,0,0,0},
	{1,0,0,0,0,0,1,0,0,1},
	{1,1,1,1,1,1,1,0,1,1},
	{1,1,0,1,0,1,1,0,0,1},
	{1,0,0,0,0,0,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1}};
	memcpy(maze,copy,sizeof(maze)); // 迷宫初始化,0为可行，1为不可行
	succeed=false;                  // 初始化为没有
}
void Maze::PrintMaze()
{
	cout<<"显示迷宫10*10："<<endl;
	for(int i=0;i<M;i++)           // 行
	{
		for(int j=0;j<N;j++)       // 列
		{
			if(maze[i][j]==1)      // 不可行
				cout<<"1";
			else                   // 可行
				cout<<"0";
		}
		cout<<endl;                // 下一行
	}
}
void Maze::GetPos()
{
	cout<<"请输入迷宫入口行：";
	cin>>start_row;
	cout<<"请输入迷宫入口列：";
	cin>>start_col;
	cout<<"请输入迷宫出口行：";
	cin>>end_row;
	cout<<"请输入迷宫出口列：";
	cin>>end_col;
}
void Maze::SearchMaze()
{
	if(EvaluateMaze(start_row,start_col)==false)// 没有找到出口
		cout<<endl<<"没有找到出口\n";
	else                                        // 找到
	{
		cout<<endl<<"显示路径："<<endl;
		for(int i=0;i<M;i++)                    // 行
		{
			for(int j=0;j<N;j++)                // 列
			{
				if(maze[i][j]==1)               // 打印不可通行位置
					cout<<"1";
				else if(maze[i][j]==2)          // 打印路径
					cout<<"*";
				else                            // 可通行的但不是路径为空格
					cout<<" ";
			}
			cout<<endl;
		}
	}
}
bool Maze::EvaluateMaze(int i,int j)
{
	maze[i][j]=2;                     // 与迷宫已被判断的元素区别
	if(i==end_row&&j==end_col)        // 搜索到出口
		succeed=true;					 
	if(succeed!=true&&maze[i][j+1]==0)// 向后一列可通行的
		EvaluateMaze(i,j+1);			 
	if(succeed!=true&&maze[i+1][j]==0)// 向后一行可通行的
		EvaluateMaze(i+1,j);			 
	if(succeed!=true&&maze[i][j-1]==0)// 向前一列可通行的
		EvaluateMaze(i,j-1);			 
	if(succeed!=true&&maze[i-1][j]==0)// 向前一行可通行的
		EvaluateMaze(i-1,j);			 
										 
	if(succeed!=true)                 // 重新赋为可通行的
		maze[i][j]=0;
	return succeed;
}

void main()
{
	//int i,j;//循环变量
	Maze _maze;                      // 迷宫对象
	_maze.PrintMaze();               // 打印迷宫
	_maze.GetPos();                  // 获取出入口位置
	_maze.SearchMaze();              // 寻找出口路径
}