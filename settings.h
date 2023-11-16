#ifndef SETTINGS_H
#define SETTINGS_H

// �궨�崦

#define ROWS 20//�� y������ ���29 30Ҫ���� �������ϱ߿� ����10��
#define COLS 70//�� x������ ���120 121Ҫ���� Ҫ���� ����28��
#define BOUNDARY_CHAR '#'// �߽��ַ�
#define SNAKE_HEAD_CHAR 'o' // �ߵ��ַ�
#define FO_CHAR '*'
#define NORMAL_SPEED 100
// �����ĸ��Ƿ����
#define UP -1
#define DOWN 1
#define LEFT 0
#define RIGHT 2
#define SNAKEHEIGHT (ROWS - 2) * (COLS - 2) - 1// ����ĳ���

// ����ṹ��

typedef struct SnakeHeaden { // �ߵĽṹ
	int index_COLS;// ��ͷ���� xֵ
	int index_ROWS;// ��ͷ���� yֵ
	char data;// ���ߵ��ַ�
	SnakeHeaden* next;// ָ����һ�������ָ��
};
typedef struct FOOD { // ʳ��Ľṹ
	int FOOD_COLS;// ʳ�����
	int FOOD_ROWS;// ʳ�����
	char data;// ��ʳ����ַ�
};

// ����ȫ�ֱ���

SnakeHeaden SnakeHead;// ��ͷ������Ĵ���
SnakeHeaden* head = (SnakeHeaden*)malloc(sizeof(SnakeHeaden));// ��ͷ��ָ��
int snakelength = 3;// ���������
FOOD snake_food;

#endif // !SETTINGS_H

