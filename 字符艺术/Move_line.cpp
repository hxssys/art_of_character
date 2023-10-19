#include "Move_line.h"
#include<graphics.h>
#include"const_number.h"
#include<iostream>
#include<math.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<functional>


Move_line::Move_line(int x1, int y1, int x2, int y2,double x_speed,double y_speed) {
	m_CollisionKind = -1;
	for(int i = 0;i < 10;i++)
	state[i] = false;

	rest_x = 0; // 余下的距离
	rest_y = 0;// 余下的距离同上 //
	rest_xt = 0;
	rest_yt = 0;

	length = 2;// 关键节点，最开始只有两个

	x[0] = x1; // 首节点的位置
	y[0] = y1;//  同上
	x[1] = x2;// 尾节点的位置
	y[1] = y2;// 同上

	r_vx = x_speed;// 运动方向
	r_vy = y_speed;// 同上
	
	r_v = sqrt(r_vx * r_vx + r_vy * r_vy);
}
Move_line::Move_line(const Move_line& m_l) {
	m_CollisionKind = m_l.m_CollisionKind;
	for (int i = 0;i < graph_point;i++)
		x[i] = m_l.x[i];

	for (int i = 0;i < graph_point;i++)
		y[i] = m_l.y[i];

	for(int i = 0;i < 10;i++)
	state[i] = m_l.state[i];

	rest_x = m_l.rest_x; 
	rest_y = m_l.rest_y;
	rest_xt = m_l.rest_xt;
	rest_yt = m_l.rest_yt ;

	length = m_l.length;// 关键节点，最开始只有两个


	r_vx = m_l.r_vx;// 运动方向
	r_vy = m_l.r_vy;// 同上
	
	r_v = m_l.r_v;
}
Move_line::~Move_line() {
}
void Move_line::move() {
	

	if (length == 1)
		return;
	double theta = atan2(y[length - 2] - y[length - 1], x[length - 2] - x[length - 1]);
   


	x[length - 1] += move_help((r_v+1) * cos(theta),&rest_xt); 
	y[length - 1] += move_help((r_v + 1) * sin(theta),&rest_yt);


//	x[length - 1] += move_help(r_v * cos(theta),&rest_xt); // 尾结点的移动
//	y[length - 1] += move_help(r_v * sin(theta),&rest_xt);//同上

	x[0] += move_help(r_vx, &rest_x);

	y[0] += move_help(r_vy, &rest_y);
	double temp;
	temp = rest_y + r_vy - (int)r_vy;

	
	if (x[0] > screen_width || x[0] < 0) {
		add();
		r_vx = -r_vx;
		x[0] += r_vx;
	}
	else if (y[0] < 0 || y[0] > screen_hight) {
		add();
		r_vy = -r_vy;
		y[0] += r_vy;
		}
	else if( sqrt( (x[0] - screen_width / 2)*(x[0] - screen_width / 2) + (y[0] - screen_hight / 2)*(y[0] - screen_hight / 2) ) < circle_radius){
		double theta1 = atan2( screen_hight / 2 - y[0],screen_width / 2 - x[0]);
		double theta2 = atan2(r_vy, r_vx);
		double theta3 = theta2 - theta1;
		double a = sqrt( (screen_width / 2 - x[0]) * (screen_width / 2 - x[0]) + (screen_hight / 2 - y[0] )*(screen_hight / 2 - y[0]) );
		add();
		r_vx = r_vx - 2 * r_v / a * cos(theta3) * (screen_width / 2 - x[0]);
		r_vy = r_vy - 2 * r_v / a * cos(theta3) * (screen_hight / 2 - y[0]);
	//	x[0] += r_vx;
	//	y[0] += r_vy;

		/*
		double theta1 = atan2( screen_hight / 2 - y[0],screen_width / 2 - x[0]);
		double theta2 = atan2(vy, vx);
		double theta3 = 3.1415926 - theta2 - 2 * theta1;
		add();
		vx = v * cos(theta3);
		vy = v * sin(theta3);

		x[0] += vx;
		y[0] += vy;
		*/
		/*
		double theta2 = atan2(y[0] - screen_hight / 2, x[0] - screen_width / 2);
		vx = v * cos(theta2);
		vy = v * sin(theta2);

		add();
		x[0] += vx;
		y[0] += vy;

*/

	}
	if (sqrt((x[length - 1] - x[length - 2]) * (x[length - 1] - x[length - 2]) + (y[length - 1] - y[length - 2]) * (y[length - 1] - y[length - 2])) < 6)
		length--;
/*
*	这个版本是太短了之后会自己死亡
	if (length > 2 && sqrt((x[length - 1] - x[length - 2]) * (x[length - 1] - x[length - 2]) + (y[length - 1] - y[length - 2]) * (y[length - 1] - y[length - 2])) < 4)
		length--;
*/
	
}
void Move_line::setStateI(int v, int vI) {
	state[vI] = v;
}
void Move_line::setXi(int vX, int vI) {
	x[vI] = vX;
}
void Move_line::setYi(int vY, int vI) {
	y[vI] = vY;
}
int Move_line::move_help(double v, double* rest) {
	double temp = *rest + v - (int)v;// 用来做某些东西的
	int solution;//储存结果
	if (temp > 1)
	{
		solution = v + 1;
		*rest -= 1;
	}
	else {
		solution = v ;
		*rest += v;
	}
	return solution;
}
void Move_line::set_position(int x, int y) {
	this->x[0] = x;
	this->y[0] = y;
}
void Move_line::draw() {
	//circle(x[0], y[0], 10);
	for (int i = 0;i < length - 1;i++) {
		line(x[i], y[i], x[i + 1], y[i + 1]);
	}
}
void Move_line::changeAfterCollision(Move_line* vCollidingWithMe)
{
}
int Move_line::getCollisionKind()
{
	return -1;
}
void Move_line::add() {
	if (length < 200) {
		for (int i = 0;i < length;i++) {
			x[length - i] = x[length - i - 1];
			y[length - i] = y[length - i - 1];
		}
		length++;
	}
}
void Move_line::turn_speed_direction_by_theta(float vTheta) {

	float CosTheta = cos(vTheta);
	float SinTheta = sin(vTheta);

	float TempVx = r_vx * CosTheta - r_vy * SinTheta;
	float TempVy = r_vx * SinTheta + r_vy * CosTheta;

	r_vx = TempVx;
	r_vy = TempVy;

}
void Move_line::turn_speed_direction_by_rebound_line(int Vx,int Vy) {
	int Temp;
	Temp = Vy;
	Vy = -Vx;
	Vx = Temp;
	//向量垂直运算
	
	if (r_vx * Vx + r_vy * Vy > 0)
		;
	else
	{
		Vx = -Vx;
		Vy = -Vy;
	}


	float ThetaV = atan2(r_vy,r_vx);
	float ThetaL = atan2(Vy,Vx);
	float DelTheta = ThetaV - ThetaL;
	if (DelTheta < 0)
		turn_speed_direction_by_theta(-2 * DelTheta - 3.1415);
	else
	{
		turn_speed_direction_by_theta(3.1415 - 2 * DelTheta);
	}

	//this->move();

}
void Move_line::set_speed(double x, double y) {
	r_vx = x;
	r_vy = y;
}
void Move_line::set_vx(double x) {
	r_vx = x;
}
void Move_line::set_vy(double y) {
	r_vy = y;
}
fire_work::fire_work(int x,int y,int len) {
	avrage_length = 130;
	avrage_speed = 3;
	length = len;
	double theta;
	for (int i = 0;i < length;i++) {
		theta = 6.28 *  rand() / RAND_MAX;

		l[i] = new Move_line(x + avrage_length * cos(theta), y + avrage_length * sin(theta),x,y,avrage_speed * cos(theta), avrage_speed * sin(theta));
	}
}

void fire_work::move() {
	for (int i = 0;i < length;i++) {
		l[i]->move();
	}
}
void fire_work::draw() {
	for (int i = 0;i < length;i++) {
		l[i]->draw();
	}
}

my_circle::my_circle(int x1, int y1,double x_speed,double y_speed):Move_line(x1,y1,1,1,x_speed,y_speed) {
	m_CollisionKind = 0;
	radius = circle_radius;
}
my_circle::my_circle(const my_circle& m_c):Move_line(m_c) {
	radius = m_c.radius;
}
void my_circle::move() {
	if (state[0])
		return;
	if(state[1])
	r_vy += _g;//重力加速度的改变
	x[0] += move_help(r_vx, &rest_x);
	y[0] += move_help(r_vy, &rest_y);

	if (x[0] + radius > screen_width || x[0] - radius < 0) {
		r_vx = -r_vx;
		x[0] += r_vx;
	}
	else if (y[0] - radius < 0 ||y[0] + radius > screen_hight) {
		if (state[2] && y[0] + radius > screen_hight)
			return;
		r_vy = -r_vy;
		y[0] += 2*r_vy;
	}

	
}
void my_circle::changeAfterCollision(Move_line* vCollidingWithMe)
{
	int ReboundLinex;
	int RevoundLiney;

	int CollisionKind = vCollidingWithMe->getCollisionKind();

	if (CollisionKind == 0) {
		my_circle* CollidingWithMe = (my_circle*)vCollidingWithMe;
		if (CollidingWithMe->circleIn(x[0], y[0], radius)) {
			;
		}
	}

	else if (CollisionKind == 1) {
		my_rectangle* CollidingWithMe = (my_rectangle *)vCollidingWithMe;
		if (CollidingWithMe->circle_in(x[0], y[0], radius, &ReboundLinex, &RevoundLiney))
		{
			turn_speed_direction_by_rebound_line(ReboundLinex, RevoundLiney);
			setXi(x[0] + r_vx, 0);
			setYi(y[0] + r_vy, 0);
		}
	}

	
}
int my_circle::getCollisionKind()
{
	return 0;
}
void my_circle::draw() {
	circle(x[0], y[0], radius);
}
void my_circle::setRadius(int vRadius)
{
	radius = vRadius;
}
bool my_circle::circleIn(int vX, int vY, int vRadius)
{
	if (vRadius + radius >= sqrt((vX - x[0]) * (vX - x[0]) + (vY - y[0]) * (vY - y[0])) )
	return true;
	else
	{
		return false;
	}
}
void my_circle::get_input(char c) {
	if (state[1] == false) {
		r_vy = -25;
		state[1] = true;
	}
}

control_circle::control_circle(int x1, int y1, double x_speed, double y_speed) :my_circle(x1, y1, x_speed, y_speed)
{
	m_speedArrowLength = 10;
}
control_circle::control_circle(const control_circle& m_c):my_circle(m_c)
{
	m_speedArrowLength = m_c.m_speedArrowLength;
}
void control_circle::processInput()
{
	if (GetAsyncKeyState('W'))
		this->setStateI(!state[0], 0);
	else if (GetAsyncKeyState('A'))
		turn_speed_direction_by_theta(-0.1);
	else if (GetAsyncKeyState('D'))
		turn_speed_direction_by_theta(0.1);

}
void control_circle::draw()
{
	circle(x[0], y[0], 10);

	float Theta = atan2(r_vy, r_vx);
	if (state[0]) {
		line(x[0], y[0], x[0] + m_speedArrowLength * cos(Theta), y[0] + m_speedArrowLength * sin(Theta));
	}
}

paotai::paotai(int h,int wid) {
	length = 100;
	height = h;
	w_range = 1;
	theta = -w_range + 0.1;
	w = 0.02;
	width = wid;
	x1 = 0;
	y1 = (screen_hight - height) / 2.0;
	x2 = width;
	y2 = (screen_hight + height) / 2.0;
}
void paotai::draw() {
	rectangle(x1, y2, x2, y1);
	line(x1, screen_hight / 2, x1 + length * cos(theta), screen_hight / 2 + length * sin(theta));

}
void paotai::move() {
	if (theta < -w_range || theta > w_range) {
		w = -w;
	}
	theta += w;



}

my_rectangle::my_rectangle(int x, int y, int wid, int h, double x_speed, double y_speed) :Move_line(x, y, 1, 1, x_speed, y_speed) {
	m_CollisionKind = 1;
	width = wid;
	height = h;
}
my_rectangle::my_rectangle():Move_line(0,0,1,1,0,0) {
	m_CollisionKind = 1;
	width = 0;
	height = 0;
}
my_rectangle::my_rectangle(const my_rectangle& m_r) :Move_line(m_r) {
	width = m_r.width;
	height = m_r.height;
}
void my_rectangle::move() {
		if (state[0])
		return;
	if(state[1])
	r_vy += _g;//重力加速度的改变

	x[0] += move_help(r_vx, &rest_x);
	y[0] += move_help(r_vy, &rest_y);

	if(!state[2])
	if (x[0] + width > screen_width || x[0]< 0) {
		r_vx = -r_vx;
		x[0] += r_vx;
	}
	else if (y[0]< 0 || y[0] + height > screen_hight) {
		r_vy = -r_vy;
		y[0] += r_vy;
	}


}
void my_rectangle::draw() {
	rectangle(x[0], y[0], x[0] + width, y[0] + height);
}

void my_rectangle::set_size(int w, int h)
{
	width = w;
	height = h;
}
bool my_rectangle::circle_in(int vx, int vy, int vr,int *vReboundLineX,int *vReboundLineY) {
	
	float Cx, Cy;
	float RlationRectangleX, RlationRectangleY;

	Cx = vx - this->x[0] - width / 2;
	Cy = vy - this->y[0] - height / 2;

	RlationRectangleX = Cx;
	RlationRectangleY = Cy;

	Cx = Cx > 0 ? Cx : -Cx;
	Cy = Cy > 0 ? Cy : -Cy;

	Cx -= width / 2;
	Cy -= height / 2;

	Cx = Cx > 0 ? Cx : 0;
	Cy = Cy > 0 ? Cy : 0;



	if (sqrt(Cx * Cx + Cy * Cy) > vr) {
		return false;
	}
	else 
	{

		if (Cx * Cy != 0) {
			if (RlationRectangleX * RlationRectangleY > 0) {
				*vReboundLineX = -height;
				*vReboundLineY = width;
			}
			else
			{
				*vReboundLineX = height;
				*vReboundLineY = width;
			}
		}
		else
		{
			*vReboundLineX = Cy;
			*vReboundLineY = Cx;
		}
		return true;
	}


}
bool my_rectangle::rectangleIn(int vX, int vY, int vWidth, int vHeight)
{
	if(x[0] + width < vX || vX + vWidth < x[0] || y[0] + height < vY || vY + vHeight < y[0])
	return false;
	else
	{
		return true;
	}
}
void my_rectangle::reboundBall(my_circle* vM)
{
	int ReboundLinex;
	int RevoundLiney;
		if (circle_in(vM->x[0], vM->y[0], vM->radius,&ReboundLinex,&RevoundLiney))
		{
			vM->turn_speed_direction_by_rebound_line(ReboundLinex,RevoundLiney);
		}
		vM->setXi(vM->x[0] + vM->r_vx,0);
		vM->setYi(vM->y[0] + vM->r_vy,0);	
}
void my_rectangle::changeAfterCollision(Move_line* vCollidingWithMe)
{
	
}
int my_rectangle::getCollisionKind()
{
	return 1;
}
my_rectangle1::my_rectangle1(int wid, int h, double x_speed) :Move_line(screen_width,screen_hight - h, 1, 1, x_speed,0) {
	g_score = NULL;
	width = wid;
	height = h;
}
void my_rectangle1::move() {
		if (state[0])
		return;
/*
	r_vy += _g;//重力加速度的改变
*/
	x[0] += move_help(r_vx, &rest_x);

	
	if (x[0] + width< 0) {
		x[0] = screen_width;
		width = 80 + rand() % 40;
		height = 100 + rand() % 100;
		r_vx = -15 - rand() % 10;
		if (g_score != NULL)
			*g_score = true;
	}



}
void my_rectangle1::draw() {
	rectangle(x[0],screen_hight - height, x[0] + width, screen_hight);
}
bool my_rectangle1::circle_in(int x, int y, int r) {
	float cx, cy;

	cx = x - this->x[0] - width / 2;
	cy = y - this->y[0] - height / 2;



	cx = cx > 0 ? cx : -cx;
	cy = cy > 0 ? cy : -cy;

	cx -= width / 2;
	cy -= height / 2;

	cx = cx > 0 ? cx : 0;
	cy = cy > 0 ? cy : 0;



	if (sqrt(cx * cx + cy * cy) > r)
		return false;
	else
		return true;



}

rectangle_map::rectangle_map(int r, int c, int h, int w,int vx,int vy) {
	broken = new bool[r * c];
	row = r;
	col = c;
	height = h;
	width = w;
	h_space = 0.1 * height;
	w_space = 0.1 * width;
	rectangles = new my_rectangle[r * c];
	my_rectangle sample(0, 0,0.8* width,0.8* height, 0, 0);

	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			broken[i * col + j] = false;
			rectangles[i * col + j] = sample;
			rectangles[i * col + j].set_position(vx + j * width + w_space,vy + i * height + h_space);
			if (rand() % 5 == 0)
				rectangles[i * col + j].setStateI(true,3);
		//	rectangles[i * col + j].set_position(j * 50, i * 50);
		}
	}

	m_Prize = new my_circle(0, screen_hight, 0, 0);
	m_PreparePrize = 0;
	m_HavePrize = false;
	m_Prize->setStateI(true, 2);

}
	/*
	* 首先矩阵分为m*n个区域
	* 每个区域大于 长方形类my_rectangel
	* 
	*/
void rectangle_map::draw() {

	m_Prize->draw();

	for (int i = 0;i < col * row;i++) {
		if (!broken[i]) {
			if(rectangles[i].state[3])
			setlinecolor(RGB(0, 255, 0));
			rectangles[i].draw();
			setlinecolor(RGB(255,255, 255));
		}
	}
}
bool rectangle_map::detect_in_circle(my_circle * m_c) {
	int i;
	bool find = false;
	int ReboundLinex;
	int RevoundLiney;
	for (i = 0;i < row * col;i++) {
		if (broken[i] == false && rectangles[i].circle_in(m_c->x[0], m_c->y[0], m_c->radius,&ReboundLinex,&RevoundLiney))
		{
			find = true;
			broken[i] = true;
			if (rectangles[i].state[3])
			preparePrize(rectangles[i].x[0],rectangles[i].y[0]);
			break;
		}
	}

	if (find) {
		m_c->turn_speed_direction_by_rebound_line(ReboundLinex,RevoundLiney);
	}
	return true;
}
void rectangle_map::preparePrize(int x, int y) {
	m_Prize->setXi(x + width / 2, 0);
	m_Prize->setYi(y + height / 2, 0);
//	m_Prize->setStateI(1, true);
	m_Prize->set_vy(5);
	m_HavePrize = true;
}
void rectangle_map::sendPrizeDetect() {
	if (m_HavePrize) {
		int TempX;
		int TempY;
		if (m_Prize->y[0] < screen_hight)
		{
			if (m_Plateform->circle_in(m_Prize->x[0], m_Prize->y[0], m_Prize->radius, &TempX, &TempY))
			{
				hidePrize();
				Ball->set_vx(1 + Ball->r_vx);
				Ball->set_vy(1 + Ball->r_vy);
			}
		}
		else
		{
			hidePrize();
		}
	}
}
void rectangle_map::hidePrize() {
		m_HavePrize = false;
		m_Prize->setXi(0, 0);
		m_Prize->setYi(screen_hight, 0);
		m_Prize->set_vy(0);
}


Going_down_map::Going_down_map(int vNumOfPlateforms,int vWidth,int vHeight) {
	m_WidthSpaceBase = 100;
	m_WidthSpaceRange = 30;

	m_HeightSpaceBase = 100;
	m_HeightSpaceRange = 30;

	m_RisingSpeed = -3;

	m_NumOfPlateforms = vNumOfPlateforms;
	Plateforms = new my_rectangle[m_NumOfPlateforms];
	width = vWidth;
	height = vHeight;
	my_rectangle sample(0, 0,width,height, 0, m_RisingSpeed);
	for (int i = 0;i < m_NumOfPlateforms;i++) {
		Plateforms[i] = sample;
		if (i == 0)
			Plateforms[i].set_position(rand() % screen_width, i * m_HeightSpaceBase + rand() % m_HeightSpaceRange + screen_hight - 100);
		else
		{
			generalNextPlateforms(i , i - 1);
			Plateforms[i].setYi(i * m_HeightSpaceBase + rand() % m_HeightSpaceRange + screen_hight - 100, 0);
		}
		Plateforms[i].setStateI(true, 2);
	}
	m_BottomPlateformX = Plateforms[0].x[0];
	m_BottomPlateformI = 0;

	m_Person = new my_circle(Plateforms[0].x[0],Plateforms[0].y[0] , 0, 0);
	m_Person->setStateI(true, 2);
	m_PersonMoveSpeed = 10;
	m_PersonJumpSpeed = -15;
	m_Hitpoint = 5;

	m_triangleHeight = 10;
	m_triangleWidth = 10;
	m_Serrated = new bool[vNumOfPlateforms];
	for (int i = 0;i < vNumOfPlateforms;i++) {
		m_Serrated[i] = false;
	}
	m_MaxSerratedNum = 1;

}
void Going_down_map::move() {

for (int i = 0;i < m_NumOfPlateforms;i++) {
			Plateforms[i].move();

		if (Plateforms[i].y[0] + height< 0) {

			if (m_Serrated[i])
				m_Serrated[i] = false;
	
			Plateforms[i].setYi(screen_hight, 0);
			if(m_Serrated[m_BottomPlateformI])
				generalNextPlateforms(i, (m_BottomPlateformI - 1) % m_NumOfPlateforms);
			else
				generalNextPlateforms(i, m_BottomPlateformI);
	
		int Sum = 0;
		for (int i = 0;i < m_NumOfPlateforms;i++) {
			if (m_Serrated[i])
				Sum++;
		}
		if (Sum >= m_MaxSerratedNum)
		{ }
		else
		{
			if (rand() % 2 == 1) {
				m_Serrated[i] = true;
			}
		}
		
		m_BottomPlateformX = Plateforms[i].x[0];
		m_BottomPlateformI = i;
		}
	}
	
	personMove();
}
void Going_down_map::generalNextPlateforms(int vGeneralI,int vSeedI) {
	int ChanceLeftOrRight = 0;
	ChanceLeftOrRight = rand() % 3;
	bool IsRight = false;
	
		if (Plateforms[vSeedI].x[0] < m_WidthSpaceBase + m_WidthSpaceRange + width) {
				IsRight = true;
			}
			else if (Plateforms[vSeedI].x[0] + 2 * width > screen_width - m_WidthSpaceBase - m_WidthSpaceRange) {
				IsRight = false;
			}
			else if (Plateforms[vSeedI].x[0] + width / 2 > screen_width) {
				if (ChanceLeftOrRight > 0) {
					IsRight = false;
				}
				else {
					IsRight = true;
				}
			}
			else {
				if (ChanceLeftOrRight == 0) {

					IsRight = false;
				}
				else {
					IsRight = true;
				}


			}
			if (IsRight) {
				Plateforms[vGeneralI].setXi(Plateforms[vSeedI].x[0] + width + m_WidthSpaceBase + rand() % m_WidthSpaceRange, 0);
			}
			else {
				Plateforms[vGeneralI].setXi(Plateforms[vSeedI].x[0] - width - m_WidthSpaceBase - rand() % m_WidthSpaceRange, 0);
			}


}
void Going_down_map::personMove() {
	m_Person->move();
	if (m_Person->y[0] > screen_hight)
		personDeath();
	else if (m_Person->y[0] - m_Person->radius < m_triangleHeight)
		personDeath();
}

void Going_down_map::draw() {
	for (int i = 0;i < m_NumOfPlateforms;i++) {
		Plateforms[i].draw();
		if (m_Serrated[i]) {
			for (int k = 0; k * m_triangleWidth < width;k++) {
				line(Plateforms[i].x[0] + k * m_triangleWidth,                       Plateforms[i].y[0],                    Plateforms[i].x[0] + k * m_triangleWidth + m_triangleWidth / 2, Plateforms[i].y[0] - m_triangleHeight);
				line(Plateforms[i].x[0] + k * m_triangleWidth + m_triangleWidth / 2, Plateforms[i].y[0] - m_triangleHeight, Plateforms[i].x[0] + (k + 1) * m_triangleWidth,                 Plateforms[i].y[0]);
			}
		}
	}
	m_Person->draw();
	for (int i = 0;i < 100;i++) {
		line(i * m_triangleWidth , 0, i * m_triangleWidth + m_triangleWidth / 2, m_triangleHeight);
		line( i * m_triangleWidth + m_triangleWidth / 2, m_triangleHeight, (i + 1) * m_triangleWidth, 0);
	}

	char Demo[20] = "";
	std::string St = "Hitpoint" + std::to_string(m_Hitpoint);
	strcpy_s(Demo, St.c_str());
	outtextxy(screen_width - 100, 100, Demo);
}
void Going_down_map::controlPerson() {
		

		if (GetAsyncKeyState(VK_UP) && m_Person->state[1] == false)	
			m_Person->set_vy(m_PersonJumpSpeed);
		else if (GetAsyncKeyState(VK_LEFT))
			m_Person->setXi(m_Person->x[0] - m_PersonMoveSpeed, 0);
		else if (GetAsyncKeyState(VK_RIGHT))
			m_Person->setXi(m_Person->x[0] +m_PersonMoveSpeed, 0);

}
void Going_down_map::personDeath() {
	m_Person->setXi(Plateforms[m_BottomPlateformI].x[0] + width / 2,0);
	m_Person->setYi(Plateforms[m_BottomPlateformI].y[0], 0);
	m_Hitpoint--;
}
void Going_down_map::detectPersonInPlateforms() {
	bool find = false;
	int ReboundLinex;
	int RevoundLiney;
	int i;
	for (i = 0;i < m_NumOfPlateforms;i++) {
		if (Plateforms[i].circle_in(m_Person->x[0], m_Person->y[0], m_Person->radius,&ReboundLinex,&RevoundLiney))
		{
			find = true;
			break;
		}
	}

	if (find) {
		if (m_Serrated[i])
			personDeath();
		else {
			m_Person->setStateI(false, 1);
			m_Person->setYi(Plateforms[i].y[0] - m_Person->radius / 2, 0);
			m_Person->set_vy(Plateforms[i].r_vy);
		}
	}
	else {
		m_Person->setStateI(true, 1);
	}

}

/*
	void detectPersonInPlateforms();
	*/


CollisionHandler::CollisionHandler()
{

}
void CollisionHandler::add(Move_line* vAddedNode)
{
	CollisionsList.push_front(vAddedNode);
}
void CollisionHandler::deleteNode(Move_line* vDeletedNode)
{
	CollisionsList.remove(vDeletedNode);
}
void CollisionHandler::collide(Move_line* vCollisionItem)
{
	std::list<Move_line*>::iterator Item = CollisionsList.begin();
	int N = CollisionsList.size();
	
	for (; Item != CollisionsList.end(); Item++) {
		if(vCollisionItem != *Item)
		vCollisionItem->changeAfterCollision(*Item);
	}
}
void CollisionHandler::collideAll()
{
	for (std::list<Move_line*>::iterator Check = CollisionsList.begin(); Check != CollisionsList.end(); Check++) {
		collide(*Check);
	}
}

CBumbor::CBumbor(int vLastTime, int vStartTime, int vRange, CollisionHandler *vCHandler, int vX, int vY, int vWidth, int vHeight):my_rectangle(vX, vY, vWidth, vHeight,1,1)
{
	m_CollisionKind = 2;
	m_LastTime = vLastTime * (1000 / time_);
	m_StartTime = vStartTime * (1000 / time_);
	m_RangeValue = vRange;
	m_Handler = vCHandler;

	m_RangeGraphic = new my_rectangle[m_RangeValue * 4];

	my_rectangle Sample(0, 0, width * 0.8, height * 0.8, 0, 0);

	for (int i = 0; i < m_RangeValue * 4; i++)
		m_RangeGraphic[i] = Sample;

	m_Handler->add(this);
}
CBumbor::CBumbor(const CBumbor& vCBumbor):my_rectangle(vCBumbor)
{
	m_CollisionKind = 2;
	m_LastTime = vCBumbor.m_LastTime;
	m_StartTime = vCBumbor.m_StartTime;
	m_RangeValue = vCBumbor.m_RangeValue;
	m_Handler = vCBumbor.m_Handler;

	m_RangeGraphic = new my_rectangle[m_RangeValue * 4];

	for (int i = 0; i < m_RangeValue * 4; i++)
		m_RangeGraphic[i] = vCBumbor.m_RangeGraphic[i];

	m_Handler->add(this);
}
CBumbor::~CBumbor()
{
	delete[] m_RangeGraphic;
}
int CBumbor::getCollisionKind()
{
	return 1;
}
void CBumbor::move()
{

	if (m_StartTime != 0) {
		m_StartTime--;

		if (m_StartTime == 0) {
		
			for (int i = 0; i < m_RangeValue; i++) {
				m_RangeGraphic[i].set_position(x[0] - (i + 1) * width , y[0] );
				m_RangeGraphic[i].setStateI(true, 0);
			}
			for (int i = 0; i < m_RangeValue; i++) {
				m_RangeGraphic[i + m_RangeValue].set_position(x[0] + (i + 1) * width , y[0] );
				m_RangeGraphic[i + m_RangeValue].setStateI(true, 0);
			}
			for (int i = 0; i < m_RangeValue; i++) {
				m_RangeGraphic[i + 2* m_RangeValue].set_position(x[0], y[0] - (i + 1) * height);
				m_RangeGraphic[i + 2 * m_RangeValue].setStateI(true, 0);
			}
			for (int i = 0; i < m_RangeValue; i++) {
				m_RangeGraphic[i + 3*m_RangeValue].set_position(x[0], y[0] + (i + 1) * height);
				m_RangeGraphic[i + 3 * m_RangeValue].setStateI(true, 0);
			}
			for (int i = 0; i < m_RangeValue * 4; i++) {
				m_RangeGraphic[i].set_position(m_RangeGraphic[i].x[0] + width * 0.1 , m_RangeGraphic[i].y[0] + height * 0.1);
				m_Handler->add(&m_RangeGraphic[i]);

			}
		}
	}
	else {

		if(m_LastTime != 0)
			m_LastTime--;

		if (m_LastTime == 0) {
			m_Handler->deleteNode(this);
			for (int i = 0; i < m_RangeValue * 4; i++) {
				m_Handler->deleteNode(&m_RangeGraphic[i]);
			}
		}

	}

}
void CBumbor::draw()
{

	rectangle(x[0] + width / 10, y[0] + height/ 10, x[0] + width - width / 10, y[0] + height - height / 10);

	if (m_StartTime != 0) {

	}
	else{
		if(m_LastTime > 0)
		for (int i = 0; i < m_RangeValue * 4; i++) {
			setfillcolor(RGB(125, 50, 0));
			fillrectangle(m_RangeGraphic[i].x[0], m_RangeGraphic[i].y[0], m_RangeGraphic[i].x[0] + m_RangeGraphic[i].width, m_RangeGraphic[i].y[0] + m_RangeGraphic[i].height);

			//m_RangeGraphic[i].draw();
			setfillcolor(RGB(255, 255, 255));
		}
	}
}

CBumborMan::CBumborMan()
{
	m_NumPlayer = 5;
	m_HeroNum = 4;
	m_NumEnemy = m_HeroNum - m_NumPlayer;
	m_Row = 12;
	m_Col = 12;
	size = 50;
	std::list<CBumborHero>::iterator P;
	CBumborHero s(&m_CHandler, &m_BumborList, size / 2 - 1, 25, 25, 0, 0);

	for (int i = 0; i < m_HeroNum; i++) {
		if (i <= 3)
			s.setControlMod(i + 1);
		else
		{
			s.setAutoMove(5);
		}

		s.set_position(25 + (rand() % (m_Row / 2)) * 2 * size, 25 + (rand() % (m_Col / 2)) * 2 * size);
	
		m_Heros.push_front(s);
		P = m_Heros.begin();
		m_CHandler.add(&(*P));
	}
	

	m_BlockMap = new my_rectangle[m_Row * m_Col + 4];


	my_rectangle Sample(0, 0, size, size, 0, 0);
	for (int i = 0; i < m_Row; i++) {
		for (int k = 0; k < m_Col; k++) {
			m_BlockMap[i * m_Col + k] = Sample;
			m_BlockMap[i * m_Col + k].set_position(k * size, i * size);

			if (i % 2  == 1 && k % 2 == 1)
				m_CHandler.add(&m_BlockMap[i * m_Col + k]);
			else if (i % 2 == 0 && k % 2 == 0) {

			}
			else {
				if (rand() % 3 == 0) {
					CBrokenBricks Sample(i, k, k * size, i * size, size, size);
					m_Bricks.push_front(Sample);
					std::list<CBrokenBricks>::iterator Temp = m_Bricks.begin();
					m_CHandler.add(&(*Temp));
				}
			
			}
				
		}
	}
	my_rectangle LeftBoard(-10, 0, 10, size * m_Row, 0, 0);
	m_BlockMap[m_Row * m_Col + 0] = LeftBoard;
	m_CHandler.add(&m_BlockMap[m_Row * m_Col + 0]);

	my_rectangle RightBoard(size * m_Col, 0,10, size*m_Row, 0, 0);
	m_BlockMap[m_Row * m_Col + 1] = RightBoard;
	m_CHandler.add(&m_BlockMap[m_Row * m_Col + 1]);

	my_rectangle TopBoard(0, -10, size * m_Col, 10, 0, 0);
	m_BlockMap[m_Row * m_Col + 2] = TopBoard;
	m_CHandler.add(&m_BlockMap[m_Row * m_Col + 2]);

	my_rectangle DownBoard(0, size * m_Row, size*m_Col, 10, 0, 0);
	m_BlockMap[m_Row * m_Col + 3] = DownBoard;
	m_CHandler.add(&m_BlockMap[m_Row * m_Col + 3]);


}
CBumborMan::~CBumborMan()
{
	delete[] m_BlockMap;
	//delete m_Hero;
}
void CBumborMan::move()
{

	for (m_CheckerHero = m_Heros.begin(); m_CheckerHero != m_Heros.end(); ) {

		if (!m_CheckerHero->m_Live) {
			if (m_CheckerHero->m_ControlMod == 0)
				m_NumEnemy--;
			else
				m_NumPlayer--;
			m_CheckerHero = m_Heros.erase(m_CheckerHero);
			continue;
		}
		else {
			if (m_CheckerHero->processInput()) {
				int TempX = m_CheckerHero->x[0] / size;
				TempX *= size;
				int TempY = m_CheckerHero->y[0] / size;
				TempY *= size;

				CBumbor Temp(1, 1, 2, &m_CHandler, TempX, TempY, 50, 50);
				m_BumborList.push_back(Temp);
			}
			m_CheckerHero->move();
			m_CHandler.collide(&(*m_CheckerHero));
			m_CheckerHero++;
		}
	}


	
	

	for (m_Checker = m_BumborList.begin(); m_Checker != m_BumborList.end(); m_Checker++) {
		m_Checker->move();
		if (m_Checker->m_LastTime == 0) { 
			m_BumborList.erase(m_Checker);
			break;
		}
	}

	for (m_CheckerBricks = m_Bricks.begin(); m_CheckerBricks != m_Bricks.end(); ) {
		m_CHandler.collide(&(*m_CheckerBricks));
		if (m_CheckerBricks->m_Broken) {
			m_CHandler.deleteNode(&(*m_CheckerBricks));
			m_Bricks.erase(m_CheckerBricks++);
		}
		else {
			m_CheckerBricks++;
		}
	}

}
void CBumborMan::draw()
{
	for (int i = 0; i < m_Row; i++) {
		for (int k = 0; k < m_Col; k++) {
			if (i % 2 ==  1&& k % 2 == 1)
				setfillcolor(RGB(255, 0, 0));
			else {
				setfillcolor(RGB(0, 255, 0));
			}
			fillrectangle(m_BlockMap[i * m_Col + k].x[0]    ,    m_BlockMap[i * m_Col + k].y[0]       ,       m_BlockMap[i * m_Col + k].x[0] + m_BlockMap[i * m_Col + k].width     ,    m_BlockMap[i * m_Col + k].y[0] + m_BlockMap[i * m_Col + k].height);
			
			setfillcolor(RGB(0, 0, 0));
		}
	}
	
	for (m_CheckerBricks = m_Bricks.begin(); m_CheckerBricks != m_Bricks.end(); m_CheckerBricks++) {
		m_CheckerBricks->draw();
	}
	
	for (m_CheckerHero = m_Heros.begin(); m_CheckerHero != m_Heros.end(); m_CheckerHero++) {
		m_CheckerHero->draw();
	}

	
	
	for (m_Checker = m_BumborList.begin(); m_Checker != m_BumborList.end(); m_Checker++) {
		m_Checker->draw();
	}

}


CBumborHero::CBumborHero(CollisionHandler *vCHandler,std::list<CBumbor>* vCBumb,int vR,int x1, int y1, double x_speed, double y_speed):control_circle(x1, y1, x_speed, y_speed)
{
	m_ControlMod = 1;
	m_Live = true;
	m_Handler = vCHandler;
	m_CreateBumb = vCBumb;
	r_v = 10;
	radius = vR;
}
CBumborHero::CBumborHero(const CBumborHero& vHero):control_circle(vHero)
{
	m_ControlMod = vHero.m_ControlMod;
	m_Live = vHero.m_Live;
	m_Handler = vHero.m_Handler;
	m_CreateBumb = vHero.m_CreateBumb;
	r_v = vHero.r_v;
	radius = vHero.radius;

	m_StepAfterThink = vHero.m_StepAfterThink;
	m_MaxStepAfterTink = vHero.m_MaxStepAfterTink;
	m_TurnDirection = vHero.m_TurnDirection;

}
int CBumborHero::processInput()
{
	int Choice = 0;
	if (m_ControlMod == 1) {
		
		if (GetAsyncKeyState('W')) {
			setYi(y[0] - r_v, 0);
			m_Direction = 'w';
		}
		else if (GetAsyncKeyState('A')) {
			setXi(x[0] - r_v, 0);
			m_Direction = 'a';
		}
		else if (GetAsyncKeyState('D')) {
			setXi(x[0] + r_v, 0);
			m_Direction = 'd';
		}
		else if (GetAsyncKeyState('S')) {
			setYi(y[0] + r_v, 0);
			m_Direction = 's';
		}
		else if (GetAsyncKeyState(' ')) {
			Choice = 1;
		}
	}
	else if (m_ControlMod == 2) {
		if (GetAsyncKeyState(VK_UP)) {
			setYi(y[0] - r_v, 0);
			m_Direction = 'w';
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			setXi(x[0] - r_v, 0);
			m_Direction = 'a';
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			setXi(x[0] + r_v, 0);
			m_Direction = 'd';
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			setYi(y[0] + r_v, 0);
			m_Direction = 's';
		}
		else if (GetAsyncKeyState(VK_RETURN)) {
			Choice = 1;
		}
	}
	else if (m_ControlMod == 0) {
		if (m_TurnDirection) {
			
			int TempDirection = rand() % 4;
			switch (TempDirection) {
			case 0:m_Direction = 'w'; break;
			case 1:m_Direction = 'a'; break;
			case 2:m_Direction = 's'; break;
			case 3:m_Direction = 'd'; break;
			}

			m_TurnDirection = false;
			m_StepAfterThink = 0;
		}
		else {
			switch (m_Direction) {
			case 'w':set_position(x[0], y[0] - r_v); break;
			case 's':set_position(x[0], y[0] + r_v); break;
			case 'a':set_position(x[0] - r_v, y[0]); break;
			case 'd':set_position(x[0] + r_v, y[0]); break;
			}
			m_StepAfterThink++;
			if (m_StepAfterThink >= m_MaxStepAfterTink) {
				
				m_TurnDirection = true;
			}
		}



	}
	else if (m_ControlMod == 3) {
		if (GetAsyncKeyState('U')) {
			setYi(y[0] - r_v, 0);
			m_Direction = 'w';
		}
		else if (GetAsyncKeyState('H')) {
			setXi(x[0] - r_v, 0);
			m_Direction = 'a';
		}
		else if (GetAsyncKeyState('K')) {
			setXi(x[0] + r_v, 0);
			m_Direction = 'd';
		}
		else if (GetAsyncKeyState('J')) {
			setYi(y[0] + r_v, 0);
			m_Direction = 's';
		}
		else if (GetAsyncKeyState('Y')) {
			Choice = 1;
		}
	}
	else if (m_ControlMod == 4) {
		if (GetAsyncKeyState(VK_NUMPAD8)) {
			setYi(y[0] - r_v, 0);
			m_Direction = 'w';
		}
		else if (GetAsyncKeyState(VK_NUMPAD4)) {
			setXi(x[0] - r_v, 0);
			m_Direction = 'a';
		}
		else if (GetAsyncKeyState(VK_NUMPAD6)) {
			setXi(x[0] + r_v, 0);
			m_Direction = 'd';
		}
		else if (GetAsyncKeyState(VK_NUMPAD5)) {
			setYi(y[0] + r_v, 0);
			m_Direction = 's';
		}
		else if (GetAsyncKeyState(VK_NUMPAD7)) {
			Choice = 1;
		}
	}
	return Choice;
}
void CBumborHero::setAutoMove(int vSpeed)
{
	m_MaxStepAfterTink = _BumborManSize / vSpeed;
	m_StepAfterThink = 0;
	m_ControlMod = 0;
	r_v = vSpeed;

}
void CBumborHero::changeAfterCollision(Move_line* vCollidingWithMe)
{

	int ReboundLinex;
	int RevoundLiney;

	my_rectangle* CCo = (my_rectangle*)vCollidingWithMe;
	int CollisionKind = vCollidingWithMe->m_CollisionKind;

	if (CollisionKind == 0) {
//		
		my_circle* CollidingWithMe = (my_circle*)vCollidingWithMe;
		if (CollidingWithMe->circleIn(x[0], y[0], radius)) {
			if(m_ControlMod != 0)
			m_Live = false;
		}
	}
	else if (CollisionKind == 1) {
		my_rectangle* CollidingWithMe = (my_rectangle*)vCollidingWithMe;
		if (CollidingWithMe->circle_in(x[0], y[0], radius, &ReboundLinex, &RevoundLiney))
		{
			if (CollidingWithMe->state[0])
				m_Live = false;
			else {
				if (m_ControlMod != 0) {
					switch (m_Direction) {
					case 'w':
						setYi(y[0] + r_v, 0);
						break;
					case 'a':
						setXi(x[0] + r_v, 0);
						break;
					case 's':
						setYi(y[0] - r_v, 0);
						break;
					case 'd':
						setXi(x[0] - r_v, 0);
						break;
					}
				}
				else {
					switch (m_Direction) {
					case 'w':
						for(int i = 0;i < m_StepAfterThink;i++)
						setYi(y[0] + r_v, 0);
						break;
					case 'a':
						for (int i = 0; i < m_StepAfterThink; i++)
						setXi(x[0] + r_v, 0);
						break;
					case 's':
						for (int i = 0; i < m_StepAfterThink; i++)
						setYi(y[0] - r_v, 0);
						break;
					case 'd':
						for (int i = 0; i < m_StepAfterThink; i++)
						setXi(x[0] - r_v, 0);
						break;
					}
				}
			}

			m_Direction = true;
		}
	}
	




	

}
void CBumborHero::draw()
{
	fillcircle(x[0], y[0], radius);
}
void CBumborHero::setControlMod(int vCMod)
{
	m_ControlMod = vCMod;
}

CBrokenBricks::CBrokenBricks(int vI, int vK, int x, int y, int vWidth, int vHeight):my_rectangle(x,y,vWidth,vHeight,0,0)
{
	m_CollisionKind = 1;
	m_Broken = false;
	m_I = vI;
	m_K = vK;

	if (m_I % 2 == 1) {
		this->y[0] += height / 10;
		height *= 0.8;
	}
	else if(m_K % 2 == 1){
		this->x[0] += width / 10;
		width *= 0.8;
	}
}
CBrokenBricks::CBrokenBricks(const CBrokenBricks& vCBricks):my_rectangle(vCBricks)
{
	m_Broken = vCBricks.m_Broken;
	m_I = vCBricks.m_I;
	m_K = vCBricks.m_K;
	//std::cout << vCBricks.width;
	
}
void CBrokenBricks::changeAfterCollision(Move_line* vCollidingWithMe)
{
	int CollisionKind = vCollidingWithMe->m_CollisionKind;

	if (CollisionKind == 0) {
		//
	}
	else if (CollisionKind == 1) {

		my_rectangle* CollidingWithMe = (my_rectangle*)vCollidingWithMe;
		if (CollidingWithMe->rectangleIn(x[0], y[0],width,height))
		{
			if (CollidingWithMe->state[0])
				m_Broken = true;
		}
	}





}
void CBrokenBricks::draw()
{
	if (m_I % 2 == 1) {
		fillrectangle(x[0], y[0], x[0] + width, y[0] + height );
	}
	else {
		fillrectangle(x[0], y[0], x[0] + width , y[0] + height);
	}
}

CAircraftBattle::CAircraftBattle()
{
	m_NormalEnemy = 0;
	m_BossBattle = false;
	m_Player1Live = true;
	m_Player2Live = true;
	m_BossLive = false;
	m_GenerateEnemyClock.setCycle(_FlyGenerateEnemy);

	m_AircraftHeight = 50;
	m_AircraftWidth = 50;

	m_Aircrafts.push_front(CAircraft(screen_width / 2, screen_hight - m_AircraftHeight, m_AircraftWidth, m_AircraftHeight, 0, 0, _FlyPlayerSpeed, &m_BulletList, &m_CHandler));
	std::list<CAircraft>::iterator TempP;
	Player1 = m_Aircrafts.begin();
	//Player1->setStateI(true, 0);
	TempP = m_Aircrafts.begin();
	m_CHandler.add(&(*TempP));

	m_Aircrafts.push_front(CAircraft(screen_width / 2, screen_hight - m_AircraftHeight, m_AircraftWidth, m_AircraftHeight, 0, 0, _FlyPlayerSpeed, &m_BulletList, &m_CHandler));
	TempP = m_Aircrafts.begin();
	Player2 = TempP;
	TempP->setPlayer2();
	m_CHandler.add(&(*TempP));
	//Player2->setStateI(true, 0);
}
CAircraftBattle::~CAircraftBattle()
{
}
void CAircraftBattle::move()
{
	if (!m_BossBattle && m_NormalEnemy > 1) {
		m_BossLive = true;
		m_BossBattle = true;
		m_Aircrafts.push_front(CAircraft(rand() % (screen_width - _FlyEnemyWidth3), 0, _FlyEnemyWidth3, _FlyEnemyHeight3, _FlyEnemyBulletSpeed3, _FlyEnemySpeed3, 10, &m_BulletList, &m_CHandler));
		std::list<CAircraft>::iterator TempP;
		TempP = m_Aircrafts.begin();
		TempP->setStateI(true, 1);
		m_CHandler.add(&(*TempP));
		TempP->setAutoMove(2);
		Boss = m_Aircrafts.begin();
		Player1->setStateI(true, 0);
		Player2->setStateI(true, 0);
	}
	if (m_GenerateEnemyClock.count() && !m_BossBattle) {
		m_NormalEnemy++;
		if (rand() % 3 == 0) {
			m_Aircrafts.push_front(CAircraft(rand() % screen_width, 0, _FlyEnemyWidth2, _FlyEnemyHeight2, _FlyEnemyBulletSpeed2, _FlyEnemySpeed2, 10, &m_BulletList, &m_CHandler));
			std::list<CAircraft>::iterator TempP;
			TempP = m_Aircrafts.begin();
			TempP->setStateI(true, 0);
			m_CHandler.add(&(*TempP));
			TempP->setAutoMove(1);
		}
		else {
			m_Aircrafts.push_front(CAircraft(rand() % screen_width, 0, _FlyEnemyWidth1, _FlyEnemyHeight1, 0, _FlyEnemySpeed1, 10, &m_BulletList, &m_CHandler));
			std::list<CAircraft>::iterator TempP;
			TempP = m_Aircrafts.begin();
			m_CHandler.add(&(*TempP));
			TempP->setAutoMove(0);
		}
	}


	for (std::list<CAircraft>::iterator Check = m_Aircrafts.begin(); Check != m_Aircrafts.end(); Check++) {
		Check->getInput();
		Check->m_ShootTimes++;
		if (Check->m_ShootTimes >= Check->m_ShootSpace) {
			Check->m_ShootTimes = 0;

			int Kind = 0;
			
			if (Check->state[1])
				Kind = 1;


			addBullet(&(*Check), 0,Kind);
			
			if (Check->state[0] && rand() % 10 == 0) {
				addBullet(&(*Check), 0.2,0);
				addBullet(&(*Check), -0.2,0);
			}
		}
	
	}
	std::for_each(m_Aircrafts.begin(), m_Aircrafts.end(), std::mem_fun_ref(&CAircraft::move));
	std::for_each(m_BulletList.begin(), m_BulletList.end(), std::mem_fun_ref(&CBullet::move));
	m_CHandler.collideAll();

	for (std::list<CBullet>::iterator Checker = m_BulletList.begin(); Checker != m_BulletList.end(); ) {
		m_CHandler.collide(&(*Checker));
		if (!Checker->m_Live) {
			m_CHandler.deleteNode(&(*Checker));
			m_BulletList.erase(Checker++);
		}
		else {
			Checker++;
		}
	}
	for (std::list<CAircraft>::iterator Checker = m_Aircrafts.begin(); Checker != m_Aircrafts.end(); ) {
		m_CHandler.collide(&(*Checker));
		if (Checker->m_HitPoint <= 0) {
			if (Checker->m_ControlMod == 0)
				m_Player1Live = false;
			else if (Checker->m_ControlMod == -1)
				m_Player2Live = false;
			else if (Checker->state[1])
				m_BossLive = false;
				

			m_CHandler.deleteNode(&(*Checker));

			m_Aircrafts.erase(Checker++);
		}
		else {
			Checker++;
		}
	}

}
void CAircraftBattle::draw()
{
	if (m_Player1Live) {
		rectangle(0, 0, _FlyHPRectangleWidth, _FlyHPRectangleHeight);
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(0, 0, _FlyHPRectangleWidth * ((Player1)->m_HitPoint * 1.0 / _FlyBattlePlayerHP), _FlyHPRectangleHeight);
		setfillcolor(RGB(255, 255, 255));
	}
	if (m_Player2Live) {
		rectangle(screen_width - _FlyHPRectangleWidth, 0,screen_width , _FlyHPRectangleHeight);
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(screen_width - _FlyHPRectangleWidth, 0, screen_width - _FlyHPRectangleWidth + _FlyHPRectangleWidth * ((Player2)->m_HitPoint * 1.0 / _FlyBattlePlayerHP), _FlyHPRectangleHeight);
		setfillcolor(RGB(255, 255, 255));

	}
	if (m_BossLive) {
		rectangle(screen_width/2 - _FlyHPRectangleWidth / 2, 0, screen_width/2 + _FlyHPRectangleWidth / 2, _FlyHPRectangleHeight);
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(screen_width/2 - _FlyHPRectangleWidth/2, 0, screen_width/2 - _FlyHPRectangleWidth/2 + _FlyHPRectangleWidth * ((Boss)->m_HitPoint * 1.0 / _FlyEnemyHP3), _FlyHPRectangleHeight);
		setfillcolor(RGB(255, 255, 255));


	}
	std::for_each(m_Aircrafts.begin(), m_Aircrafts.end(), std::mem_fun_ref(&CAircraft::draw));
	std::for_each(m_BulletList.begin(), m_BulletList.end(), std::mem_fun_ref(&CBullet::draw));
}

void CAircraftBattle::addBullet(CAircraft * vCheck,float vTheta,int vMod)
{
		if (vCheck->m_Camp == 0) {
			CBullet C(vCheck->x[0] + vCheck->width / 2, vCheck->y[0], vCheck->m_BulletSpeed*sin(vTheta), -vCheck->m_BulletSpeed * cos(vTheta), vCheck->m_Camp);
			C.setRadius(vCheck->m_BulletRadius);
			m_BulletList.push_front(C);
		}
		else {
			CBullet C(vCheck->x[0] + vCheck->width / 2, vCheck->y[0] + vCheck->height, vCheck->m_BulletSpeed * sin(vTheta), vCheck->m_BulletSpeed * cos(vTheta), vCheck->m_Camp);
			C.setRadius(vCheck->m_BulletRadius);
			m_BulletList.push_front(C);
		}
		std::list<CBullet>::iterator TempP;
		TempP = m_BulletList.begin();
		m_CHandler.add(&(*TempP));
		if(m_Player1Live || m_Player2Live)
		if (vMod == 1) {
			TempP->setStateI(true, 0);
			if(rand() % 2 == 0)
				if(m_Player1Live)
				TempP->setPoint(&(*Player1));
				else
				{
					TempP->setPoint(&(*Player2));

				}
			else
			{
				if(m_Player2Live)
				TempP->setPoint(&(*Player2));
				else
				{
					TempP->setPoint(&(*Player1));
				}
			}
		}
}
CAircraft::CAircraft(int vX, int vY, int vWidth, int vHeight, double vX_speed, double vY_speed,int vSpeed,std::list<CBullet>* vBullet,CollisionHandler* vCHandler):my_rectangle(vX,vY,vWidth,vHeight,vX_speed,vY_speed)
{
	m_Camp = 0;
	m_ShootSpace = _FlyShootSpacePlayer;
	m_ShootTimes = 0;
	m_Bullet = vBullet;
	r_v = vSpeed;
	m_HitPoint = _FlyBattlePlayerHP;
	m_ControlMod = 0;
	m_Graphic = 0;
	m_BulletSpeed = _FlyBulletSpeed;
	m_BulletRadius = _FlyBulletRadius;
}
CAircraft::CAircraft(const CAircraft& vCAircraft):my_rectangle(vCAircraft)
{
	m_Camp = vCAircraft.m_Camp;
	m_ShootTimes = 0;
	m_ShootSpace = vCAircraft.m_ShootSpace;
	m_Bullet = vCAircraft.m_Bullet;
	r_v = vCAircraft.r_v;
	m_HitPoint = vCAircraft.m_HitPoint;
	m_ControlMod = vCAircraft.m_ControlMod;
	m_Graphic = vCAircraft.m_Graphic;
	m_BulletSpeed = vCAircraft.m_BulletSpeed;
	m_BulletRadius = vCAircraft.m_BulletRadius;
}
int CAircraft::getInput()
{
	int Choice = 0;
	m_Operation = 0;
	if (m_ControlMod == 0) {

		if (GetAsyncKeyState(VK_UP)) {
			
			m_Operation |=  1;
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			m_Operation |= 2;
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			m_Operation |= 4;
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			m_Operation |= 8;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			m_Operation |= 16;
			Choice = 1;
		}
	}
	else if (m_ControlMod == -1) {
		if (GetAsyncKeyState('W')) {
			m_Operation |= 1;
		}
		if (GetAsyncKeyState('A')) {
			m_Operation |= 2;
		}
		if (GetAsyncKeyState('D')) {
			m_Operation |= 4;
		}
		if (GetAsyncKeyState('S')) {
			m_Operation |= 8;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			m_Operation |= 16;
			Choice = 1;
		}
	}
	return Choice;

}
void CAircraft::move()
{
	if (m_ControlMod <= 0 ) {
		if ((m_Operation & 1) != 0) {
			if(y[0] - r_v > 0)
			setYi(y[0] - r_v, 0);
			else
			{
				setYi(0, 0);
			}
		}
		if ((m_Operation & 2) != 0) {
			if(x[0] - r_v > 0)
			setXi(x[0] - r_v, 0);
			else
			{
				setXi(0, 0);
			}
		}
		if ((m_Operation & 4) != 0) {
			if (x[0] + r_v + width< screen_width)
			setXi(x[0] + r_v, 0);
			else
			{
				setXi(screen_width - width, 0);
			}
		}
		if ((m_Operation & 8) != 0) {
			if(y[0] + r_v + height < screen_hight)
			setYi(y[0] + r_v, 0);
			else
			{
				setYi(screen_hight - height, 0);
			}
		}
		m_Operation = 0;

	}
	else {
		set_position(x[0], y[0] + r_vy);

		if (state[0]) {
			set_position(x[0] + r_vx, y[0]);
			if (x[0] < 0) {
				r_vx = -r_vx;
				x[0] += r_vx;
			}
			else if (x[0] + width > screen_width) {
				r_vx = -r_vx;
				x[0] += r_vx;
			}
		}
		else if (state[1]) {
			set_position(x[0] + r_vx, y[0]);
			if (x[0] < 0) {
				r_vx = -r_vx;
				x[0] += r_vx;
			}
			else if (x[0] + width > screen_width) {
				r_vx = -r_vx;
				x[0] += r_vx;
			}
			else if (y[0] < 0) {
				r_vy = -r_vy;
				y[0] += r_vy;
			}
			else if (y[0] + height > screen_hight / 2) {
				r_vy = -r_vy;
				y[0] += r_vy;
			}
		}
		
		if (y[0] >= screen_hight)
			m_HitPoint = 0;
	}
}
void CAircraft::changeAfterCollision(Move_line* vCollidingWithMe)
{
	int ReboundLinex;
	int RevoundLiney;

	int CollisionKind = vCollidingWithMe->m_CollisionKind;

	if (CollisionKind == 0) {
		//		
		CBullet* CollidingWithMe = (CBullet*)vCollidingWithMe;
		if (this->circle_in(CollidingWithMe->x[0], CollidingWithMe->y[0],CollidingWithMe->radius,&ReboundLinex,&RevoundLiney)) {
			if (m_Camp != CollidingWithMe->m_Camp)
			{
				m_HitPoint--;
			}
			
		}
	}
	else if (CollisionKind == 1) {
		;
	}
}
void CAircraft::draw()
{

	switch (m_Graphic) {
	case 0:
		if(m_ControlMod == -1)
			setlinecolor(RGB(125, 125,0 ));
		else if(m_ControlMod == 0)
			setlinecolor(RGB(0, 255, 0));
	
		line(x[0], y[0] + height, x[0] + width / 2, y[0]);
		line(x[0] + width, y[0] + height, x[0] + width / 2, y[0]);
		setlinecolor(RGB(255, 255, 255));
		break;
	case 1:
		if (state[0])
			setlinecolor(RGB(255, 0, 0));
		line(x[0], y[0], x[0] + width / 2, y[0] + height);
		line(x[0] + width / 2, y[0] + height, x[0] + width , y[0]);
		setlinecolor(RGB(255, 255, 255));
		break;
	}
	

}
void CAircraft::setAutoMove(int vKind)
{
	if (vKind == 0) {
		m_Camp = 1;
		m_ShootSpace = _FlyShootSpaceEnemy1;
		r_v = _FlyEnemySpeed1;
		m_HitPoint = _FlyEnemyHP1;
		m_ControlMod = 1;
		m_Graphic = 1;
		m_BulletSpeed = _FlyEnemyBulletSpeed1;
		m_BulletRadius = _FlyEnemyBulletRadius1;
	}
	else if(vKind == 1){
		m_Camp = 1;
		m_ShootSpace = _FlyShootSpaceEnemy2;
		r_v = _FlyEnemySpeed2;
		m_HitPoint = _FlyEnemyHP2;
		m_ControlMod = 1;
		m_Graphic = 1;
		m_BulletSpeed = _FlyEnemyBulletSpeed2;
		m_BulletRadius = _FlyEnemyBulletRadius2;
	}
	else if (vKind == 2) {
		state[1] = true;
		m_Camp = 1;
		m_ShootSpace = _FlyShootSpaceEnemy3;
		r_v = _FlyEnemySpeed3;
		m_HitPoint = _FlyEnemyHP3;
		m_ControlMod = 1;
		m_Graphic = 1;
		m_BulletSpeed = _FlyEnemyBulletSpeed3;
		m_BulletRadius = _FlyEnemyBulletRadius3;
	}
}
void CAircraft::setPlayer2()
{
	m_ControlMod = -1;
	m_Graphic = 0;
}

CBullet::CBullet(int x1, int y1, double x_speed, double y_speed,int vCamp):my_circle(x1,y1,x_speed,y_speed)
{
	m_Camp = vCamp;
	m_Live = true;
}
CBullet::CBullet(const CBullet& m_c) :my_circle(m_c)
{
	m_Camp = m_c.m_Camp;
	m_Live = m_c.m_Live;
}
void CBullet::setPoint(CAircraft* vPoint)
{
	m_Point = vPoint;
}
void CBullet::move()
{

	x[0] += move_help(r_vx, &rest_x);
	y[0] += move_help(r_vy, &rest_y);
	//state[0]
	if (state[0]) {
		float Theta = atan2(m_Point->y[0] - y[0],m_Point->x[0] - x[0]);
		
		x[0] += r_v * cos(Theta);
		y[0] += r_v * sin(Theta);
		
		
	}


	if (x[0] + radius > screen_width || x[0] - radius < 0) {
		m_Live = false;
	}
	else if (y[0] - radius < 0 || y[0] + radius > screen_hight) {
		m_Live = false;
	}



}
void CBullet::changeAfterCollision(Move_line* vCollidingWithMe)
{
	int ReboundLinex;
	int RevoundLiney;

	int CollisionKind = vCollidingWithMe->getCollisionKind();

	if (CollisionKind == 0) {
		CBullet* CollidingWithMe = (CBullet*)vCollidingWithMe;
		if (CollidingWithMe->circleIn(x[0], y[0], radius)) {
			if(m_Camp != CollidingWithMe->m_Camp)
			m_Live = false;
		}
	}
	else if (CollisionKind == 1) {

		CAircraft* CollidingWithMe = (CAircraft*)vCollidingWithMe;
		if (CollidingWithMe->circle_in(x[0], y[0], radius, &ReboundLinex, &RevoundLiney))
		{
			if(m_Camp != CollidingWithMe->m_Camp)
			m_Live = false;
		}
	}
}

CClock::CClock()
{
	m_Cycle = 0;
}
CClock::CClock(int vCycle)
{
	m_Cycle = vCycle;
	m_TimeAfterSet = 0;
}
void CClock::setCycle(int vCycle)
{
	m_Cycle = vCycle;
}
bool CClock::count()
{
	bool Outcome = false;

	m_TimeAfterSet++;
	if (m_TimeAfterSet == m_Cycle)
	{
		m_TimeAfterSet = 0;
		Outcome = true;
	}

	return Outcome;
}
