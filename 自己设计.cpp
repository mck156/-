#include "stdio.h"
#include "something.h"

void disableCursor() {
	CONSOLE_CURSOR_INFO cursorAttributes;// ����ر�����������洢���йع�����Ե���Ϣ
	cursorAttributes.bVisible = 0;// ����Ƿ�ɼ����ɼ�Ϊ1�����ɼ�Ϊ0
	cursorAttributes.dwSize = 1;// ������Ϊ1���Ҳ���������ʲô��˼��
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);// �漰����̨���
	SetConsoleCursorInfo(outputHandle, &cursorAttributes);// �ѹ����Ϣ���ǵ�����̨�ϲ����
}
void wallgenerateMazeWalls() {
	// ��/β��
	for (int i = 0; i < COLS/*i���±꣬���Ա߽���COLS-1*/; i++) { /*iΪʲô�Ǵ�0��COLS-1��*/
		mazewallCharacter[0][i] = mazewallCharacter[ROWS - 1][i] = BOUNDARY_CHAR;
	}
	// ������β���м�ı߿���ո�
	for (int j/*��Ӧyֵ*/ = 1; j < ROWS - 1; j++)/*������β���м�*/ { /*jΪʲô�Ǵ�1��ROWS-2��*/
		for (int i/*��Ӧxֵ*/ = 0; i < COLS; i++)/*ÿ���е�ÿ���ַ�*/ { /*iΪʲô�Ǵ�0��COLS-1��*/
			if (i == 0/*����*/ || i == COLS - 1/*β��*/) {
				mazewallCharacter[j][i] = BOUNDARY_CHAR;
				continue;
			}
			else {
				mazewallCharacter[j][i] = ' ';
			}
		}
	}
	// ��ӡ
	printMaze();
}
void printsnake() {	
	SnakeHeaden* current = head;// ����ѭ������
	while (current != NULL) { // ѭ�������һ��ָ��ʱֹͣ
		moveToXY(current->index_COLS, current->index_ROWS);
		printf("%c", current->data);
		current = current->next;
	}
}
void printMaze() {
	for (int j = 0; j < ROWS; j++) {
		for (int i = 0; i < COLS; i++) {
			printf("%c", mazewallCharacter[j][i]);
		}
		printf("\n");
	}
}
void initFood() {
	srand(time(NULL));
	// �������ʳ��λ��
	snake_food.FOOD_COLS = rand() % (COLS - 2) + 1;
	snake_food.FOOD_ROWS = rand() % (ROWS - 2) + 1;
	// ����ʳ���ַ�
	snake_food.data = FO_CHAR;
}
void generateFood() {
	initFood();// ����ʳ��λ�� 
	// ���ʳ�������Ƿ�λ����ͬ
	SnakeHeaden* current = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// ��̬�洢
	current = head;// ��ʼ��
	while (current != NULL) {
		if (current->index_COLS == snake_food.FOOD_COLS && current->index_ROWS == snake_food.FOOD_ROWS) {
			initFood();// ��������ʳ��λ��
			current = head;// ���¿�ʼ�Ƚ�
			continue;
		}
		current = current->next;
	}
	free(current);
}
void printFood() {
	moveToXY(snake_food.FOOD_COLS, snake_food.FOOD_ROWS);
	printf("%c", snake_food.data);
}
void initializeSnake() {
	// ȡ��ͷ��������߽ڵ�	
	SnakeHeaden* p = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// p�ǵڶ����ڵ�	
	SnakeHeaden* q = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// q�ǵ������ڵ�

	// ���������������ϵ
	head->next = p;
	p->next = q;
	q->next = NULL;
	// ���ȡ��ͷλ��
	srand(time(NULL));
	if (COLS % 2 != 0) {
		head->index_COLS = rand() % 4 + (COLS / 2 - 0.5 - 2);// 0.5���Ǹ���������
	}
	else {
		head->index_COLS = rand() % 4 + (COLS / 2 - 2);
	}
	if (ROWS % 2 != 0) {
		head->index_ROWS = rand() % 4 + (ROWS / 2 - 0.5 - 2);
	}
	else {
		head->index_ROWS = rand() % 4 + (ROWS / 2 - 2);
	}	
	// �ж������м������е���һ�ţ�����getHemisphere�洢
	int getHemisphere;// ���ݸ��������ȡ�õ����ڵİ���
	if (head->index_ROWS - ROWS / 2 <= 2) {// �м���м�����һ��
		getHemisphere = -1;// ������ ��-1
	}
	else {
		getHemisphere = 1;// ������ ��+1
	}

	// ������/�����ɵĴ���
	p->index_ROWS = head->index_ROWS + getHemisphere;
	q->index_ROWS = p->index_ROWS + getHemisphere;
	p->index_COLS = q->index_COLS = head->index_COLS;// �����ƶ�����COLS����

	// �����ַ������ڵ���
	head->data = p->data = q->data = SNAKE_HEAD_CHAR;

	// ����ʳ��
	generateFood();
	
	// ��ӡʳ�����
	printFood();
	printsnake();
}
void moveToXY(int x, int y) {
	COORD position;// ��position��x��y������
	HANDLE OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);// ����������ͷ��x yֵ����OutputHandle
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(OutputHandle, position);// ����������ͷ��xyֵ�ƶ���position��
}

int isDirectionKey(char direction/*�����ַ�*/) {
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
	if (!_kbhit()) {// û�м���
		if (*Direction_chose == -2) {// �״ν���û����
			if (head->index_COLS >= COLS / 2) {// ͷ�ڵ����Ұ�㣬�������ƶ�
				*Direction_chose = LEFT;
			}
			else {// ͷ�ڵ������㣬�������ƶ�
				*Direction_chose = RIGHT;
			}
		}
		// ������������ҵ�û���룬�ҾͿ�����ԭ�������ѭ����
	}
	else {
		char enteringDirection;/*��������ķ����ַ�*/
		enteringDirection = _getch();
		if (isDirectionKey(enteringDirection) == 7) return;// �ȶ�ʧ�ܣ��˳�����
		*Direction_chose = isDirectionKey(enteringDirection);// ��wsad��ɶ�Ӧ����
	}
}
SnakeHeaden* traverseSnakeBody(int length) {// ����������Ҫ��λ��
	SnakeHeaden* current = head;
	int num = 1;
	while (current != NULL) {
		if (num == length) {
			return current;
		}
		num++;
		current = current->next;
	}
	return NULL;
}
void move_snake(int current) {
	
	// ������ͷ��λ��
	int prev_head_row = head->index_ROWS;// ��ͷ����ֵ
	int prev_head_col = head->index_COLS;// ��ͷ����ֵ

	// �ƶ���ͷ������ͷλ����Ҫ����������ǰ��Ҫ������ͷ��λ��
	if (current == UP || current == DOWN) {
		head->index_ROWS += current;
	}
	else if (current == LEFT || current == RIGHT) {
		head->index_COLS += current - 1;// -1�����Ϻ����º��������֣��������ұ����´�1�������Ҳʶ��ĳ���
	}

	// ����Ƿ����߽�
	if (head->index_ROWS <= 0/*�ϱ߿�*/ || head->index_ROWS >= ROWS - 1 /*�±߿�*/ || head->index_COLS <= 0/*��߿�*/ || head->index_COLS >= COLS - 1/*�ұ߿�*/) {
		moveToXY(0, ROWS);// ���׿���һ����ǰ��
		printf("�����߽磬��Ϸ������");
		exit(0);
	}

	// ����Ƿ�ײ���Լ�������
	SnakeHeaden* current_body = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));
	current_body = head->next;
	while (current_body != NULL) {
		if (head->index_ROWS == current_body->index_ROWS && head->index_COLS == current_body->index_COLS) {
			free(current_body);
			moveToXY(0, ROWS);// ���׿���һ����ǰ��
			printf("�����Լ������壬��Ϸ������");
			exit(0);
		}
		current_body = current_body->next;
	}
	free(current_body);

	// ����Ƿ�Ե�ʳ��
	SnakeHeaden* new_head = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));
	if (head->index_COLS == snake_food.FOOD_COLS && head->index_ROWS == snake_food.FOOD_ROWS) {
		generateFood();// ����ʳ��
		printFood();// ��ӡʳ��
		new_head->data = SNAKE_HEAD_CHAR;// �½��ڵ�Ҫ��ֵ
		snakelength++;
	}
	else { // �����ߵ��ƶ�
		
		// �ҵ���β�ڵ㲢����
		new_head = traverseSnakeBody(snakelength)/*�����snakelength-1���±�����*/;
		moveToXY(new_head->index_COLS, new_head->index_ROWS); printf(" ");// ����ĩβ�ڵ�
		// �����ڶ������ָ���
		SnakeHeaden* second_end = traverseSnakeBody(snakelength - 1);
		second_end->next = NULL;
	}
	// �ѽڵ�����ԭ���ڶ����ڵ���
		// �ı�ڵ�λ��
	new_head->index_ROWS = prev_head_row;
	new_head->index_COLS = prev_head_col;
		// �ı������߼�
	new_head->next = head->next;
	head->next = new_head;

	// �ѵ�һ������ӡ����
	moveToXY(head->index_COLS, head->index_ROWS); printf("%c", head->data);

	Sleep(200);
}

int main() {
	disableCursor();// ֻ�ܷ���λ
	wallgenerateMazeWalls();
	initializeSnake();
	int currentDirection = -2;// ���ƶ��еķ���
	while (1) {
		newDirection(&currentDirection);
		move_snake(currentDirection);
	}
	moveToXY(0, ROWS);// ���׿���һ����ǰ��
	printf("�����߽磬��Ϸ������");
	system("pause");
	return 0;
}