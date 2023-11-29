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


// 关于模式

	//  第一次进入程序,即游戏体验 and 无限模式
void initScreen(int* currentDirection, int num/*看是不是首次进入程序*/);
	// 闯关模式
//void ChallengeMode();
	// 神秘模式
//void MysteryMode();

// 关于蛇

	// 移动蛇
void moveToXY(int x, int y);
	// 确定蛇移动的方向。包括：对上下左右键盘输入转码的整个程序，各种情况的错误处理
void newDirection(int* Direction_chose/*与移动程序交互的变量*/);
	// 收到上下左右指示后移动蛇头
int move_snake(int current/*与移动程序交互的变量*/, int num/*1时有进主界面的程序，0时没有*/);
	// 遍历链表 打印蛇
void printsnake(int num);
	// 首次进入程序 生成蛇和食物
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
void last_wait(int num/*接收退出原因并按字典打印*/, int choice/*体验程序过程中死亡的玩家为1 否则为0*/);
	// 神秘奖励 主界面的文字打印
void WelcomeScreen(int* currentDirection);
	// 首次进入游戏的介绍
void initTextEffects();
	// 查找光标的横坐标x
int GetConsoleCursorY();
	// 清空缓存区
void ClearInput();

// 关于食物
	// 生成食物位置(没有错误检测)
void initFood();
	// 生成食物位置
void generateFood();
	// 打印食物
void printFood(int num/*如果为1，则输出提示，否则不输出提示*/);/*1是介绍食物*/

#endif