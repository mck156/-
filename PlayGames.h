#ifndef PLAYGAMES_H
#define PLAYGAMES_H

// 头文件处

#include "stdio.h"
#include "stdlib.h"// rand函数
#include "time.h"// 随机时间
#include "graphics.h"// 图形库
#include "conio.h"// getch有用
#include "windows.h"// 移动光标
#include "iostream"
#include "string.h"
#include "settings.h"// 宏定义 全局变量 结构体

// 所有函数声明


// 关于蛇
	// 移动蛇的位置
void moveToXY(int x, int y);
	// 确定蛇移动的方向。包括：对上下左右键盘输入转码的整个程序，各种情况的错误处理
void newDirection(int* Direction_chose/*与移动程序交互的变量*/);
	// 收到上下左右指示后移动蛇头
int move_snake(int current/*与移动程序交互的变量*/);
	// 遍历链表 把蛇打印出来
void printsnake();
	// 随机生成三个蛇节点的位置，以及食物的位置
void initializeSnake();

// 关于界面和方向
	// 禁用或关闭光标的可见性
void disableCursor();
	// 对比上下左右是否为wsad, 比对成功返回该方向的值，比对失败返回7
int isDirectionKey(char direction/*方向字符*/);
	// 打印地图边框
void printMaze(int num/*如果为1，则输出提示，否则不输出提示*/);
	// 遍历链表到想要的位置
SnakeHeaden* traverseSnakeBody(int length);
	// 最后的结果处理
void last_wait(int num/*接受退出原因并按字典打印*/);
	// 神秘奖励主界面
void WelcomeScreen();
	// 首次进入游戏的介绍
void initTextEffects();
	// 查找光标的横坐标x
int GetConsoleCursorY();

// 关于食物
	// 生成食物位置(没有错误检测)
void initFood();
	// 确定食物位置
void generateFood();
	// 打印食物
void printFood(int num/*如果为1，则输出提示，否则不输出提示*/);/*1是介绍食物*/

#endif