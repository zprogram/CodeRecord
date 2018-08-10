// DLL_01_利用_declspec(dllexport)导出类.cpp : 定义 DLL 应用程序的导出函数。
//

#define MAZE_API  _declspec(dllexport)   //导出
#include "DLL_01_利用_declspec(dllexport)导出类.h"

Maze::Maze()
{
	int copy[M][N] = { { 1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,1 },
	{ 1,0,1,0,1,0,1,0,0,1 },
	{ 1,0,0,1,0,1,1,1,0,1 },
	{ 1,1,0,1,0,1,1,0,0,0 },
	{ 1,0,0,0,0,0,1,0,0,1 },
	{ 1,1,1,1,1,1,1,0,1,1 },
	{ 1,1,0,1,0,1,1,0,0,1 },
	{ 1,0,0,0,0,0,1,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1 } };
	memcpy(maze, copy, sizeof(maze));//迷宫初始化,0为可行，1为不可行
	succeed = false;//初始化为没有
}
void Maze::PrintMaze()
{
	cout << "显示迷宫10*10：" << endl;
	for (int i = 0; i < M; i++)//行
	{
		for (int j = 0; j < N; j++)//列
		{
			if (maze[i][j] == 1)//不可行
				cout << "1";
			else//可行
				cout << "0";
		}
		cout << endl;//下一行
	}
}
void Maze::GetPos()
{
	cout << "请输入迷宫入口行：";
	cin >> start_row;
	cout << "请输入迷宫入口列：";
	cin >> start_col;
	cout << "请输入迷宫出口行：";
	cin >> end_row;
	cout << "请输入迷宫出口列：";
	cin >> end_col;
}
void Maze::SearchMaze()
{
	if (EvaluateMaze(start_row, start_col) == false)//没有找到出口
		cout << endl << "没有找到出口\n";
	else//找到
	{
		cout << endl << "显示路径：" << endl;
		for (int i = 0; i < M; i++)//行
		{
			for (int j = 0; j < N; j++)//列
			{
				if (maze[i][j] == 1)//打印不可通行位置
					cout << "1";
				else if (maze[i][j] == 2)//打印路径
					cout << "*";
				else//可通行的但不是路径为空格
					cout << " ";
			}
			cout << endl;
		}
	}
}
bool Maze::EvaluateMaze(int i, int j)
{
	maze[i][j] = 2;//与迷宫已被判断的元素区别
	if (i == end_row&&j == end_col)//搜索到出口
		succeed = true;
	if (succeed != true && maze[i][j + 1] == 0)//向后一列可通行的
		EvaluateMaze(i, j + 1);
	if (succeed != true && maze[i + 1][j] == 0)//向后一行可通行的
		EvaluateMaze(i + 1, j);
	if (succeed != true && maze[i][j - 1] == 0)//向前一列可通行的
		EvaluateMaze(i, j - 1);
	if (succeed != true && maze[i - 1][j] == 0)//向前一行可通行的
		EvaluateMaze(i - 1, j);

	if (succeed != true)//重新赋为可通行的
		maze[i][j] = 0;
	return succeed;
}