
#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>
#include"const_number.h"
#include"Move_line.h"
#include<iostream>
#include<conio.h>
#include<math.h>

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
	bool live;

	CAircraftBattle Battle;

while (1) {

		BeginBatchDraw();
		cleardevice();	
		
		Battle.move();
		//cc.move();
		
		
		//CHandler.collide(&cc);

	
		
		Sleep(time_);

		Battle.draw();
		//cc.draw();
		
		

		EndBatchDraw();
	}
		BeginBatchDraw();
		if(live)
			outtextxy(0, 0, "YOU LOSE THE GAME!");
		else
		{
			outtextxy(0, 0, "YOU WIN!");
		}
		EndBatchDraw();
		getchar();

	return 0;
	
	
}
