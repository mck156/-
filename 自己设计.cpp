#include "something.h"

void disableCursor() {
	CONSOLE_CURSOR_INFO cursorAttributes;// ����ر�����������洢���йع�����Ե���Ϣ
	cursorAttributes.bVisible = 0;// ����Ƿ�ɼ����ɼ�Ϊ1�����ɼ�Ϊ0
	cursorAttributes.dwSize = 1;// ������Ϊ1���Ҳ���������ʲô��˼��
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);// �漰����̨���
	SetConsoleCursorInfo(outputHandle, &cursorAttributes);// �ѹ����Ϣ���ǵ�����̨�ϲ����
}
void printsnake() {	
	// ���߽��б�������ӡ
	SnakeHeaden* current = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));
	current = head;
	while (current != NULL) { 
		moveToXY(current->index_COLS, current->index_ROWS);
		printf("%c", current->data);
		current = current->next;
	}
	free(current);
	if (head->index_COLS <= COLS / 2) {
		moveToXY(head->index_COLS - 10, head->index_ROWS);
		printf("������ͷ!");
		Sleep(2000);
		moveToXY(head->index_COLS - 10, head->index_ROWS);
		printf("         ");
	}
	else {
		moveToXY(head->index_COLS + 1, head->index_ROWS);
		printf("������ͷ!");
		Sleep(2000);
		moveToXY(head->index_COLS + 1, head->index_ROWS);
		printf("         ");
	}	
}
void printMaze() {
	// ��һ��
	for (int j = 0; j < COLS; j++) {
		moveToXY(j, 0);
		printf("%c", BOUNDARY_CHAR);
		moveToXY(COLS - 1 - j, ROWS - 1);
		printf("%c", BOUNDARY_CHAR);
		Sleep(10);
	}
	// ��һ�к�β��
	for (int j = 1; j < ROWS - 1; j++) {
		moveToXY(0, ROWS - 1 - j);
		printf("%c", BOUNDARY_CHAR);
		moveToXY(COLS - 1, j);
		printf("%c", BOUNDARY_CHAR);
		Sleep(20);
	}
	moveToXY(1, 1);
	printf("���Ǳ߿�Ŷ��");
	Sleep(2000);
	moveToXY(1, 1);
	printf("            ");
}
void initFood() {
	srand(time(NULL));
	// �������ʳ��λ��
	snake_food.FOOD_COLS = rand() % (COLS - 2) + 1;
	snake_food.FOOD_ROWS = rand() % (ROWS - 2) + 1;
	// �洢or����ʳ���ַ�
	snake_food.data = FO_CHAR;
}
void generateFood() {
	initFood();
	// ���ʳ���Ƿ�����������(λ����ͬ) ��������б���
	SnakeHeaden* current = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// 
	current = head;
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
void printFood(int num) {
	moveToXY(snake_food.FOOD_COLS, snake_food.FOOD_ROWS);
	printf("%c", snake_food.data);
	if (num == 1) {
		if (snake_food.FOOD_COLS <= COLS / 2) {
			printf("����ʳ�");
			Sleep(2000);
			for (int i = 1; i <= 10; i++) {
				moveToXY(snake_food.FOOD_COLS + i, snake_food.FOOD_ROWS);
				printf(" ");
			}		
		}
		else {
			moveToXY(snake_food.FOOD_COLS - 10, snake_food.FOOD_ROWS);
			printf("����ʳ�");
			Sleep(2000);
			moveToXY(snake_food.FOOD_COLS - 10, snake_food.FOOD_ROWS);
			printf("          ");
		}
	}


}
void initializeSnake() {
	// ȡ��ͷ��������߽ڵ�	
	SnakeHeaden* p = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// p�ǵڶ����ڵ�	
	SnakeHeaden* q = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// q�ǵ������ڵ�

	// ���������ϵ head - p - q
	head->next = p;
	p->next = q;
	q->next = NULL;
	// ��ͷλ���ڵ�ͼ�м���������
	srand(time(NULL));
	if (COLS % 2 != 0) {// ������
		head->index_COLS = rand() % 4 + (COLS / 2 - 0.5 - 2);// 0.5�ܱ�֤����Ϊ�������Դﵽ"COLS / 2 - 2"��Ч��
	}
	else {// ż����
		head->index_COLS = rand() % 4 + (COLS / 2 - 2);
	}
	if (ROWS % 2 != 0) {// ������
		head->index_ROWS = rand() % 4 + (ROWS / 2 - 0.5 - 2);
	}
	else {// ż����
		head->index_ROWS = rand() % 4 + (ROWS / 2 - 2);
	}
	// ��ȡ���������е�λ�� �ж�����or��������ʣ�µ����� ����������getHemisphere�洢
	int getHemisphere;// ����or������������
	if (head->index_ROWS - ROWS / 2 <= 2) {// ������
		getHemisphere = -1;// ������ ��-1
	}
	else {// ������
		getHemisphere = 1;// ������ ��+1
	}

	// ���ɺ�������
	p->index_ROWS = head->index_ROWS + getHemisphere;
	q->index_ROWS = p->index_ROWS + getHemisphere;
	p->index_COLS = q->index_COLS = head->index_COLS;// ������ʱ�б仯���в���
	head->data = p->data = q->data = SNAKE_HEAD_CHAR;// ���ߵ��ַ�

	// ����ʳ��
	generateFood();
	
	// ��ӡʳ�����
	printFood(1);// ��һ�δ�ӡʳ����Ҫ����
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
			if (head->index_COLS >= COLS / 2) {// ͷ�ڵ����Ұ�ߣ��������ƶ�
				*Direction_chose = LEFT;
			}
			else {// ͷ�ڵ������ߣ��������ƶ�
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
int move_snake(int current) {
	
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
		return 1;
	}

	// ����Ƿ�ײ���Լ�������
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
	if (head->index_COLS == snake_food.FOOD_COLS && head->index_ROWS == snake_food.FOOD_ROWS) {// ����Ƿ�Ե�ʳ��
		generateFood();// ����ʳ��
		printFood(0);// ��ӡʳ������δ�ӡʳ����ý���
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

	Sleep(100);
	return 0;
}

int main() {
	disableCursor();
	printMaze();
	initializeSnake();
	int currentDirection = -2;// ���ƶ��еķ���
	int num;
	while (1) {
		newDirection(&currentDirection);
		if((num = move_snake(currentDirection))!=0) break;
	}
	moveToXY(0, ROWS);// ���׿���һ����ǰ��
	if (num == 1) {
		printf("�����߽磬��Ϸ������");
	}
	else if (num == 2) {
		printf("�����Լ������壬��Ϸ������");
	}
	return 0;
}