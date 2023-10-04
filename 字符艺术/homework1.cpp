#include<graphics.h>
#include<iostream>
#define circle_number 15
/*
int main() {

	initgraph(250, 250);

	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	int count = 0;
	while (1) {
		count++;
		count = count % circle_number;
		for (int i = 0;i < circle_number;i++) {
			setlinecolor(RGB(10 * ((i - count)%circle_number), 0, 0));
			circle(125, 125, i * 5);
		}
		for (int i = 0;i < circle_number;i++) {
			setlinecolor(RGB(0, 255 - i * 10, 0));
			circle(375, 250, i * 5);
		}
		Sleep(100);
		//getchar();
		cleardevice();
	}
	getchar();
	return 0;
}
*/