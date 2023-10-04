#pragma once
#include"const_number.h"
class Move_line
{
public:
	bool state[10];//ʮ��״̬
	int length;//һ���ж��ٸ���Ҫת�۵�
	int x[graph_point], y[graph_point];//��Ҫ��ת�۵�
	double r_vx, r_vy;//�ٶ�
	double rest_x,rest_y;//ʣ�µ�
	double rest_xt, rest_yt;//β�͵�ʣ�µ�����
	double r_v;//�ٶ�
	int length1;//�ߵĳ���

	Move_line(int x1, int y1, int x2, int y2,double x_speed,double y_speed);
	Move_line(const Move_line& m_l);
	~Move_line();
	void move();
	int move_help(double v, double *rest);//��������С��������֮�������Ϊ������������Ļ�ܴ�Ӱ���Ӿ���
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
	double avrage_length;//�̻���ƽ������
	double avrage_speed;
	Move_line* l[fire_work_num];
	int length;
	fire_work(int x,int y,int len);
	void move();
	void draw();
};
class my_circle :public Move_line {
public:
	int radius;//�뾶
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

	bool* g_score; //����
	my_rectangle1(int width, int height, double x_speed);//���캯��
	void move();//�ƶ�

	int height;
	int width;
	void draw();
	bool circle_in(int x, int y, int r);
};
class paotai {
public:
	float w_range;//��ת���ֵ
	float w;//���ٶ�
	float theta;//��̨����Ƕ�
	int length;//��̨��׼��
	int x1, y1;//���½ǵ�����
	int x2, y2;//���½ǵ�����
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
	int row;//����
	int col;//����
	int width;
	int height;
	int h_space;//�߶�֮��ļ���������ϱ����������������ľ���
	int w_space;//ͬ�ϣ�ֻ�����Ǻ�������
	int m_PreparePrize;
	my_circle *m_Prize;
	my_circle* Ball;
	my_rectangle* rectangles;//���еľ���,�� m*n ��

	rectangle_map(int r, int c, int h, int w,int vx,int vy);
	/*
	* ���Ⱦ����Ϊm*n������
	* ÿ��������� ��������my_rectangel
	* 
	*/
	void draw();
	bool detect_in_circle(my_circle * m_c);
	void sendPrizeDetect();
	void preparePrize(int x,int y);
	void hidePrize();

};
