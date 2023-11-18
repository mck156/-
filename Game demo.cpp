#include "PlayGames.h"

void disableCursor() {
	CONSOLE_CURSOR_INFO cursorAttributes;// 具体地表明这个变量存储了有关光标属性的信息
	cursorAttributes.bVisible = 0;// 光标是否可见，可见为1，不可见为0
	cursorAttributes.dwSize = 1;// 像素设为1（我不懂像素是什么意思）
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);// 涉及控制台输出
	SetConsoleCursorInfo(outputHandle, &cursorAttributes);// 把光标信息覆盖到控制台上并输出
}
void printsnake(int num) {
	// 对蛇进行遍历并打印
	SnakeHeaden* current = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));
	current = head;
	while (current != NULL) {
		moveToXY(current->index_COLS, current->index_ROWS);
		printf("%c", current->data);
		current = current->next;
	}
	free(current);

	// 首次进入会有提示（提示本示）因为生成蛇头只在游戏开始 所以不用设置变量 除非改变玩法
	if (num == 1) {
		if (head->index_COLS <= COLS / 2) {// 蛇头在左半边 字在右半边 箭头指向左 
			moveToXY(head->index_COLS + 1, head->index_ROWS);
			printf("←这是蛇头！");
			Sleep(2000);
			moveToXY(head->index_COLS + 1, head->index_ROWS);
			printf("            ");
		}
		else {
			moveToXY(head->index_COLS - 12, head->index_ROWS);
			printf("这是蛇头!→");
			Sleep(2000);
			moveToXY(head->index_COLS - 12, head->index_ROWS);
			printf("           ");
		}
	}
}
int GetConsoleCursorY() {
	// 获取控制台句柄
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	// 获取光标位置
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);// 把光标的信息给了csbi
	// 返回光标位置的x坐标
	return csbi.dwCursorPosition.X;
}
void initTextEffects() {
	char texts[] = "你好，这是一个贪吃蛇的游玩引导程序，旨在学习贪吃蛇的基本操作以及体验贪吃蛇的玩法！\b请提前将输入法切换至英语模式，并用鼠标点击一下屏幕\b请不要调整窗口的大小，以免出现以外状况！\b现在开始游戏,祝你玩的开心\b";
	char* text = texts;
	// 用指针指向字符，进行比对
	while (*text != '\0') {// 字符数组末尾
		if (*text == '\b') {// 回退
			Sleep(2000);// 一秒钟的暂停 模拟光标闪烁
			for (int i = GetConsoleCursorY(); i >=0 ; i--) {
				// 模拟删除效果
				printf("\b\b  \b\b");
				Sleep(50);
			}			
		} else {
			printf("%c", *text);
		}
		fflush(stdout);// 实时把缓存区的内容输出到屏幕上
		Sleep(50);// 50毫秒延时
		text++;// 切换到下一个字符
	}
	return;
}
void printMaze(int num) {
	// 第一排
	for (int j = 0; j < COLS; j++) {
		moveToXY(j, 0);
		printf("%c", BOUNDARY_CHAR);
		moveToXY(COLS - 1 - j, ROWS - 1);
		printf("%c", BOUNDARY_CHAR);
		Sleep(10);// 边框
	}
	// 第一列和尾列
	for (int j = 1; j < ROWS - 1; j++) {
		moveToXY(0, ROWS - 1 - j);
		printf("%c", BOUNDARY_CHAR);
		moveToXY(COLS - 1, j);
		printf("%c", BOUNDARY_CHAR);
		Sleep(20);
	}

	// 首次进入会有提示（提示本示）
	if (num == 1) {
		moveToXY(COLS, 1);
		printf("←这是边框！");
		Sleep(2000);
		moveToXY(COLS, 1);
		printf("              ");
	}
}
void initFood() {
	srand(time(NULL));
	// 随机生成食物位置
	snake_food.FOOD_COLS = rand() % (COLS - 2) + 1;
	snake_food.FOOD_ROWS = rand() % (ROWS - 2) + 1;
	// 存储or设置食物字符
	snake_food.data = FO_CHAR;
}
void generateFood() {
	initFood();
	// 检查食物是否生在蛇身上(位置相同) 对蛇身进行遍历
	SnakeHeaden* current = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// 
	current = head;
	while (current != NULL) {
		if (current->index_COLS == snake_food.FOOD_COLS && current->index_ROWS == snake_food.FOOD_ROWS || head->index_ROWS == snake_food.FOOD_ROWS) {
			initFood();// 重新生成食物位置
			current = head;// 重新开始比较
			continue;
		}
		current = current->next;
	}
	free(current);
}
void printFood(int num) {
	moveToXY(snake_food.FOOD_COLS, snake_food.FOOD_ROWS);
	printf("%c", snake_food.data);

	// 首次进入会有提示（提示本示）
	if (num == 1) {
		if (snake_food.FOOD_COLS <= COLS / 2) {// 食物在左 字在右 箭头向左
			moveToXY(snake_food.FOOD_COLS + 1, snake_food.FOOD_ROWS);
			printf("←这是食物！");
			Sleep(2000);
			moveToXY(snake_food.FOOD_COLS + 1, snake_food.FOOD_ROWS);
			printf("            ");
		}
		else {// 食物在右 字在左 箭头向右
			moveToXY(snake_food.FOOD_COLS - 12, snake_food.FOOD_ROWS);
			printf("这是食物！→");
			Sleep(2000);
			moveToXY(snake_food.FOOD_COLS - 12, snake_food.FOOD_ROWS);
			printf("            ");
		}
	}
}
void ClearInput() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);// 获取句柄
	FlushConsoleInputBuffer(hStdin);// 清空缓存区
}
void initializeSnake() {
	// 取蛇头后的两个蛇节点	
	SnakeHeaden* p = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// p是第二个节点	
	SnakeHeaden* q = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// q是第三个节点

	// 建立链表关系 head - p - q
	head->next = p;
	p->next = q;
	q->next = NULL;
	// 蛇头位置在地图中间三行生成
	srand(time(NULL));
	if (COLS % 2 != 0) {// 奇数列
		head->index_COLS = rand() % 4 + (COLS / 2 - 0.5 - 2);// 0.5能保证减数为整数，以达到"COLS / 2 - 2"的效果
	}
	else {// 偶数列
		head->index_COLS = rand() % 4 + (COLS / 2 - 2);
	}
	if (ROWS % 2 != 0) {// 奇数行
		head->index_ROWS = rand() % 4 + (ROWS / 2 - 0.5 - 2);
	}
	else {// 偶数行
		head->index_ROWS = rand() % 4 + (ROWS / 2 - 2);
	}
	// 获取蛇在三行中的位置 判断向上or向下生成剩下的蛇身 并将方向用getHemisphere存储
	int getHemisphere;// 向上or向下生成蛇身
	if (head->index_ROWS - ROWS / 2 <= 2) {// 上两行
		getHemisphere = -1;// 蛇往上 行-1
	}
	else {// 第三行
		getHemisphere = 1;// 蛇往下 行+1
	}

	// 生成后两节蛇
	p->index_ROWS = head->index_ROWS + getHemisphere;
	q->index_ROWS = p->index_ROWS + getHemisphere;
	p->index_COLS = q->index_COLS = head->index_COLS;// 生成蛇时行变化，列不变
	head->data = p->data = q->data = SNAKE_HEAD_CHAR;// 存蛇的字符

	// 生成食物
	generateFood();
	
	// 打印食物和蛇
	printFood(1);// 第一次打印食物需要介绍
	printsnake(1);

	// 打印旁边的分数（目前是节数）
	moveToXY(COLS + 4, 4);
	printf("蛇身节数：%d", snakelength); // 节数的坐标（COLS + 14, 4）

	ClearInput();
}
void moveToXY(int x, int y) {
	COORD position;// 用position放x和y的坐标
	HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);// 将界面上蛇头的x y值赋给OutputHandle
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(OutputHandle, position);// 将界面上蛇头的xy值移动到position上
}

int isDirectionKey(char direction/*方向字符*/) {
	if (direction == 'w' || direction == 'W') {
		return UP;
	}
	else if (direction == 's' || direction == 'S') {
		return DOWN;
	}
	else if (direction == 'a' || direction == 'A') {
		return LEFT;
	}
	else if (direction == 'd' || direction == 'D') {
		return RIGHT;
	}
	else {
		return 7;
	}
}
void newDirection(int* Direction_chose) {
	if (!_kbhit()) {// 没有键入
		if (*Direction_chose == -2) {// 首次进入没按键
			if (head->index_COLS >= COLS / 2) {// 头节点在右半边，则往左移动
				*Direction_chose = LEFT;
			}
			else {// 头节点在左半边，则往右移动
				*Direction_chose = RIGHT;
			}
		}
		// 如果是上下左右但没键入，我就可以沿原方向继续循环了
	}
	else {
		char enteringDirection;/*键盘输入的方向字符*/
		enteringDirection = _getch();
		if (enteringDirection == ' ') {
			char space = '$';
			while (space != ' ') {
				space = _getch();
				if (space == ' ') return;
			}
		}
		if (isDirectionKey(enteringDirection) == 7) return;// 比对失败，退出函数
		*Direction_chose = isDirectionKey(enteringDirection);// 把wsad变成对应数字
	}
}
SnakeHeaden* traverseSnakeBody(int length) {// 遍历链表到想要的位置
	SnakeHeaden* current = head;
	int num_ber = 1;
	while (current != NULL) {
		if (num_ber == length) {
			return current;
		}
		num_ber++;
		current = current->next;
	}
	return NULL;
}
int move_snake(int current, int num) {
	
	// 复制蛇头的位置
	int prev_head_row = head->index_ROWS;// 蛇头的行值
	int prev_head_col = head->index_COLS;// 蛇头的列值

	// 移动蛇头，但蛇头位置需要保留，所以前面要复制蛇头的位置
	if (current == UP || current == DOWN) {
		head->index_ROWS += current;
	}
	else if (current == LEFT || current == RIGHT) {
		head->index_COLS += current - 1;// -1是让上和左、下和右有区分，所以左右比上下大1，计算机也识别的出来
	}

	// 检测是否触碰边界
	if (head->index_ROWS <= 0/*上边框*/ || head->index_ROWS >= ROWS - 1 /*下边框*/ || head->index_COLS <= 0/*左边框*/ || head->index_COLS >= COLS - 1/*右边框*/) {
		return 1;
	}

	// 检查是否撞到自己的身体
	SnakeHeaden* current_body = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));
	current_body = head->next;
	while (current_body != NULL) {
		if (head->index_ROWS == current_body->index_ROWS && head->index_COLS == current_body->index_COLS) {
			free(current_body);
			return 2;
		}
		current_body = current_body->next;
	}
	free(current_body);

	SnakeHeaden* new_head = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));

	// 检查是否吃掉食物
	if (head->index_COLS == snake_food.FOOD_COLS && head->index_ROWS == snake_food.FOOD_ROWS) {
		generateFood();// 生成食物
		printFood(0);// 打印食物，其他次打印食物，不用介绍
		new_head->data = SNAKE_HEAD_CHAR;// 新建节点要赋值
		snakelength++;

		// 改变蛇节的计数
		moveToXY(COLS + 14, 4);
		printf("%d", snakelength);
	}

	// 正常蛇的移动
	else { 		
		// 找到蛇尾节点并擦除
		new_head = traverseSnakeBody(snakelength)/*这里的snakelength-1是下标输入*/;
		moveToXY(new_head->index_COLS, new_head->index_ROWS); printf(" ");// 擦除末尾节点
		// 倒数第二个结点指向空
		SnakeHeaden* second_end = traverseSnakeBody(snakelength - 1);
		second_end->next = NULL;
	}
	// 把节点填在原本第二个节点上
		// 改变节点位置
	new_head->index_ROWS = prev_head_row;
	new_head->index_COLS = prev_head_col;
		// 改变链表逻辑
	new_head->next = head->next;
	head->next = new_head;

	// 把第一个结点打印出来
	moveToXY(head->index_COLS, head->index_ROWS); printf("%c", head->data);

	// 检查长度是否为20 若为20 则跳转到另一个界面 当前仅为刷新界面+在中间写"闯关成功"
	if (snakelength == 5 && num == 1) {
		return 3;
	}
	
	if (current == LEFT || current == RIGHT) {
		Sleep(NORMAL_SPEED_ROWS);
	}
	else if (current == UP || current == DOWN) {
		Sleep(NORMAL_SPEED_COLS);
	}
	return 0;
}

void last_wait(int num) {
	moveToXY(0, ROWS);// 到底框下一排最前面
	if (num == 1) {
		printf("碰到边界，进入结算程序");
	}
	else if (num == 2) {
		printf("碰到自己的身体，进入结算程序");
	}
	else if (num == 3) {
		printf("闯关成功！进入主界面");
	}
	int n = 0;
	moveToXY(0, ROWS + 1);// 到底框下一排最前面
	printf("...%d%%",n);
	while (n < 100) {
		Sleep(100);
		moveToXY(3, ROWS + 1);
		printf("%d%%", ++n);
	}
	Sleep(100);
	system("cls");

	// 游戏结束的动画
	if (num == 1 || num == 2) {
		printMaze(0);
		moveToXY(COLS / 2 - 4, ROWS / 2 - 1);
		printf("游戏结束");
		moveToXY(0, ROWS);
		exit(0);
	}
	//跳转到主界面 实现方式：先跳转到主程序 再开始介绍
	else if (num == 3) {
		return;
	}
}

void WelcomeScreen(int* currentDirection) {
	printf("=======================================\n");
	printf("          欢迎来到贪吃蛇游戏           \n");
	printf("=======================================\n");
	printf("              请选择功能               \n");
	printf("                                       \n");
	printf("              1. 无限模式              \n");
	printf("              2. 闯关模式              \n");
	printf("              3. 神秘模式              \n");
	printf("                                       \n");
	printf("=======================================\n");
	printf("                                       \n");
	printf("     请做出你的选择：");
	int choice;
	ClearInput();
	scanf("%d", &choice);
	system("cls");
	switch (choice) {
	case 1:
		InfiniteMode(currentDirection);
		break;
	default:
		break;
	}
}

void InfiniteMode(int* currentDirection) {
	printMaze(0);
	printsnake(0);
	generateFood();
	printFood(0);
	// 打印旁边的分数（目前是节数）
	moveToXY(COLS + 4, 4);
	printf("蛇身节数：%d", snakelength); // 节数的坐标（COLS + 14, 4）
	moveToXY(COLS + 4, 5);
	printf("倒数 ");
	for (int i = 3; i > 0; i--) {
		moveToXY(COLS + 9, 5);
		printf("%d", i);
		Sleep(1000);
	}
	moveToXY(COLS + 4, 5);
	printf("      ");
	int choice;
	while (1) {
		newDirection(currentDirection);
		if ((choice = move_snake(*currentDirection,0)) != 0) break;
	}
	last_wait(choice);
	moveToXY(0, ROWS);
}

void initScreen(int* currentDirection, int num/*看是不是首次进入程序*/) {
	printMaze(num);
	initializeSnake();
	int choice;
	while (1) {
		newDirection(currentDirection);
		if((choice = move_snake(*currentDirection,1)) != 0) break;
	}
	last_wait(choice);// 结算程序结束后，满足惊喜条件就去游戏主界面，不满足直接走了
}

int main() {
	initTextEffects();// 介绍程序
	disableCursor();
	int currentDirection = -2;// 蛇移动中的方向
	initScreen(&currentDirection, 1);
	WelcomeScreen(&currentDirection);
	return 0;
}