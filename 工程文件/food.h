#pragma once
#include"Wall.h"
class Food
{
private:
	//储存食物的位置
	int foodPlaceX[50];
	int foodPlaceY[50];

	int allNum;//食物总量
	int isEat[150][150];//记录该位置的食物是否被吃掉了
public:
	Food(Wall& tempwall);
	bool randomFood();//随机产生食物
	void addFood(int x, int y);//在x,y位置增加食物
	void clearFood(int level);//清理掉所有的食物
	void eatFood(int x,int y);//记录x,y位置的食物被吃掉了
	void drawFood();//展示食物
	COORD getAfood();//获得一个随机食物的位置信息
	bool checkIsEat(COORD p);//检查x,y位置的食物是否被吃了
	int num;//记录当前食物数量
	Wall& wall;
};

COORD Food::getAfood()//获得一个随机食物的位置信息
{
	while(1)
	{
		int i = rand() % allNum;//在所有食物数中随机出一个
		if (wall.getCharInMap(foodPlaceX[i], foodPlaceY[i]) == '$'&&!isEat[foodPlaceX[i]][ foodPlaceY[i]])//判断食物是否还在，还在就返回信息
		{
			COORD a;
			a.X = foodPlaceX[i];
			a.Y = foodPlaceY[i];
			return a;
		}
	}
}

bool Food::checkIsEat(COORD p)//检查x,y位置的食物是否被吃了
{
	if (isEat[p.X][p.Y])
		return 1;
	else
		return 0;
}

Food::Food(Wall& tempwall) :wall(tempwall)//初始化
{
	memset(foodPlaceX, 0, sizeof(foodPlaceX));
	memset(foodPlaceY, 0, sizeof(foodPlaceY));
	memset(isEat, 1, sizeof(isEat));
}

bool Food::randomFood()
{
	bool isBornFood = 0, isBreak = 0;//是否成功产生了食物，是否需要跳出循环
	num = 0;//食物数量为0
	
	//先要判断是否还有空间产生食物，以及最多可以产生的小于5的食物的数量
	for (int x = 1; x <= wall.COL; x++)
	{
		for (int y = 1; y <= wall.ROW; y++)
		{
			if (wall.getCharInMap(x, y) == ' ')//如果有一处是空的，就说明至少可以产生一个食物
			{
				isBornFood = 1;
				num++;
			}
			if (num >= 5)//如果可以大于5了，就说明不用继续判断了，直接跳出循环
			{
				isBreak = 1;
				break;
			}
		}
		if (isBreak)
			break;
	}

	if (!isBornFood)//如果没有成功产生食物，就说明失败了，就返回0
		return 0;

	srand((unsigned int)time(NULL));//刷新随机种子
	int placeN = 0;
	int n = rand() % num + 1;//随机出食物数量
	num = n;
	for (int i = 0; i < n; i++)//随机出n个食物的信息
	{
		while (1)
		{
			int x = rand() % wall.COL + 1;//随机出食物的位置x
			int y = rand() % wall.ROW + 1;//随机出食物的位置y
			if (wall.getCharInMap(x, y) == ' ')//如果随机出的这个位置原本就没有东西的话，就把食物放入这个位置，并加载图像
			{
				wall.putCharInMap(x, y, '$');//放入符号、图片
				isEat[x][y] = 0;
				foodPlaceX[placeN] = x;//记录进去
				foodPlaceY[placeN] = y;//记录进去
				placeN++;//记录下有几个有效食物信息
				break;
			}
		}
	}
	allNum = num;//记录下原本食物总数量
	return 1;
}

void Food::addFood(int x, int y)//在x、y增加食物
{
	//记录x,y处的食物信息
	foodPlaceX[allNum] = x;
	foodPlaceY[allNum] = y;
	wall.putCharInMap(x, y, '$');
	isEat[x][y] = 0;
	num++;//现在食物的数量+1
	allNum++;//总食物的数量+1
}

void Food::clearFood(int level)//清理掉食物的图像
{

	for (int i = 0; i < allNum; i++)//在map中记录下这几块的食物都没有了，换成' '
	{
		if (!isEat[foodPlaceX[i]][foodPlaceY[i]])//如果那个没有被吃掉，就替换
		{
			wall.putCharInMap(foodPlaceX[i], foodPlaceY[i], ' ');
			isEat[foodPlaceX[i]][foodPlaceY[i]] = 1;
		}
	}
	//记录数量归0
	allNum = 0;
	num = 0;
}

void Food::eatFood(int x,int y)//记录吃掉了x,y处的食物
{
	num--;
	isEat[x][y] = 1;
}

void Food::drawFood()//展示食物
{
	IMAGE zhizhu(10, 10);
	loadimage(&zhizhu, _T("zhizhu.jpg"), 10, 10);
	for (int i = 0; i < allNum; i++)
	{
		if (!isEat[foodPlaceX[i]][foodPlaceY[i]])//如果没有被吃掉才展示
		{
			putimage(10 * foodPlaceX[i], 10 * foodPlaceY[i], &zhizhu);
		}
	}
}