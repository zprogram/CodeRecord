// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DLL_01__DECLSPECDLLEXPORT_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DLL_01__DECLSPECDLLEXPORT_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef MAZE_API
#else
#define MAZE_API _declspec(dllimport)    // 定义导出标识符
#endif

#include <iostream>
using namespace std;

#define M 10
#define N 10

class MAZE_API Maze                     // 导出类声明
{
public:
	Maze();//构造函数
	~Maze() {}//析构函数
	void PrintMaze();//打印迷宫
	void GetPos();//获取出入口位置
	void SearchMaze();//获取迷宫路径
	bool EvaluateMaze(int i, int j);//判断当前点是否可行
private:
	int maze[M][N];//迷宫
	int start_row;//入口行
	int start_col;//入口列
	int end_row;//出口行
	int end_col;//出口列
	bool succeed;//是否找到出口
};