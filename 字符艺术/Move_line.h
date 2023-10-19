#pragma once
#include"const_number.h"
#include<list>

class CBrokenBricks;
class CollisionHandler;
class CBumbor;
class CBullet;


class Move_line
{
public:
	int m_CollisionKind;
	bool state[10];//十种状态
	int length;//一共有多少个重要转折点
	int x[graph_point], y[graph_point];//重要的转折点
	int length1;//线的长度float m_speedTheta;
	double r_vx, r_vy;//速度
	double rest_x,rest_y;//剩下的
	double rest_xt, rest_yt;//尾巴的剩下的余量
	double r_v;//速度
	CollisionHandler* m_Handler;

	Move_line(int x1, int y1, int x2, int y2,double x_speed,double y_speed);
	Move_line(const Move_line& m_l);
	~Move_line();

	void setStateI(int v, int vI);
	
	void move();
	void setXi(int vX, int vI);
	void setYi(int vY, int vI);
	int move_help(double v, double* rest);//用来调和小数与整数之间的误差，因为误差积累起来真的会很大，影响视觉。
	void set_position(int x, int y);

	void set_speed(double x, double y);
	void set_vx(double x);
	void set_vy(double y);
	void turn_speed_direction_by_theta(float vTheta);
	void turn_speed_direction_by_rebound_line(int vX, int vY);


	void add();

	void draw();

	virtual void changeAfterCollision(Move_line * vCollidingWithMe);
	virtual int getCollisionKind();
};
class CollisionHandler {
private:
	std::list<Move_line*> CollisionsList;
public:
	CollisionHandler();
	void add(Move_line* vAddedNode);
	void deleteNode(Move_line* vDeletedNode);
	void collide(Move_line* collisionItem);
	void collideAll();
};

class CClock {
public:
	CClock();
	CClock(int vCycle);
	void setCycle(int vCycle);
	bool count();
private:
	int m_TimeAfterSet;
	int m_Cycle;
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

	bool circleIn(int vX, int vY, int vRadius);
	void get_input(char c);
	void move();


	virtual void changeAfterCollision(Move_line* vCollidingWithMe);
	virtual int getCollisionKind();

	void draw();
	void setRadius(int vRadius);
};
class control_circle :public my_circle {
public:
	float m_speedArrowLength;

	control_circle(int x1, int y1, double x_speed, double y_speed);
	control_circle(const control_circle& m_c);
	void processInput();


	void draw();
};
class my_rectangle:public Move_line {
public:
	int width;
	int height;
	
	my_rectangle();
	my_rectangle(int x, int y, int width, int height, double x_speed, double y_speed);
	my_rectangle(const my_rectangle& m_r);
	
	void set_size(int w, int h);
	void move();
	bool circle_in(int vx, int vy, int vr,int *vReboundLineX,int *vReboundLineY);
	bool rectangleIn(int vX, int vY, int vWidth, int vHeight);
	void reboundBall(my_circle* m);

	virtual void changeAfterCollision(Move_line* vCollidingWithMe);
	virtual int getCollisionKind();

	void draw();
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
 

 class CBumborHero:public control_circle{
 public:
	 int m_StepAfterThink;
	 int m_MaxStepAfterTink;
	 bool m_TurnDirection;

	 bool m_Live;
	 int m_ControlMod;
	 std::list<CBumbor>* m_CreateBumb;
	 char m_Direction;
	 CBumborHero(CollisionHandler *vCHandler,std::list<CBumbor>* vCBumb,int vR,int x1, int y1, double x_speed, double y_speed);
	 CBumborHero(const CBumborHero & vHero);


	 int processInput();
	 void setAutoMove(int vSpeed);
	 virtual void changeAfterCollision(Move_line* vCollidingWithMe);
	 void draw();
	 void setControlMod(int vCMod);
 };
 class CBumbor:public my_rectangle{
 public:

	 int m_LastTime;
	 int m_StartTime;
	 int m_RangeValue;
	 my_rectangle* m_RangeGraphic;

 	 CBumbor(int vLastTime, int vStartTime, int vRange,CollisionHandler * vCHandler, int x, int y, int width, int height);
	 CBumbor(const CBumbor& vCBumbor);
	 ~CBumbor();
	 virtual int getCollisionKind();
	 void move();
	 void draw();
 };
 class CBumborMan {
 public:

	 int m_NumEnemy;
	 int m_NumPlayer;
	 int m_HeroNum;
	 int m_Row;
	 int m_Col;
	 int size;
	 CollisionHandler m_CHandler;
	 my_rectangle* m_BlockMap;
	 //CBumborHero* m_Hero;
	 std::list<CBumbor> m_BumborList;
	 std::list<CBumbor>::iterator m_Checker;

	 std::list<CBrokenBricks> m_Bricks;
	 std::list<CBrokenBricks>::iterator m_CheckerBricks;

	 std::list<CBumborHero> m_Heros;
	 std::list<CBumborHero>::iterator m_CheckerHero;



	 CBumborMan();
	 ~CBumborMan();

	 void move();

	 void draw();

	 
 };
 class CBrokenBricks:public my_rectangle {
 public:
	 bool m_Broken;
	 int m_I;
	 int m_K;
	 CBrokenBricks(int vI,int vK,int x, int y, int width, int height);
	 CBrokenBricks(const CBrokenBricks& vCBricks);
	 void move();
	 

	 virtual void changeAfterCollision(Move_line* vCollidingWithMe);
	

	 void draw();
 };
 // 可控制方向球 和 直线Ax + By +C = 0 的生成
 /*
 srand(time(0));
 initgraph(screen_width,screen_hight);

 float A;
 float B;
 float C;
 float TempX = 5.235;
 float TempY = 4.077;
 A = TempY;
 B = -TempX;
 C = -(A * screen_width / 2 + B * screen_hight / 2);
 control_circle test_speed(screen_width / 2, screen_hight / 2,4.59, 0);


 while (1) {
		 BeginBatchDraw();
		 cleardevice();
		 test_speed.processInput();
		 test_speed.move();

		 if (abs(A * test_speed.x[0] + B * test_speed.y[0] + C) / sqrt(A * A + B * B) < test_speed.radius)
			 test_speed.turn_speed_direction_by_rebound_line(TempX, TempY);
		 Sleep(time_);

		 test_speed.draw();
		 line(0, -C / B, screen_width, (-A * screen_width - C) / B);

		 EndBatchDraw();
	 }

	 BeginBatchDraw();
	 cleardevice();

	 return 0;
	 */

 class CAircraft :public my_rectangle{
 public:
	 int m_Camp;
	 int m_ShootSpace;
	 int m_ShootTimes;
	 int m_HitPoint;
	 int m_Operation;
	 int m_ControlMod;
	 int m_Graphic;
	 int m_BulletSpeed;
	 int m_BulletRadius;

	 std::list<CBullet>* m_Bullet;
	 CollisionHandler *m_CHandler;

	 CAircraft(int vX, int vY,int vWidth,int vHeight,double vX_speed, double vY_speed,int vSpeed,std::list<CBullet>* vBullet,CollisionHandler * vCHandler);
	 CAircraft(const CAircraft& m_c);


	 int getInput();
	 void move();
	 virtual void changeAfterCollision(Move_line* vCollidingWithMe);
	 void draw();
	 void setAutoMove(int vKind);
	 void setPlayer2();

 };
 class CAircraftBattle {
 public:
	 int m_NormalEnemy;
	 int m_AircraftWidth;
	 int m_AircraftHeight;
	 bool m_Player1Live;
	 bool m_Player2Live;
	 bool m_BossBattle;
	 bool m_BossLive;
	 CClock m_GenerateEnemyClock;
	 CollisionHandler m_CHandler;
	 std::list<CBullet> m_BulletList;
	 std::list<CAircraft> m_Aircrafts;
	 std::list<CAircraft>::iterator Player1;
	 std::list<CAircraft>::iterator Player2;
	 std::list<CAircraft>::iterator Boss;


	 CAircraftBattle();
	 ~CAircraftBattle();
	 void move();
	 void draw();
	 void addBullet(CAircraft* vCheck, float vTheta,int Mod);
 };

 class CBullet:public my_circle {
 public:
	 int m_Camp;
	 bool m_Live;
	 CBullet(int x1, int y1, double x_speed, double y_speed,int vCamp);
	 CBullet(const CBullet& m_c);
	 CAircraft* m_Point;
	 void setPoint(CAircraft* vPint);
	 void move();
	 virtual void changeAfterCollision(Move_line* vCollidingWithMe);
 };