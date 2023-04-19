#pragma once
#include"Wall.h"
#include"Food.h"
#include<fstream>
#include<iostream>
using namespace std;
class Snake
{
private:
	int len;//蛇的长度

	//记录蛇数据的节点
	struct snakeDate
	{
		int x;
		int y;
		snakeDate* next;
	};

	snakeDate* shead;//蛇头
	int life;//蛇的生命
	void move(int dx, int dy);//移动蛇身
	int score;//得分
	char predir;//上一次移动的方向
	bool isDead;//判断蛇是否以及死掉了
	int sleepChange;//停顿时间修改
public:
	Snake(Wall& tempWall, Food& food);
	Wall& wall;
	Food& food;
	int gameLeve;//游戏等级
	bool isPutV;//是否放置奖励物品
	bool isPutBoom;//是否放置炸弹
	enum//设置方向键
	{
		UP = 'w',
		DOWN = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};

	void initSnake();//重新初始化蛇的一些数据
	bool randBron();//重新随机诞生蛇
	bool getIsDead();//得到蛇是否死亡
	int getScore();//得到分数
	int getSnakeLen();//得到蛇的长度
	int getLife();//得到蛇的生命值
	int getHeadX();//得到蛇头的位置x
	int getHeadY();//得到蛇头的位置y
	void moveSnake(char dir);//依据方位移动蛇
	void sleep();//设置停止时间
	void deatorySnake();//删除掉蛇身的数据
	void trySaveDate();//尝试保存游戏记录
	void snakeToWall();//将蛇身转变为墙
	void snakeToFood();//将蛇身变为食物
	void snakeToNull();//将蛇身转变为空
	void dieNote();//跳出游戏结束的提示
	void downLife(int n);//减少生命
	void drawSnake();//画蛇
};

//初始化蛇的一些信息
Snake::Snake(Wall& tempWall, Food& tempFood) : wall(tempWall), food(tempFood)
{
	shead = new snakeDate;//开辟蛇头的空间

	//初始一些信息
	isDead = false;//没死亡
	len = 4;//长度4
	score = 0;//分数0
	life = 5;//生命值有5
	predir = UP;//一开始之前的方向向上
	gameLeve = 1;//初始默认选择第一版游戏
	isPutV = 0;//不放奖励
	isPutBoom = 0;//不放炸弹
	sleepChange = 0;
}

void Snake::initSnake()
{
	isDead = false;//改为没死
	predir = UP;//一开始方向向上
}

int Snake::getSnakeLen()//得到蛇长
{
	return len;
}

//移动
void Snake::move(int dx, int dy)
{
	bool isputhead = 1;//是否要绘制蛇头

	snakeDate* p = shead, * pre = NULL;
	p = new snakeDate;//p为储存移动过后蛇头的信息
	p->x = shead->x + dx;
	p->y = shead->y + dy;
	p->next = shead;

	shead = p;//shead更新为蛇头信息
	while (p->next != NULL)//p转为储存最后一节蛇身的信息
	{
		pre = p;
		p = p->next;
	}

	if (gameLeve == 4)
	{
		if (shead->x > 50 && shead->y < 30)
			sleepChange--;
		else
		{
			if (shead->x < 30 && shead->y > 30)
				sleepChange++;
			else
			{
				sleepChange = 0;
			}
		}
	}

	if (wall.getCharInMap(shead->x, shead->y) == ' '||(shead->x==p->x&&shead->y==p->y))//如果前方是空白
	{
		wall.putCharInMap(p->x, p->y, ' ');//最后一位改为空白
		delete p;//删除掉最后一个节点
		pre->next = NULL;//上一个改为最后一个
	}
	
	if (wall.getCharInMap(shead->x, shead->y) == '$')//如果吃到了食物
	{
		food.eatFood(shead->x, shead->y);//记录这点的食物被吃了
		len++;//长度+1
		score+=10;//成绩+10
	}

	if (wall.getCharInMap(shead->x, shead->y) == '&')//如果吃到了奖励
	{
		isPutV = 0;//不再放奖励
		len++;//长度+1
		life += 3;//生命+3
		score += 50;//成绩+50
	}

	if (wall.getCharInMap(shead->x, shead->y) == '!')//如果吃到了炸弹
	{
		isPutBoom = 0;//不再放炸弹
		isDead = 1;//死亡
		life -= 3;//生命-3
		score =0;//分数归零
	}

	//撞到墙
	if (gameLeve == 4)//如果游戏版本为第四版
	{
		if (wall.getCharInMap(shead->x, shead->y) == '#')//并且撞墙了
		{
			isDead = TRUE;//标记死亡
			if (shead->y > 59)//如果撞到下面的墙，生命-2
			{
				life-=2;
				return;
			}

			if (shead->y < 1)//如果撞到上面的墙
			{
				int d = 3;//蛇长减少3
				len = len  - d;
				if (len >=1)//如果长度依然有
				{
					isDead = FALSE;//改为没死
					score -= 5;//分数-5
					p = shead->next;//因为头已经在墙里了，就从下一个开始
					while (p != NULL)
					{
						if (d > 0)//当d>0
						{
							wall.putCharInMap(p->x, p->y, ' ');//记录这个点为空
							shead = p->next;//依次轮换蛇头
						}
						else
						{
							wall.putCharInMap(p->x, p->y, '*');//展示蛇身
						}
						d--;
						p = p->next;
					}
				}
				else//如果没长度了
				{
					life--;//生命-1
					len = 4;//长度归4，为了和提示契合
				}
				return;
			}
			
			life--;//如果不是在上述位置撞墙，就生命-1
		}
	}
	else//如果不是第四版
	{
		if (wall.getCharInMap(shead->x, shead->y) == '#')//撞墙
		{
			isDead = TRUE;//死了
			life--;//生命-1
			return;
		}
	}

	if (wall.getCharInMap(shead->x, shead->y) == '*')//如果吃到了自己，因为已经提前处理了最后一位追尾的问题，不用但是误判
	{
		isDead = TRUE;//死了
		life--;//生命-1
		return;
	}

	//将剩余的蛇身绘制出来
	p = shead;
	while (p != NULL)
	{
		wall.putCharInMap(p->x, p->y, '*');
		p = p->next;
	}
}

void Snake::moveSnake(char dir)//移动蛇
{
	//确保按的是方向
	if ((predir == UP && dir == DOWN) || (predir == DOWN && dir == UP) || (predir == LEFT && dir == RIGHT) || (predir == RIGHT && dir == LEFT))
	{
		dir = predir;
	}

	//不同的方向不同的移动
	switch (dir)
	{
	case UP:
	{
		move(0, -1);
		break;
	}
	case DOWN:
	{
		move(0, 1);
		break;
	}
	case RIGHT:
	{
		move(1, 0);
		break;
	}
	case LEFT:
	{
		move(-1, 0);
		break;
	}
	}
	predir = dir;//更新之前的移动方向
}

void Snake::sleep()//休息时间
{
	//不同等级对应不同
	switch (gameLeve)
	{
	case 1:
	{
		Sleep(60);
		break;
	}
	case 2:
	{
		Sleep(50);
		break;
	}
	case 3:
	{
		Sleep(40);
		break;
	}
	case 4://模式4因为有加速和减速区，休息时间要变化
	{
		int s = 100 + sleepChange;
		if (s < 3)
			s = 2;
		Sleep(s);
		break;
	}
	case 5:
	{
		Sleep(10);
		break;
	}
	}
}

void Snake::trySaveDate()//尝试储存休息
{
	//打开文件
	fstream fscore("record.txt");
	fstream fhis("history.txt");

	if (!fscore.is_open())
	{
		cout << "打开记录文件夹失败";
		return;
	}
	if (!fhis.is_open())
	{
		cout << "打开历史记录文件失败";
		return;
	}

	string name[6] = { " ","---","---","---" ,"---","---" };//初始数组，防止没有记录的时候出现乱码
	int userScore[6] = { 0 };

	for (int i = 1; i <= 5; i++)//获取记录
	{
		fscore >> name[i] >> userScore[i];
	}

	if (userScore[gameLeve] < score)//如果打破了记录
	{
		wall.goMapXY(50, 25);
		cout << "你已经打破记录了！！！请输入你的大名";//提示
		wall.goMapXY(50, 27);
		cin >> name[gameLeve];//载入数据
		userScore[gameLeve] = score;
		fscore.clear();
		fscore.seekp(0, ios::beg);//回到记录文件开头，输入数据
		for (int i = 1; i <= 5; i++)
		{
			fscore << name[i] << " " << userScore[i] << " ";
		}
		fhis.seekp(0, ios::end);//去到历史记录结尾，记录数据
		fhis << " " << gameLeve << " " << name[gameLeve] << " " << score;
	}
	else//如果没有打破数据,只记录进历史文档
	{
		wall.goMapXY(50, 25);
		cout << "请输入你的姓名";
		wall.goMapXY(50, 27);
		cin >> name[gameLeve];
		fhis.seekp(0, ios::end);
		fhis << " " << gameLeve << " " << name[gameLeve] << " " << score;
	}
	//关闭文件
	fscore.close();
	fhis.close();

}

void Snake::snakeToWall()//将蛇身变为墙
{
	snakeDate* p = shead->next;
	int x, y;
	while (p != NULL)//遍历
	{
		x = p->x;
		y = p->y;
		wall.putCharInMap(x, y, '#');
		wall.addWall(x, y);
		p = p->next;
	}
}

void Snake::snakeToFood()//蛇身变为食物
{

	snakeDate* p = shead->next;
	int x, y;

	while (p != NULL)//遍历
	{
		x = p->x;
		y = p->y;
		food.addFood(x, y);
		p = p->next;
	}
}

int Snake::getLife()//得到生命
{
	return life;
}


bool Snake::randBron()//随机产生蛇
{
	bool isBorn = 0;//判断是否有足够空间可以产生蛇
	int bornPlaceX[500] = { 0 }, placeN = 0;//记录可以诞生蛇头的x

	//因为是产生上下方面的蛇，所以下面要有3个空格
	for (int i = 1; i <= wall.COL; i++)
	{
		for (int j = 1; j <= wall.ROW - 3; j++)
		{
			if (wall.getCharInMap(i, j) == ' ' && wall.getCharInMap(i, j + 1) == ' ' && wall.getCharInMap(i, j + 2) == ' ' && wall.getCharInMap(i, j + 3) == ' ')
			{
				isBorn = 1;
				bornPlaceX[placeN++] = i;
				break;
			}
		}
	}

	if (isBorn)
	{
		isDead = false;//改为没死
		predir = UP;//一开始方向向上

		//在可以诞生蛇头的x中随机出位置
		srand((unsigned int)time(NULL));
		int x = bornPlaceX[rand() % placeN];
		int y = rand() % (wall.ROW - 3) + 1;//蛇长为4
		while (1)
		{
			//遍历判断这一条蛇身是否可以顺利诞生出蛇
			if (wall.getCharInMap(x, y) == ' ' && wall.getCharInMap(x, y + 1) == ' ' && wall.getCharInMap(x, y + 2) == ' ' && wall.getCharInMap(x, y + 3) == ' ')
				break;
			y = rand() % (wall.ROW - 3) + 1;//蛇长为4
		}

		len = 4;//长度

		//在地图中标记蛇的位置
		shead = new snakeDate;
		shead->x = x;
		shead->y = y;
		shead->next = NULL;
		wall.putCharInMap(shead->x, shead->y, '*');
		snakeDate* now = NULL;
		snakeDate* pre = shead;
		for (int i = 1; i < 4; i++)
		{
			wall.putCharInMap(x, y + i, '*');
			now = new snakeDate;
			now->x = x;
			now->y = y + i;
			pre->next = now;
			pre = now;
		}
		now->next = NULL;
		return 1;
	}
	else
		return 0;//没有空间产生蛇了
}

void Snake::deatorySnake()//销毁掉蛇的申请空间
{
	snakeDate* p = shead, * k = NULL;
	while (p != NULL)
	{
		k = p;
		p = p->next;
		delete k;
	}
}

void Snake::dieNote()//游戏结束提示
{
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(50, 0, _T("宋体"));
	outtextxy(450, 200, _T("游戏结束"));
	outtextxy(450, 300, _T("按任意键结束"));
}

void Snake::snakeToNull()//将蛇死亡的地方的标记标空
{
	snakeDate* p = shead->next;
	int x, y;

	while (p != NULL)
	{
		x = p->x;
		y = p->y;
		wall.putCharInMap(x, y, ' ');
		p = p->next;
	}
}

int Snake::getHeadX()//得到头位置X
{
	return shead->x;
}

int Snake::getHeadY()//得到头位置Y
{
	return shead->y;
}

void Snake::downLife(int n)//减少什么n
{
	life -= n;
}

int Snake::getScore()//得到分数
{
	return score;
}

bool Snake::getIsDead()//得到是否死亡信息
{
	return isDead;
}

void Snake::drawSnake()//画蛇的图像
{
	snakeDate* p = shead;
	while (p != NULL)
	{
		IMAGE wowo(10, 10);
		loadimage(&wowo, _T("wowo.jpg"), 10, 10);
		putimage(10 * p->x, 10 *p-> y, &wowo);
		p = p->next;
	}
}