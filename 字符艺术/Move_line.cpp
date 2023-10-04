#include "Move_line.h"
#include<graphics.h>
#include"const_number.h"
#include<iostream>
#include<math.h>
#include<string>
#include<iostream>
Move_line::Move_line(int x1, int y1, int x2, int y2,double x_speed,double y_speed) {
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
	// 关于点的移动问题。最主要的只是移动一下首尾⚔两个点而已！
	double theta = atan2(y[length - 2] - y[length - 1], x[length - 2] - x[length - 1]);//这是尾结点与倒数第二个节点的不同位置
   


	x[length - 1] += move_help((r_v+1) * cos(theta),&rest_xt); // 尾结点的移动
	y[length - 1] += move_help((r_v + 1) * sin(theta),&rest_yt);//同上


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
void Move_line::draw() {
	//circle(x[0], y[0], 10);
	for (int i = 0;i < length - 1;i++) {
		line(x[i], y[i], x[i + 1], y[i + 1]);
	}
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
	std::cout << "垂直的向量X,Y：" <<Vx << " Y:" << Vy << std::endl;

	if (r_vx * Vx + r_vy * Vy > 0)
		;
	else
	{
		Vx = -Vx;
		Vy = -Vy;
	}


	std::cout << "改变夹角X,Y：" <<Vx << " Y:" << Vy << std::endl;
	float ThetaV = atan2(r_vy,r_vx);
	float ThetaL = atan2(Vy,Vx);
	float DelTheta = ThetaV - ThetaL;
	std::cout << "ThetaV ThetaL DelTheta" << ThetaV<< " " << ThetaL << " " << DelTheta << std::endl;
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
	radius = 10;
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
void my_circle::draw() {
	circle(x[0], y[0], 10);
}
void my_circle::get_input(char c) {
	if (state[1] == false) {
		r_vy = -25;
		state[1] = true;
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
	width = wid;
	height = h;
}
my_rectangle::my_rectangle():Move_line(0,0,1,1,0,0) {
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
void my_rectangle::set_position(int x, int y) {
	this->x[0] = x;
	this->y[0] = y;
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



	if (sqrt(Cx * Cx + Cy * Cy) > vr)
		return false;
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
void my_rectangle::reboundBall(my_circle* vM)
{
	bool find;

	int ReboundLinex;
	int RevoundLiney;
		if (circle_in(vM->x[0], vM->y[0], vM->radius,&ReboundLinex,&RevoundLiney))
		{
		vM->turn_speed_direction_by_rebound_line(ReboundLinex,RevoundLiney);
		}
		vM->setXi(vM->x[0] + vM->r_vx,0);

		vM->setYi(vM->y[0] + vM->r_vy,0);
	
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
