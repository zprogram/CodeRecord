#pragma comment(lib,"DLL_01_利用_declspec(dllexport)导出类.lib")
#include "DLL_01_利用_declspec(dllexport)导出类.h"

void main()
{
	Maze _maze;//迷宫对象
	_maze.PrintMaze();//打印迷宫
	_maze.GetPos();//获取出入口位置
	_maze.SearchMaze();//寻找出口路径
}