#pragma once
#include"../ui/widget.h"
#include"../ui/painter.h"
#include"../base/camera.h"
#include"../base/ui_base.h"
#include"../ui/window.h"
using namespace ui;

class Circle :public Widget {
public:
	float r;//半径
	float px; float py;//旋转时圆心相对旋转中心的位置
	float rx; float ry;//旋转中心
	Circle();
	~Circle() {}
	Circle(float xx , float yy , float rr);

	inline void scale(float times)
	{
		r *= times;
	}
	inline void setRotateCenter(float xx , float yy)
	{
		rx = xx; ry = yy;
	}

	inline void draw()
	{
		ptr.setColor(mBackgroundColor);
		ptr.setCenter(mPosition.x , mPosition.y);
		ptr.cfillCircle(r);
		//ptr.cfillCircle(10);
	}
	inline void rotate(float deg) {
		point2 p(px , py);
		p.rot(deg);
		px = p.x;
		py = p.y;
		mPosition.x = rx + p.x;
		mPosition.y = ry + p.y;
	}
private:
};

class Triangle :public Widget {
public:
	float x1 = 0; float y1 = 100;
	float x2 = 100; float y2 = -80;
	float x3 = -100; float y3 = -40;

	Triangle(float xx , float yy) {
		w = 200; h = 200;
		//setOffset(-100 , -100);
		mPosition.x = xx; mPosition.y = yy;
		setBGC(120 , 160 , 240);
		onmove = [=](MouseEvent& e)->bool {
			moveto(e.x , e.y);
		};
		setStickScale();
	}
	void scale(float times)
	{
		x1 *= times; y1 *= times;
		x2 *= times; y2 *= times;
		x3 *= times; y3 *= times;
	}
	void rotate(float deg) {
		point2 p(x1 , y1);
		p.rot(deg);
		x1 = p.x;
		y1 = p.y;
		p.rot(deg);
		x2 = p.x;
		y2 = p.y;
		p.rot(deg);
		x3 = p.x;
		y3 = p.y;
	}

	void draw()
	{
		ptr.setColor(mBackgroundColor);
		ptr.setCenter(mPosition.x , mPosition.y);
		ptr.cfillTriangle(x1 , y1 , x2 , y2 , x3 , y3);
	}
private:
};

class Rect :public Widget
{
public:
	Rect();
	Rect(float xx , float yy , float w , float h);

	void draw()
	{
		ptr.setColor(mBackgroundColor);
		ptr.setCenter(mPosition.x , mPosition.y);
		ptr.cfillRect(w , h);
	}
};

class LineOBJ :public FixedWidget {
public:
	float deltax;
	float deltay;
	LineOBJ(float xx , float yy , float endx , float endy) {
		setBGC(255 , 0 , 0);
		mPosition.x = (xx + endx) / 2; mPosition.y = (yy + endy) / 2;
		deltax = endx - xx; deltay = endy - yy;
	}
	void scale(float times)
	{
		deltax *= times;
		deltay *= times;
	}
	void draw()
	{
		ptr.setColor(mBackgroundColor);
		ptr.setCenter(mPosition.x , mPosition.y);
		ptr.cdrawLine(deltax , deltay);
	}
};

template<class T>
class CirList {//循环表
public:
	CirList(int n) :list(n) {
		maxSize = n;
	}
	void push_back(const T& t)
	{
		curr++;
		if (curr == maxSize)curr = 0;
		list[curr] = t;
	}
	T& operator[](int i)
	{
		if (i + curr < maxSize)
			return list[curr + i];
		return list[curr + i - maxSize];
	}
	int size()
	{
		return list.size();
	}
	int curr = 0;
	int maxSize;
	vector<T> list;
};

class bullets {
public:
	bullets() {}

	bullets(float xx , float yy)
	{
		x = xx; y = yy;
		dx = (rand() % 10000 - 5000) / 5000.0;
		dy = (rand() % 10000 - 5000) / 5000.0;
	}

	void update()
	{
		x += dx;	y += dy;
	}
	float x; float y;
	float dx;
	float dy;
};

class Plane :public Widget {
public:
	int HP = 5000;
	int width = 100;
	int height = 100;
	Plane();

	void draw();

	CirList<point<int>> strbul = CirList<point<int>>(1000);//直线子弹
	CirList<bullets> randbul = CirList<bullets>(1000);//随机子弹
};

class Enemy :public Widget {
public:
	int width = 100;
	int height = 100;
	int HP = 1000;
	Enemy()
	{
		setPriority(200);
		moveto(300 , 300);
		onmove = 0;
	}
	void draw();

	CirList<point<int>> strbul = CirList<point<int>>(1000);//直线子弹
	CirList<bullets> randbul = CirList<bullets>(1000);//随机子弹
};

class BezierCurve
{
public:
	BezierCurve(const int pnum);
	void draw();
	void addPoint(int x , int y)
	{
		busy = true;
		c[num] = new Circle;
		c[num]->r = 10;
		c[num]->setBGC(255 , 0 , 0);
		c[num]->moveto(x , y);
	}
	void erasePoint()
	{
		num--;
		c[num]->~Circle();
	}
	bool showing = true;
	bool busy = false;

	void show(bool _show)
	{
		showing = _show;
		for (int i = 0; i < num; i++)
		{
			c[i]->show(showing);
		}
	}

	int num;
	Circle** c; point2* tt;
};
#define pot point<float>
class BezierSurf
{
public:
	BezierSurf(const int pnum);

	void addPoint(int x , int y)
	{
		busy = true;
		//c[num] = new Circle;
		//c[num]->r = 10;
		//c[num]->setColor(255 , 0 , 0);
		//c[num]->moveto(x , y);
	}
	void erasePoint()
	{
		//num--;
		//c[num]->~Circle();
	}
	bool showing = true;
	bool busy = false;
	void draw();

	void show(bool _show)
	{
		showing = _show;
		for (int i = 0; i < num; i++)
		{
			//c[i]->show(showing);
		}
	}
	int cc(int n , int m)
	{
		if (m == 0 || m == n)return 1;
		int up = 1; int down = 1;
		for (int i = n; i > n - m; i--)
		{
			up *= (n - i);
		}
		for (int i = m; i >= 1; i--)
		{
			down *= i;
		}
		return up / down;
	}

	float ppow(float base , int power)
	{
		if (power == 0)
			return 1.0;
		else return pow(base , power);
	}

	int num;
	pot** c; pot** tt; pot* tp;
};


class  BSplineCurve
{
public:
	BSplineCurve(const int pnum , int kk);//点数，次数
	void setClamped();
	void draw();
	bool showctrl = true;
	bool showing = true;
	bool busy = false;

	void show(bool showw)
	{
		showing = showw;
	}
	void showCtrl(bool show = true)
	{
		showctrl = show;
		for (int i = 0; i < num; i++)
			c[i]->mIsShowing = show;
	}
	void setEven()
	{
		for (int i = 0; i < k + num; i++)
		{
			seqt[i] = i * 1.0f / (k + num - 1);
		}

	}
	void addPoint(int x , int y)
	{
		busy = true;
		c[num] = new Circle;
		c[num]->r = 10;
		c[num]->setBGC(0 , 0 , 255);
		c[num]->moveto(x , y);
	}
	void erasePoint()
	{
		num--;
		c[num]->~Circle();
		setClamped();
	}

	float sang(float a , float b)
	{
		if (a == 0.0f || b == 0.0f)
			return 0.0f;
		return a / b;
	}
	float* seqt; int num; int k;
	Circle** c; point2* P;
};
