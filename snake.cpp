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
#define L_WIDTH 640  //双人模式
#define L_HEIGHT 480  //双人模式
#define B_WIDTH 640  //障碍模式
#define B_HEIGHT 480  //障碍模式
#define RADIUS 5
#define FOOD_RADIUS 8
#define DISTANCE 10
#define COLUMN_NUM 46  //COLUMN_NUM=WIDTH/DISTANCE-2;
#define ROW_NUM 34  //ROW_NUM=HEIGHT/DISTANCE-2;
#define L_COLUMN_NUM 62  //双人模式，L_COLUMN_NUM=L_WIDTH/DISTANCE-2;
#define L_ROW_NUM 46  //双人模式，L_ROW_NUM=L_HEIGHT/DISTANCE-2;
#define B_COLUMN_NUM 62  //障碍模式，B_COLUMN_NUM=B_WIDTH/DISTANCE-2;
#define B_ROW_NUM 46  //障碍模式，B_ROW_NUM=B_HEIGHT/DISTANCE-2;
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
#define INIT_LEN 6  //蛇的初始长度
#define L_INIT_LEN 4  //双人模式蛇的初始长度
#define TIME_BONUS 5  //奖励时间，双人模式时间可调
#define MAX_TIME_BONUS 20  //最大奖励时间
#define MIN_TIME_BONUS 5  //最小奖励时间
#define BONUS_SCORE 150  //奖励分数
#define MAX_BONUS_SCORE 200  //最大奖励分数
#define MIN_BONUS_SCORE 20  //最小奖励分数
#define DERIVED_SCORE 50  //毒食物扣除BONUS
#define F_FOOD 100  //道具周期
#define F_FOOD_DOUBLE_MODE 50  //双人模式道具周期
#define F_FOOD_FIRST_ROUND 80  //障碍模式第一轮道具周期
#define F_FOOD_SECOND_ROUND 100  //障碍模式第二轮道具周期
//按照一般难度，第一关通过分数为1500，第二关为3500
#define FIRST_REQUIRED_SCORE 1000  //障碍模式第一轮需要总分
#define SECOND_REQUIRED_SCORE 2000  //障碍模式第二轮需要总分

using namespace std;

//模式1，练习模式；模式2，限时模式；模式3，双人模式；模式4，障碍模式
//大于0表示蛇身，递加表示新蛇身，-1表示食物，-2表示毒食物，-3表示奖励分数食物，-4表示奖励时间食物，-5表示障碍物
//食物为红色，毒食物减少一节蛇尾并扣除50分BONUS，奖励时间食物加15秒游戏时间，奖励分数食物加150游戏分数
int SNAKE[COLUMN_NUM][ROW_NUM];  //表示奖励及蛇的情况
int SNAKE1[L_COLUMN_NUM][L_ROW_NUM], SNAKE2[L_COLUMN_NUM][L_ROW_NUM]; //双人模式，SNAKE1表示玩家1，SNAKE2表示玩家2
int SNAKE4[B_COLUMN_NUM][B_ROW_NUM];  //表示奖励及蛇的情况
int MODE = 1; //选择游戏模式，1表示练习模式，2表示限时模式，3表示双人模式
int DIRECTION = 4;  //表示蛇头运动的方向，1，2，3，4分别表示上下左右
int DIRECTION1 = 4, DIRECTION2 = 4;  //双人模式表示蛇头运动的方向，1，2，3，4分别表示上下左右
bool ifLose = false;  //判断是否输，默认为false
int HEAD_X, HEAD_Y;  //记录蛇头的数组位置
int HEAD1_X, HEAD1_Y, HEAD2_X, HEAD2_Y;  //双人模式记录蛇头的数组位置
int TAIL_X, TAIL_Y;  //记录蛇尾的数组位置 
int TAIL1_X, TAIL1_Y, TAIL2_X, TAIL2_Y;  //双人模式记录蛇尾的数组位置
int SLEEP_INTERVAL = 100;  //每次绘制停留在屏幕上时间
int NUM = 0;  //标记蛇的身体
int NUM1 = 0, NUM2 = 0;  //双人模式标记蛇的身体
bool NO_FOOD = true;  //是否有食物
bool ifEndGame = false;  //默认不退出游戏
int LOSER = 1;  //双人模式记录哪一个玩家输，默认玩家一
bool isTimeOut = false;  //默认不超时
int TURN = 0;  //判断产生毒食物,奖励分数食物，奖励时间食物
int BONUS = 0;  //奖励分数
int BONUS1 = 0,BONUS2 = 0;  //双人模式奖励分数
int TIME_LIMIT = 60;  //限时模式的限时，单位秒
int TIME_LIMIT_DOUBLE = 120;  //双人模式的限时，单位秒
int LAST_GLUTTON = 0;  //表示最后吞食的道具，1表示毒食物，2表示奖励分数食物，3表示奖励时间食物
int LAST_GLUTTON1 = 0, LAST_GLUTTON2 = 0;  //双人模式中表示最后吞食的道具
int TOX_FOOD_NUM = 0, POINT_FOOD_NUM = 0, TIME_FOOD_NUM = 0;  //表示分别吞吃数量
int TOX_FOOD_NUM1 = 0, POINT_FOOD_NUM1 = 0, TIME_FOOD_NUM1 = 0;  //玩家一控制的蛇表示分别吞吃数量
int TOX_FOOD_NUM2 = 0, POINT_FOOD_NUM2 = 0, TIME_FOOD_NUM2 = 0;  //玩家二控制的蛇表示分别吞吃数量
int TOTAL = 0;  //障碍模式记录多轮游戏的总分
int ROUND = 1;  //障碍模式记录当前轮数
bool BarrierGameNotLose = true;  //障碍模式是否输
bool WinBarrierMode = false;  //障碍模式是否赢

void Greeting();  //确认游戏规则并选择游戏模式
void ModeChoose();  //选择游戏模式，1表示练习模式，2表示限时模式，3表示双人模式
void Initialize_Mode1();  //适用于模式1（练习模式）、模式2（限时模式）
void Initialize_Mode3();  //适用于模式3（双人模式）
void Initialize_Mode4();  //适用于模式4（障碍模式）
void Game_Mode1();  //模式1，练习模式的主程序
void Game_Mode2();  //模式2，限时模式的主程序
void Game_Mode3();  //模式3，双人模式的主程序
void Game_Mode4();  //模式4，障碍模式的主程序
void Round1();  //模式4，障碍模式的第一轮
void Round2();  //模式4，障碍模式的第二轮
void InstructionMode2();  //模式2，限时模式的游戏说明
void InstructionMode3();  //模式3，双人模式的游戏说明
void InstructionMode4();  //模式4，障碍模式的游戏说明
void CountDown();  //游戏前倒数三秒
void CountDownDoubleMode();  //双人模式游戏前倒数三秒
void CountDownBarrierMode();  //双人模式游戏前倒数三秒
void DrawFrame();  //画蛇移动的边框
void DrawFrameDoubleMode();  //双人模式画蛇移动的边框
void DrawFrameBarrierMode();  //障碍模式画蛇移动的边框
void DrawFood();  //清屏后重新绘制食物
void DrawFoodDoubleMode();  //双人模式清屏后重新绘制食物
void DrawFoodBarrierMode();  //障碍模式清屏后重新绘制食物
void DrawBarrier();  //障碍模式清屏后重新绘制障碍物
void ChToDirection(char ch);  //将输入字符转化为方向
void ChToDirectionDoubleMode(char ch);  //双人模式将字符转化为方向
void Moving();  //蛇（数组）的移动
void MovingDoubleMode();  //双人模式蛇（数组）的移动
void MovingSnakeOne();  //双人模式玩家一蛇（数组）的移动
void MovingSnakeTwo();  //双人模式玩家二蛇（数组）的移动
void MovingBarrierMode();  //障碍模式蛇（数组）的移动
void ObliterateSnake();  //擦除蛇
void ObliterateSnakeDoubleMode();  //双人模式擦除蛇
void ObliterateSnakeBarrierMode();  //障碍模式擦除蛇
void DrawSnake();  //在屏幕上绘制蛇
void DrawSnakeDoubleMode();  //双人模式在屏幕上绘制蛇
void DrawSnakeOne();  //双人模式在屏幕上绘制玩家一的蛇
void DrawSnakeTwo();  //双人模式在屏幕上绘制玩家二的蛇
void DrawSnakeBarrierMode();  //障碍模式在屏幕上绘制蛇
void ShowTag();  //显示最后吞吃道具
void ShowTagDoubleMode();  //双人模式显示最后吞吃道具
bool IfLose();  //判断是否输
bool IfHitFrame();  //判断是否由于触边输
bool IfHitSelf();  //判断是否咬到自己输
bool IfLoseDoubleMode();  //双人模式判断是否输
bool IfHitFrameDoubleMode();  //双人模式判断是否由于触边输
bool IfHitSelfDoubleMode();  //双人模式判断是否咬到自己输
bool IfHitOpponentDoubleMode();  //双人模式判断是否咬到对手
bool IfLoseBarrierMode();  //障碍模式判断是否输
bool IfHitFrameBarrierMode();  //障碍模式判断是否由于触边输
bool IfHitSelfBarrierMode();  //障碍模式判断是否咬到自己输
bool IfHitBarrier();  //障碍模式判断是否碰到障碍物
void Food();  //随机在地图中心部分随机产生食物
void FoodDoubleMode();  //双人模式随机在地图中心部分随机产生食物
void FoodBarrierMode();  //障碍模式随机在地图中心部分随机产生食物
bool WithinScreen(int x, int y);  //判断点是否在TAG标签范围内
bool WithinScreenDoubleMode(int x, int y);  //双人模式判断点是否在TAG标签范围内
bool WithinScreenBarrierMode(int x, int y);  //障碍模式判断点是否在TAG标签范围内
void Glutton();  //吞吃食物
void GluttonDoubleMode();  //双人模式吞吃食物
void GluttonBarrierMode();  //障碍模式吞吃食物
void MovingTag();  //更新蛇的标签值,用于吞吃时
void MovingTagDoubleMode(int tag);  //双人模式更新蛇的标签值,用于吞吃时
void ObliterateFood(int x,int y);  //擦除食物
void ObliterateSnakeTail();  //吞食毒食物消除蛇尾
void ObliterateSnakeTailDoubleMode(int mask);  //双人模式吞食毒食物消除蛇尾
void ObliterateSnakeTailBarrierMode();  //障碍模式吞食毒食物消除蛇尾
void TurnOperation();  //对三种turn参数的操作
void ToxFood();  //产生有毒食物
void PointFood();  //产生奖励分数食物
void TimeFood();  //产生奖励时间食物
void ToxFoodDoubleMode();  //双人模式产生有毒食物
void PointFoodDoubleMode();  //双人模式产生奖励分数食物
void TimeFoodDoubleMode();  //双人模式产生奖励时间食物
void ToxFoodBarrierMode();  //障碍模式产生有毒食物
void PointFoodBarrierMode();  //障碍模式产生奖励分数食物
void TimeFoodBarrierMode();  //障碍模式产生奖励时间食物
void Pause();  //用于暂停游戏
bool Quit();  //用于退出游戏
void LoseGame();  //游戏输后
void LoseGameDoubleMode();  //双人模式游戏输后
void TimeOutDoubleMode();  //双人模式到时
void ShowPlayerOne(long snake1);  //在屏幕上显示玩家一的情况
void ShowPlayerTwo(long snake2);  //在屏幕上显示玩家二的情况
void ShowGluttonNum();  //在屏幕上显示道具吞吃数量
void ShowScore();  //显示分数
void ShowResultBarrierMode();  //障碍模式结束一轮后显示本轮游戏结果
bool IfPlayAgain();  //一局结束后是否再玩一局
void BarrierModeInitialize();  //障碍模式游戏数据初始化
void Congratulations();  //障碍模式通过所有轮卡

void Greeting()
{
	system("cls");
	puts("欢迎进入贪吃蛇游戏！");
	puts("按键AWSD控制方向，P暂停游戏，Q退出游戏");

	while (1)
	{
		string str;
		printf("Understand?[y/n]");
		getline(cin, str);  //读入输入的行
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
	puts("选择游戏模式");
	puts("1-------练习模式");
	puts("2-------限时模式");
	puts("3-------双人模式");
	puts("4-------障碍模式");

	while (1)
	{
		string str;
		printf("Mode:");
		getline(cin, str);  //读入输入的行

		if (!str.compare("1") || !str.compare("2") || !str.compare("3") || !str.compare("4"))
		{
			istringstream stream;
			stream.str(str);  //将字符串转化为流
			int mode = 1;
			stream >> mode;  //将流转化为整形

			MODE = mode;
			return;
		}
	}
}

void Initialize_Mode1()  //单人模式
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
	}  //用NUM标记蛇身
		
	HEAD_X = COLUMN_NUM / 2 + INIT_LEN / 2;
	HEAD_Y = ROW_NUM / 2;
	TAIL_X = COLUMN_NUM / 2 - INIT_LEN / 2;
	TAIL_Y = ROW_NUM / 2;  //记录蛇头、蛇尾坐标
}

void Initialize_Mode3()  //双人模式
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

	//用NUM标记蛇身
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
	
	//记录蛇头、蛇尾坐标
	HEAD1_X = L_COLUMN_NUM / 4 + L_INIT_LEN / 2;
	HEAD1_Y = j1;
	TAIL1_X = L_COLUMN_NUM / 4 - L_INIT_LEN / 2;
	TAIL1_Y = j1;  //玩家一控制的蛇

	HEAD2_X = L_COLUMN_NUM * 3 / 4 + L_INIT_LEN / 2;
	HEAD2_Y = j2;
	TAIL2_X = L_COLUMN_NUM * 3 / 4 - L_INIT_LEN / 2;
	TAIL2_Y = j2;  //玩家二控制的蛇
}

void Initialize_Mode4()  //障碍模式
{
	initgraph(B_WIDTH, B_HEIGHT);
	cleardevice();
	CountDownBarrierMode();  //倒计时
	DrawFrameBarrierMode();  //绘制游戏边框

	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
			SNAKE4[i][j] = 0;

	int j = B_ROW_NUM / 2 + 10;
	for (int i = B_COLUMN_NUM / 2 + INIT_LEN / 2;i >= B_COLUMN_NUM / 2 - INIT_LEN / 2;i--)
	{
		NUM += 1;
		SNAKE4[i][j] = NUM;
	}  //用NUM标记蛇身

	HEAD_X = B_COLUMN_NUM / 2 + INIT_LEN / 2;
	HEAD_Y = B_ROW_NUM / 2 + 10;
	TAIL_X = B_COLUMN_NUM / 2 - INIT_LEN / 2;
	TAIL_Y = B_ROW_NUM / 2 + 10;  //记录蛇头、蛇尾坐标
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
		string s = s1.str();  //将int转化为string型
		LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
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
		string s = s1.str();  //将int转化为string型
		LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
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
		string s = s1.str();  //将int转化为string型
		LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
		outtextxy(B_WIDTH / 2 - 10, B_HEIGHT / 2 - 10, str);

		Sleep(1000);
	}
}

void InstructionMode2()
{
	cleardevice();

	string s = "限时60秒";
	LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(WIDTH / 2 - 20, HEIGHT / 2 - 20, str);

	Sleep(1000);
}

void InstructionMode3()
{
	cleardevice();

	string s = "限时120秒";
	LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 30, L_HEIGHT / 2 - 30, str);

	Sleep(1800);

	cleardevice();

	s = "确认小键盘开启";
	str = s.c_str();  //将string类型转化为LPCTSTR类型
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
	}  //将每轮需要的分数转化为字符串

	string s = "ROUND " + stream1.str(), s1 = "TIME LIMIT:   60 SEC", s2 = "REQUIRED SCORE:   "+stream2.str();
	LPCTSTR str = s.c_str(), str1 = s1.c_str(), str2 = s2.c_str(); //将string类型转化为LPCTSTR类型
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
			break;  //IfLose()返回值为true时表示输，退出本轮游戏

		Glutton();  //吞吃食物
		ObliterateSnake();  //擦除蛇
		Moving();  //调整数组
		DrawSnake();  //绘制蛇

		if (NO_FOOD)
			Food();

		TurnOperation();  //对三个turn参数进行操作
	}
}

void Game_Mode2()
{
	char ch = 'd';  //默认方向为右
	SYSTEMTIME time;  //定义变量保存当前时间
	GetLocalTime(&time); //获取当前时间
	int tHour = time.wHour;  //获取当前时间的小时数
	int tMin = time.wMinute;  //获取当前时间的分钟数
	int tSec = time.wSecond;  //获取当前时间的秒数
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
			break;  //IfLose()返回值为true时表示输，退出本轮游戏

		Glutton();  //吞吃食物
		ObliterateSnake();  //擦除蛇
		Moving();  //调整数组
		DrawSnake();  //绘制蛇

		if (NO_FOOD)
			Food();

		TurnOperation();  //对三个turn参数进行操作

		GetLocalTime(&time); //获取当前时间
		int num2 = time.wHour * 3600 + time.wMinute * 60 + time.wSecond;
		if (num2 - num1 >= TIME_LIMIT)
			break;  //当游戏时间大于限制时间时退出
	}
}

void Game_Mode3()  //双人模式
{
	char ch = 'd';
	SYSTEMTIME time;  //定义变量保存当前时间
	GetLocalTime(&time); //获取当前时间
	int tHour = time.wHour;  //获取当前时间的小时数
	int tMin = time.wMinute;  //获取当前时间的分钟数
	int tSec = time.wSecond;  //获取当前时间的秒数
	int num1 = tHour * 3600 + tMin * 60 + tSec;

	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			ChToDirectionDoubleMode(tolower(ch));  //玩家一输入字母

			if (tolower(ch) == 'q')
			{
				ifEndGame = Quit();
				if (ifEndGame)
					break;
			}
		}

		if (IfLoseDoubleMode())
			break;  //IfLose()返回值为true时表示输，退出本轮游戏

		GluttonDoubleMode();  //吞吃食物
		ObliterateSnakeDoubleMode();  //擦除蛇
		MovingDoubleMode();  //调整数组
		DrawSnakeDoubleMode();  //绘制蛇

		if (NO_FOOD)
			FoodDoubleMode();  //场地上有两个食物

		TurnOperation();  //对三个turn参数进行操作

		GetLocalTime(&time); //获取当前时间
		int num2 = time.wHour * 3600 + time.wMinute * 60 + time.wSecond;
		if (num2 - num1 >= TIME_LIMIT_DOUBLE)
		{
			isTimeOut = true;
			break;  //当游戏时间大于限制时间时退出
		}
	}
}

void Game_Mode4()
{
	switch (ROUND)
	{
	case 1:
		Round1();  //布置地图
		break;

	case 2:
		Round2();  //布置地图
		break;

	default:return;
	}

	char ch = 'd';
	SYSTEMTIME time;  //定义变量保存当前时间
	GetLocalTime(&time); //获取当前时间
	int tHour = time.wHour;  //获取当前时间的小时数
	int tMin = time.wMinute;  //获取当前时间的分钟数
	int tSec = time.wSecond;  //获取当前时间的秒数
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
					int score = 100 * (NUM - INIT_LEN) + BONUS;  //当局分数
					TOTAL += score;  //总分

					break;
				}
			}
		}

		if (IfLoseBarrierMode())
		{
			BarrierGameNotLose = false;  //游戏输

			int score = 100 * (NUM - INIT_LEN) + BONUS;  //当局分数
			TOTAL += score;  //总分

			break;  //IfLoseBarrierMode()返回值为true时表示输，退出本轮游戏
		}
			
		GluttonBarrierMode();  //吞吃食物
		ObliterateSnakeBarrierMode();  //擦除蛇
		MovingBarrierMode();  //调整数组
		DrawSnakeBarrierMode();  //绘制蛇

		if (NO_FOOD)
			FoodBarrierMode();

		TurnOperation();  //对三个turn参数进行操作

		GetLocalTime(&time); //获取当前时间
		int num2 = time.wHour * 3600 + time.wMinute * 60 + time.wSecond;
		if (num2 - num1 >= TIME_LIMIT)
		{
			int score = 100 * (NUM - INIT_LEN) + BONUS;  //当局分数
			TOTAL += score;  //总分

			switch (ROUND)  //根据轮数决定要求的分数
			{
			case 1:
			{
				if (TOTAL < FIRST_REQUIRED_SCORE)
					BarrierGameNotLose = false;  //若总分未到达1500分则输
			}
			break;

			case 2:
			{
				if (TOTAL < SECOND_REQUIRED_SCORE)
					BarrierGameNotLose = false;  //若总分未到达1500分则输
			}
			break;

			default:break;
			}
			
			if (ROUND == 2)
				WinBarrierMode = true;  //表示两轮过后已经赢

			break;  //当游戏时间大于限制时间时退出
		}
	}
}

void Round1()
{
	for (int i = B_COLUMN_NUM / 2 - 8;i <= B_COLUMN_NUM / 2 + 8;i++)
		for (int j = B_ROW_NUM / 2 - 4;j <= B_ROW_NUM / 2 + 4;j++)
			SNAKE4[i][j] = -5;  //设置障碍物
	//障碍物左侧坐标为DISTANCE*(B_COLUMN_NUM/2-8)，右侧坐标为DISTANCE*(B_COLUMN_NUM/2+8)+DISTANCE
	//上方坐标为DISTANCE*(B_ROW_NUM/2-4)，下方坐标为DISTANCE*(B_ROW_NUM/2+4)+DISRANCE
}

void Round2()
{
	for (int i = B_COLUMN_NUM / 4 + 1;i <= B_COLUMN_NUM / 4 + 5;i++)
		for (int j = B_ROW_NUM / 4 + 1;j <= B_ROW_NUM / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //设置障碍物
	//障碍物左侧坐标为DISTANCE*(B_COLUMN_NUM/4+1)，右侧坐标为DISTANCE*(B_COLUMN_NUM/4+5)+DISTANCE
	//上方坐标为DISTANCE*(B_ROW_NUM/4+1)，下方坐标为DISTANCE*(B_ROW_NUM/4+5)+DISTANCE

	for (int i = B_COLUMN_NUM * 3 / 4 + 1;i <= B_COLUMN_NUM * 3 / 4 + 5;i++)
		for (int j = B_ROW_NUM / 4 + 1;j <= B_ROW_NUM / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //设置障碍物
	//障碍物左侧坐标为DISTANCE*(B_COLUMN_NUM*3/4+1)，右侧坐标为DISTANCE*(B_COLUMN_NUM*3/4+5)+DISTANCE
	//上方坐标为DISTANCE*(B_ROW_NUM/4+1)，下方坐标为DISTANCE*(B_ROW_NUM/4+5)+DISTANCE

	for (int i = B_COLUMN_NUM / 4 + 1;i <= B_COLUMN_NUM / 4 + 5;i++)
		for (int j = B_ROW_NUM * 3 / 4 + 1;j <= B_ROW_NUM * 3 / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //设置障碍物
	//障碍物左侧坐标为DISTANCE*(B_COLUMN_NUM/4+1)，右侧坐标为DISTANCE*(B_COLUMN_NUM/4+5)+DISTANCE
	//上方坐标为DISTANCE*(B_ROW_NUM*3/4+1)，下方坐标为DISTANCE*(B_ROW_NUM*3/4+5)+DISTANCE

	for (int i = B_COLUMN_NUM * 3 / 4 + 1;i <= B_COLUMN_NUM * 3 / 4 + 5;i++)
		for (int j = B_ROW_NUM * 3 / 4 + 1;j <= B_ROW_NUM * 3 / 4 + 5;j++)
			SNAKE4[i][j] = -5;  //设置障碍物
	//障碍物左侧坐标为DISTANCE*(B_COLUMN_NUM*3/4+1)，右侧坐标为DISTANCE*(B_COLUMN_NUM*3/4+5)+DISTANCE
	//上方坐标为DISTANCE*(B_ROW_NUM*3/4+1)，下方坐标为DISTANCE*(B_ROW_NUM*3/4+5)+DISTANCE
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
	//玩家一awsd控制蛇
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

	//玩家二控制的蛇
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
			//食物
			if (SNAKE[i][j] == -1)
			{
				setlinecolor(BLUE);
				setfillcolor(RED);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}

			//毒食物，奖励时间食物，奖励分数食物的外形相同
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
			//食物
			if (SNAKE1[i][j] == -1 && SNAKE2[i][j] == -1)
			{
				setlinecolor(BLUE);
				setfillcolor(RED);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}

			//毒食物，奖励时间食物，奖励分数食物的外形相同
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
			//食物
			if (SNAKE4[i][j] == -1)
			{
				setlinecolor(BLUE);
				setfillcolor(RED);
				fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, FOOD_RADIUS);
			}

			//毒食物，奖励时间食物，奖励分数食物的外形相同
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
		//左上方障碍物
		int left = DISTANCE*(B_COLUMN_NUM / 4 + 1), right = DISTANCE*(B_COLUMN_NUM / 4 + 5) + DISTANCE;
		int top = DISTANCE*(B_ROW_NUM / 4 + 1), bottom = DISTANCE*(B_ROW_NUM / 4 + 5) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);

		//右上方障碍物
		left = DISTANCE*(B_COLUMN_NUM * 3 / 4 + 1), right = DISTANCE*(B_COLUMN_NUM * 3 / 4 + 5) + DISTANCE;
		top = DISTANCE*(B_ROW_NUM / 4 + 1), bottom = DISTANCE*(B_ROW_NUM / 4 + 5) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);

		//左下方障碍物
		left = DISTANCE*(B_COLUMN_NUM / 4 + 1), right = DISTANCE*(B_COLUMN_NUM / 4 + 5) + DISTANCE;
		top = DISTANCE*(B_ROW_NUM * 3 / 4 + 1), bottom = DISTANCE*(B_ROW_NUM * 3 / 4 + 5) + DISTANCE;
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);
		fillrectangle(left, top, right, bottom);

		//右下方障碍物
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
	//方向向上
	case 1:
		if (SNAKE[HEAD_X][HEAD_Y - 1] > 0)
			return true;
		break;

	//方向向下
	case 2:
		if (SNAKE[HEAD_X][HEAD_Y + 1] > 0)
			return true;
		break;

	//方向向左
	case 3:
		if (SNAKE[HEAD_X - 1][HEAD_Y] > 0)
			return true;
		break;

	//方向向右
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
	int head2_x = DISTANCE*HEAD2_X + DISTANCE / 2, head2_y = DISTANCE*HEAD2_Y + DISTANCE / 2;  //数组下标对应的坐标

	if (head1_x<DISTANCE + RADIUS || head1_x>L_WIDTH - DISTANCE - RADIUS || head1_y<DISTANCE + RADIUS || head1_y>L_HEIGHT - DISTANCE - RADIUS)
	{
		LOSER = 1;  //玩家一输
		return true;
	}
	if (head2_x<DISTANCE + RADIUS || head2_x>L_WIDTH - DISTANCE - RADIUS || head2_y<DISTANCE + RADIUS || head2_y>L_HEIGHT - DISTANCE - RADIUS)
	{
		LOSER = 2;  //玩家二输
		return true;
	}
	return false;
}

bool IfHitSelfDoubleMode()
{
	//检查玩家一
	switch (DIRECTION1)
	{
		//方向向上
	case 1:
		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//方向向下
	case 2:
		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//方向向左
	case 3:
		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//方向向右
	case 4:
		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;
	}

	//检查玩家二
	switch (DIRECTION2)
	{
		//方向向上
	case 1:
		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//方向向下
	case 2:
		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//方向向左
	case 3:
		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//方向向右
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
	//检查玩家一
	switch (DIRECTION1)
	{
		//方向向上
	case 1:
		if (SNAKE2[HEAD1_X][HEAD1_Y - 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//方向向下
	case 2:
		if (SNAKE2[HEAD1_X][HEAD1_Y + 1] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//方向向左
	case 3:
		if (SNAKE2[HEAD1_X - 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;

		//方向向右
	case 4:
		if (SNAKE2[HEAD1_X + 1][HEAD1_Y] > 0)
		{
			LOSER = 1;
			return true;
		}
		break;
	}

	//检查玩家二
	switch (DIRECTION2)
	{
		//方向向上
	case 1:
		if (SNAKE1[HEAD2_X][HEAD2_Y - 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//方向向下
	case 2:
		if (SNAKE1[HEAD2_X][HEAD2_Y + 1] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//方向向左
	case 3:
		if (SNAKE1[HEAD2_X - 1][HEAD2_Y] > 0)
		{
			LOSER = 2;
			return true;
		}
		break;

		//方向向右
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
		//方向向上
	case 1:
		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -5)
			return true;
		break;

		//方向向下
	case 2:
		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -5)
			return true;
		break;

		//方向向左
	case 3:
		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -5)
			return true;
		break;

		//方向向右
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
		//方向向上
	case 1:
		if (SNAKE4[HEAD_X][HEAD_Y - 1] > 0)
			return true;
		break;

		//方向向下
	case 2:
		if (SNAKE4[HEAD_X][HEAD_Y + 1] > 0)
			return true;
		break;

		//方向向左
	case 3:
		if (SNAKE4[HEAD_X - 1][HEAD_Y] > 0)
			return true;
		break;

		//方向向右
	case 4:
		if (SNAKE4[HEAD_X + 1][HEAD_Y] > 0)
			return true;
		break;
	}

	return false;
}

void ObliterateSnake()
{
	cleardevice();  //清屏
	DrawFrame();  //绘制边框
	DrawFood();  //重新绘制食物
	ShowTag();  //显示最后吞吃道具
}

void ObliterateSnakeDoubleMode()
{
	cleardevice();  //清屏
	DrawFrameDoubleMode();  //绘制边框
	DrawFoodDoubleMode();  //重新绘制食物
	ShowTagDoubleMode();  //显示最后吞吃道具
}

void ObliterateSnakeBarrierMode()
{
	cleardevice();  //清屏
	DrawFrameBarrierMode();  //绘制边框
	DrawFoodBarrierMode();  //重新绘制食物
	DrawBarrier();  //重新绘制障碍物
	ShowTag();  //显示最后吞吃道具
}

void DrawSnake()
{
	setlinecolor(YELLOW);
	setfillcolor(BLUE);
	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			if (SNAKE[i][j] > 0)
				if (SNAKE[i][j] == 1)
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //突出蛇头
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
	setfillcolor(BLUE);  //玩家一的蛇为黄色边框蓝色内部
	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE1[i][j] > 0)
				if (SNAKE1[i][j] == 1)
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //突出蛇头
				else
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS);

	Sleep(SLEEP_INTERVAL / 2);
}

void DrawSnakeTwo()
{
	setlinecolor(RED);
	setfillcolor(BROWN);  //玩家二的蛇为红色边框棕色内部
	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE2[i][j] > 0)
				if (SNAKE2[i][j] == 1)
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //突出蛇头
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
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS + 1);  //突出蛇头
				else
					fillcircle(DISTANCE*i + DISTANCE / 2, DISTANCE*j + DISTANCE / 2, RADIUS);


	Sleep(SLEEP_INTERVAL);
}

void ShowTag() 
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(DISTANCE + 3, DISTANCE + 3, 10 * DISTANCE, 5 * DISTANCE);  //擦去之前在角落里写的TAG

	string tag = "";
	if (LAST_GLUTTON == 1)  //毒食物
		tag = "POISON FOOD";
	else if (LAST_GLUTTON == 2)  //奖励分数
		tag = "SCORE BONUS";
	else if (LAST_GLUTTON == 3)  //奖励时间
		tag = "TIME BONUS";
	LPCTSTR TAG = tag.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(DISTANCE, DISTANCE, TAG);
}

void ShowTagDoubleMode()  
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(DISTANCE + 3, DISTANCE + 3, 10 * DISTANCE, 5 * DISTANCE);  
	fillrectangle(L_WIDTH - 10 * DISTANCE, DISTANCE + 3, L_WIDTH - DISTANCE - 3, 5 * DISTANCE);  //擦去之前在角落里写的TAG

	string tag1 = "", tag2 = "";
	if (LAST_GLUTTON1 == 1)  //毒食物
		tag1 = "POISON FOOD";
	else if (LAST_GLUTTON1 == 2)  //奖励分数
		tag1 = "SCORE BONUS";
	else if (LAST_GLUTTON1 == 3)  //奖励时间
		tag1 = "TIME BONUS";

	if (LAST_GLUTTON2 == 1)  //毒食物
		tag2 = "POISON FOOD";
	else if (LAST_GLUTTON2 == 2)  //奖励分数
		tag2 = "SCORE BONUS";
	else if (LAST_GLUTTON2 == 3)  //奖励时间
		tag2 = "TIME BONUS";

	LPCTSTR TAG = tag1.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(DISTANCE, DISTANCE, TAG);

	TAG = tag2.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH - 10 * DISTANCE, DISTANCE, TAG);
}

void Pause()
{
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, "游戏暂停", "系统提示", MB_OK) == IDYES)
		return;
}

bool Quit()
{
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, "确认退出游戏？", "系统提示", MB_YESNO) == IDYES)
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
				SNAKE[i][j] = 0;  //去除蛇尾

			if (SNAKE[i][j] == NUM - 1)
			{
				TAIL_X = i;
				TAIL_Y = j;
			}  //新蛇尾
		}

	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			if (SNAKE[i][j] > 0)
				SNAKE[i][j]++;  //除目前的蛇首与蛇尾
	
	switch (DIRECTION)
	{
	//蛇头向上
	case 1:
	{
		SNAKE[HEAD_X][HEAD_Y - 1] = 1;
		HEAD_Y -= 1;
	}
		break;

	//蛇头向下
	case 2:
	{
		SNAKE[HEAD_X][HEAD_Y + 1] = 1;
		HEAD_Y += 1;
	}
		break;
	
	//蛇头向左
	case 3:
	{
		SNAKE[HEAD_X - 1][HEAD_Y] = 1;
		HEAD_X -= 1;
	}
		break;

	//蛇头向右
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
				SNAKE1[i][j] = 0;  //去除蛇尾

			if (SNAKE1[i][j] == NUM1 - 1)
			{
				TAIL1_X = i;
				TAIL1_Y = j;
			}  //新蛇尾
		}

	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE1[i][j] > 0)
				SNAKE1[i][j]++;  //除目前的蛇首与蛇尾

	switch (DIRECTION1)
	{
		//蛇头向上
	case 1:
	{
		SNAKE1[HEAD1_X][HEAD1_Y - 1] = 1;
		HEAD1_Y -= 1;
	}
	break;

	//蛇头向下
	case 2:
	{
		SNAKE1[HEAD1_X][HEAD1_Y + 1] = 1;
		HEAD1_Y += 1;
	}
	break;

	//蛇头向左
	case 3:
	{
		SNAKE1[HEAD1_X - 1][HEAD1_Y] = 1;
		HEAD1_X -= 1;
	}
	break;

	//蛇头向右
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
				SNAKE2[i][j] = 0;  //去除蛇尾

			if (SNAKE2[i][j] == NUM2 - 1)
			{
				TAIL2_X = i;
				TAIL2_Y = j;
			}  //新蛇尾
		}

	for (int i = 0;i < L_COLUMN_NUM;i++)
		for (int j = 0;j < L_ROW_NUM;j++)
			if (SNAKE2[i][j] > 0)
				SNAKE2[i][j]++;  //除目前的蛇首与蛇尾

	switch (DIRECTION2)
	{
		//蛇头向上
	case 1:
	{
		SNAKE2[HEAD2_X][HEAD2_Y - 1] = 1;
		HEAD2_Y -= 1;
	}
	break;

	//蛇头向下
	case 2:
	{
		SNAKE2[HEAD2_X][HEAD2_Y + 1] = 1;
		HEAD2_Y += 1;
	}
	break;

	//蛇头向左
	case 3:
	{
		SNAKE2[HEAD2_X - 1][HEAD2_Y] = 1;
		HEAD2_X -= 1;
	}
	break;

	//蛇头向右
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
				SNAKE4[i][j] = 0;  //去除蛇尾

			if (SNAKE4[i][j] == NUM - 1)
			{
				TAIL_X = i;
				TAIL_Y = j;
			}  //新蛇尾
		}

	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
			if (SNAKE4[i][j] > 0)
				SNAKE4[i][j]++;  //除目前的蛇首与蛇尾

	switch (DIRECTION)
	{
		//蛇头向上
	case 1:
	{
		SNAKE4[HEAD_X][HEAD_Y - 1] = 1;
		HEAD_Y -= 1;
	}
	break;

	//蛇头向下
	case 2:
	{
		SNAKE4[HEAD_X][HEAD_Y + 1] = 1;
		HEAD_Y += 1;
	}
	break;

	//蛇头向左
	case 3:
	{
		SNAKE4[HEAD_X - 1][HEAD_Y] = 1;
		HEAD_X -= 1;
	}
	break;

	//蛇头向右
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
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_X取值范围[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Y取值范围[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int X = DISTANCE*x + DISTANCE / 2;  //待判断点的横坐标
	int Y = DISTANCE*y + DISTANCE / 2;  //待判断点的纵坐标
	if (X < 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //在TAG标签范围内
	return false;  //在TAG标签范围外
}

void PointFood()
{
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_X取值范围[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Y取值范围[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_X取值范围[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Y取值范围[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (MAX_FOOD_X - MIN_FOOD_X) + MIN_FOOD_X;  //FOOD_X取值范围[MIN_FOOD_X,MAX_FOOD_X]
		FOOD_Y = rand() % (MAX_FOOD_Y - MIN_FOOD_Y) + MIN_FOOD_Y;  //FOOD_Y取值范围[MIN_FOOD_Y,MAX_FOOD_Y]

		if (SNAKE[FOOD_X][FOOD_Y] == 0 && !WithinScreen(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_X取值范围[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Y取值范围[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //若不为蛇身
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
	int X = DISTANCE*x + DISTANCE / 2;  //待判断点的横坐标
	int Y = DISTANCE*y + DISTANCE / 2;  //待判断点的纵坐标
	if (X < 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //在玩家一TAG标签范围内
	if (X > L_WIDTH - 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //在玩家二TAG标签范围内
	return false;  //在TAG标签范围外
}

void PointFoodDoubleMode()
{
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_X取值范围[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Y取值范围[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_X取值范围[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Y取值范围[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (L_MAX_FOOD_X - L_MIN_FOOD_X) + L_MIN_FOOD_X;  //FOOD_X取值范围[L_MIN_FOOD_X,L_MAX_FOOD_X]
		FOOD_Y = rand() % (L_MAX_FOOD_Y - L_MIN_FOOD_Y) + L_MIN_FOOD_Y;  //FOOD_Y取值范围[L_MIN_FOOD_Y,L_MAX_FOOD_Y]

		if (SNAKE1[FOOD_X][FOOD_Y] == 0 && SNAKE2[FOOD_X][FOOD_Y] == 0 && !WithinScreenDoubleMode(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int FOOD_X, FOOD_Y;  //FOOD_X的取值范围在[4,145]，FOOD_Y的取值范围在[4,75]
	srand((unsigned)time(NULL));
	while (true)
	{
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_X取值范围[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Y取值范围[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	int X = DISTANCE*x + DISTANCE / 2;  //待判断点的横坐标
	int Y = DISTANCE*y + DISTANCE / 2;  //待判断点的纵坐标
	if (X < 14 * DISTANCE && Y < 4 * DISTANCE)
		return true;  //在TAG标签范围内
	return false;  //在TAG标签范围外
}

void PointFoodBarrierMode()
{
	int FOOD_X, FOOD_Y; 
	srand((unsigned)time(NULL));

	while (true)
	{
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_X取值范围[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Y取值范围[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_X取值范围[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Y取值范围[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
		FOOD_X = rand() % (B_MAX_FOOD_X - B_MIN_FOOD_X) + B_MIN_FOOD_X;  //FOOD_X取值范围[B_MIN_FOOD_X,B_MAX_FOOD_X]
		FOOD_Y = rand() % (B_MAX_FOOD_Y - B_MIN_FOOD_Y) + B_MIN_FOOD_Y;  //FOOD_Y取值范围[B_MIN_FOOD_Y,B_MAX_FOOD_Y]

		if (SNAKE4[FOOD_X][FOOD_Y] == 0 && !WithinScreenBarrierMode(FOOD_X, FOOD_Y))  //若不为蛇身、道具、食物
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
	//方向向上
	case 1:
		if (SNAKE[HEAD_X][HEAD_Y - 1] == -1)  //食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			SNAKE[HEAD_X][HEAD_Y - 1] = 1;
			HEAD_Y -= 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE[HEAD_X][HEAD_Y - 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE[HEAD_X][HEAD_Y - 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			BONUS += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE[HEAD_X][HEAD_Y - 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
		}

		break;

	//方向向下
	case 2:
		if (SNAKE[HEAD_X][HEAD_Y + 1] == -1)  //食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			SNAKE[HEAD_X][HEAD_Y + 1] = 1;
			HEAD_Y += 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE[HEAD_X][HEAD_Y + 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE[HEAD_X][HEAD_Y + 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			BONUS += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE[HEAD_X][HEAD_Y + 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
		}

		break;

	//方向向左
	case 3:
		if (SNAKE[HEAD_X - 1][HEAD_Y] == -1)  //食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			SNAKE[HEAD_X - 1][HEAD_Y] = 1;
			HEAD_X -= 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE[HEAD_X - 1][HEAD_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE[HEAD_X - 1][HEAD_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			BONUS += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE[HEAD_X - 1][HEAD_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
		}

		break;

	//方向向右
	case 4:
		if (SNAKE[HEAD_X + 1][HEAD_Y] == -1)  //食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			SNAKE[HEAD_X + 1][HEAD_Y] = 1;
			HEAD_X += 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE[HEAD_X + 1][HEAD_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			ObliterateSnakeTail();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE[HEAD_X + 1][HEAD_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			BONUS += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE[HEAD_X + 1][HEAD_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			TIME_LIMIT += TIME_BONUS;
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
		}

		break;

	default:break;
	}
}

void GluttonDoubleMode()
{
	//玩家一吞吃食物
	switch (DIRECTION1)
	{
		//方向向上
	case 1:
		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -1)  //食物
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			SNAKE1[HEAD1_X][HEAD1_Y - 1] = 1;
			SNAKE2[HEAD1_X][HEAD1_Y - 1] = 0;
			HEAD1_Y -= 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			if (NUM1 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON1 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM1 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			BONUS1 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON1 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM1 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y - 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD1_X, HEAD1_Y - 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM1 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向下
	case 2:
		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -1)
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			SNAKE1[HEAD1_X][HEAD1_Y + 1] = 1;
			SNAKE2[HEAD1_X][HEAD1_Y + 1] = 0;
			HEAD1_Y += 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			if (NUM1 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON1 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM1 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			BONUS1 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON1 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM1 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE1[HEAD1_X][HEAD1_Y + 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD1_X, HEAD1_Y + 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM1 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向左
	case 3:
		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -1)
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			SNAKE1[HEAD1_X - 1][HEAD1_Y] = 1;
			SNAKE2[HEAD1_X - 1][HEAD1_Y] = 0;
			HEAD1_X -= 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			if (NUM1 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON1 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM1 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			BONUS1 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON1 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM1 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE1[HEAD1_X - 1][HEAD1_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD1_X - 1, HEAD1_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM1 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向右
	case 4:
		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -1)
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			SNAKE1[HEAD1_X + 1][HEAD1_Y] = 1;
			SNAKE2[HEAD1_X + 1][HEAD1_Y] = 0;
			HEAD1_X += 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(1);
		}

		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			if (NUM1 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(1);
			BONUS1 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON1 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM1 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			BONUS1 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON1 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM1 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE1[HEAD1_X + 1][HEAD1_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD1_X + 1, HEAD1_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON1 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM1 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

	default:break;
	}

	//玩家二吞吃食物
	switch (DIRECTION2)
	{
		//方向向上
	case 1:
		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -1)
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			SNAKE2[HEAD2_X][HEAD2_Y - 1] = 1;
			SNAKE1[HEAD2_X][HEAD2_Y - 1] = 0;
			HEAD2_Y -= 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			if (NUM2 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON2 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM2 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			BONUS2 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON2 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM2 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y - 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD2_X, HEAD2_Y - 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM2 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向下
	case 2:
		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -1)
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			SNAKE2[HEAD2_X][HEAD2_Y + 1] = 1;
			SNAKE1[HEAD2_X][HEAD2_Y + 1] = 0;
			HEAD2_Y += 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			if (NUM2 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON2 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM2 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			BONUS2 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON2 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM2 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE2[HEAD2_X][HEAD2_Y + 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD2_X, HEAD2_Y + 1);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM2 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向左
	case 3:
		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -1)
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			SNAKE2[HEAD2_X - 1][HEAD2_Y] = 1;
			SNAKE1[HEAD2_X - 1][HEAD2_Y] = 0;
			HEAD2_X -= 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			if (NUM2 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON2 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM2 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			BONUS2 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON2 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM2 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE2[HEAD2_X - 1][HEAD2_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD2_X - 1, HEAD2_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM2 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向右
	case 4:
		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -1)
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			SNAKE2[HEAD2_X + 1][HEAD2_Y] = 1;
			SNAKE1[HEAD2_X + 1][HEAD2_Y] = 0;
			HEAD2_X += 1;  //将食物变为蛇的头部

			MovingTagDoubleMode(2);
		}

		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			if (NUM2 >= 2)  //在蛇长度大于1时
				ObliterateSnakeTailDoubleMode(2);
			BONUS2 -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON2 = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM2 += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			BONUS2 += BONUS_SCORE;  //奖励分数
			LAST_GLUTTON2 = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM2 += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE2[HEAD2_X + 1][HEAD2_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD2_X + 1, HEAD2_Y);
			TIME_LIMIT_DOUBLE += TIME_BONUS;
			LAST_GLUTTON2 = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM2 += 1;  //吞吃奖励时间食物数量加1
		}

		break;

	default:break;
	}
}

void GluttonBarrierMode()
{
	srand((unsigned)time(NULL));  //随机种子
	int bonus_score = rand() % (MAX_BONUS_SCORE - MIN_BONUS_SCORE) + MIN_BONUS_SCORE;  
	//bonus_score取值范围[MIN_BONUS_SCORE，MAX_BONUS_SCORE]
	int time_bonus = rand() % (MAX_TIME_BONUS - MIN_TIME_BONUS) + MIN_TIME_BONUS;
	//time_bonus取值范围[MIN_TIME_BONUS，MAX_TIME_BONUS]
	
	switch (DIRECTION)
	{
		//方向向上
	case 1:
		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -1)  //食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			SNAKE4[HEAD_X][HEAD_Y - 1] = 1;
			HEAD_Y -= 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			BONUS += bonus_score;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE4[HEAD_X][HEAD_Y - 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X, HEAD_Y - 1);
			TIME_LIMIT += time_bonus;  //奖励时间
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向下
	case 2:
		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -1)  //食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			SNAKE4[HEAD_X][HEAD_Y + 1] = 1;
			HEAD_Y += 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			BONUS += bonus_score;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE4[HEAD_X][HEAD_Y + 1] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X, HEAD_Y + 1);
			TIME_LIMIT += time_bonus;  //奖励时间
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向左
	case 3:
		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -1)  //食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			SNAKE4[HEAD_X - 1][HEAD_Y] = 1;
			HEAD_X -= 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			BONUS += bonus_score;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE4[HEAD_X - 1][HEAD_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X - 1, HEAD_Y);
			TIME_LIMIT += time_bonus;  //奖励时间
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
		}

		break;

		//方向向右
	case 4:
		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -1)  //食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			SNAKE4[HEAD_X + 1][HEAD_Y] = 1;
			HEAD_X += 1;  //将食物变为蛇的头部

			MovingTag();
		}

		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -2)  //毒食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			ObliterateSnakeTailBarrierMode();
			BONUS -= DERIVED_SCORE;  //扣除奖励分数
			LAST_GLUTTON = 1;  //最后吞吃的是毒食物
			TOX_FOOD_NUM += 1;  //吞吃毒食物数量加1
		}

		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -3)  //奖励分数食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			BONUS += bonus_score;  //奖励分数
			LAST_GLUTTON = 2;  //最后吞吃的是奖励分数食物
			POINT_FOOD_NUM += 1;  //吞吃奖励分数食物数量加1
		}

		if (SNAKE4[HEAD_X + 1][HEAD_Y] == -4)  //奖励时间食物
		{
			ObliterateFood(HEAD_X + 1, HEAD_Y);
			TIME_LIMIT += time_bonus;  //奖励时间
			LAST_GLUTTON = 3;  //最后吞吃的是奖励时间食物
			TIME_FOOD_NUM += 1;  //吞吃奖励时间食物数量加1
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
	SNAKE[HEAD_X][HEAD_Y] = 1;  //蛇首
	NUM += 1;  //NUM加1
	NO_FOOD = true;  //场地上没有食物
}

void MovingTagDoubleMode(int tag)
{
	switch (tag)
	{
	//玩家一的蛇移动NUM
	case 1:
	{
		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE1[i][j] > 0)
					SNAKE1[i][j] += 1;
		SNAKE1[HEAD1_X][HEAD1_Y] = 1;  //蛇首
		NUM1 += 1;  //NUM加1
		NO_FOOD = true;  //场地上没有食物
	}
	break;

	//玩家二的蛇移动NUM
	case 2:
	{
		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE2[i][j] > 0)
					SNAKE2[i][j] += 1;
		SNAKE2[HEAD2_X][HEAD2_Y] = 1;  //蛇首
		NUM2 += 1;  //NUM加1
		NO_FOOD = true;  //场地上没有食物
	}
	break;

	default:break;
	}
}

void ObliterateFood(int x,int y)
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(DISTANCE*x + DISTANCE / 2, DISTANCE*y + DISTANCE / 2, 2 * RADIUS);  //擦除食物图像

	SNAKE[x][y] = 0;  //改变食物元素的值
}

void ObliterateSnakeTail()
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(DISTANCE*TAIL_X + DISTANCE / 2, DISTANCE*TAIL_Y + DISTANCE / 2, RADIUS);  //擦除尾部

	for (int i = 0;i < COLUMN_NUM;i++)
		for (int j = 0;j < ROW_NUM;j++)
			if (SNAKE[i][j] == NUM - 1)
			{
				SNAKE[TAIL_X][TAIL_Y] = 0;  //蛇尾清零
				TAIL_X = i;
				TAIL_Y = j;  //改变蛇尾
				NUM--;  //改变NUM
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
		fillcircle(DISTANCE*TAIL1_X + DISTANCE / 2, DISTANCE*TAIL1_Y + DISTANCE / 2, RADIUS);  //擦除尾部

		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE1[i][j] == NUM1 - 1)
				{
					SNAKE1[TAIL1_X][TAIL1_Y] = 0;  //蛇尾清零
					TAIL1_X = i;
					TAIL1_Y = j;  //改变蛇尾
					NUM1--;  //改变NUM
					return;
				}
	}
	break;

	case 2:
	{
		fillcircle(DISTANCE*TAIL2_X + DISTANCE / 2, DISTANCE*TAIL2_Y + DISTANCE / 2, RADIUS);  //擦除尾部

		for (int i = 0;i < L_COLUMN_NUM;i++)
			for (int j = 0;j < L_ROW_NUM;j++)
				if (SNAKE2[i][j] == NUM2 - 1)
				{
					SNAKE2[TAIL2_X][TAIL2_Y] = 0;  //蛇尾清零
					TAIL2_X = i;
					TAIL2_Y = j;  //改变蛇尾
					NUM2--;  //改变NUM
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
	fillcircle(DISTANCE*TAIL_X + DISTANCE / 2, DISTANCE*TAIL_Y + DISTANCE / 2, RADIUS);  //擦除尾部

	for (int i = 0;i < B_COLUMN_NUM;i++)
		for (int j = 0;j < B_ROW_NUM;j++)
			if (SNAKE4[i][j] == NUM - 1)
			{
				SNAKE4[TAIL_X][TAIL_Y] = 0;  //蛇尾清零
				TAIL_X = i;
				TAIL_Y = j;  //改变蛇尾
				NUM--;  //改变NUM
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

			//毒食物概率30%，奖励时间食物概率35%，奖励分数食物概率35%
			if (random >= 1 && random <= 35)
				PointFood();  //奖励分数食物

			else if (random >= 36 && random <= 70)
				TimeFood();  //奖励时间食物

			else
				ToxFood();  //毒食物
		}
	}
	break;

	case 3:
		if (TURN % F_FOOD_DOUBLE_MODE == 0)
		{
			TURN = 0;
			int random = rand() % 100 + 1;  //[1,100]

			//毒食物概率30%，奖励时间食物概率35%，奖励分数食物概率35%
			if (random >= 1 && random <= 35)
				PointFoodDoubleMode();  //奖励分数食物

			else if (random >= 36 && random <= 70)
				TimeFoodDoubleMode();  //奖励时间食物

			else
				ToxFoodDoubleMode();  //毒食物
		}
		break;

	case 4:
		switch (ROUND)
		{
		case 1:  //第一轮
			if (TURN % F_FOOD_FIRST_ROUND == 0)
			{
				TURN = 0;
				int random = rand() % 100 + 1;  //[1,100]

				//毒食物概率30%，奖励时间食物概率35%，奖励分数食物概率35%
				if (random >= 1 && random <= 35)
					PointFoodBarrierMode();  //奖励分数食物

				else if (random >= 36 && random <= 70)
					TimeFoodBarrierMode();  //奖励时间食物

				else
					ToxFoodBarrierMode();  //毒食物
			}
			break;

		case 2:  //第二轮
			if (TURN % F_FOOD_SECOND_ROUND == 0)
			{
				TURN = 0;
				int random = rand() % 100 + 1;  //[1,100]

				//毒食物概率34%，奖励时间食物概率33%，奖励分数食物概率33%
				if (random >= 1 && random <= 33)
					PointFoodBarrierMode();  //奖励分数食物

				else if (random >= 34 && random <= 66)
					TimeFoodBarrierMode();  //奖励时间食物

				else
					ToxFoodBarrierMode();  //毒食物
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
	LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 70, str);

	ShowGluttonNum();  //在屏幕上显示道具吞吃数量
	ShowScore();  //在屏幕上显示分数
}

void LoseGameDoubleMode()
{
	_getch();
	cleardevice();

	long snake1 = 100 * (NUM1 - L_INIT_LEN) + BONUS1;  //玩家一总分
	long snake2 = 100 * (NUM1 - L_INIT_LEN) + BONUS2;  //玩家二总分

	string gameover = "GAME OVER";
	LPCTSTR GAMEOVER = gameover.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2 - 120, GAMEOVER);
	
	ShowPlayerOne(snake1);
	ShowPlayerTwo(snake2);  //显示玩家情况
	
	string s;
	if (LOSER == 1)
		s = "PLAYER 2 WIN!";
	else
		s = "PLAYER 1 WIN!";
	LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2, str);
}

void TimeOutDoubleMode()
{
	_getch();
	cleardevice();

	long snake1 = 100 * (NUM1 - L_INIT_LEN) + BONUS1;  //玩家一总分
	long snake2 = 100 * (NUM1 - L_INIT_LEN) + BONUS2;  //玩家二总分
	
	string timeout = "TIME UP";
	LPCTSTR TIMEOUT = timeout.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2 - 120, TIMEOUT);
	
	ShowPlayerOne(snake1);
	ShowPlayerTwo(snake2);  //显示玩家情况

	if (snake1 > snake2)
		LOSER = 2;
	else if (snake1 < snake2)
		LOSER = 1;
	else
		LOSER = 0;
	string result = "";  //结果的字符串
	if (LOSER == 1)
		result = "PLAYER 1 WIN!";
	else if (LOSER == 2)
		result = "PLAYER 2 WIN!";
	else
		result = "EVEN!";
	LPCTSTR str = result.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 50, L_HEIGHT / 2, str);
}

void ShowPlayerOne(long snake1)
{
	//显示“PLAYER 1:”
	string player = "PLAYER 1:";
	LPCTSTR PLAYER = player.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 100, PLAYER);

	 //显示毒食物吞吃数量
	stringstream num1;
	num1 << TOX_FOOD_NUM1;
	string num_str = "POISON FOOD:  " + num1.str();  //将整形转化为string类型
	LPCTSTR NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 80, NUM_STR);

	//显示奖励分数食物吞吃数量
	stringstream num2;
	num2 << POINT_FOOD_NUM1;
	num_str = "POINT BONUS:  " + num2.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 60, NUM_STR);

	//显示奖励时间食物吞吃数量
	stringstream num3;
	num3 << TIME_FOOD_NUM1;
	num_str = "TIME BONUS:    " + num3.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 40, NUM_STR);

	//显示玩家一的总分
	if (isTimeOut)  //在时间到的情况下
	{
		stringstream num4;
		num4 << snake1;
		num_str = "TOTAL SCORE:   " + num4.str();  //将整形转化为string类型
		NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
		outtextxy(L_WIDTH / 2 - 140, L_HEIGHT / 2 - 20, NUM_STR);
	}
}

void ShowPlayerTwo(long snake2)
{
	//显示“PLAYER 2:”
	string player = "PLAYER 2:";
	LPCTSTR PLAYER = player.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 100, PLAYER);

	//显示毒食物吞吃数量
	stringstream num1;
	num1 << TOX_FOOD_NUM2;
	string num_str = "POISON FOOD:  " + num1.str();  //将整形转化为string类型
	LPCTSTR NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 80, NUM_STR);

	//显示奖励分数食物吞吃数量
	stringstream num2;
	num2 << POINT_FOOD_NUM2;
	num_str = "POINT BONUS:  " + num2.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 60, NUM_STR);

	//显示奖励时间食物吞吃数量
	stringstream num3;
	num3 << TIME_FOOD_NUM2;
	num_str = "TIME BONUS:    " + num3.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 40, NUM_STR);

	//显示玩家二的总分
	if (isTimeOut)  //在时间到的情况下
	{
		stringstream num4;
		num4 << snake2;
		num_str = "TOTAL SCORE:   " + num4.str();  //将整形转化为string类型
		NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
		outtextxy(L_WIDTH / 2 + 10, L_HEIGHT / 2 - 20, NUM_STR);
	}
}

void ShowGluttonNum()
{
	//显示毒食物吞吃数量
	stringstream num1;
	num1 << TOX_FOOD_NUM;
	string num_str = "POISON FOOD:  " + num1.str();  //将整形转化为string类型
	LPCTSTR NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 50, NUM_STR);

	//显示奖励分数食物吞吃数量
	stringstream num2;
	num2 << POINT_FOOD_NUM;
	num_str = "POINT BONUS:  " + num2.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 30, NUM_STR);

	//显示奖励时间食物吞吃数量
	stringstream num3;
	num3 << TIME_FOOD_NUM;
	num_str = "TIME BONUS:    " + num3.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 10, NUM_STR);
}

void ShowScore()
{
	long score = 100 * (NUM - INIT_LEN) + BONUS;
	stringstream s1;
	s1 << score;
	string s = "SCORE:  " + s1.str();  //将整形转化为string类型
	LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(WIDTH / 2 - 50, HEIGHT / 2 + 10, str);

	system("pause");
}

void ShowResultBarrierMode()
{
	_getch();
	cleardevice();
	
	//显示毒食物吞吃数量
	stringstream num1;
	num1 << TOX_FOOD_NUM;
	string num_str = "POISON FOOD:  " + num1.str();  //将整形转化为string类型
	LPCTSTR NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 - 50, NUM_STR);

	//显示奖励分数食物吞吃数量
	stringstream num2;
	num2 << POINT_FOOD_NUM;
	num_str = "POINT BONUS:  " + num2.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 - 30, NUM_STR);

	//显示奖励时间食物吞吃数量
	stringstream num3;
	num3 << TIME_FOOD_NUM;
	num_str = "TIME BONUS:    " + num3.str();  //将整形转化为string类型
	NUM_STR = num_str.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 - 10, NUM_STR);

	//显示本轮游戏分数
	long score = 100 * (NUM - INIT_LEN) + BONUS;
	stringstream s1;
	s1 << score;
	string s = "SCORE:             " + s1.str();  //将整形转化为string类型
	LPCTSTR str = s.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 + 10, str);

	//显示总分数
	stringstream s2;
	s2 << TOTAL;
	string total_score = "TOTAL SCORE:  " + s2.str();  //将整形转化为string类型
	LPCTSTR total = total_score.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(B_WIDTH / 2 - 50, B_HEIGHT / 2 + 30, total);

	system("pause");
}

bool IfPlayAgain()
{
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, "是否再玩一局？", "系统提示", MB_YESNO) == IDYES)
		return true;
	else
		return false;
}

void BarrierModeInitialize()
{
	NUM = 0;  //每局游戏初始化NUM
	NO_FOOD = true;  //每局游戏初始化食物情况
	ifEndGame = false;  //每局游戏初始化不结束游戏
	ifLose = false;  //每局游戏初始化未输游戏
	DIRECTION = 4;  //默认初始方向为右
	isTimeOut = false;  //每局游戏初始化为未超时
	TIME_LIMIT = 60;  //每局游戏初始化限制时间
	TURN = 0;  //每局游戏初始化TURN
	BONUS = 0;  //每局游戏初始化BONUS
	LAST_GLUTTON = 0;  //每局游戏初始化最后吞吃的食物
	TOX_FOOD_NUM = 0, POINT_FOOD_NUM = 0, TIME_FOOD_NUM = 0;  //每局初始化分别吞吃数量
	BarrierGameNotLose = true;  //每局游戏初始化障碍模式情况
	WinBarrierMode = false;  //每局游戏赢得障碍模式
}

void Congratulations()
{
	_getch();
	cleardevice();

	string s1 = "YOU WIN!", s2 = "CONGRATULATIONS!";
	LPCTSTR str1 = s1.c_str(), str2 = s2.c_str();  //将string类型转化为LPCTSTR类型
	outtextxy(B_WIDTH / 2 - 30, B_HEIGHT / 2 - 10, str1);
	outtextxy(B_WIDTH / 2 - 30, B_HEIGHT / 2 + 10, str2);
}

void main()
{
	bool PlayAgain = true;  //默认再玩一局
	
	while (PlayAgain && !ifEndGame)
	{
		NUM = NUM1 = NUM2 = 0;  //每局游戏初始化NUM
		NO_FOOD = true;  //每局游戏初始化食物情况
		ifEndGame = false;  //每局游戏初始化不结束游戏
		ifLose = false;  //每局游戏初始化未输游戏
		MODE = 1;  //默认练习模式
		DIRECTION = DIRECTION1 = DIRECTION2 = 4;  //默认初始方向为右
		isTimeOut = false;  //每局游戏初始化为未超时
		TIME_LIMIT = 60;
		TIME_LIMIT_DOUBLE = 120;  //每局游戏初始化限制时间
		TURN = 0;  //每局游戏初始化TURN
		BONUS = BONUS1 = BONUS2 = 0;  //每局游戏初始化BONUS
		LAST_GLUTTON = 0;  //每局游戏初始化最后吞吃的食物
		LAST_GLUTTON1 = 0, LAST_GLUTTON2 = 0;  //每局游戏初始化双人模式中表示最后吞食的道具
		TOX_FOOD_NUM = 0, POINT_FOOD_NUM = 0, TIME_FOOD_NUM = 0;  //每局初始化分别吞吃数量
		TOX_FOOD_NUM1 = 0, POINT_FOOD_NUM1 = 0, TIME_FOOD_NUM1 = 0;  //每局游戏玩家一控制的蛇表示分别吞吃数量
		TOX_FOOD_NUM2 = 0, POINT_FOOD_NUM2 = 0, TIME_FOOD_NUM2 = 0;  //每局游戏玩家二控制的蛇表示分别吞吃数量
		TOTAL = 0;  //每局游戏初始化游戏总分
		ROUND = 1;  //每局游戏初始化当前轮数
		BarrierGameNotLose = true;  //每局游戏初始化障碍模式情况
		WinBarrierMode = false;  //每局游戏赢得障碍模式

		Greeting();  //确认规则并选择游戏模式

		switch (MODE)
		{
		//模式1，练习模式
		case 1:
		{
			Initialize_Mode1();
			Game_Mode1();
		}
		break;

		//模式2，限时模式
		case 2:
		{
			Initialize_Mode1();
			Game_Mode2();
		}
		break;

		//模式3,双人模式
		case 3:
		{
			Initialize_Mode3();
			Game_Mode3();
		}
		break;

		//模式4，障碍模式
		case 4:
		{
			while (PlayAgain && !ifEndGame && BarrierGameNotLose)
			{
				BarrierModeInitialize();  //障碍模式游戏数据初始化

				Initialize_Mode4();
				Game_Mode4();
				ShowResultBarrierMode();  //显示本轮游戏结果
				ROUND += 1;

				if (WinBarrierMode)
					break;  //游戏一共两轮
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
					Congratulations();  //若通过所有轮卡
			}
			
			PlayAgain = IfPlayAgain();
			closegraph();
		}  //若不是用户退出游戏的情况
		else
		{
			_getch();
			cleardevice();

			if (MODE == 1 || MODE == 2)
				LoseGame();
			else if (MODE == 3)
				LoseGameDoubleMode();
			else if (MODE == 4)
				ShowResultBarrierMode();  //显示本轮游戏情况

			closegraph();
			break;
		}  //用户退出的情况
	}
	
	system("cls");
	printf("欢迎下次再来！\n");
	system("pause");
}