#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>
#include"const_number.h"
#include"Move_line.h"
#include<iostream>
#include<conio.h>
#define circle_number 20
#define line_number 1
#define circle_v 30
#define Plateform_width 100
#define Plateform_height 20
#define Plateform_speed 10
#define PersonJumpSpeed -10

using namespace std;

int main() {

	srand(time(0));
	initgraph(screen_width,screen_hight);
	my_rectangle Plateform(0,screen_hight - Plateform_height - 2,Plateform_width,Plateform_height,0,0);
	my_circle Ball( 0 + Plateform_width/2, screen_hight - Plateform_height - 12  , 0, 0);
	Ball.setStateI(true, 0);
	Ball.setStateI(true, 2);//3就是会飞到下面不会反弹，飞出屏幕外
	rectangle_map Map(5,7, 50, 100, 0,0);
	Map.m_Plateform = &Plateform;
	Map.Ball = &Ball;
	BeginBatchDraw();
	cleardevice();	

	outtextxy(screen_width / 2 - 300, screen_hight / 2, "use left and right key to move platforms, up to shoot the ball,\n enter to begin the game ");

	EndBatchDraw();

	getchar();
	
while (1) {
		BeginBatchDraw();
		cleardevice();	
		//outtextxy(0, 0,num);
		Ball.move();
		Map.m_Prize->move();
		if (Ball.y[0] > screen_hight)
			break;
		Map.detect_in_circle(&Ball);
		Map.sendPrizeDetect();
		Plateform.reboundBall(&Ball);
	if (_kbhit()) {
		if (GetAsyncKeyState(VK_UP)) {
			Ball.setStateI(false, 0);
			Ball.set_speed(2.5, 3.4);
		}

		else if (GetAsyncKeyState(VK_LEFT))
		{
			Plateform.setXi(Plateform.x[0] - Plateform_speed, 0);
			if (Ball.state[0])
				Ball.setXi(Ball.x[0] - Plateform_speed, 0);
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
				Plateform.setXi(Plateform.x[0] + Plateform_speed, 0);
				if(Ball.state[0])
				Ball.setXi(Ball.x[0] + Plateform_speed, 0);	
		}
	
	}
			Sleep(time_);


		Map.draw();
		Plateform.draw();
		Ball.draw();
		EndBatchDraw();
	}
		
	BeginBatchDraw();
	cleardevice();	


	outtextxy(screen_width / 2, screen_hight / 2, "Game over");
	EndBatchDraw();

	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
