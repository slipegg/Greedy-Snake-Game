#include"wall.h"
#include"food.h"
#include"snake.h"
#include"menu.h"
#include<fstream>
using namespace std;
IMAGE img(1120, 620);
void loadPhoto(int n)//加载img对应的图片
{
	switch (n)
	{
	case 1: 
	{
		loadimage(&img, _T("1.jpg"), 1120, 620);
		break;
	}
	case 2:
	{
		loadimage(&img, _T("2.jpg"), 1120, 620);
		break;
	}
	case 3:
	{
		loadimage(&img, _T("3.jpg"), 1120, 620);
		break;
	}
	case 4:
	{
		loadimage(&img, _T("4.jpg"), 1120, 620);
		break;
	}
	case 5:
	{
		loadimage(&img, _T("5.jpg"), 1120, 620);
		break;
	}
	}
	// 设置绘图目标为 img 对象
	SetWorkingImage(&img);
	if (n == 4)//4模式的话，还要对应加上点，对应加速、减速区
	{
		//加速区
		for (int i = 51; i <= 80; i++)
		{
			for (int j = 1; j < 30; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, BLUE);
				putpixel(i * 10, j * 10, BLUE);
			}
		}
		//减速区
		for (int i = 1; i < 30; i++)
		{
			for (int j = 31; j <= 60; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, RED);
				putpixel(i * 10, j * 10, RED);
			}
		}
	}
}

void showPhoto()//将图片及在上面绘制的蛇、墙、食物展现出来
{
	// 设置绘图目标为绘图窗口
	SetWorkingImage();
	// 将 img 对象显示在绘图窗口中
	putimage(0, 0, &img);
	SetWorkingImage(&img);
}

void addVB(bool isPutV = 0,bool isPutBoom=0)//放置奖励和炸弹的图片
{
	if (isPutV)
	{
		IMAGE V(20, 20);
		loadimage(&V, _T("V.png"), 20, 20);
		putimage(10 * 1, 10 * 1, &V);
	}
	if (isPutBoom)
	{
		IMAGE B(20, 20);
		loadimage(&B, _T("B.png"), 20,20);
		putimage(10 * 10, 10 * 10, &B);
	}
}

void rePhoto(int n)//用图片覆盖原来的图片，以达到刷新的效果
{
	switch (n)
	{
	case 1:
	{
		loadimage(&img, _T("1.jpg"), 1120, 620);
		break;
	}
	case 2:
	{
		loadimage(&img, _T("2.jpg"), 1120, 620);

		break;
	}
	case 3:
	{
		loadimage(&img, _T("3.jpg"), 1120, 620);
		break;
	}
	case 4:
	{
		loadimage(&img, _T("4.jpg"), 1120, 620);
		break;
	}
	case 5:
	{
		loadimage(&img, _T("5.jpg"), 1120, 620);
		break;
	}
	}
	if (n == 4)
	{
		for (int i = 51; i <= 80; i++)
		{
			for (int j = 1; j < 30; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, BLUE);
				putpixel(i * 10, j * 10, BLUE);
			}
		}
		for (int i = 1; i < 30; i++)
		{
			for (int j = 31; j <= 60; j++)
			{
				putpixel(i * 10 + 5, j * 10 + 5, RED);
				putpixel(i * 10, j * 10, RED);
			}
		}
	}
	putimage(0, 0, &img);
}

void putVB(Snake &s,Wall &w)//放置奖励和炸弹的信息到Map中
{
	if (s.getLife() == 2)
	{
		w.putCharInMap(1, 1, '&');
		w.putCharInMap(1, 2, '&');
		w.putCharInMap(2, 1, '&');
		w.putCharInMap(2, 2, '&');
		s.isPutV = 1;
	}
	if (s.getLife() != 2)
	{
		if (w.getCharInMap(1, 1) == '&')
			w.putCharInMap(1, 1, ' ');
		if (w.getCharInMap(1, 2) == '&')
			w.putCharInMap(1, 2, ' ');
		if (w.getCharInMap(2, 1) == '&')
			w.putCharInMap(2, 1, ' ');
		if (w.getCharInMap(2, 2) == '&')
			w.putCharInMap(2, 2, ' ');

		s.isPutV = 0;
	}
	if (s.getLife() == 4)
	{
		w.putCharInMap(10, 10, '!');
		w.putCharInMap(10, 11, '!');
		w.putCharInMap(11, 10, '!');
		w.putCharInMap(11, 11, '!');
		s.isPutBoom = 1;
		//addVB(snake.isPutV,snake.isPutBoom);
	}
	if (s.getLife() != 4 )
	{
		if (w.getCharInMap(10, 10) == '!')
			w.putCharInMap(10, 10, ' ');
		if (w.getCharInMap(10, 11) == '!')
			w.putCharInMap(10, 11, ' ');
		if (w.getCharInMap(11, 10) == '!')
			w.putCharInMap(11, 10, ' ');
		if (w.getCharInMap(11, 11) == '!')
			w.putCharInMap(11, 11, ' ');

		s.isPutBoom = 0;
	}
}

void showAll(Snake& s,  Wall& w, Food& f, Menu& m)//绘制所图片有画面
{
	rePhoto(s.gameLeve);//刷新
	s.drawSnake();//蛇身
	w.drawWall();//墙
	w.drawTipUI(s.getSnakeLen(), s.getScore(), m.getScore(s.gameLeve), s.gameLeve, s.getLife());//提示
	f.drawFood();//食物
	addVB(s.isPutV, s.isPutBoom);//奖励、炸弹
	showPhoto();//展示
}

void showThreeAll(Snake& s, Snake& t,Snake &r, Wall& w, Food& f, Menu& m)
{
	//与上差不多，就是多展示了2条AI蛇
	rePhoto(s.gameLeve);
	w.drawWall();
	w.drawTipUI(s.getSnakeLen(), s.getScore(), m.getScore(s.gameLeve), s.gameLeve, s.getLife());

	f.drawFood();

	s.drawSnake();
	addVB(s.isPutV, s.isPutBoom);

	t.drawSnake();
	addVB(t.isPutV, t.isPutBoom);

	r.drawSnake();
	addVB(r.isPutV, r.isPutBoom);
	showPhoto();
}

void easyPlay()
{
	system("cls");//清屏
	loadPhoto(1);//加载背景界面

	//墙的初始化
	Wall wall;
	wall.initMap();
	wall.drawWall();

	//食物初始化
	Food food(wall);
	food.randomFood();

	//蛇的初始化
	Snake snake(wall, food);
	snake.gameLeve = 1;
	snake.randBron();

	//菜单的初始化，主要为了获得历史最高分
	Menu menu(wall);
	
	char dir = NULL, d = NULL;
	while (!snake.getIsDead())//如果没有死掉
	{
		showAll(snake, wall, food, menu);//将所有需要展示在图片界面上的都在一个函数展示出来
		dir = _getch();//等待方向键
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)//是方向键才录入
		{
			d = dir;
		}
		do//如果没有新输入方向键并且没死掉就一直循环
		{
			snake.moveSnake(d);//蛇的移动
			snake.sleep();//停顿一段时间
			if (food.num == 0)//如果食物为0了，就初始化一些
				food.randomFood();
			showAll(snake, wall, food, menu);//展示移动后的界面
		} while (!_kbhit() && !snake.getIsDead());
	}

	if (snake.getIsDead())//如果死掉了
	{
		snake.dieNote();//游戏结束提示
		showPhoto();//将游戏结束提示显示出来
		_getch();
		closegraph();//关闭游戏窗口
		snake.deatorySnake();//释放空间
		snake.trySaveDate();//记录数据
		
	}
}

void hardPlay()
{
	//与easyPlay相同部分不再赘述了
	system("cls");
	loadPhoto(2);

	Wall wall;
	wall.initMap();
	wall.drawWall();

	Food food(wall);
	food.randomFood();

	Snake snake(wall, food);
	snake.gameLeve = 2;
	snake.randBron();

	Menu menu(wall);
	char dir = NULL, d = NULL;
	bool isGameOver = 0;//依靠是否有产生食物和蛇的空间来决定游戏是否可以继续进行
	while (!isGameOver)
	{
		showAll(snake, wall, food, menu);
		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do
		{
			snake.moveSnake(d);
			snake.sleep();
			if (food.num == 0)
			{
				if (!snake.randBron())
					isGameOver = 1;
			}
			showAll(snake, wall, food, menu);
			showPhoto();
		} while (!_kbhit() && !snake.getIsDead());

		if (snake.getIsDead())//如果死亡
		{
			snake.snakeToWall();//将蛇身变为墙
			//刷新食物
			food.clearFood(snake.gameLeve);
			if (!food.randomFood())//重新诞生食物，如果失败，游戏结束
				isGameOver = 1;

			snake.deatorySnake();//释放空间
			snake.initSnake();//初始化一些数据
			if (!snake.randBron())//重新诞生蛇，如果失败游戏结束
				isGameOver = 1;
		}
	}
	snake.dieNote();
	showPhoto();
	_getch();
	closegraph();
	snake.trySaveDate();
}

void hhhardPlay()
{
	//与easyPlay相同部分不再赘述了
	system("cls");
	loadPhoto(3);

	Wall wall;
	wall.initMap();
	wall.drawWall();

	Food food(wall);
	food.randomFood();

	Snake snake(wall, food);
	snake.gameLeve = 3;
	snake.randBron();

	Menu menu(wall);
	wall.drawTipUI(snake.getSnakeLen(), snake.getScore(), menu.getScore(snake.gameLeve), snake.gameLeve, snake.getLife());
	char dir = NULL, d = NULL;
	bool isGameOver = 0;
	while (!isGameOver && snake.getLife())//判断游戏结束的依据，是否蛇还有生命值，是否有可以产生蛇和食物的空间
	{
		showAll(snake, wall, food, menu);
		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do
		{
			snake.moveSnake(d);
			snake.sleep();
			if (food.num == 0)
			{
				if (!snake.randBron())
					isGameOver = 1;
			}
			showAll(snake, wall, food, menu);
		} while (!_kbhit() && !snake.getIsDead());

		if (snake.getIsDead())
		{
			//蛇死亡后刷新食物
			food.clearFood(snake.gameLeve);
			if (!food.randomFood())
				isGameOver = 1;
			//蛇重生
			snake.snakeToFood();//蛇身转化为食物
			snake.deatorySnake();//释放空间
			snake.initSnake();
			if (!snake.randBron())
				isGameOver = 1;
		}
	}
	snake.dieNote();
	showPhoto();
	_getch();
	closegraph();
	snake.trySaveDate();
}

void funPlay(int n)
{
	//与easyPlay相同部分不再赘述了
	system("cls");
	loadPhoto(4);

	Wall wall;
	wall.initMap();

	Food food(wall);
	food.randomFood();

	Snake snake(wall, food);
	snake.gameLeve = n;
	snake.randBron();

	Menu menu(wall);

	char dir = NULL, d = NULL;
	int sleepChange = 0;//停顿时间改变，对应加速，减速区
	bool isGameOver = 0;
	while (!isGameOver&&snake.getLife()>0)
	{
		showAll(snake, wall, food, menu);
		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do
		{
			snake.moveSnake(d);
			snake.sleep();
			if (food.num == 0)
			{
				if (!snake.randBron())
					isGameOver = 1;
			}
			showAll(snake, wall, food, menu);
		} while (!_kbhit() && !snake.getIsDead());

		if (snake.getLife() && snake.getIsDead())
		{
			snake.snakeToNull();//死后变空
			//刷新食物
			food.clearFood(snake.gameLeve);
			if (!food.randomFood())
				isGameOver = 1;
			//刷新蛇
			snake.deatorySnake();
			if (!snake.randBron())
				isGameOver = 1;

			putVB(snake, wall);//判断是否要放置奖励和炸弹
		}
	}

		snake.dieNote();
		showPhoto();
		_getch();
		closegraph();
		snake.deatorySnake();
		snake.trySaveDate();
}

char getAIdir(Snake &snake,Wall &wall,Food &food, COORD p,char pre)//获取AI到达食物的方向
{
	char d = pre;
	if (p.X < snake.getHeadX())//如果在食物在蛇左边
	{
		if (pre == snake.RIGHT)//如果原本是向右运动，这时按左键是无效的，就检查一下上下，来往上或下走，好调个头
		{
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')
				d = snake.UP;
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')
				d = snake.DOWN;
		}
		else
		{
			if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) == '#' || wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) == '*')//如果往左走有障碍
			{
				if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')//往上安全，就暂时往上
					d = snake.UP;
				else
				{
					if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')//往下安全，就暂时往下
						d = snake.DOWN;
				}
			}
			else//如果往左安全
				d = snake.LEFT;
		}
	}
	//其他都差不多
	//在右边
	if (p.X > snake.getHeadX())
	{
		if (pre == snake.LEFT)
		{
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')
				d = snake.UP;
			if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')
				d = snake.DOWN;
		}
		else
		{
			if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) == '#' || wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) == '*')
			{
				int x = snake.getHeadX() + 1;
				int y = snake.getHeadY();
				char t = wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY());
				if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() - 1) != '*')
					d = snake.UP;
				else
				{
					if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '#' && wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) != '*')
						d = snake.DOWN;
				}
			}
			else
				d = snake.RIGHT;
		}
	}

	if (p.X == snake.getHeadX())
	{
		//在上面
		if (p.Y < snake.getHeadY())
		{
			if (pre == snake.DOWN)
			{
				if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '*')
					d = snake.LEFT;
				if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '*')
					d = snake.RIGHT;
			}
			else
			{
				if (wall.getCharInMap(snake.getHeadX() , snake.getHeadY()-1) == '#' || wall.getCharInMap(snake.getHeadX() , snake.getHeadY()-1 )== '*')
				{
					if (wall.getCharInMap(snake.getHeadX()-1, snake.getHeadY() ) != '#' && wall.getCharInMap(snake.getHeadX()-1, snake.getHeadY() ) != '*')
						d = snake.LEFT;
					else
					{
						if (wall.getCharInMap(snake.getHeadX()+1, snake.getHeadY() ) != '#' && wall.getCharInMap(snake.getHeadX()+1, snake.getHeadY()) != '*')
							d = snake.RIGHT;
					}
				}
				else
					d = snake.UP;
			}
		}
		//在下面
		if (p.Y > snake.getHeadY())
		{
			if (pre == snake.UP)
			{
				if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '*')
					d = snake.LEFT;
				if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '*')
					d = snake.RIGHT;
			}
			else
			{
				if (wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) == '#' || wall.getCharInMap(snake.getHeadX(), snake.getHeadY() + 1) == '*')
				{

					if (wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() - 1, snake.getHeadY()) != '*')
						d = snake.LEFT;
					else
					{
						if (wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '#' && wall.getCharInMap(snake.getHeadX() + 1, snake.getHeadY()) != '*')
							d = snake.RIGHT;
					}
				}
				else
					d = snake.DOWN;
			}
		}

	}
	return d;
}

void AI()
{
	system("cls");
	loadPhoto(5);

	Wall wall;
	wall.initMap();

	Food food(wall);
	food.randomFood();

	//人控制的蛇
	Snake snake(wall, food);
	snake.gameLeve = 5;
	snake.randBron();

	//下面是2条AI蛇
	Snake two(wall, food);
	two.gameLeve = 1;
	two.randBron();

	Snake three(wall, food);
	three.gameLeve = 1;
	three.randBron();

	Menu menu(wall);

	char dir = NULL, d = snake.UP,d3=three.UP,pre3=three.UP,d2=two.UP,pre2=two.UP;
	int sleepChange = 0;

	COORD f3 = food.getAfood(), f2 = food.getAfood();//分别获得随机的食物位置信息

	while (snake.getLife() > 0)
	{
		showThreeAll(snake,two,three, wall, food, menu);//专门用来展示他们的画面

		dir = _getch();
		if (dir == snake.UP || dir == snake.DOWN || dir == snake.LEFT || dir == snake.RIGHT)
		{
			d = dir;
		}
		do//在这个循环中蛇一起动
		{
			//人控制的
			snake.moveSnake(d);
			if (food.num == 0)
				food.randomFood();

			//AI蛇2号
			if (food.checkIsEat(f2))//判断之前锁定的那个食物有没有被吃掉
			{
				f2 = food.getAfood();//如果被吃掉了，就找另一个
			}
			d2 = getAIdir(two, wall, food, f2, pre2);//刷新获得方向
			two.moveSnake(d2);//移动
			if (food.num == 0)//如果在它嘴里食物为0了，就刷新食物
				food.randomFood();
			if (two.getLife() && two.getIsDead())
			{
				two.snakeToNull();
				two.deatorySnake();
				two.randBron();
			}

			//与AI2相同
			if (food.checkIsEat(f3))
			{
				f3 = food.getAfood();

			}
			d3 = getAIdir(three, wall, food, f3, pre3);
			three.moveSnake(d3);
			if (food.num == 0)
				food.randomFood();
			if (three.getLife() && three.getIsDead())
			{
				three.snakeToNull();
				three.deatorySnake();
				three.randBron();
			}

			snake.sleep();//只要一起停滞一次
			showThreeAll(snake, two, three, wall, food, menu);
			//专门刷新之前AI蛇方向
			pre3 = d3;
			pre2 = d2;

		} while (!_kbhit() && !snake.getIsDead());

		
		if (snake.getLife() && snake.getIsDead())
		{
			snake.snakeToNull();
			snake.deatorySnake();
			snake.randBron();
		}



	}
	//游戏结束
	snake.dieNote();
	showPhoto();
	_getch();
	closegraph();
	snake.deatorySnake();
	two.deatorySnake();
	three.deatorySnake();
	snake.trySaveDate();
}

void play(int gameleve)//依据不同选择，进入不同游戏
{
	initgraph(1120, 620);//创建新窗口
	//依次选择
	switch (gameleve)
	{
	case 1:
	{
		easyPlay();
		break;
	}
	case 2:
	{
		hardPlay();
		break;
	}
	case 3:
	{
		hhhardPlay();
		break;
	}
	case 4:
	{
		funPlay(4);
		break;
	}
	case 5:
	{
		AI();
		break;
	}
	}
	closegraph();
}

int main()
{
	//_mkdir("d:\\snakeDate");
	//主要是为了初次打开的时候创建2个空文件
	ofstream out("record.txt", ios::app);
	ofstream hout("history.txt", ios::app);

	if (!out.is_open())
	{
		cout << "创建储存文件失败";
		return -1;
	}
	if (!hout.is_open())
	{
		cout << "创建历史文件失败";
		return -1;
	}

	out.close();
	hout.close();

	Wall wall;
	Menu  menu(wall);
	int chose;
	int gameLeve = 1;//初始游戏等级为1
	menu.drawMenu();
	while (TRUE)
	{
		chose = menu.chooseFunct();//选择菜单功能
		switch (chose)
		{
		case 1://选择游戏
		{
			play(gameLeve);//游戏
			menu.drawMenu();//返回菜单界面
			menu.isChoose = 0;
			break;
		}
		case 2:
		{
			gameLeve = menu.chosePlayLeve();//获取、选择游戏等级，里面包含了返回菜单
			menu.isChoose = 0;
			break;
		}
		case 3:
		{
			menu.showScore();//展示历史记录
			menu.drawMenu();//返回
			menu.isChoose = 0;
			break;
		}
		case 4:
		{
			menu.readHistory();//展示历史记录
			menu.isChoose = 0;
			break;
		}
		case 5:
			return 0;//程序结束
		}
	}
	return 0;
}
