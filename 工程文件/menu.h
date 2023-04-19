#pragma once
#include<iostream>
#include<Windows.h>
#include<ctime>
#include<iomanip>
#include"Wall.h"
class Menu
{
private:
	string leveStr[6];//等级语句
	int choseNum;//选择的菜单功能数字
	int choseLeveNum;//选择的游戏等级数字
	int sumHis;//历史记录数量
	void drawChose(int n);//画选项>  <标记
	struct Record//最高分
	{
		string name;
		int score;
	}record[10];
	//历史记录数据
	struct hisDate
	{
		int hlevel;
		string hname;
		int hscore;
		struct hisDate* next;
	}h[10];
	void deleteHis(int n);//删除历史数据
	hisDate* head;//头部
public:
	bool isChoose;//是否选择了
	bool isFinish;//判断菜单功能是否结束了
	void drawMenu();//画菜单界面
	int chooseFunct();//选择菜单功能
	void showScore();//展示最高记录
	int getScore(int level);//得到分数
	int chosePlayLeve();//选择游戏等级
	void readHistory();//阅读历史记录
	void drawHistory();//绘制历史记录
	void drawChoseHistory(int n);//绘制选择>   
	void findName();//查找名字
	Menu(Wall& tempwall);
	Wall& wall;
};
Menu::Menu(Wall& tempwall) :wall(tempwall)
{

	CONSOLE_CURSOR_INFO cursor;           //光标结构 
	cursor.dwSize = 10;

	HANDLE outsys = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量
	cursor.bVisible = 0;                  //0为隐藏光标
	SetConsoleCursorInfo(outsys, &cursor);//设置隐藏光标函数 

	//初始化一些数据
	choseNum = 1;
	isFinish = 0;
	isChoose = 0;
	choseLeveNum = 1;
	sumHis = 0;
	head = NULL;
	leveStr[1] = "入门版";
	leveStr[2] = "进阶版";
	leveStr[3] = "高级版";
	leveStr[4] = "趣味版";
	leveStr[5] = "智障版";
}

void Menu::drawMenu()//绘制界面
{
	system("mode con cols=150 lines=44");//改变宽高
	wall.goMapXY(wall.COL / 2 , 10);
	cout << "贪吃蛇!";
	wall.goMapXY(wall.COL / 2, 12);
	cout << "开始游戏";
	wall.goMapXY(wall.COL / 2, 14);
	cout << "选择难度";
	wall.goMapXY(wall.COL / 2, 16);
	cout << "最高分数";
	wall.goMapXY(wall.COL / 2, 18);
	cout << "历史记录";
	wall.goMapXY(wall.COL / 2, 20);
	cout << "退出游戏";
}

void Menu::drawChose(int n)//绘制选择>  < ，注意到把上下的之前记号掩盖掉
{
	wall.goMapXY(wall.COL / 2 - 2, 10+2*n);
	putchar('>');
	wall.goMapXY(wall.COL / 2 + 9, 10+2*n);
	putchar('<');
	wall.goMapXY(wall.COL / 2 - 2, 8+2*n);
	putchar(' ');
	wall.goMapXY(wall.COL / 2 + 9, 8+2*n);
	putchar(' ');
	wall.goMapXY(wall.COL / 2 - 2, 12+2*n);
	putchar(' ');
	wall.goMapXY(wall.COL / 2 + 9, 12+2*n);
	putchar(' ');
}

int Menu::chooseFunct()//选择菜单功能
{
	drawChose(choseNum);//绘制选择> <
	//采用上下键操作

	int ch1 = 0;
	int ch2 = 0;
	while (!isChoose)//当没有选定
	{
		ch1 = _getch();
		if (ch1 == '\r')//回车键表示选定了
		{
			isChoose = 1;
			break;
		}if (ch1 == 224)//表示按下了上下键
		{
			ch2 = _getch();//第一次调用getch()，返回值224

			switch (ch2)//第二次调用getch()
			{
			case 72://上键，选择-1
			{
				if (choseNum > 1)//选择的数字不能越界
				{
					choseNum--;
				}
				break;
			}
			case 80://下键，选择+1
			{
				if (choseNum < 5)//选择的数字不能越界
				{
					choseNum++;
				}
				break;
			}
			}
			drawChose(choseNum);//绘制选择
		}
	}
	return choseNum;//返回选择
}

void Menu::showScore()//展示最高分数
{
	system("cls");
	//打开文件
	fstream fscore("record.txt");
	if (!fscore.is_open())
	{
		cout << "打开记录文件夹失败";
		return;
	}
	for (int i = 1; i <= 5; i++)
		fscore >> record[i].name >> record[i].score;
	fscore.close();

	for (int i = 1; i <= 5; i++)//将历史最高分打印上去
	{
		wall.goMapXY(wall.COL / 2, 3 + 2 * i);
		cout << leveStr[i] << setw(5) << record[i].name << "  " << record[i].score;
	}

	wall.goMapXY(wall.COL / 2, 30);
	cout << "按任意键返回";
	_getch();
}


int Menu::getScore(int level)//得到分数
{
	return record[level].score;
}

int Menu::chosePlayLeve()//选择游戏等级
{
	//绘制选项
	system("cls");
	wall.goMapXY(wall.COL / 2, 12);
	cout << leveStr[1];
	wall.goMapXY(wall.COL / 2, 14);
	cout << leveStr[2];
	wall.goMapXY(wall.COL / 2, 16);
	cout << leveStr[3];
	wall.goMapXY(wall.COL / 2, 18);
	cout << leveStr[4];
	wall.goMapXY(wall.COL / 2, 20);
	cout << leveStr[5];
	wall.goMapXY(wall.COL / 2, 22);
	cout << "返回菜单";
	wall.goMapXY(wall.COL / 2 + 40, 12);
	cout << "当前选择模式：" << leveStr[choseLeveNum];

	drawChose(choseLeveNum);//绘制选择键>   

	int choseNow = choseLeveNum;
	int ch1 = 0;
	int ch2 = 0;
	while (1)
	{
		ch1 = _getch();
		if (ch1 == '\r')//回车键表示选择了
		{
			if (choseNow != 6)
			{
				choseLeveNum = choseNow;
				//在一边显示出选择的模式
				wall.goMapXY(wall.COL / 2 + 40, 12);
				cout << "当前选择模式：" << leveStr[choseLeveNum];
				continue;
			}
			else//选择了返回菜单
			{
				drawMenu();
				break;
			}
		}
		if (ch1 == 224)//上下键
		{
			ch2 = _getch();//第一次调用getch()，返回值224
			switch (ch2)//第二次调用getch()
			{
			case 72://上键，不能超过限制
			{
				if (choseNow > 1 && choseNow <= 6)
				{
					choseNow--;
				}
				break;
			}
			case 80://下键不能超过限制
			{
				if (choseNow < 6 && choseNow >= 1)
				{
					choseNow++;
				}
				break;
			}
			}
			drawChose(choseNow);
		}
	}
	return choseLeveNum;
}

void Menu::drawChoseHistory(int n)//绘制选择键>
{

	wall.goMapXY(wall.COL / 2 - 2, 5 + 2 * n);
	cout << '>';
	wall.goMapXY(wall.COL / 2 - 2, 5 + 2 * (n - 1));
	cout << ' ';
	wall.goMapXY(wall.COL / 2 - 2, 5 + 2 * (n + 1));
	cout << ' ';
}

void Menu::deleteHis(int n)//删除掉一条历史记录
{
	hisDate* p = head->next, * pre = head;
	int i = 1;
	while (i != sumHis + 1 - n)//查找到这一条，注意得到的n是倒序，但是是正序查找
	{
		pre = p;
		p = p->next;
		i++;
	}
	pre->next = p->next;
	delete p;
	sumHis--;
}

void Menu::drawHistory()//绘制历史记录
{
	system("cls");
	hisDate* p = head->next, * q = NULL;
	//绘制信息
	wall.goMapXY(wall.COL, 20);
	cout << "按删除键可删除所选项";
	wall.goMapXY(wall.COL / 2, 3);
	cout << "返回";
	wall.goMapXY(wall.COL / 2, 5);
	cout << "查询";
	int n = 1;
	while (p != NULL)
	{
		if (sumHis + 1 - n < 19)
		{
			wall.goMapXY(wall.COL / 2, 5 + 2 * (sumHis + 1 - n));
			cout << sumHis + 1 - n << "   版本：" << leveStr[p->hlevel] << "   用户名：" << p->hname << "   得分：" << p->hscore;
		}
		p = p->next;
		n++;
	}
}

void Menu::findName()//当选择了查询
{
	system("cls");

	wall.goMapXY(wall.COL / 2, 5);
	cout << "请输入要查询的玩家名字：";
	wall.goMapXY(wall.COL / 2, 7);
	string fin;
	cin >> fin;
	hisDate* p = head->next;
	//尝试查找这个名字，只找一个人
	while (p != NULL && p->hname != fin)
	{
		p = p->next;
	}
	wall.goMapXY(wall.COL / 2, 9);
	if (p != NULL)//如果找到了
	{
		cout << "版本：" << leveStr[p->hlevel] << "   用户名：" << p->hname << "   得分：" << p->hscore;//输出信息
		wall.goMapXY(wall.COL / 2, 11);
		cout << "是否修改玩家姓名，按空格确定，按其他键返回";//询问是否要改名
		if (_getch() == ' ')//空格确认改名
		{
			//输入替换新的名字
			wall.goMapXY(wall.COL / 2, 13);
			cout << "请输入新的名字：";
			string newname;
			cin >> newname;
			p->hname = newname;
			wall.goMapXY(wall.COL / 2, 15);
			//返回
			cout << "已完成，按任意键返回";
			_getch();
		}
	}
	else//没找到
	{
		cout << "未找到" << "  按任意键返回";
	}
}

void Menu::readHistory()//阅读、选择历史记录
{
	system("cls");

	//打开文件
	fstream fhistory("history.txt");
	if (!fhistory.is_open())
	{
		cout << "打开记录文件夹失败";
		return;
	}

	head = new hisDate;
	hisDate* p = head, * q = NULL;
	sumHis = 0;

	while (fhistory.peek() != EOF)//将历史信息输入到数组中去
	{
		q = new hisDate;
		p->next = q;
		p = q;
		fhistory >> p->hlevel >> p->hname >> p->hscore;
		sumHis++;
	}
	p->next = NULL;
	drawHistory();

	//删除操作
	int ch1 = 0;
	int ch2 = 0;
	bool isChooseHis = 0;
	int choseNumHis = -1;
	while (!isChooseHis)
	{
		drawChoseHistory(choseNumHis);
		ch1 = _getch();
		if (ch1 == '\r' && choseNumHis < 1)//回车选择
		{
			if (choseNumHis == -1)//返回
			{
				drawMenu();
				break;
			}

			if (choseNumHis == 0)//查找历史记录
			{
				findName();
				drawHistory();//找完之后返回
				continue;
			}
		}
		if (ch1 == 8)//按delete键，删除
		{
			wall.goMapXY(wall.COL / 2 + 60, 25);
			cout << "是否确认删除？";
			wall.goMapXY(wall.COL / 2 + 60, 27);
			cout << "按回车键确认，任意其他键取消";
			char a = _getch();
			if (a == '\r')
			{
				deleteHis(choseNumHis);//删除
				drawHistory();//重新绘制历史记录
			}
			continue;
		}
		if (ch1 == 224)//按上下键
		{
			ch2 = _getch();//第一次调用getch()，返回值224
			switch (ch2)//第二次调用getch()
			{
			case 72://下键
			{
				if (choseNumHis > -1)
				{
					choseNumHis--;
				}
				break;
			}
			case 80://上键
			{
				if (choseNumHis < 18 && choseNumHis < sumHis)
				{
					choseNumHis++;
				}
				break;
			}
			default:break;
			}
		}
	}

	//关闭又重新打开，为了在打开的时候把原本的文件内容清空，进行输入
	fhistory.close();

	ofstream whistory("history.txt");
	if (!whistory.is_open())
	{
		cout << "写入记录文件失败";
		return;
	}

	p = head->next;
	while (p != NULL)//写入原本的记录，可能有更改
	{
		whistory << " " << p->hlevel << " " << p->hname << " " << p->hscore;
		p = p->next;
	}
	whistory.close();
}