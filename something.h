#ifndef SOMETHING_H
#define SOMETHING_H

// 头文件处
#include "stdio.h"
#include "stdlib.h"// rand函数
#include "time.h"// 随机时间
#include "graphics.h"// 图形库
#include "conio.h"// getch有用
#include "windows.h"// 移动光标
#include "iostream"

// 宏定义处
#define ROWS 24//行 y的数量 最多29 30要跳框 看不见上边框 
#define COLS 77//列 x的数量 最多120 121要跳框 要乱码 
#define BOUNDARY_CHAR '#'// 边界字符
#define SNAKE_HEAD_CHAR 'o' // 蛇的字符
#define FO_CHAR '*'
// 底下四个是方向键
#define UP -1
#define DOWN 1
#define LEFT 0
#define RIGHT 2
#define SNAKEHEIGHT (ROWS - 2) * (COLS - 2) - 1// 蛇身的长度

// 定义全局变量和格式处
typedef struct SnakeHeaden { // 蛇的结构
	int index_COLS;// 蛇头的列 x值
	int index_ROWS;// 蛇头的行 y值
	char data;// 存蛇的字符
	SnakeHeaden* next;// 指向下一个蛇身的指针
};
typedef struct FOOD { // 食物的结构
	int FOOD_COLS;// 食物的列
	int FOOD_ROWS;// 食物的行
	char data;// 存食物的字符
};

char mazewallCharacter[ROWS][COLS];// 边框
SnakeHeaden SnakeHead;// 蛇头和蛇身的代码
SnakeHeaden* head = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// 蛇头的指针
int snakelength = 3;// 蛇身体节数
FOOD snake_food;

// 所有函数声明

// 禁用或关闭光标的可见性
void disableCursor();
// 边框
void wallgenerateMazeWalls();
// 生成食物位置(没有错误检测)
void initFood();
// 确定食物位置
void generateFood();
// 打印食物
void printFood();
// 遍历链表 把蛇打印出来
void printsnake();
// 打印地图
void printMaze();
// 随机生成三个蛇节点的位置，以及食物的位置
void initializeSnake();
// 对比上下左右是否为wsad, 比对成功返回该方向的值，比对失败返回7
int isDirectionKey(char direction/*方向字符*/);
// 移动蛇的位置
void moveToXY(int x, int y);
// 确定蛇移动的方向。包括：对上下左右键盘输入转码的整个程序，各种情况的错误处理
void newDirection(int* Direction_chose/*与移动程序交互的变量*/);
// 遍历链表到想要的位置
SnakeHeaden* traverseSnakeBody(int length);
// 收到上下左右指示后移动蛇头
int move_snake(char currentDirection/*与移动程序交互的变量*/);





#endif