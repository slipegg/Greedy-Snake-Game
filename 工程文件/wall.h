#pragma once
#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<time.h>
#include<cstring>
#include<Windows.h>
using namespace std;
class Wall
{
private:
	clock_t stratT;//记录开始时间
	char map[150][150];//关键地图，用来记录每一处储存的信息
	int addWallNum;//增加的墙壁的数量
	//增加的墙壁的信息
	int addWallX[100];
	int addWallY[100];
public:
	enum
	{
		COL = 80,//列数
		ROW = 60, //行数
	};
	Wall();
	void goMapXY(int x,int y);//去地图上的XY处输出字符
	void initMap();//初始化地图，将地图Map内的信息更新
	void drawWall();//画地图
	void drawTipUI(int len, int score, int record, int level, int life);//输出提示
	void drawAITipUI(int len, int score, int record, int level, int life);
	void putCharInMap(int x, int y, char c);//在x,y处将字符c放入地图，并输出图片
	char getCharInMap(int x, int y);//获取x,y处的字符信息
	void addWall(int x,int y);//增加墙壁
	int getTime();//得到游戏时间
};

Wall::Wall()//初始化一些信息
{
	stratT = clock();//开始时间
	addWallNum = 0;//一开始设置没有增加的墙壁数量
	memset(addWallX, 0, sizeof(addWallX));
	memset(addWallY, 0, sizeof(addWallY));
}

void Wall::goMapXY(int x, int y)//将光标移动到地图x,y的地方，进行输出字符
{
	HANDLE outsys = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

	CONSOLE_CURSOR_INFO cursor;           //光标结构 
	cursor.dwSize = 10;
	cursor.bVisible = 0;                  //0为隐藏光标
	SetConsoleCursorInfo(outsys, &cursor);//设置隐藏光标函数 
	COORD pos;
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	SetConsoleCursorPosition(outsys, pos);
}

void Wall::initMap()//初始化地图Map
{
	for (int i = 0; i <= COL + 1; i++)//四周记录为墙壁
	{
		map[i][ROW + 1] = '#';
		map[i][0] = '#';
	}
	for (int i = 0; i <= ROW + 1; i++)
	{
		map[0][i] = '#';
		map[COL + 1][i] = '#';
	}
	for (int i = 1; i <= COL; i++)//中间记录为空白
	{
		for (int j = 1; j <= ROW; j++)
			map[i][j] = ' ';
	}

}

void Wall::drawWall()//绘制地图
{
	//绘制上下的地图
	setfillcolor(RGB(255, 228, 181));
	solidrectangle(0, 0, 820, 10);
	setfillcolor(RGB(255, 99 ,71));
	solidrectangle(0, 610, 820, 620);
	
	//绘制左右的地图
	setfillcolor(GREEN);
	solidrectangle(0, 0, 10, 620);
	solidrectangle(810, 0, 820, 620);

	//对于增加的墙壁的分析
	int n = addWallNum;
	while(n)//如果有增加的墙壁
	{
		solidrectangle(10 * addWallX[n], 10 * addWallY[n], 10 + 10 * addWallX[n], 10 + 10 * addWallY[n]);//绘制墙壁
		n--;
	}

}

void Wall::putCharInMap(int x, int y, char c)//关键性函数，在地图中标记，写入进Map数组中，同时绘制图片
{
	map[x][y] = c;//写入数组中
}

char Wall::getCharInMap(int x, int y)//得到地图中x,y的字符
{
	return map[x][y];
}

void Wall::drawTipUI(int len, int score, int record, int level, int life = 0)//绘制提示
{
	//设置背景颜色
	setbkcolor(RGB(238, 238, 224));
	setbkmode(OPAQUE);
	//设置字体、颜色
	settextstyle(20, 0, _T("宋体"));
	settextcolor(RGB(255, 127, 36));

	//一下是绘制提示
	outtextxy(870,100,_T( "贪吃蛇大作战"));
	TCHAR l[10];
	_stprintf_s(l, _T("%d"), len);//把数字变为字符
	outtextxy(850, 150, _T("长度："));
	outtextxy(900, 150, l);
	
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), score);//把数字变为字符
	outtextxy(850, 200, _T("分数："));
	outtextxy(900, 200, s);
	
	TCHAR r[10];
	outtextxy(850, 250, _T("历史最高分："));
	if (score < record)
	   _stprintf_s(r, _T("%d"), record);//把数字变为字符
	else
		_stprintf_s(r, _T("%d"), score);
	outtextxy(960, 250, r);

	int tim =(int) (clock() - stratT) / 1000;
	TCHAR t[10];
	_stprintf_s(t, _T("%d"), tim);//把数字变为字符
	outtextxy(850, 300, _T("游戏时间："));
	outtextxy(950, 300, t);

	//依据游戏模式不同，展示其他信息
	outtextxy(850,360,_T("w a s d为方向键"));
	outtextxy(850,400,_T( "游戏规则："));
	switch (level)
	{
	case 1:
	{
		outtextxy(850,450,_T( "当碰到墙或自己时就会结束哦"));
		break;
	}
	case 2:
	{
		settextstyle(15, 0, _T("宋体"));
		outtextxy(850,450,_T("当碰到墙或自己时就会变成墙哦"));
		outtextxy(850,490,_T( "到剩余空间不足以生成新的蛇和食物时"));
		outtextxy(850,530,_T( "就会结束游戏啦"));
		break;
	}
	case 3:
	{

		TCHAR bloon[10];
		_stprintf_s(bloon, _T("%d"), life);//把数字变为字符
		outtextxy(850, 330, _T("血量："));
		outtextxy(910, 330, bloon);
		settextstyle(15, 0, _T("宋体"));
		outtextxy(850, 450, _T("当碰到墙或自己时就会变成食物哦"));
		outtextxy(850, 480, _T("到以及死亡5次"));
		outtextxy(850, 510, _T("或剩余空间不足以生成新的蛇和食物时"));
		outtextxy(850, 540, _T("就会结束游戏啦"));
	
		settextstyle(20, 0, _T("宋体"));
		break;
	}
	case 4:
	{
		TCHAR bloon[10];
		_stprintf_s(bloon, _T("%d"), life);//把数字变为字符
		outtextxy(850, 330, _T("血量："));
		outtextxy(910, 330, bloon);
		settextstyle(15, 0, _T("宋体"));
		outtextxy(850, 420, _T("血量为0，游戏结束"));
		outtextxy(850, 435, _T("有右上加速区，有左下减速区"));
		outtextxy(850, 450, _T("注意会出现道具,吃灭火器左上加2滴血"));
		outtextxy(850, 465, _T("吃雪人左上扣2滴血"));
		outtextxy(850, 480, _T("上为软墙，碰到蛇长-4"));
		outtextxy(850, 495, _T("下为硬墙，碰到扣2滴血"));//吃灭火器加2滴血，吃雪人直接死亡，上为软墙，碰到蛇长-3，下为硬墙，碰到扣2滴血

		settextstyle(20, 0, _T("宋体"));
		break;
	}
	case 5:
	{
		TCHAR bloon[10];
		_stprintf_s(bloon, _T("%d"), life);//把数字变为字符
		outtextxy(850, 330, _T("血量："));
		outtextxy(910, 330, bloon);
		outtextxy(850, 420, _T("血量为0，游戏结束"));
		outtextxy(850, 450, _T("也可以把其中一条蛇的"));
		outtextxy(850, 480, _T("五条命逼死就好了"));
		break;
	}
	}
}

void Wall::addWall(int x,int y)//增加墙壁数量
{
	addWallNum++;//记录+1
	//记录位置信息
	addWallX[addWallNum] = x;
	addWallY[addWallNum] = y;
}


int Wall::getTime()//得到时间
{
	return (int)(clock() - stratT) / 1000;
}