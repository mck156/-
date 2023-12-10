#ifndef SETTINGS_H
#define SETTINGS_H

#pragma warning(disable:4996)
// 宏定义处

#define ROWS 25//行 y的数量 最多29 30要跳框 看不见上边框 最少10行
#define COLS 50//列 x的数量 最多120 121要跳框 要乱码 最少28列
#define BOUNDARY_CHAR '#'// 边界字符
#define SNAKE_HEAD_CHAR 'o' // 蛇的字符
#define FO_CHAR '*'
#define NORMAL_SPEED_ROWS 100 // 行速度
#define NORMAL_SPEED_COLS 200 // 列速度
// 底下四个是方向键
#define UP -1
#define DOWN 1
#define LEFT 0
#define RIGHT 2
#define SPACEBAR 3
#define SNAKEHEIGHT (ROWS - 2) * (COLS - 2) - 1// 蛇身的长度


// 定义结构体

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

// 定义全局变量

SnakeHeaden* head = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// 蛇头指针
int snakelength = 3;// 蛇身体节数
FOOD snake_food;
FOOD snake_foods[(ROWS - 5) * (COLS - 10)];
int snake_Point = 0;

HANDLE wHnd; /* write (output) handle */
HANDLE rHnd; /* read (input handle */

#endif // !SETTINGS_H

