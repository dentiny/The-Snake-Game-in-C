#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<queue>
#include<iostream>
#include<ctype.h>
#include<string> 
#include<sstream>

#define WIDTH 480
#define HEIGHT 360
#define L_WIDTH 640  //˫��ģʽ
#define L_HEIGHT 480  //˫��ģʽ
#define B_WIDTH 640  //�ϰ�ģʽ
#define B_HEIGHT 480  //�ϰ�ģʽ
#define RADIUS 5
#define FOOD_RADIUS 8
#define DISTANCE 10
#define COLUMN_NUM 46  //COLUMN_NUM=WIDTH/DISTANCE-2;
#define ROW_NUM 34  //ROW_NUM=HEIGHT/DISTANCE-2;
#define L_COLUMN_NUM 62  //˫��ģʽ��L_COLUMN_NUM=L_WIDTH/DISTANCE-2;
#define L_ROW_NUM 46  //˫��ģʽ��L_ROW_NUM=L_HEIGHT/DISTANCE-2;
#define B_COLUMN_NUM 62  //�ϰ�ģʽ��B_COLUMN_NUM=B_WIDTH/DISTANCE-2;
#define B_ROW_NUM 46  //�ϰ�ģʽ��B_ROW_NUM=B_HEIGHT/DISTANCE-2;
#define MIN_FOOD_X 3  //MIN_FOOD_X=1+2;
#define MIN_FOOD_Y 3  //MAX_FOOD_Y=1+2;
#define MAX_FOOD_X 44  //MAX_FOOD_X=COLUMN_NUM-2;
#define MAX_FOOD_Y 32  //MAX_FOOD_Y=ROW_NUM-2;
#define L_MIN_FOOD_X 3  //L_MIN_FOOD_X=1+2;
#define L_MIN_FOOD_Y 3  //L_MAX_FOOD_Y=1+2;
#define L_MAX_FOOD_X 60  //L_MAX_FOOD_X=L_COLUMN_NUM-2;
#define L_MAX_FOOD_Y 44  //L_MAX_FOOD_Y=L_ROW_NUM-2;
#define B_MIN_FOOD_X 3  //B_MIN_FOOD_X=1+2;
#define B_MIN_FOOD_Y 3  //B_MAX_FOOD_Y=1+2;
#define B_MAX_FOOD_X 60  //B_MAX_FOOD_X=B_COLUMN_NUM-2;
#define B_MAX_FOOD_Y 44  //B_MAX_FOOD_Y=B_ROW_NUM-2;
#define INIT_LEN 6  //�ߵĳ�ʼ����
#define L_INIT_LEN 4  //˫��ģʽ�ߵĳ�ʼ����
#define TIME_BONUS 5  //����ʱ�䣬˫��ģʽʱ��ɵ�
#define MAX_TIME_BONUS 20  //�����ʱ��
#define MIN_TIME_BONUS 5  //��С����ʱ��
#define BONUS_SCORE 150  //��������
#define MAX_BONUS_SCORE 200  //���������
#define MIN_BONUS_SCORE 20  //��С��������
#define DERIVED_SCORE 50  //��ʳ��۳�BONUS
#define F_FOOD 100  //��������
#define F_FOOD_DOUBLE_MODE 50  //˫��ģʽ��������
#define F_FOOD_FIRST_ROUND 80  //�ϰ�ģʽ��һ�ֵ�������
#define F_FOOD_SECOND_ROUND 100  //�ϰ�ģʽ�ڶ��ֵ�������
//����һ���Ѷȣ���һ��ͨ������Ϊ1500���ڶ���Ϊ3500
#define FIRST_REQUIRED_SCORE 1000  //�ϰ�ģʽ��һ����Ҫ�ܷ�
#define SECOND_REQUIRED_SCORE 2000  //�ϰ�ģʽ�ڶ�����Ҫ�ܷ�

using namespace std;

//ģʽ1����ϰģʽ��ģʽ2����ʱģʽ��ģʽ3��˫��ģʽ��ģʽ4���ϰ�ģʽ
//����0��ʾ�����ݼӱ�ʾ������-1��ʾʳ�-2��ʾ��ʳ�-3��ʾ��������ʳ�-4��ʾ����ʱ��ʳ�-5��ʾ�ϰ���
//ʳ��Ϊ��ɫ����ʳ�����һ����β���۳�50��BONUS������ʱ��ʳ���15����Ϸʱ�䣬��������ʳ���150��Ϸ����
int SNAKE[COLUMN_NUM][ROW_NUM];  //��ʾ�������ߵ����
int SNAKE1[L_COLUMN_NUM][L_ROW_NUM], SNAKE2[L_COLUMN_NUM][L_ROW_NUM]; //˫��ģʽ��SNAKE1��ʾ���1��SNAKE2��ʾ���2
int SNAKE4[B_COLUMN_NUM][B_ROW_NUM];  //��ʾ�������ߵ����
int MODE = 1; //ѡ����Ϸģʽ��1��ʾ��ϰģʽ��2��ʾ��ʱģʽ��3��ʾ˫��ģʽ
int DIRECTION = 4;  //��ʾ��ͷ�˶��ķ���1��2��3��4�ֱ��ʾ��������
int DIRECTION1 = 4, DIRECTION2 = 4;  //˫��ģʽ��ʾ��ͷ�˶��ķ���1��2��3��4�ֱ��ʾ��������
bool ifLose = false;  //�ж��Ƿ��䣬Ĭ��Ϊfalse
int HEAD_X, HEAD_Y;  //��¼��ͷ������λ��
int HEAD1_X, HEAD1_Y, HEAD2_X, HEAD2_Y;  //˫��ģʽ��¼��ͷ������λ��
int TAIL_X, TAIL_Y;  //��¼��β������λ�� 
int TAIL1_X, TAIL1_Y, TAIL2_X, TAIL2_Y;  //˫��ģʽ��¼��β������λ��
int SLEEP_INTERVAL = 100;  //ÿ�λ���ͣ������Ļ��ʱ��
int NUM = 0;  //����ߵ�����
int NUM1 = 0, NUM2 = 0;  //˫��ģʽ����ߵ�����
bool NO_FOOD = true;  //�Ƿ���ʳ��
bool ifEndGame = false;  //Ĭ�ϲ��˳���Ϸ
int LOSER = 1;  //˫��ģʽ��¼��һ������䣬Ĭ�����һ
bool isTimeOut = false;  //Ĭ�ϲ���ʱ
int TURN = 0;  //�жϲ�����ʳ��,��������ʳ�����ʱ��ʳ��
int BONUS = 0;  //��������
int BONUS1 = 0,BONUS2 = 0;  //˫��ģʽ��������
int TIME_LIMIT = 60;  //��ʱģʽ����ʱ����λ��
int TIME_LIMIT_DOUBLE = 120;  //˫��ģʽ����ʱ����λ��
int LAST_GLUTTON = 0;  //��ʾ�����ʳ�ĵ��ߣ�1��ʾ��ʳ�2��ʾ��������ʳ�3��ʾ����ʱ��ʳ��
int LAST_GLUTTON1 = 0, LAST_GLUTTON2 = 0;  //˫��ģʽ�б�ʾ�����ʳ�ĵ���
int TOX_FOOD_NUM = 0, POINT_FOOD_NUM = 0, TIME_FOOD_NUM = 0;  //��ʾ�ֱ��̳�����
int TOX_FOOD_NUM1 = 0, POINT_FOOD_NUM1 = 0, TIME_FOOD_NUM1 = 0;  //���һ���Ƶ��߱�ʾ�ֱ��̳�����
int TOX_FOOD_NUM2 = 0, POINT_FOOD_NUM2 = 0, TIME_FOOD_NUM2 = 0;  //��Ҷ����Ƶ��߱�ʾ�ֱ��̳�����
int TOTAL = 0;  //�ϰ�ģʽ��¼������Ϸ���ܷ�
int ROUND = 1;  //�ϰ�ģʽ��¼��ǰ����
bool BarrierGameNotLose = true;  //�ϰ�ģʽ�Ƿ���
bool WinBarrierMode = false;  //�ϰ�ģʽ�Ƿ�Ӯ

void Greeting();  //ȷ����Ϸ����ѡ����Ϸģʽ
void ModeChoose();  //ѡ����Ϸģʽ��1��ʾ��ϰģʽ��2��ʾ��ʱģʽ��3��ʾ˫��ģʽ
void Initialize_Mode1();  //������ģʽ1����ϰģʽ����ģʽ2����ʱģʽ��
void Initialize_Mode3();  //������ģʽ3��˫��ģʽ��
void Initialize_Mode4();  //������ģʽ4���ϰ�ģʽ��
void Game_Mode1();  //ģʽ1����ϰģʽ��������
void Game_Mode2();  //ģʽ2����ʱģʽ��������
void Game_Mode3();  //ģʽ3��˫��ģʽ��������
void Game_Mode4();  //ģʽ4���ϰ�ģʽ��������
void Round1();  //ģʽ4���ϰ�ģʽ�ĵ�һ��
void Round2();  //ģʽ4���ϰ�ģʽ�ĵڶ���
void InstructionMode2();  //ģʽ2����ʱģʽ����Ϸ˵��
void InstructionMode3();  //ģʽ3��˫��ģʽ����Ϸ˵��
void InstructionMode4();  //ģʽ4���ϰ�ģʽ����Ϸ˵��
void CountDown();  //��Ϸǰ��������
void CountDownDoubleMode();  //˫��ģʽ��Ϸǰ��������
void CountDownBarrierMode();  //˫��ģʽ��Ϸǰ��������
void DrawFrame();  //�����ƶ��ı߿�
void DrawFrameDoubleMode();  //˫��ģʽ�����ƶ��ı߿�
void DrawFrameBarrierMode();  //�ϰ�ģʽ�����ƶ��ı߿�
void DrawFood();  //���������»���ʳ��
void DrawFoodDoubleMode();  //˫��ģʽ���������»���ʳ��
void DrawFoodBarrierMode();  //�ϰ�ģʽ���������»���ʳ��
void DrawBarrier();  //�ϰ�ģʽ���������»����ϰ���
void ChToDirection(char ch);  //�������ַ�ת��Ϊ����
void ChToDirectionDoubleMode(char ch);  //˫��ģʽ���ַ�ת��Ϊ����
void Moving();  //�ߣ����飩���ƶ�
void MovingDoubleMode();  //˫��ģʽ�ߣ����飩���ƶ�
void MovingSnakeOne();  //˫��ģʽ���һ�ߣ����飩���ƶ�
void MovingSnakeTwo();  //˫��ģʽ��Ҷ��ߣ����飩���ƶ�
void MovingBarrierMode();  //�ϰ�ģʽ�ߣ����飩���ƶ�
void ObliterateSnake();  //������
void ObliterateSnakeDoubleMode();  //˫��ģʽ������
void ObliterateSnakeBarrierMode();  //�ϰ�ģʽ������
void DrawSnake();  //����Ļ�ϻ�����
void DrawSnakeDoubleMode();  //˫��ģʽ����Ļ�ϻ�����
void DrawSnakeOne();  //˫��ģʽ����Ļ�ϻ������һ����
void DrawSnakeTwo();  //˫��ģʽ����Ļ�ϻ�����Ҷ�����
void DrawSnakeBarrierMode();  //�ϰ�ģʽ����Ļ�ϻ�����
void ShowTag();  //��ʾ����̳Ե���
void ShowTagDoubleMode();  //˫��ģʽ��ʾ����̳Ե���
bool IfLose();  //�ж��Ƿ���
bool IfHitFrame();  //�ж��Ƿ����ڴ�����
bool IfHitSelf();  //�ж��Ƿ�ҧ���Լ���
bool IfLoseDoubleMode();  //˫��ģʽ�ж��Ƿ���
bool IfHitFrameDoubleMode();  //˫��ģʽ�ж��Ƿ����ڴ�����
bool IfHitSelfDoubleMode();  //˫��ģʽ�ж��Ƿ�ҧ���Լ���
bool IfHitOpponentDoubleMode();  //˫��ģʽ�ж��Ƿ�ҧ������
bool IfLoseBarrierMode();  //�ϰ�ģʽ�ж��Ƿ���
bool IfHitFrameBarrierMode();  //�ϰ�ģʽ�ж��Ƿ����ڴ�����
bool IfHitSelfBarrierMode();  //�ϰ�ģʽ�ж��Ƿ�ҧ���Լ���
bool IfHitBarrier();  //�ϰ�ģʽ�ж��Ƿ������ϰ���
void Food();  //����ڵ�ͼ���Ĳ����������ʳ��
void FoodDoubleMode();  //˫��ģʽ����ڵ�ͼ���Ĳ����������ʳ��
void FoodBarrierMode();  //�ϰ�ģʽ����ڵ�ͼ���Ĳ����������ʳ��
bool WithinScreen(int x, int y);  //�жϵ��Ƿ���TAG��ǩ��Χ��
bool WithinScreenDoubleMode(int x, int y);  //˫��ģʽ�жϵ��Ƿ���TAG��ǩ��Χ��
bool WithinScreenBarrierMode(int x, int y);  //�ϰ�ģʽ�жϵ��Ƿ���TAG��ǩ��Χ��
void Glutton();  //�̳�ʳ��
void GluttonDoubleMode();  //˫��ģʽ�̳�ʳ��
void GluttonBarrierMode();  //�ϰ�ģʽ�̳�ʳ��
void MovingTag();  //�����ߵı�ǩֵ,�����̳�ʱ
void MovingTagDoubleMode(int tag);  //˫��ģʽ�����ߵı�ǩֵ,�����̳�ʱ
void ObliterateFood(int x,int y);  //����ʳ��
void ObliterateSnakeTail();  //��ʳ��ʳ��������β
void ObliterateSnakeTailDoubleMode(int mask);  //˫��ģʽ��ʳ��ʳ��������β
void ObliterateSnakeTailBarrierMode();  //�ϰ�ģʽ��ʳ��ʳ��������β
void TurnOperation();  //������turn�����Ĳ���
void ToxFood();  //�����ж�ʳ��
void PointFood();  //������������ʳ��
void TimeFood();  //��������ʱ��ʳ��
void ToxFoodDoubleMode();  //˫��ģʽ�����ж�ʳ��
void PointFoodDoubleMode();  //˫��ģʽ������������ʳ��
void TimeFoodDoubleMode();  //˫��ģʽ��������ʱ��ʳ��
void ToxFoodBarrierMode();  //�ϰ�ģʽ�����ж�ʳ��
void PointFoodBarrierMode();  //�ϰ�ģʽ������������ʳ��
void TimeFoodBarrierMode();  //�ϰ�ģʽ��������ʱ��ʳ��
void Pause();  //������ͣ��Ϸ
bool Quit();  //�����˳���Ϸ
void LoseGame();  //��Ϸ���
void LoseGameDoubleMode();  //˫��ģʽ��Ϸ���
void TimeOutDoubleMode();  //˫��ģʽ��ʱ
void ShowPlayerOne(long snake1);  //����Ļ����ʾ���һ�����
void ShowPlayerTwo(long snake2);  //����Ļ����ʾ��Ҷ������
void ShowGluttonNum();  //����Ļ����ʾ�����̳�����
void ShowScore();  //��ʾ����
void ShowResultBarrierMode();  //�ϰ�ģʽ����һ�ֺ���ʾ������Ϸ���
bool IfPlayAgain();  //һ�ֽ������Ƿ�����һ��
void BarrierModeInitialize();  //�ϰ�ģʽ��Ϸ���ݳ�ʼ��
void Congratulations();  //�ϰ�ģʽͨ�������ֿ�

void Greeting()
{
	system("cls");
	puts("��ӭ����̰������Ϸ��");
	puts("����AWSD���Ʒ���P��ͣ��Ϸ��Q�˳���Ϸ");

	while (1)
	{
		string str;
		printf("Understand?[y/n]");
		getline(cin, str);  //�����������
		if (!str.compare("y") || !str.compare("Y"))
		{
			ModeChoose();
			return;
		}
	}
}

void ModeChoose()
{
	system("cls");
	puts("ѡ����Ϸģʽ");
	puts("1-------��ϰģʽ");
	puts("2-------��ʱģʽ");
	puts("3-------˫��ģʽ");
	puts("4-------�ϰ�ģʽ");

	while (1)
	{
		string str;
		printf("Mode:");
		getline(cin, str);  //�����������

		if (!str.compare("1") || !str.compare("2") || !str.compare("3") || !str.compare("4"))
		{
			istringstream stream;
			stream.str(str);  //���ַ���ת��Ϊ��
			int mode = 1;
			stream >> mode;  //����ת��Ϊ����

			MODE = mode;
			return;
		}
	}
}

void Initialize_Mode1()  //����ģʽ
{
	initgraph(WIDTH, HEIGHT);
	cleardevice();
	CountDown();
	DrawFrame();

	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			SNAKE[i][j] = 0;

	int j = ROW_NUM / 2;
	for (int i = COLUMN_NUM / 2 + INIT_LEN / 2;i >= COLUMN_NUM / 2 - INIT_LEN / 2;i--)
	{
		NUM += 1;
		SNAKE[i][j] = NUM;
	}  //��NUM�������
		
	HEAD_X = COLUMN_NUM / 2 + INIT_LEN / 2;
	HEAD_Y = ROW_NUM / 2;
	TAIL_X = COLUMN_NUM / 2 - INIT_LEN / 2;
	TAIL_Y = ROW_NUM / 2;  //��¼��ͷ����β����
}

void Initialize_Mode3()  //˫��ģʽ
{
	initgraph(L_WIDTH, L_HEIGHT);
	cleardevice();
	CountDownDoubleMode();
	DrawFrameDoubleMode();

	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
		{
			SNAKE1[i][j] = 0;
			SNAKE2[i][j] = 0;
		}

	//��NUM�������
	int j1 = L_ROW_NUM / 4, j2 = L_ROW_NUM * 3 / 4;
	for (int i = L_COLUMN_NUM / 4 + L_INIT_LEN / 2;i >= L_COLUMN_NUM / 4 - L_INIT_LEN / 2;i--)
	{
		NUM1 += 1;
		SNAKE1[i][j1] = NUM1;
	}  
	for (int i = L_COLUMN_NUM * 3 / 4 + L_INIT_LEN / 2;i >= L_COLUMN_NUM * 3 / 4 - L_INIT_LEN / 2;i--)
	{
		NUM2 += 1;
		SNAKE2[i][j2] = NUM2;
	}
	
	//��¼��ͷ����β����
	HEAD1_X = L_COLUMN_NUM / 4 + L_INIT_LEN / 2;
	HEAD1_Y = j1;
	TAIL1_X = L_COLUMN_NUM / 4 - L_INIT_LEN / 2;
	TAIL1_Y = j1;  //���һ���Ƶ���

	HEAD2_X = L_COLUMN_NUM * 3 / 4 + L_INIT_LEN / 2;
	HEAD2_Y = j2;
	TAIL2_X = L_COLUMN_NUM * 3 / 4 - L_INIT_LEN / 2;
	TAIL2_Y = j2;  //��Ҷ����Ƶ���
}

void Initialize_Mode4()  //�ϰ�ģʽ
{
	initgraph(B_WIDTH, B_HEIGHT);
	cleardevice();
	CountDownBarrierMode();  //����ʱ
	DrawFrameBarrierMode();  //������Ϸ�߿�

	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
			SNAKE4[i][j] = 0;

	int j = B_ROW_NUM / 2 + 10;
	for (int i = B_COLUMN_NUM / 2 + INIT_LEN / 2;i >= B_COLUMN_NUM / 2 - INIT_LEN / 2;i--)
	{
		NUM += 1;
		SNAKE4[i][j] = NUM;
	}  //��NUM�������

	HEAD_X = B_COLUMN_NUM / 2 + INIT_LEN / 2;
	HEAD_Y = B_ROW_NUM / 2 + 10;
	TAIL_X = B_COLUMN_NUM / 2 - INIT_LEN / 2;
	TAIL_Y = B_ROW_NUM / 2 + 10;  //��¼��ͷ����β����
}

void CountDown()
{
	if (MODE == 2)
		InstructionMode2();
	
	for (int i = 3;i > 0;i--)
	{
		cleardevice();
		
		stringstream s1;
		s1 << i;
		string s = s1.str();  //��intת��Ϊstring��
		LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
		outtextxy(WIDTH / 2 - 10, HEIGHT / 2 - 10, str);

		Sleep(1000);
	}
}

void CountDownDoubleMode()
{
	InstructionMode3();
	
	for (int i = 3;i > 0;i--)
	{
		cleardevice();

		stringstream s1;
		s1 << i;
		string s = s1.str();  //��intת��Ϊstring��
		LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
		outtextxy(L_WIDTH / 2 - 30, L_HEIGHT / 2 - 30, str);

		Sleep(1000);
	}
}

void CountDownBarrierMode()
{
	if (MODE == 4)
		InstructionMode4();

	for (int i = 3;i > 0;i--)
	{
		cleardevice();

		stringstream s1;
		s1 << i;
		string s = s1.str();  //��intת��Ϊstring��
		LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
		outtextxy(B_WIDTH / 2 - 10, B_HEIGHT / 2 - 10, str);

		Sleep(1000);
	}
}

void InstructionMode2()
{
	cleardevice();

	string s = "��ʱ60��";
	LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(WIDTH / 2 - 20, HEIGHT / 2 - 20, str);

	Sleep(1000);
}

void InstructionMode3()
{
	cleardevice();

	string s = "��ʱ120��";
	LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 30, L_HEIGHT / 2 - 30, str);

	Sleep(1800);

	cleardevice();

	s = "ȷ��С���̿���";
	str = s.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 30, L_HEIGHT / 2 - 30, str);

	Sleep(1800);
}

void InstructionMode4()
{
	cleardevice();

	stringstream stream1;
	stream1 << ROUND;

	stringstream stream2;
	switch (ROUND)
	{
	case 1:
		stream2 << FIRST_REQUIRED_SCORE;
		break;

	case 2:
		stream2 << SECOND_REQUIRED_SCORE;
		break;

	default:break;
	}  //��ÿ����Ҫ�ķ���ת��Ϊ�ַ���

	string s = "ROUND " + stream1.str(), s1 = "TIME LIMIT:   60 SEC", s2 = "REQUIRED SCORE:   "+stream2.str();
	LPCTSTR str = s.c_str(), str1 = s1.c_str(), str2 = s2.c_str(); //��string����ת��ΪLPCTSTR����
	outtextxy(B_WIDTH / 2 - 90, B_HEIGHT / 2 - 40, str);
	outtextxy(B_WIDTH / 2 - 90, B_HEIGHT / 2 - 20, str1);
	outtextxy(B_WIDTH / 2 - 90, B_HEIGHT / 2 , str2);

	Sleep(1800);
}

void DrawFrame()
{
	setlinecolor(WHITE);
	rectangle(DISTANCE, DISTANCE, WIDTH - DISTANCE, HEIGHT - DISTANCE);
}

void DrawFrameDoubleMode()
{
	setlinecolor(WHITE);
	rectangle(DISTANCE, DISTANCE, L_WIDTH - DISTANCE, L_HEIGHT - DISTANCE);
}

void DrawFrameBarrierMode()
{
	setlinecolor(WHITE);
	rectangle(DISTANCE, DISTANCE, B_WIDTH - DISTANCE, B_HEIGHT - DISTANCE);
}

void Game_Mode1()
{
	char ch = 'd';
	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			ChToDirection(tolower(ch));

			if (tolower(ch) == 'q')
			{
				ifEndGame = Quit();
				if (ifEndGame)
					break;
			}
		}

		if (IfLose())
			break;  //IfLose()����ֵΪtrueʱ��ʾ�䣬�˳�������Ϸ

		Glutton();  //�̳�ʳ��
		ObliterateSnake();  //������
		Moving();  //��������
		DrawSnake();  //������

		if (NO_FOOD)
			Food();

		TurnOperation();  //������turn�������в���
	}
}

void Game_Mode2()
{
	char ch = 'd';  //Ĭ�Ϸ���Ϊ��
	SYSTEMTIME time;  //����������浱ǰʱ��
	GetLocalTime(&time); //��ȡ��ǰʱ��
	int tHour = time.wHour;  //��ȡ��ǰʱ���Сʱ��
	int tMin = time.wMinute;  //��ȡ��ǰʱ��ķ�����
	int tSec = time.wSecond;  //��ȡ��ǰʱ�������
	int num1 = tHour * 3600 + tMin * 60 + tSec;

	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			ChToDirection(tolower(ch));

			if (tolower(ch) == 'q')
			{
				ifEndGame = Quit();
				if (ifEndGame)
					break;
			}
		}

		if (IfLose())
			break;  //IfLose()����ֵΪtrueʱ��ʾ�䣬�˳�������Ϸ

		Glutton();  //�̳�ʳ��
		ObliterateSnake();  //������
		Moving();  //��������
		DrawSnake();  //������

		if (NO_FOOD)
			Food();

		TurnOperation();  //������turn�������в���

		GetLocalTime(&time); //��ȡ��ǰʱ��
		int num2 = time.wHour * 3600 + time.wMinute * 60 + time.wSecond;
		if (num2 - num1 >= TIME_LIMIT)
			break;  //����Ϸʱ���������ʱ��ʱ�˳�
	}
}

void Game_Mode3()  //˫��ģʽ
{
	char ch = 'd';
	SYSTEMTIME time;  //����������浱ǰʱ��
	GetLocalTime(&time); //��ȡ��ǰʱ��
	int tHour = time.wHour;  //��ȡ��ǰʱ���Сʱ��
	int tMin = time.wMinute;  //��ȡ��ǰʱ��ķ�����
	int tSec = time.wSecond;  //��ȡ��ǰʱ�������
	int num1 = tHour * 3600 + tMin * 60 + tSec;

	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			ChToDirectionDoubleMode(tolower(ch));  //���һ������ĸ

			if (tolower(ch) == 'q')
			{
				ifEndGame = Quit();
				if (ifEndGame)
					break;
			}
		}

		if (IfLoseDoubleMode())
			break;  //IfLose()����ֵΪtrueʱ��ʾ�䣬�˳�������Ϸ

		GluttonDoubleMode();  //�̳�ʳ��
		ObliterateSnakeDoubleMode();  //������
		MovingDoubleMode();  //��������
		DrawSnakeDoubleMode();  //������

		if (NO_FOOD)
			FoodDoubleMode();  //������������ʳ��

		TurnOperation();  //������turn�������в���

		GetLocalTime(&time); //��ȡ��ǰʱ��
		int num2 = time.wHour * 3600 + time.wMinute * 60 + time.wSecond;
		if (num2 - num1 >= TIME_LIMIT_DOUBLE)
		{
			isTimeOut = true;
			break;  //����Ϸʱ���������ʱ��ʱ�˳�
		}
	}
}

void Game_Mode4()
{
	switch (ROUND)
	{
	case 1:
		Round1();  //���õ�ͼ
		break;

	case 2:
		Round2();  //���õ�ͼ
		break;

	default:return;
	}

	char ch = 'd';
	SYSTEMTIME time;  //����������浱ǰʱ��
	GetLocalTime(&time); //��ȡ��ǰʱ��
	int tHour = time.wHour;  //��ȡ��ǰʱ���Сʱ��
	int tMin = time.wMinute;  //��ȡ��ǰʱ��ķ�����
	int tSec = time.wSecond;  //��ȡ��ǰʱ�������
	int num1 = tHour * 3600 + tMin * 60 + tSec;

	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			ChToDirection(tolower(ch));

			if (tolower(ch) == 'q')
			{
				ifEndGame = Quit();
				if (ifEndGame)
				{
					int score = 100 * (NUM - INIT_LEN) + BONUS;  //���ַ���
					TOTAL += score;  //�ܷ�

					break;
				}
			}
		}

		if (IfLoseBarrierMode())
		{
			BarrierGameNotLose = false;  //��Ϸ��

			int score = 100 * (NUM - INIT_LEN) + BONUS;  //���ַ���
			TOTAL += score;  //�ܷ�

			break;  //IfLoseBarrierMode()����ֵΪtrueʱ��ʾ�䣬�˳�������Ϸ
		}
			
		GluttonBarrierMode();  //�̳�ʳ��
		ObliterateSnakeBarrierMode();  //������
		MovingBarrierMode();  //��������
		DrawSnakeBarrierMode();  //������

		if (NO_FOOD)
			FoodBarrierMode();

		TurnOperation();  //������turn�������в���

		GetLocalTime(&time); //��ȡ��ǰʱ��
		int num2 = time.wHour * 3600 + time.wMinute * 60 + time.wSecond;
		if (num2 - num1 >= TIME_LIMIT)
		{
			int score = 100 * (NUM - INIT_LEN) + BONUS;  //���ַ���
			TOTAL += score;  //�ܷ�

			switch (ROUND)  //������������Ҫ��ķ���
			{
			case 1:
			{
				if (TOTAL < FIRST_REQUIRED_SCORE)
					BarrierGameNotLose = false;  //���ܷ�δ����1500������
			}
			break;

			case 2:
			{
				if (TOTAL < SECOND_REQUIRED_SCORE)
					BarrierGameNotLose = false;  //���ܷ�δ����1500������
			}
			break;

			default:break;
			}
			
			if (ROUND == 2)
				WinBarrierMode = true;  //��ʾ���ֹ����Ѿ�Ӯ

			break;  //����Ϸʱ���������ʱ��ʱ�˳�
		}
	}
}

void Round1()
{
	for (int i = B_COLUMN_NUM / 2 - 8;i <= B_COLUMN_NUM / 2 + 8;i++)
		for (int j = B_ROW_NUM / 2 - 4;j <= B_ROW_NUM / 2 + 4;j++)
			SNAKE4[i][j] = -5;  //�����ϰ���
	//�ϰ����������ΪDISTANCE*(B_COLUMN_NUM/2-8)���Ҳ�����ΪDISTANCE*(B_COLUMN_NUM/2+8)+DISTANCE
	//�Ϸ�����ΪDISTANCE*(B_ROW_NUM/2-4)���·�����ΪDISTANCE*(B_ROW_NUM/2+4)+DISRANCE
}

void Round2()
{
	for (int i = B_COLUMN_NUM / 4 + 1;i <= B_COLUMN_NUM / 4 + 5;i++)
		for (int j = B_ROW_NUM / 4 + 1;j <= B_ROW_NUM / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //�����ϰ���
	//�ϰ����������ΪDISTANCE*(B_COLUMN_NUM/4+1)���Ҳ�����ΪDISTANCE*(B_COLUMN_NUM/4+5)+DISTANCE
	//�Ϸ�����ΪDISTANCE*(B_ROW_NUM/4+1)���·�����ΪDISTANCE*(B_ROW_NUM/4+5)+DISTANCE

	for (int i = B_COLUMN_NUM * 3 / 4 + 1;i <= B_COLUMN_NUM * 3 / 4 + 5;i++)
		for (int j = B_ROW_NUM / 4 + 1;j <= B_ROW_NUM / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //�����ϰ���
	//�ϰ����������ΪDISTANCE*(B_COLUMN_NUM*3/4+1)���Ҳ�����ΪDISTANCE*(B_COLUMN_NUM*3/4+5)+DISTANCE
	//�Ϸ�����ΪDISTANCE*(B_ROW_NUM/4+1)���·�����ΪDISTANCE*(B_ROW_NUM/4+5)+DISTANCE

	for (int i = B_COLUMN_NUM / 4 + 1;i <= B_COLUMN_NUM / 4 + 5;i++)
		for (int j = B_ROW_NUM * 3 / 4 + 1;j <= B_ROW_NUM * 3 / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //�����ϰ���
	//�ϰ����������ΪDISTANCE*(B_COLUMN_NUM/4+1)���Ҳ�����ΪDISTANCE*(B_COLUMN_NUM/4+5)+DISTANCE
	//�Ϸ�����ΪDISTANCE*(B_ROW_NUM*3/4+1)���·�����ΪDISTANCE*(B_ROW_NUM*3/4+5)+DISTANCE

	for (int i = B_COLUMN_NUM * 3 / 4 + 1;i <= B_COLUMN_NUM * 3 / 4 + 5;i++)
		for (int j = B_ROW_NUM * 3 / 4 + 1;j <= B_ROW_NUM * 3 / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //�����ϰ���
	//�ϰ����������ΪDISTANCE*(B_COLUMN_NUM*3/4+1)���Ҳ�����ΪDISTANCE*(B_COLUMN_NUM*3/4+5)+DISTANCE
	//�Ϸ�����ΪDISTANCE*(B_ROW_NUM*3/4+1)���·�����ΪDISTANCE*(B_ROW_NUM*3/4+5)+DISTANCE
}

void ChToDirection(char ch)
{
	if (ch == 'a' && DIRECTION != 4)
		DIRECTION = 3;
	if (ch == 'd' && DIRECTION != 3)
		DIRECTION = 4;
	if (ch == 'w' && DIRECTION != 2)
		DIRECTION = 1;
	if (ch == 's' && DIRECTION != 1)
		DIRECTION = 2;
	if (ch == 'p')
		Pause();
}

void ChToDirectionDoubleMode(char ch)
{
	switch (ch)
	{
	//���һawsd������
	case 'a':
	{
		if(DIRECTION1 != 4)
			DIRECTION1 = 3;
	}
	break;

	case 'd':
	{
		if (DIRECTION1 != 3)
			DIRECTION1 = 4;
	}
	break;

	case 'w':
	{
		if (DIRECTION1 != 2)
			DIRECTION1 = 1;
	}
	break;

	case 's':
	{
		if (DIRECTION1 != 1)
			DIRECTION1 = 2;
	}
	break;

	//��Ҷ����Ƶ���
	case '1':
	{
		if(DIRECTION2!=4)
			DIRECTION2 = 3;
	}
	break;

	case '3':
	{
		if (DIRECTION2 != 3)
			DIRECTION2 = 4;
	}
	break;

	case '5':
	{
		if (DIRECTION2 != 2)
			DIRECTION2 = 1;
	}
	break;

	case '2':
	{
		if (DIRECTION2 != 1)
			DIRECTION2 = 2;
	}
	break;

	case 'p':
		Pause();
	break;

	default:break;
	}
}

void DrawFood()
{
	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
		{
			//ʳ��
			if (SNAKE[i][j] == -1)
			{
				setlinecolor(BLUE);
				setfillcolor(RED);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}

			//��ʳ�����ʱ��ʳ���������ʳ���������ͬ
			if (SNAKE[i][j] == -2 || SNAKE[i][j] == -3 || SNAKE[i][j] == -4)
			{
				setlinecolor(BLUE);
				setfillcolor(LIGHTGREEN);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}
		}
}

void DrawFoodDoubleMode()
{
	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
		{
			//ʳ��
			if (SNAKE1[i][j] == -1 && SNAKE2[i][j] == -1)
			{
				setlinecolor(BLUE);
				setfillcolor(RED);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}

			//��ʳ�����ʱ��ʳ���������ʳ���������ͬ
			if (SNAKE1[i][j] == -2 && SNAKE2[i][j] == -2)
			{
				setlinecolor(BLUE);
				setfillcolor(LIGHTGREEN);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}
			if (SNAKE1[i][j] == -3 && SNAKE2[i][j] == -3)
			{
				setlinecolor(BLUE);
				setfillcolor(LIGHTGREEN);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}
			if (SNAKE1[i][j] == -4 && SNAKE2[i][j] == -4)
			{
				setlinecolor(BLUE);
				setfillcolor(LIGHTGREEN);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}
		}
}

void DrawFoodBarrierMode()
{
	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
		{
			//ʳ��
			if (SNAKE4[i][j] == -1)
			{
				setlinecolor(BLUE);
				setfillcolor(RED);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}

			//��ʳ�����ʱ��ʳ���������ʳ���������ͬ
			if (SNAKE4[i][j] == -2 || SNAKE4[i][j] == -3 || SNAKE4[i][j] == -4)
			{
				setlinecolor(BLUE);
				setfillcolor(LIGHTGREEN);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}
		}
}

void DrawBarrier()
{
	switch (ROUND)
	{
	case 1:
	{
		int left = DISTANCE*(B_COLUMN_NUM / 2 - 8), right = DISTANCE*(B_COLUMN_NUM / 2 + 8) + DISTANCE;
		int top = DISTANCE*(B_ROW_NUM / 2 - 4), bottom = DISTANCE*(B_ROW_NUM / 2 + 4) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);
	}
	break;

	case 2:
	{
		//���Ϸ��ϰ���
		int left = DISTANCE*(B_COLUMN_NUM / 4 + 1), right = DISTANCE*(B_COLUMN_NUM / 4 + 5) + DISTANCE;
		int top = DISTANCE*(B_ROW_NUM / 4 + 1), bottom = DISTANCE*(B_ROW_NUM / 4 + 5) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);

		//���Ϸ��ϰ���
		left = DISTANCE*(B_COLUMN_NUM * 3 / 4 + 1), right = DISTANCE*(B_COLUMN_NUM * 3 / 4 + 5) + DISTANCE;
		top = DISTANCE*(B_ROW_NUM / 4 + 1), bottom = DISTANCE*(B_ROW_NUM / 4 + 5) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);

		//���·��ϰ���
		left = DISTANCE*(B_COLUMN_NUM / 4 + 1), right = DISTANCE*(B_COLUMN_NUM / 4 + 5) + DISTANCE;
		top = DISTANCE*(B_ROW_NUM * 3 / 4 + 1), bottom = DISTANCE*(B_ROW_NUM * 3 / 4 + 5) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);

		//���·��ϰ���
		left = DISTANCE*(B_COLUMN_NUM * 3 / 4 + 1), right = DISTANCE*(B_COLUMN_NUM * 3 / 4 + 5) + DISTANCE;
		top = DISTANCE*(B_ROW_NUM * 3 / 4 + 1), bottom = DISTANCE*(B_ROW_NUM * 3 / 4 + 5) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);
	}
	break;

	default:break;
	}
}

bool IfLose()
{
	return  IfHitFrame() || IfHitSelf();
}

bool IfHitFrame()
{
	int head_x = DISTANCE*HEAD_X + DISTANCE / 2, head_y = DISTANCE*HEAD_Y + DISTANCE / 2;
	if (head_x<DISTANCE + RADIUS || head_x>WIDTH - DISTANCE - RADIUS || head_y<DISTANCE + RADIUS || head_y>HEIGHT - DISTANCE - RADIUS)
		return true;
	return false;
}

bool IfHitSelf()
{
	switch (DIRECTION)
	{
	//��������
	case 1:
		if (SNAKE[HEAD_X][HEAD_Y - 1] > 0)
			return true;
		break;

	//��������
	case 2:
		if (SNAKE[HEAD_X][HEAD_Y + 1] > 0)
			return true;
		break;

	//��������
	case 3:
		if (SNAKE[HEAD_X - 1][HEAD_Y] > 0)
			return true;
		break;

	//��������
	case 4:
		if (SNAKE[HEAD_X + 1][HEAD_Y] > 0)
			return true;
		break;
	}
	
	return false;
}

bool IfLoseDoubleMode()
{
	return IfHitFrameDoubleMode() || IfHitSelfDoubleMode() || IfHitOpponentDoubleMode();
}

bool IfHitFrameDoubleMode()
{
	int head1_x = DISTANCE*HEAD1_X + DISTANCE / 2, head1_y = DISTANCE*HEAD1_Y + DISTANCE / 2;
	int head2_x = DISTANCE*HEAD2_X + DISTANCE / 2, head2_y = DISTANCE*HEAD2_Y + DISTANCE / 2;  //�����±��Ӧ������

	if (head1_x<DISTANCE + RADIUS || head1_x>L_WIDTH - DISTANCE - RADIUS || head1_y<DISTANCE + RADIUS || head1_y>L_HEIGHT - DISTANCE - RADIUS)
	{
		LOSER = 1;  //���һ��
		return true;
	}
	if (head2_x<DISTANCE + RADIUS || head2_x>L_WIDTH - DISTANCE - RADIUS || head2_y<DISTANCE + RADIUS || head2_y>L_HEIGHT - DISTANCE - RADIUS)
	{
		LOSER = 2;  //��Ҷ���
		return true;
	}
	return false;
}

bool IfHitSelfDoubleMode()
{
	//������һ
	switch (DIRECTION1)
	{
		//��������
	case 1:
		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//��������
	case 2:
		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//��������
	case 3:
		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//��������
	case 4:
		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;
	}

	//�����Ҷ�
	switch (DIRECTION2)
	{
		//��������
	case 1:
		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//��������
	case 2:
		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//��������
	case 3:
		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//��������
	case 4:
		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;
	}

	return false;
}

bool IfHitOpponentDoubleMode()
{
	//������һ
	switch (DIRECTION1)
	{
		//��������
	case 1:
		if (SNAKE2[HEAD1_X][HEAD1_Y - 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//��������
	case 2:
		if (SNAKE2[HEAD1_X][HEAD1_Y + 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//��������
	case 3:
		if (SNAKE2[HEAD1_X - 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//��������
	case 4:
		if (SNAKE2[HEAD1_X + 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;
	}

	//�����Ҷ�
	switch (DIRECTION2)
	{
		//��������
	case 1:
		if (SNAKE1[HEAD2_X][HEAD2_Y - 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//��������
	case 2:
		if (SNAKE1[HEAD2_X][HEAD2_Y + 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//��������
	case 3:
		if (SNAKE1[HEAD2_X - 1][HEAD2_Y] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//��������
	case 4:
		if (SNAKE1[HEAD2_X + 1][HEAD2_Y] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;
	}

	return false;
}

bool IfLoseBarrierMode()
{
	return IfHitFrameBarrierMode() || IfHitSelfBarrierMode() || IfHitBarrier();
}

bool IfHitFrameBarrierMode()
{
	int head_x = DISTANCE*HEAD_X + DISTANCE / 2, head_y = DISTANCE*HEAD_Y + DISTANCE / 2;
	if (head_x<DISTANCE + RADIUS || head_x>B_WIDTH - DISTANCE - RADIUS || head_y<DISTANCE + RADIUS || head_y>B_HEIGHT - DISTANCE - RADIUS)
		return true;
	return false;
}

bool IfHitBarrier()
{
	switch (DIRECTION)
	{
		//��������
	case 1:
		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -5)
			return true;
		break;

		//��������
	case 2:
		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -5)
			return true;
		break;

		//��������
	case 3:
		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -5)
			return true;
		break;

		//��������
	case 4:
		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -5)
			return true;
		break;
	}

	return false;
}

bool IfHitSelfBarrierMode()
{
	switch (DIRECTION)
	{
		//��������
	case 1:
		if (SNAKE4[HEAD_X][HEAD_Y - 1] > 0)
			return true;
		break;

		//��������
	case 2:
		if (SNAKE4[HEAD_X][HEAD_Y + 1] > 0)
			return true;
		break;

		//��������
	case 3:
		if (SNAKE4[HEAD_X - 1][HEAD_Y] > 0)
			return true;
		break;

		//��������
	case 4:
		if (SNAKE4[HEAD_X + 1][HEAD_Y] > 0)
			return true;
		break;
	}

	return false;
}

void ObliterateSnake()
{
	cleardevice();  //����
	DrawFrame();  //���Ʊ߿�
	DrawFood();  //���»���ʳ��
	ShowTag();  //��ʾ����̳Ե���
}

void ObliterateSnakeDoubleMode()
{
	cleardevice();  //����
	DrawFrameDoubleMode();  //���Ʊ߿�
	DrawFoodDoubleMode();  //���»���ʳ��
	ShowTagDoubleMode();  //��ʾ����̳Ե���
}

void ObliterateSnakeBarrierMode()
{
	cleardevice();  //����
	DrawFrameBarrierMode();  //���Ʊ߿�
	DrawFoodBarrierMode();  //���»���ʳ��
	DrawBarrier();  //���»����ϰ���
	ShowTag();  //��ʾ����̳Ե���
}

void DrawSnake()
{
	setlinecolor(YELLOW);
	setfillcolor(BLUE);
	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			if (SNAKE[i][j] > 0)
				if (SNAKE[i][j] == 1)
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //ͻ����ͷ
				else
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS);
	

	Sleep(SLEEP_INTERVAL);
}

void DrawSnakeDoubleMode()
{
	DrawSnakeOne();
	DrawSnakeTwo();
}

void DrawSnakeOne()
{
	setlinecolor(YELLOW);
	setfillcolor(BLUE);  //���һ����Ϊ��ɫ�߿���ɫ�ڲ�
	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE1[i][j] > 0)
				if (SNAKE1[i][j] == 1)
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //ͻ����ͷ
				else
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS);

	Sleep(SLEEP_INTERVAL / 2);
}

void DrawSnakeTwo()
{
	setlinecolor(RED);
	setfillcolor(BROWN);  //��Ҷ�����Ϊ��ɫ�߿���ɫ�ڲ�
	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE2[i][j] > 0)
				if (SNAKE2[i][j] == 1)
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //ͻ����ͷ
				else
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS);

	Sleep(SLEEP_INTERVAL / 2);
}

void DrawSnakeBarrierMode()
{
	setlinecolor(YELLOW);
	setfillcolor(BLUE);
	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
			if (SNAKE4[i][j] > 0)
				if (SNAKE4[i][j] == 1)
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //ͻ����ͷ
				else
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS);


	Sleep(SLEEP_INTERVAL);
}

void ShowTag() 
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(DISTANCE + 3, DISTANCE + 3, 10 * DISTANCE, 5 * DISTANCE);  //��ȥ֮ǰ�ڽ�����д��TAG

	string tag = "";
	if (LAST_GLUTTON == 1)  //��ʳ��
		tag = "POISON FOOD";
	else if (LAST_GLUTTON == 2)  //��������
		tag = "SCORE BONUS";
	else if (LAST_GLUTTON == 3)  //����ʱ��
		tag = "TIME BONUS";
	LPCTSTR TAG = tag.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(DISTANCE, DISTANCE, TAG);
}

void ShowTagDoubleMode()  
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(DISTANCE + 3, DISTANCE + 3, 10 * DISTANCE, 5 * DISTANCE);  
	fillrectangle(L_WIDTH - 10 * DISTANCE, DISTANCE + 3, L_WIDTH - DISTANCE - 3, 5 * DISTANCE);  //��ȥ֮ǰ�ڽ�����д��TAG

	string tag1 = "", tag2 = "";
	if (LAST_GLUTTON1 == 1)  //��ʳ��
		tag1 = "POISON FOOD";
	else if (LAST_GLUTTON1 == 2)  //��������
		tag1 = "SCORE BONUS";
	else if (LAST_GLUTTON1 == 3)  //����ʱ��
		tag1 = "TIME BONUS";

	if (LAST_GLUTTON2 == 1)  //��ʳ��
		tag2 = "POISON FOOD";
	else if (LAST_GLUTTON2 == 2)  //��������
		tag2 = "SCORE BONUS";
	else if (LAST_GLUTTON2 == 3)  //����ʱ��
		tag2 = "TIME BONUS";

	LPCTSTR TAG = tag1.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(DISTANCE, DISTANCE, TAG);

	TAG = tag2.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH - 10 * DISTANCE, DISTANCE, TAG);
}

void Pause()
{
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, "��Ϸ��ͣ", "ϵͳ��ʾ", MB_OK) == IDYES)
		return;
}

bool Quit()
{
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, "ȷ���˳���Ϸ��", "ϵͳ��ʾ", MB_YESNO) == IDYES)
		return true;
	else
		return false;
}

void Moving()
{
	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
		{
			if (SNAKE[i][j] == NUM)
				SNAKE[i][j] = 0;  //ȥ����β

			if (SNAKE[i][j] == NUM - 1)
			{
				TAIL_X = i;
				TAIL_Y = j;
			}  //����β
		}

	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			if (SNAKE[i][j] > 0)
				SNAKE[i][j]++;  //��Ŀǰ����������β
	
	switch (DIRECTION)
	{
	//��ͷ����
	case 1:
	{
		SNAKE[HEAD_X][HEAD_Y - 1] = 1;
		HEAD_Y -= 1;
	}
		break;

	//��ͷ����
	case 2:
	{
		SNAKE[HEAD_X][HEAD_Y + 1] = 1;
		HEAD_Y += 1;
	}
		break;
	
	//��ͷ����
	case 3:
	{
		SNAKE[HEAD_X - 1][HEAD_Y] = 1;
		HEAD_X -= 1;
	}
		break;

	//��ͷ����
	case 4:
	{
		SNAKE[HEAD_X + 1][HEAD_Y] = 1;
		HEAD_X += 1;
	}
		break;

	default:break;
	}
}

void MovingDoubleMode()
{
	MovingSnakeOne();
	MovingSnakeTwo();
}

void MovingSnakeOne()
{
	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
		{
			if (SNAKE1[i][j] == NUM1)
				SNAKE1[i][j] = 0;  //ȥ����β

			if (SNAKE1[i][j] == NUM1 - 1)
			{
				TAIL1_X = i;
				TAIL1_Y = j;
			}  //����β
		}

	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE1[i][j] > 0)
				SNAKE1[i][j]++;  //��Ŀǰ����������β

	switch (DIRECTION1)
	{
		//��ͷ����
	case 1:
	{
		SNAKE1[HEAD1_X][HEAD1_Y - 1] = 1;
		HEAD1_Y -= 1;
	}
	break;

	//��ͷ����
	case 2:
	{
		SNAKE1[HEAD1_X][HEAD1_Y + 1] = 1;
		HEAD1_Y += 1;
	}
	break;

	//��ͷ����
	case 3:
	{
		SNAKE1[HEAD1_X - 1][HEAD1_Y] = 1;
		HEAD1_X -= 1;
	}
	break;

	//��ͷ����
	case 4:
	{
		SNAKE1[HEAD1_X + 1][HEAD1_Y] = 1;
		HEAD1_X += 1;
	}
	break;

	default:break;
	}
}

void MovingSnakeTwo()
{
	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
		{
			if (SNAKE2[i][j] == NUM2)
				SNAKE2[i][j] = 0;  //ȥ����β

			if (SNAKE2[i][j] == NUM2 - 1)
			{
				TAIL2_X = i;
				TAIL2_Y = j;
			}  //����β
		}

	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE2[i][j] > 0)
				SNAKE2[i][j]++;  //��Ŀǰ����������β

	switch (DIRECTION2)
	{
		//��ͷ����
	case 1:
	{
		SNAKE2[HEAD2_X][HEAD2_Y - 1] = 1;
		HEAD2_Y -= 1;
	}
	break;

	//��ͷ����
	case 2:
	{
		SNAKE2[HEAD2_X][HEAD2_Y + 1] = 1;
		HEAD2_Y += 1;
	}
	break;

	//��ͷ����
	case 3:
	{
		SNAKE2[HEAD2_X - 1][HEAD2_Y] = 1;
		HEAD2_X -= 1;
	}
	break;

	//��ͷ����
	case 4:
	{
		SNAKE2[HEAD2_X + 1][HEAD2_Y] = 1;
		HEAD2_X += 1;
	}
	break;

	default:break;
	}
}

void MovingBarrierMode()
{
	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
		{
			if (SNAKE4[i][j] == NUM)
				SNAKE4[i][j] = 0;  //ȥ����β

			if (SNAKE4[i][j] == NUM - 1)
			{
				TAIL_X = i;
				TAIL_Y = j;
			}  //����β
		}

	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
			if (SNAKE4[i][j] > 0)
				SNAKE4[i][j]++;  //��Ŀǰ����������β

	switch (DIRECTION)
	{
		//��ͷ����
	case 1:
	{
		SNAKE4[HEAD_X][HEAD_Y - 1] = 1;
		HEAD_Y -= 1;
	}
	break;

	//��ͷ����
	case 2:
	{
		SNAKE4[HEAD_X][HEAD_Y + 1] = 1;
		HEAD_Y += 1;
	}
	break;

	//��ͷ����
	case 3:
	{
		SNAKE4[HEAD_X - 1][HEAD_Y] = 1;
		HEAD_X -= 1;
	}
	break;

	//��ͷ����
	case 4:
	{
		SNAKE4[HEAD_X + 1][HEAD_Y] = 1;
		HEAD_X += 1;
	}
	break;

	default:break;
	}
}

void Food()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE[FOOD_X][FOOD_Y] = -1;
			
			setlinecolor(BLUE);
			setfillcolor(RED);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2*RADIUS);

			break;
		}
	}
	NO_FOOD = false;
}

bool WithinScreen(int x,int y)
{
	int X = DISTANCE*x + DISTANCE / 2;  //���жϵ�ĺ�����
	int Y = DISTANCE*y + DISTANCE / 2;  //���жϵ��������
	if (X < 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //��TAG��ǩ��Χ��
	return false;  //��TAG��ǩ��Χ��
}

void PointFood()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE[FOOD_X][FOOD_Y] = -3;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
}

void ToxFood()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE[FOOD_X][FOOD_Y] = -2;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, FOOD_RADIUS);

			break;
		}
	}
}

void TimeFood()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE[FOOD_X][FOOD_Y] = -4;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
}

void FoodDoubleMode()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //����Ϊ����
		{
			SNAKE1[FOOD_X][FOOD_Y] = -1;
			SNAKE2[FOOD_X][FOOD_Y] = -1;

			setlinecolor(BLUE);
			setfillcolor(RED);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
	NO_FOOD = false;
}

bool WithinScreenDoubleMode(int x, int y)
{
	int X = DISTANCE*x + DISTANCE / 2;  //���жϵ�ĺ�����
	int Y = DISTANCE*y + DISTANCE / 2;  //���жϵ��������
	if (X < 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //�����һTAG��ǩ��Χ��
	if (X > L_WIDTH - 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //����Ҷ�TAG��ǩ��Χ��
	return false;  //��TAG��ǩ��Χ��
}

void PointFoodDoubleMode()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE1[FOOD_X][FOOD_Y] = -3;
			SNAKE2[FOOD_X][FOOD_Y] = -3;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
}

void ToxFoodDoubleMode()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE1[FOOD_X][FOOD_Y] = -2;
			SNAKE2[FOOD_X][FOOD_Y] = -2;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
}

void TimeFoodDoubleMode()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE1[FOOD_X][FOOD_Y] = -4;
			SNAKE2[FOOD_X][FOOD_Y] = -4;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
}

void FoodBarrierMode()
{
	int FOOD_X, FOOD_Y;  //FOOD_X��ȡֵ��Χ��[4,145]��FOOD_Y��ȡֵ��Χ��[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE4[FOOD_X][FOOD_Y] = -1;

			setlinecolor(BLUE);
			setfillcolor(RED);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
	NO_FOOD = false;
}

bool WithinScreenBarrierMode(int x, int y)
{
	int X = DISTANCE*x + DISTANCE / 2;  //���жϵ�ĺ�����
	int Y = DISTANCE*y + DISTANCE / 2;  //���жϵ��������
	if (X < 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //��TAG��ǩ��Χ��
	return false;  //��TAG��ǩ��Χ��
}

void PointFoodBarrierMode()
{
	int FOOD_X, FOOD_Y; 
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE4[FOOD_X][FOOD_Y] = -3;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
}

void ToxFoodBarrierMode()
{
	int FOOD_X, FOOD_Y; 
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE4[FOOD_X][FOOD_Y] = -2;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, FOOD_RADIUS);

			break;
		}
	}
}

void TimeFoodBarrierMode()
{
	int FOOD_X, FOOD_Y;  
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_Xȡֵ��Χ[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Yȡֵ��Χ[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //����Ϊ�������ߡ�ʳ��
		{
			SNAKE4[FOOD_X][FOOD_Y] = -4;

			setlinecolor(BLUE);
			setfillcolor(LIGHTGREEN);
			fillcircle(DISTANCE*FOOD_X + DISTANCE / 2, DISTANCE*FOOD_Y + DISTANCE / 2, 2 * RADIUS);

			break;
		}
	}
}

void Glutton()
{
	switch (DIRECTION)
	{
	//��������
	case 1:
		if (SNAKE[HEAD_X][HEAD_Y - 1] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			SNAKE[HEAD_X][HEAD_Y - 1] = 1;
			HEAD_Y -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE[HEAD_X][HEAD_Y - 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE[HEAD_X][HEAD_Y - 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			BONUS += BONUS_SCORE;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE[HEAD_X][HEAD_Y - 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

	//��������
	case 2:
		if (SNAKE[HEAD_X][HEAD_Y + 1] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			SNAKE[HEAD_X][HEAD_Y + 1] = 1;
			HEAD_Y += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE[HEAD_X][HEAD_Y + 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE[HEAD_X][HEAD_Y + 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			BONUS += BONUS_SCORE;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE[HEAD_X][HEAD_Y + 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

	//��������
	case 3:
		if (SNAKE[HEAD_X - 1][HEAD_Y] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			SNAKE[HEAD_X - 1][HEAD_Y] = 1;
			HEAD_X -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE[HEAD_X - 1][HEAD_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE[HEAD_X - 1][HEAD_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			BONUS += BONUS_SCORE;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE[HEAD_X - 1][HEAD_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

	//��������
	case 4:
		if (SNAKE[HEAD_X + 1][HEAD_Y] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			SNAKE[HEAD_X + 1][HEAD_Y] = 1;
			HEAD_X += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE[HEAD_X + 1][HEAD_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE[HEAD_X + 1][HEAD_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			BONUS += BONUS_SCORE;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE[HEAD_X + 1][HEAD_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

	default:break;
	}
}

void GluttonDoubleMode()
{
	//���һ�̳�ʳ��
	switch (DIRECTION1)
	{
		//��������
	case 1:
		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -1)  //ʳ��
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			SNAKE1[HEAD1_X][HEAD1_Y - 1] = 1;
			SNAKE2[HEAD1_X][HEAD1_Y - 1] = 0;
			HEAD1_Y -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			if (NUM1 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON1 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM1 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			BONUS1 += BONUS_SCORE;  //��������
			LAST_GLUTTON1 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM1 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM1 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 2:
		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -1)
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			SNAKE1[HEAD1_X][HEAD1_Y + 1] = 1;
			SNAKE2[HEAD1_X][HEAD1_Y + 1] = 0;
			HEAD1_Y += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			if (NUM1 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON1 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM1 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			BONUS1 += BONUS_SCORE;  //��������
			LAST_GLUTTON1 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM1 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM1 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 3:
		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -1)
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			SNAKE1[HEAD1_X - 1][HEAD1_Y] = 1;
			SNAKE2[HEAD1_X - 1][HEAD1_Y] = 0;
			HEAD1_X -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			if (NUM1 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON1 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM1 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			BONUS1 += BONUS_SCORE;  //��������
			LAST_GLUTTON1 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM1 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM1 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 4:
		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -1)
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			SNAKE1[HEAD1_X + 1][HEAD1_Y] = 1;
			SNAKE2[HEAD1_X + 1][HEAD1_Y] = 0;
			HEAD1_X += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			if (NUM1 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON1 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM1 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			BONUS1 += BONUS_SCORE;  //��������
			LAST_GLUTTON1 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM1 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM1 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

	default:break;
	}

	//��Ҷ��̳�ʳ��
	switch (DIRECTION2)
	{
		//��������
	case 1:
		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -1)
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			SNAKE2[HEAD2_X][HEAD2_Y - 1] = 1;
			SNAKE1[HEAD2_X][HEAD2_Y - 1] = 0;
			HEAD2_Y -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			if (NUM2 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON2 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM2 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			BONUS2 += BONUS_SCORE;  //��������
			LAST_GLUTTON2 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM2 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM2 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 2:
		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -1)
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			SNAKE2[HEAD2_X][HEAD2_Y + 1] = 1;
			SNAKE1[HEAD2_X][HEAD2_Y + 1] = 0;
			HEAD2_Y += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			if (NUM2 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON2 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM2 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			BONUS2 += BONUS_SCORE;  //��������
			LAST_GLUTTON2 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM2 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM2 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 3:
		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -1)
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			SNAKE2[HEAD2_X - 1][HEAD2_Y] = 1;
			SNAKE1[HEAD2_X - 1][HEAD2_Y] = 0;
			HEAD2_X -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			if (NUM2 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON2 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM2 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			BONUS2 += BONUS_SCORE;  //��������
			LAST_GLUTTON2 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM2 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM2 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 4:
		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -1)
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			SNAKE2[HEAD2_X + 1][HEAD2_Y] = 1;
			SNAKE1[HEAD2_X + 1][HEAD2_Y] = 0;
			HEAD2_X += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			if (NUM2 >= 2)  //���߳��ȴ���1ʱ
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON2 = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM2 += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			BONUS2 += BONUS_SCORE;  //��������
			LAST_GLUTTON2 = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM2 += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM2 += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

	default:break;
	}
}

void GluttonBarrierMode()
{
	srand((unsigned)time(NULL));  //�������
	int bonus_score = rand() % (MAX_BONUS_SCORE - MIN_BONUS_SCORE) + MIN_BONUS_SCORE;  
	//bonus_scoreȡֵ��Χ[MIN_BONUS_SCORE��MAX_BONUS_SCORE]
	int time_bonus = rand() % (MAX_TIME_BONUS - MIN_TIME_BONUS) + MIN_TIME_BONUS;
	//time_bonusȡֵ��Χ[MIN_TIME_BONUS��MAX_TIME_BONUS]
	
	switch (DIRECTION)
	{
		//��������
	case 1:
		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			SNAKE4[HEAD_X][HEAD_Y - 1] = 1;
			HEAD_Y -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			BONUS += bonus_score;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			TIME_LIMIT += time_bonus;  //����ʱ��
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 2:
		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			SNAKE4[HEAD_X][HEAD_Y + 1] = 1;
			HEAD_Y += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			BONUS += bonus_score;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			TIME_LIMIT += time_bonus;  //����ʱ��
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 3:
		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			SNAKE4[HEAD_X - 1][HEAD_Y] = 1;
			HEAD_X -= 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			BONUS += bonus_score;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			TIME_LIMIT += time_bonus;  //����ʱ��
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

		//��������
	case 4:
		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -1)  //ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			SNAKE4[HEAD_X + 1][HEAD_Y] = 1;
			HEAD_X += 1;  //��ʳ���Ϊ�ߵ�ͷ��

			MovingTag();
		}

		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -2)  //��ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //�۳���������
			LAST_GLUTTON = 1;  //����̳Ե��Ƕ�ʳ��
			TOX_FOOD_NUM += 1;  //�̳Զ�ʳ��������1
		}

		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -3)  //��������ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			BONUS += bonus_score;  //��������
			LAST_GLUTTON = 2;  //����̳Ե��ǽ�������ʳ��
			POINT_FOOD_NUM += 1;  //�̳Խ�������ʳ��������1
		}

		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -4)  //����ʱ��ʳ��
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			TIME_LIMIT += time_bonus;  //����ʱ��
			LAST_GLUTTON = 3;  //����̳Ե��ǽ���ʱ��ʳ��
			TIME_FOOD_NUM += 1;  //�̳Խ���ʱ��ʳ��������1
		}

		break;

	default:break;
	}
}

void MovingTag()
{
	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			if (SNAKE[i][j] > 0)
				SNAKE[i][j] += 1;
	SNAKE[HEAD_X][HEAD_Y] = 1;  //����
	NUM += 1;  //NUM��1
	NO_FOOD = true;  //������û��ʳ��
}

void MovingTagDoubleMode(int tag)
{
	switch (tag)
	{
	//���һ�����ƶ�NUM
	case 1:
	{
		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE1[i][j] > 0)
					SNAKE1[i][j] += 1;
		SNAKE1[HEAD1_X][HEAD1_Y] = 1;  //����
		NUM1 += 1;  //NUM��1
		NO_FOOD = true;  //������û��ʳ��
	}
	break;

	//��Ҷ������ƶ�NUM
	case 2:
	{
		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE2[i][j] > 0)
					SNAKE2[i][j] += 1;
		SNAKE2[HEAD2_X][HEAD2_Y] = 1;  //����
		NUM2 += 1;  //NUM��1
		NO_FOOD = true;  //������û��ʳ��
	}
	break;

	default:break;
	}
}

void ObliterateFood(int x,int y)
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(DISTANCE*x + DISTANCE / 2, DISTANCE*y + DISTANCE / 2, 2 * RADIUS);  //����ʳ��ͼ��

	SNAKE[x][y] = 0;  //�ı�ʳ��Ԫ�ص�ֵ
}

void ObliterateSnakeTail()
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(DISTANCE*TAIL_X + DISTANCE / 2, DISTANCE*TAIL_Y + DISTANCE / 2, RADIUS);  //����β��

	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			if (SNAKE[i][j] == NUM - 1)
			{
				SNAKE[TAIL_X][TAIL_Y] = 0;  //��β����
				TAIL_X = i;
				TAIL_Y = j;  //�ı���β
				NUM--;  //�ı�NUM
				return;
			}
}

void ObliterateSnakeTailDoubleMode(int mask)
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);

	switch (mask)
	{
	case 1:
	{
		fillcircle(DISTANCE*TAIL1_X + DISTANCE / 2, DISTANCE*TAIL1_Y + DISTANCE / 2, RADIUS);  //����β��

		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE1[i][j] == NUM1 - 1)
				{
					SNAKE1[TAIL1_X][TAIL1_Y] = 0;  //��β����
					TAIL1_X = i;
					TAIL1_Y = j;  //�ı���β
					NUM1--;  //�ı�NUM
					return;
				}
	}
	break;

	case 2:
	{
		fillcircle(DISTANCE*TAIL2_X + DISTANCE / 2, DISTANCE*TAIL2_Y + DISTANCE / 2, RADIUS);  //����β��

		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE2[i][j] == NUM2 - 1)
				{
					SNAKE2[TAIL2_X][TAIL2_Y] = 0;  //��β����
					TAIL2_X = i;
					TAIL2_Y = j;  //�ı���β
					NUM2--;  //�ı�NUM
					return;
				}
	}
	break;

	default:break;
	}
}

void ObliterateSnakeTailBarrierMode()
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(DISTANCE*TAIL_X + DISTANCE / 2, DISTANCE*TAIL_Y + DISTANCE / 2, RADIUS);  //����β��

	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
			if (SNAKE4[i][j] == NUM - 1)
			{
				SNAKE4[TAIL_X][TAIL_Y] = 0;  //��β����
				TAIL_X = i;
				TAIL_Y = j;  //�ı���β
				NUM--;  //�ı�NUM
				return;
			}
}

void TurnOperation()
{
	TURN++;
	srand((unsigned)time(NULL));
	
	switch (MODE)
	{
	case 1:
	case 2:
	{
		if (TURN % F_FOOD == 0)
		{
			TURN = 0;
			int random = rand() % 100 + 1;  //[1,100]

			//��ʳ�����30%������ʱ��ʳ�����35%����������ʳ�����35%
			if (random >= 1 && random <= 35)
				PointFood();  //��������ʳ��

			else if (random >= 36 && random <= 70)
				TimeFood();  //����ʱ��ʳ��

			else
				ToxFood();  //��ʳ��
		}
	}
	break;

	case 3:
		if (TURN % F_FOOD_DOUBLE_MODE == 0)
		{
			TURN = 0;
			int random = rand() % 100 + 1;  //[1,100]

			//��ʳ�����30%������ʱ��ʳ�����35%����������ʳ�����35%
			if (random >= 1 && random <= 35)
				PointFoodDoubleMode();  //��������ʳ��

			else if (random >= 36 && random <= 70)
				TimeFoodDoubleMode();  //����ʱ��ʳ��

			else
				ToxFoodDoubleMode();  //��ʳ��
		}
		break;

	case 4:
		switch (ROUND)
		{
		case 1:  //��һ��
			if (TURN % F_FOOD_FIRST_ROUND == 0)
			{
				TURN = 0;
				int random = rand() % 100 + 1;  //[1,100]

				//��ʳ�����30%������ʱ��ʳ�����35%����������ʳ�����35%
				if (random >= 1 && random <= 35)
					PointFoodBarrierMode();  //��������ʳ��

				else if (random >= 36 && random <= 70)
					TimeFoodBarrierMode();  //����ʱ��ʳ��

				else
					ToxFoodBarrierMode();  //��ʳ��
			}
			break;

		case 2:  //�ڶ���
			if (TURN % F_FOOD_SECOND_ROUND == 0)
			{
				TURN = 0;
				int random = rand() % 100 + 1;  //[1,100]

				//��ʳ�����34%������ʱ��ʳ�����33%����������ʳ�����33%
				if (random >= 1 && random <= 33)
					PointFoodBarrierMode();  //��������ʳ��

				else if (random >= 34 && random <= 66)
					TimeFoodBarrierMode();  //����ʱ��ʳ��

				else
					ToxFoodBarrierMode();  //��ʳ��
			}
			break;

		default:break;
		}
		break;

	default:break;
	}
}

void LoseGame()
{
	_getch();
	cleardevice();

	string s = "GAME OVER";
	LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 70, str);

	ShowGluttonNum();  //����Ļ����ʾ�����̳�����
	ShowScore();  //����Ļ����ʾ����
}

void LoseGameDoubleMode()
{
	_getch();
	cleardevice();

	long snake1 = 100 * (NUM1 - L_INIT_LEN) + BONUS1;  //���һ�ܷ�
	long snake2 = 100 * (NUM1 - L_INIT_LEN) + BONUS2;  //��Ҷ��ܷ�

	string gameover = "GAME OVER";
	LPCTSTR GAMEOVER = gameover.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2 - 120, GAMEOVER);
	
	ShowPlayerOne(snake1);
	ShowPlayerTwo(snake2);  //��ʾ������
	
	string s;
	if (LOSER == 1)
		s = "PLAYER 2 WIN!";
	else
		s = "PLAYER 1 WIN!";
	LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2, str);
}

void TimeOutDoubleMode()
{
	_getch();
	cleardevice();

	long snake1 = 100 * (NUM1 - L_INIT_LEN) + BONUS1;  //���һ�ܷ�
	long snake2 = 100 * (NUM1 - L_INIT_LEN) + BONUS2;  //��Ҷ��ܷ�
	
	string timeout = "TIME UP";
	LPCTSTR TIMEOUT = timeout.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2 - 120, TIMEOUT);
	
	ShowPlayerOne(snake1);
	ShowPlayerTwo(snake2);  //��ʾ������

	if (snake1 > snake2)
		LOSER = 2;
	else if (snake1 < snake2)
		LOSER = 1;
	else
		LOSER = 0;
	string result = "";  //������ַ���
	if (LOSER == 1)
		result = "PLAYER 1 WIN!";
	else if (LOSER == 2)
		result = "PLAYER 2 WIN!";
	else
		result = "EVEN!";
	LPCTSTR str = result.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2, str);
}

void ShowPlayerOne(long snake1)
{
	//��ʾ��PLAYER 1:��
	string player = "PLAYER 1:";
	LPCTSTR PLAYER = player.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 100, PLAYER);

	 //��ʾ��ʳ���̳�����
	stringstream num1;
	num1 << TOX_FOOD_NUM1;
	string num_str = "POISON FOOD:  " + num1.str();  //������ת��Ϊstring����
	LPCTSTR NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 80, NUM_STR);

	//��ʾ��������ʳ���̳�����
	stringstream num2;
	num2 << POINT_FOOD_NUM1;
	num_str = "POINT BONUS:  " + num2.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 60, NUM_STR);

	//��ʾ����ʱ��ʳ���̳�����
	stringstream num3;
	num3 << TIME_FOOD_NUM1;
	num_str = "TIME BONUS:    " + num3.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 40, NUM_STR);

	//��ʾ���һ���ܷ�
	if (isTimeOut)  //��ʱ�䵽�������
	{
		stringstream num4;
		num4 << snake1;
		num_str = "TOTAL SCORE:   " + num4.str();  //������ת��Ϊstring����
		NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
		outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 20, NUM_STR);
	}
}

void ShowPlayerTwo(long snake2)
{
	//��ʾ��PLAYER 2:��
	string player = "PLAYER 2:";
	LPCTSTR PLAYER = player.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 100, PLAYER);

	//��ʾ��ʳ���̳�����
	stringstream num1;
	num1 << TOX_FOOD_NUM2;
	string num_str = "POISON FOOD:  " + num1.str();  //������ת��Ϊstring����
	LPCTSTR NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 80, NUM_STR);

	//��ʾ��������ʳ���̳�����
	stringstream num2;
	num2 << POINT_FOOD_NUM2;
	num_str = "POINT BONUS:  " + num2.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 60, NUM_STR);

	//��ʾ����ʱ��ʳ���̳�����
	stringstream num3;
	num3 << TIME_FOOD_NUM2;
	num_str = "TIME BONUS:    " + num3.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 40, NUM_STR);

	//��ʾ��Ҷ����ܷ�
	if (isTimeOut)  //��ʱ�䵽�������
	{
		stringstream num4;
		num4 << snake2;
		num_str = "TOTAL SCORE:   " + num4.str();  //������ת��Ϊstring����
		NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
		outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 20, NUM_STR);
	}
}

void ShowGluttonNum()
{
	//��ʾ��ʳ���̳�����
	stringstream num1;
	num1 << TOX_FOOD_NUM;
	string num_str = "POISON FOOD:  " + num1.str();  //������ת��Ϊstring����
	LPCTSTR NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 50, NUM_STR);

	//��ʾ��������ʳ���̳�����
	stringstream num2;
	num2 << POINT_FOOD_NUM;
	num_str = "POINT BONUS:  " + num2.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 30, NUM_STR);

	//��ʾ����ʱ��ʳ���̳�����
	stringstream num3;
	num3 << TIME_FOOD_NUM;
	num_str = "TIME BONUS:    " + num3.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 10, NUM_STR);
}

void ShowScore()
{
	long score = 100 * (NUM - INIT_LEN) + BONUS;
	stringstream s1;
	s1 << score;
	string s = "SCORE:  " + s1.str();  //������ת��Ϊstring����
	LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 + 10, str);

	system("pause");
}

void ShowResultBarrierMode()
{
	_getch();
	cleardevice();
	
	//��ʾ��ʳ���̳�����
	stringstream num1;
	num1 << TOX_FOOD_NUM;
	string num_str = "POISON FOOD:  " + num1.str();  //������ת��Ϊstring����
	LPCTSTR NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 - 50, NUM_STR);

	//��ʾ��������ʳ���̳�����
	stringstream num2;
	num2 << POINT_FOOD_NUM;
	num_str = "POINT BONUS:  " + num2.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 - 30, NUM_STR);

	//��ʾ����ʱ��ʳ���̳�����
	stringstream num3;
	num3 << TIME_FOOD_NUM;
	num_str = "TIME BONUS:    " + num3.str();  //������ת��Ϊstring����
	NUM_STR = num_str.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 - 10, NUM_STR);

	//��ʾ������Ϸ����
	long score = 100 * (NUM - INIT_LEN) + BONUS;
	stringstream s1;
	s1 << score;
	string s = "SCORE:             " + s1.str();  //������ת��Ϊstring����
	LPCTSTR str = s.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 + 10, str);

	//��ʾ�ܷ���
	stringstream s2;
	s2 << TOTAL;
	string total_score = "TOTAL SCORE:  " + s2.str();  //������ת��Ϊstring����
	LPCTSTR total = total_score.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 + 30, total);

	system("pause");
}

bool IfPlayAgain()
{
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, "�Ƿ�����һ�֣�", "ϵͳ��ʾ", MB_YESNO) == IDYES)
		return true;
	else
		return false;
}

void BarrierModeInitialize()
{
	NUM = 0;  //ÿ����Ϸ��ʼ��NUM
	NO_FOOD = true;  //ÿ����Ϸ��ʼ��ʳ�����
	ifEndGame = false;  //ÿ����Ϸ��ʼ����������Ϸ
	ifLose = false;  //ÿ����Ϸ��ʼ��δ����Ϸ
	DIRECTION = 4;  //Ĭ�ϳ�ʼ����Ϊ��
	isTimeOut = false;  //ÿ����Ϸ��ʼ��Ϊδ��ʱ
	TIME_LIMIT = 60;  //ÿ����Ϸ��ʼ������ʱ��
	TURN = 0;  //ÿ����Ϸ��ʼ��TURN
	BONUS = 0;  //ÿ����Ϸ��ʼ��BONUS
	LAST_GLUTTON = 0;  //ÿ����Ϸ��ʼ������̳Ե�ʳ��
	TOX_FOOD_NUM = 0, POINT_FOOD_NUM = 0, TIME_FOOD_NUM = 0;  //ÿ�ֳ�ʼ���ֱ��̳�����
	BarrierGameNotLose = true;  //ÿ����Ϸ��ʼ���ϰ�ģʽ���
	WinBarrierMode = false;  //ÿ����ϷӮ���ϰ�ģʽ
}

void Congratulations()
{
	_getch();
	cleardevice();

	string s1 = "YOU WIN!", s2 = "CONGRATULATIONS!";
	LPCTSTR str1 = s1.c_str(), str2 = s2.c_str();  //��string����ת��ΪLPCTSTR����
	outtextxy(B_WIDTH / 2 - 30, B_HEIGHT / 2 - 10, str1);
	outtextxy(B_WIDTH / 2 - 30, B_HEIGHT / 2 + 10, str2);
}

void main()
{
	bool PlayAgain = true;  //Ĭ������һ��
	
	while (PlayAgain && !ifEndGame)
	{
		NUM = NUM1 = NUM2 = 0;  //ÿ����Ϸ��ʼ��NUM
		NO_FOOD = true;  //ÿ����Ϸ��ʼ��ʳ�����
		ifEndGame = false;  //ÿ����Ϸ��ʼ����������Ϸ
		ifLose = false;  //ÿ����Ϸ��ʼ��δ����Ϸ
		MODE = 1;  //Ĭ����ϰģʽ
		DIRECTION = DIRECTION1 = DIRECTION2 = 4;  //Ĭ�ϳ�ʼ����Ϊ��
		isTimeOut = false;  //ÿ����Ϸ��ʼ��Ϊδ��ʱ
		TIME_LIMIT = 60;
		TIME_LIMIT_DOUBLE = 120;  //ÿ����Ϸ��ʼ������ʱ��
		TURN = 0;  //ÿ����Ϸ��ʼ��TURN
		BONUS = BONUS1 = BONUS2 = 0;  //ÿ����Ϸ��ʼ��BONUS
		LAST_GLUTTON = 0;  //ÿ����Ϸ��ʼ������̳Ե�ʳ��
		LAST_GLUTTON1 = 0, LAST_GLUTTON2 = 0;  //ÿ����Ϸ��ʼ��˫��ģʽ�б�ʾ�����ʳ�ĵ���
		TOX_FOOD_NUM = 0, POINT_FOOD_NUM = 0, TIME_FOOD_NUM = 0;  //ÿ�ֳ�ʼ���ֱ��̳�����
		TOX_FOOD_NUM1 = 0, POINT_FOOD_NUM1 = 0, TIME_FOOD_NUM1 = 0;  //ÿ����Ϸ���һ���Ƶ��߱�ʾ�ֱ��̳�����
		TOX_FOOD_NUM2 = 0, POINT_FOOD_NUM2 = 0, TIME_FOOD_NUM2 = 0;  //ÿ����Ϸ��Ҷ����Ƶ��߱�ʾ�ֱ��̳�����
		TOTAL = 0;  //ÿ����Ϸ��ʼ����Ϸ�ܷ�
		ROUND = 1;  //ÿ����Ϸ��ʼ����ǰ����
		BarrierGameNotLose = true;  //ÿ����Ϸ��ʼ���ϰ�ģʽ���
		WinBarrierMode = false;  //ÿ����ϷӮ���ϰ�ģʽ

		Greeting();  //ȷ�Ϲ���ѡ����Ϸģʽ

		switch (MODE)
		{
		//ģʽ1����ϰģʽ
		case 1:
		{
			Initialize_Mode1();
			Game_Mode1();
		}
		break;

		//ģʽ2����ʱģʽ
		case 2:
		{
			Initialize_Mode1();
			Game_Mode2();
		}
		break;

		//ģʽ3,˫��ģʽ
		case 3:
		{
			Initialize_Mode3();
			Game_Mode3();
		}
		break;

		//ģʽ4���ϰ�ģʽ
		case 4:
		{
			while (PlayAgain && !ifEndGame && BarrierGameNotLose)
			{
				BarrierModeInitialize();  //�ϰ�ģʽ��Ϸ���ݳ�ʼ��

				Initialize_Mode4();
				Game_Mode4();
				ShowResultBarrierMode();  //��ʾ������Ϸ���
				ROUND += 1;

				if (WinBarrierMode)
					break;  //��Ϸһ������
			}
		}
		break;

		default:break;
		}
		
		if (!ifEndGame)
		{
			if (MODE == 1 || MODE == 2)
				LoseGame();
			else if (MODE == 3)
			{
				if (isTimeOut)
					TimeOutDoubleMode();
				else
					LoseGameDoubleMode();
			}
			else if (MODE == 4)
			{
				if (WinBarrierMode)
					Congratulations();  //��ͨ�������ֿ�
			}
			
			PlayAgain = IfPlayAgain();
			closegraph();
		}  //�������û��˳���Ϸ�����
		else
		{
			_getch();
			cleardevice();

			if (MODE == 1 || MODE == 2)
				LoseGame();
			else if (MODE == 3)
				LoseGameDoubleMode();
			else if (MODE == 4)
				ShowResultBarrierMode();  //��ʾ������Ϸ���

			closegraph();
			break;
		}  //�û��˳������
	}
	
	system("cls");
	printf("��ӭ�´�������\n");
	system("pause");
}