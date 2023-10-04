#pragma once
#include"const_number.h"
class Move_line
{
public:
	bool state[10];//十种状态
	int length;//一共有多少个重要转折点
	int x[graph_point], y[graph_point];//重要的转折点
	double r_vx, r_vy;//速度
	double rest_x,rest_y;//剩下的
	double rest_xt, rest_yt;//尾巴的剩下的余量
	double r_v;//速度
	int length1;//线的长度

	Move_line(int x1, int y1, int x2, int y2,double x_speed,double y_speed);
	Move_line(const Move_line& m_l);
	~Move_line();
	void move();
	int move_help(double v, double *rest);//用来调和小数与整数之间的误差，因为误差积累起来真的会很大，影响视觉。
	void turn_speed_direction_by_theta(float vTheta);
	void turn_speed_direction_by_rebound_line(int vX, int vY);
	void set_speed(double x, double y);
	void setXi(int vX, int vI);
	void setStateI(int v, int vI);

	void setYi(int vY, int vI);
	void set_vx(double x);
	void set_vy(double y);
	void add();
	void draw();
};
class fire_work {
public:
	int x, y;
	double avrage_length;//烟花的平均长度
	double avrage_speed;
	Move_line* l[fire_work_num];
	int length;
	fire_work(int x,int y,int len);
	void move();
	void draw();
};
class my_circle :public Move_line {
public:
	int radius;//半径
	my_circle(int x1, int y1, double x_speed, double y_speed);
	my_circle(const my_circle& m_c);
	void get_input(char c);
	void move();
	void draw();
};
class my_rectangle:public Move_line {
	int width;
	int height;
public:
	my_rectangle();
	my_rectangle(int x, int y, int width, int height, double x_speed, double y_speed);
	my_rectangle(const my_rectangle& m_r);
	void set_position(int x, int y);
	void set_size(int w, int h);
	void move();
	void draw();
	bool circle_in(int vx, int vy, int vr,int *vReboundLineX,int *vReboundLineY);
	void reboundBall(my_circle* m);
};

class my_rectangle1:public Move_line {
public:

	bool* g_score; //核心
	my_rectangle1(int width, int height, double x_speed);//构造函数
	void move();//移动

	int height;
	int width;
	void draw();
	bool circle_in(int x, int y, int r);
};
class paotai {
public:
	float w_range;//旋转最大值
	float w;//角速度
	float theta;//炮台发射角度
	int length;//炮台瞄准镜
	int x1, y1;//左下角的坐标
	int x2, y2;//右下角的坐标
	int height;
	int width;

	paotai(int h,int w);
	void move();
	void draw();

};
class Going_down_map {
public:

	Going_down_map(int vNumOfPlateforms,int vWidth,int vHeight);

	my_rectangle* Plateforms;
	bool *m_Serrated;
	int m_MaxSerratedNum;
	int width;
	int height;
	int m_NumOfPlateforms;
	int m_BottomPlateformX;
	int m_BottomPlateformI;
	int m_HeightSpaceBase;
	int m_HeightSpaceRange;
	int m_WidthSpaceBase;
	int m_WidthSpaceRange;
	float m_RisingSpeed;

	my_circle* m_Person;
	int m_Hitpoint;
	int m_PersonMoveSpeed;
	int m_PersonJumpSpeed;

	int m_triangleHeight;
	int m_triangleWidth;
	void personDeath();
	void controlPerson();
	void move();
	void personMove();
	void draw();
	void detectPersonInPlateforms();
	void generalNextPlateforms(int vGeneralI,int vSeedI);
	

};
 class rectangle_map {
public:
	my_rectangle* m_Plateform;
	bool m_HavePrize;
	bool *broken;
	int x;
	int y;
	int row;//行数
	int col;//列数
	int width;
	int height;
	int h_space;//高度之间的间隔。矩阵上表面距离其所在区域的距离
	int w_space;//同上，只不过是横着来的
	int m_PreparePrize;
	my_circle *m_Prize;
	my_circle* Ball;
	my_rectangle* rectangles;//所有的矩阵,有 m*n 个

	rectangle_map(int r, int c, int h, int w,int vx,int vy);
	/*
	* 首先矩阵分为m*n个区域
	* 每个区域大于 长方形类my_rectangel
	* 
	*/
	void draw();
	bool detect_in_circle(my_circle * m_c);
	void sendPrizeDetect();
	void preparePrize(int x,int y);
	void hidePrize();

};
