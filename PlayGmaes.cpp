#include "PlayGames.h"

void disableCursor() {
	CONSOLE_CURSOR_INFO cursorAttributes;// 具体地表明这个变量存储了有关光标属性的信息
	cursorAttributes.bVisible = 0;// 光标是否可见，可见为1，不可见为0
	cursorAttributes.dwSize = 1;// 像素设为1（我不懂像素是什么意思）
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);// 涉及控制台输出
	SetConsoleCursorInfo(outputHandle, &cursorAttributes);// 把光标信息覆盖到控制台上并输出
}

void printsnake(int num) {
	// 遍历并打印蛇
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

int story_addsnake(SnakeHeaden* currented/*当前位置*/, int timenum/*几节蛇*/) {
// 找到蛇尾位置需要找到当前蛇的最后一个位置，即需要遍历 由于需要移动 则改变原来位置 到新位置上
	SnakeHeaden* current = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// 遍历中的当前位置
	current = head;
	int prev_COLS, prev_ROWS;// 存放新建蛇尾的xy坐标
	while (current != NULL) {// 保证当前位置不是空
		if (current->next == NULL) {// 若下一个位置是空 则蛇尾到了 
			// 复制移动前的节点xy坐标
			prev_COLS = current->index_COLS;
			prev_ROWS = current->index_ROWS;
		}
		current->index_COLS += 1;
		current->index_ROWS = current->index_ROWS;
		if (current->next != NULL) {// 下一个位置不是空位置
			current = current->next;// 由于当前位置一定不是空位置，即探查下一个位置
		}
		else {
			break;
		}
	}
	SnakeHeaden* p = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// 新建蛇尾
	// 设置蛇尾参数
	p->index_COLS = prev_COLS;
	p->index_ROWS = prev_ROWS;
	p->data = SNAKE_HEAD_CHAR;
	p->next = NULL;
	current->next = p;
	timenum++;
	printsnake(0);
	Sleep(250);// 间隔
	if (timenum < 5) {// 最多5节蛇 timenum=5说明已经有5节蛇要退出 显然timenum≠5
		return story_addsnake(current, timenum);
	}
	else {
		free(current);// 将current注销掉
		return timenum;
	}
}

void initTextEffects() {
	SetConsoleTitle(TEXT("情景介绍"));
	char texts1[] = "你好，这是一个贪吃蛇的游玩引导程序，旨在学习贪吃蛇的基本操作以及体验贪吃蛇的玩法！\b请提前将输入法切换至英语模式，并用鼠标点击一下屏幕\b请不要调整窗口的大小，以免出现以外状况！\b你可以上下左右移动，并按wsad键。\b也可以按空格键暂停\b引导程序结束后会有神秘惊喜哦！\b赶快开始游戏吧！\b";
//	char texts2[] = "";
	char* text = texts1;
	// 用指针指向字符，进行比对
	while (*text != '\0') {// 字符数组末尾
		if (*text == '\b') {// 回退
			Sleep(2000);// 二秒钟的暂停 模拟光标闪烁
			for (int i = GetConsoleCursorY(); i >=0 ; i--) {
				// 模拟删除效果
				printf("\b\b  \b\b");
				Sleep(50);
			}			
		} else {
			printf("%c", *text);
		}
		fflush(stdout);// 实时把缓存区的内容输出到屏幕上
		Sleep(20);// 50毫秒延时
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
	generateFood();
	moveToXY(snake_food.FOOD_COLS, snake_food.FOOD_ROWS);
	printf("%c", snake_food.data);

	// 首次进入 提示
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
	// 蛇头在上半边,蛇身向上生成   蛇头在下半边,蛇身向下生成
	int getHemisphere;// 存储蛇身生成方向 上or下
	if (head->index_ROWS - ROWS / 2 <= 2) {// 上两行
		getHemisphere = -1;// 蛇往上 行-1
	}
	else {// 第三行
		getHemisphere = 1;// 蛇往下 行+1
	}

	// 生成蛇身 上下增加 左右不动
	p->index_ROWS = head->index_ROWS + getHemisphere;
	q->index_ROWS = p->index_ROWS + getHemisphere;
	p->index_COLS = q->index_COLS = head->index_COLS;
	head->data = p->data = q->data = SNAKE_HEAD_CHAR;
	
	printFood(1);// 生成、打印食物 第一次打印食物需要介绍
	printsnake(1);// 打印蛇

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

void newDirection(int* Direction_chose, char* num1) {
	if (!_kbhit()) {// 没有键入
		if (*Direction_chose == -2) {// 首次进入
			if (head->index_COLS >= COLS / 2) {// 蛇头在右半边 往左
				*Direction_chose = LEFT;
			}
			else {// 蛇头在左半边 往右
				*Direction_chose = RIGHT;
			}
		}
		else {
			*num1 = '$';
		}
		// 若上下左右没键入 则不改变方向
	}
	else {
		char enteringDirection = _getch(); // 键盘输入的方向
		// 暂停 空格
		if (enteringDirection == ' ') {
			char space = '$'; // 无效字符
			do {
				space = _getch();
			} while (space != ' '/*这里的条件和单独while循环的时候一样*/);	
			return;
		}
		// 加速
		if (enteringDirection == 'K' || enteringDirection == 'k') {
			*num1 = enteringDirection;
		}
		else {
			*num1 = '$';
		}
		// 不能把*Direction_chose放在if里 如果是错误的值还要重新赋值进去 更麻烦
		if (isDirectionKey(enteringDirection) == 7) return;// 比对失败 若成功继续运行
		*Direction_chose = isDirectionKey(enteringDirection);// 比对成功
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

int move_snake(int current, int num, char* num1) {	
	// 蛇尾要跑到蛇头移动前的位置 所以要复制蛇头坐标
	int prev_head_row = head->index_ROWS;// 蛇头的行值
	int prev_head_col = head->index_COLS;// 蛇头的列值

	// 移动蛇头坐标 
	if (current == UP || current == DOWN) {
		head->index_ROWS += current;
	}
	else if (current == LEFT || current == RIGHT) {
		head->index_COLS += current - 1;// 左-1 右1 但LEFT=0 RIGHT=2 所以要-1
	}

	// 撞墙
	if (head->index_ROWS <= 0/*上边框*/ || head->index_ROWS >= ROWS - 1 /*下边框*/ || head->index_COLS <= 0/*左边框*/ || head->index_COLS >= COLS - 1/*右边框*/) {
		return 1;
	}

	// 撞障碍物


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

	int snakelengthplus = 5;
	SnakeHeaden* new_head = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));

	// 检查是否吃掉食物
	if (head->index_COLS == snake_food.FOOD_COLS && head->index_ROWS == snake_food.FOOD_ROWS) {
		new_head->data = SNAKE_HEAD_CHAR;// 新建节点要赋值
		snakelength++;

		// 改变蛇节的计数
		moveToXY(COLS + 14, 4);
		printf("%d", snakelength);

		// 在游戏主体时增加分数显示
		if (num != 1) {
			moveToXY(COLS + 12, 5);
			if (snakelength < 10) {
				snake_Point += 1;
			}
			else if (snakelength >= 10 && snakelength < 20) {
				snake_Point += 2;
			}
			else if (snakelength >= 20) {
				snake_Point += 3;
			}
			printf("%d", snake_Point);
		}

		// 神秘界面开启时 不打印食物
		if (snakelength != snakelengthplus) {
			printFood(0);// 生成 打印食物
		}		
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
	if (snakelength == snakelengthplus && num == 1) {
		return 3;
	}

	// 横竖的速度
	if (current == LEFT || current == RIGHT) {
		if (*num1 == 'K' || *num1 == 'k') Sleep(NORMAL_SPEED_ROWS / 2);
		else Sleep(NORMAL_SPEED_ROWS);
	}
	else if (current == UP || current == DOWN) {
		if (*num1 == 'K' || *num1 == 'k') Sleep(NORMAL_SPEED_COLS / 2);
		else Sleep(NORMAL_SPEED_COLS);
	}
	return 0;
}

void last_wait(int num, int choice) {
	moveToXY(0, ROWS);// 到底框下一排最前面
	if (num == 1) {
		printf("碰到边界，正在结算中");
	}
	else if (num == 2) {
		printf("碰到自己的身体，正在结算中");
	}
	else if (num == 3) {
		printf("触发神秘奖励！正在打开中");
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
		// 触发神秘奖励 选择无限模式 加分数后 游戏结束
		if (choice != 1) {
			moveToXY(COLS / 2 - 4, ROWS / 2 - 1);
			printf("最终得分：%d", snake_Point);
			moveToXY(COLS / 2 - 4, ROWS / 2 + 1);
		}
		// 体验游戏结束
		else {
			moveToXY(COLS / 2 - 4, ROWS / 2 - 1);
		}
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
//	printf("              2. 闯关模式              \n");
//	printf("              3. 神秘模式              \n");
	printf("                                       \n");
	printf("=======================================\n");
	printf("                                       \n");
	printf("     请做出你的选择：");
	int choice;
	ClearInput();
	while (1) {
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			initScreen(currentDirection, 0);
			break;
		//case 2:
		//	system("cls");
		//	StoryMode();
		//	break;
		default:			
			printf("选错了，重新选。");
			moveToXY(21, 12-1);
			printf("  ");
			moveToXY(21, 12-1);
			ClearInput();
		}
	}
}

void initScreen(int* currentDirection, int num/*看是不是首次进入程序*/) {
	if (num == 1) {
		printMaze(num);
		initializeSnake();
	}
	else {
		printMaze(0);
		printsnake(0);
		printFood(0);

		// 打印旁边的节数和分数
		moveToXY(COLS + 4, 4);
		printf("蛇身节数：%d", snakelength); // 节数的坐标（COLS + 14, 4）
		moveToXY(COLS + 4, 5);
		printf("总分数：0");

		// 倒计时
		moveToXY(COLS + 4, 6);
		printf("倒数 ");
		for (int i = 3; i > 0; i--) {
			moveToXY(COLS + 9, 6);
			printf("%d", i);
			Sleep(1000);
		}
		moveToXY(COLS + 4, 6);
		printf("      ");
	}
	int choice;// 游戏死掉后结尾选项
	char choice_1 = '$';// 游戏的过程选项
	while (1) {
		newDirection(currentDirection, &choice_1);
		if((choice = move_snake(*currentDirection,num, &choice_1)) != 0) break;
	}
	last_wait(choice, num);// 结算程序结束后，满足惊喜条件就去游戏主界面，不满足直接走了
}

int main() {
	disableCursor();
	initTextEffects();// 介绍程序
	int currentDirection = -2;// 蛇移动中的方向
	initScreen(&currentDirection, 1);// 首次进入
	WelcomeScreen(&currentDirection);
	return 0;
}