#pragma once
#include"../base/global_values.h"
#include"../physics/collision_dectect.h"
using namespace globals;
class Painter {
public:
	Painter() {
		initCir(6);
	}
	static void setColor(float r, float g, float b, float a = 1)
	{
		curColor = Color(r, g, b, a);
	}
	static void setPriority(float pri)
	{
		curPriority = pri;
	}
	//设置绘图的原点，所有绘制的点都会加上原点
	static void setOrigin(float x = 0.0f, float y = 0.0f) {
		origin_x = x; origin_y = y;
	}
	static void setOrigin(const vec2& v) {
		origin_x = v.x; origin_y = v.y;
	}

	static void setLineWidth(float width) {
		glLineWidth(width);
		line_width = width;
	}
	static void setPointSize(float size) {
		glPointSize(size);
		point_size = size;
	}
	static void reset() {
		curPriority = 0.0;
	}//重置优先级
	static void setColor(const Color& c) {
		curColor = c;
	}
	static void fix()
	{
		globals::fixed = true;
	}
	static void stopfix()
	{
		globals::fixed = false;
	}
	void setCenter(float x, float y)
	{
		cx = x; cy = y;
	}
	void setCenter(const vec2& cen) {
		cx = cen.x; cy = cen.y;
	}
	static void drawCoord() {
		setColor(255, 0, 0);
		drawLine(0, win_h / 2, win_w, win_h / 2);
		setColor(0, 0, 255);
		drawLine(win_w / 2, 0, win_w / 2, win_h);
	}
	static void left_up(bool left_up_as_origin = true) {
		LEFT_UP = left_up_as_origin;
	}
	static void drawRect(float xx, float yy, float w, float h);
	static void drawRect(const vec2& p, const vec2& q) {
		glStart(GL_LINE_LOOP);
		glPixel(p.x, p.y);
		glPixel(p.x, q.y);
		glPixel(q.x, q.y);
		glPixel(q.x, p.y);
		glOver();
	}

	static void drawLine(const Line& l);

	static void drawLine(float xx, float yy, float ex, float ey);

	static void circlePoints(float x, float y, float x0, float y0)
	{
		glPixel(x0 + x, y0 + y);
		glPixel(x0 + x, y0 - y);
		glPixel(x0 - x, y0 + y);
		glPixel(x0 - x, y0 - y);
		glPixel(x0 + y, y0 + x);
		glPixel(x0 - y, y0 + x);
		glPixel(x0 + y, y0 - x);
		glPixel(x0 - y, y0 - x);
	}

	static void drawCircle(float x, float y, float r);

	//cx,cy:中心坐标，p,o:极坐标表示的圆弧
	static void drawArc(float cx, float cy, float p, float o1, float o2);

	static void fillCircle(float xx, float yy, float rr, float precision = 30);

	inline static void drawPoint(float x, float y)
	{
		glStart(GL_POINTS);
		glPixel(x, y);
		glOver();
	}

	//以p1,p2为对角线画矩形
	static void fillRect(vec2 p1, vec2 p2)
	{
		glStart(GL_TRIANGLES);
		glPoint(p2);
		glPixel(p1.x, p2.y);
		glPoint(p1);

		glPoint(p1);
		glPixel(p2.x, p1.y);
		glPoint(p2);
		glOver();
	}

	static void fillRect(float x, float y, float b);

	static void fillRect(float x, float y, float width, float height);

	static void fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	static void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	static void fillTriangle(point<int> p1, point<int> p2, point<int> p3);

	static void drawTriangle(point<int> p1, point<int> p2, point<int> p3);

	static void ellipsePoints(float x, float y, float cx, float cy)
	{
		glPixel(cx + x, cy + y);
		glPixel(cx + x, cy - y);
		glPixel(cx - x, cy + y);
		glPixel(cx - x, cy - y);
	}

	//不设置中心时，在屏幕的中心画
	//a:x轴的交点，b：y轴上的交点
	static void drawEllipse(float a, float b, float cx = -1, float cy = -1);


	//中心绘图函数,调用前需要setCenter
	void cdrawRect(float w, float h);

	void cdrawPoint(float x, float y) {
		glStart(GL_POINTS);
		glPoint(vec2(cx + x, cy + y));
		glOver();
	}

	void cdrawLine(float x, float y);

	void cdrawCircle(float r);

	void cfillCircle(float r, float precision = 30);

	void cfillRect(float w, float h);

	void cfillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	void cdrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	void cfillTriangle(point<int> p1, point<int> p2, point<int> p3);

	void cdrawTriangle(point<int> p1, point<int> p2, point<int> p3);

	void initCir(float r);

	void fillPie(float x, float y, float r)
	{
		glStart(GL_POINTS);
		for (float i = 0; i < M_PI / 2; i += 0.1) {
			float xx = cos(i) * r; float yy = sin(i) * r;
			for (float j = -xx; j <= xx; ++j) {
				glPoint(vec2(x + j, y + yy));
				glPoint(vec2(x + j, y - yy));
			}
		}
		glOver();
	}
	void randColor()
	{
		curColor.setRandColor();
	}
	float cx = 0.0f; float cy = 0.0f; float cz = 0.0f;
};
___global(Painter, ptr);
#define ptr _get_ptr()

class Baisc3DObject;
class Painter3 {
public:
	using pt = point<float>;
	void randColor() {
		curColor3.setRandColor();
	}
	void setColor(const Color& r)
	{
		curColor3 = r;
	}
	void setColor(float r, float g, float b, float a = 1)
	{
		curColor3 = Color(r, g, b, a);
	}
	void setModel(const gm::mat4& m)
	{
		curModel = m;
	}
	void setNormal(const vec3& norm)
	{
		curNormal = norm;
	}
	void unitModel()
	{
		curModel = gm::mat4(1.0f);
	}

	static void drawLine(const pt& p1, const pt& p2);
	static void drawPoint(const pt& p) {
		glStart3(GL_POINTS);
		glPoint3(p);
		glOver3();
	}
	void drawCoordinate(float max = 100.0f, float interval = 4.0f) {
		setColor(10, 255, 10);
		drawLine(vec3(0, -max, 0), vec3(0, max, 0));
		setColor(255, 10, 10);
		for (float i = 0; i < max; i += interval) {
			drawLine(vec3(0, 0.0f, i), vec3(max, 0.0f, i));
		}
		setColor(10, 10, 255);
		for (float i = 0; i < max; i += interval) {
			drawLine(vec3(i, 0, 0.0f), vec3(i, 0, max));
		}
	}
	void drawCoord(const mat4& model, float len = 1.0f) {
		vec3 p = model.p();
		setColor(RED);
		drawLine(p, model * vec4(len, 0, 0, 1));
		setColor(GREEN);
		drawLine(p, model * vec4(0, len, 0, 1));
		setColor(BLUE);
		drawLine(p, model * vec4(0, 0, len, 1));
	}
	void drawTriangle(point<float> p1, point<float> p2, point<float> p3) {
		glStart3(GL_LINE_LOOP);
		glPoint3(p1);
		glPoint3(p2);
		glPoint3(p3);
		glOver3();
	}
	void drawParallelogram(point<float> p1, point<float> p2, point<float> p3) {
		glStart3(GL_LINE_LOOP);
		glPoint3(p1);
		glPoint3(p2);
		glPoint3(p3);
		glPoint3(p1 + p3 - p2);
		glOver3();
	}
	void drawCube(point<float> p1, point<float> p2, point<float> p3, point<float> p4) {
		glStart3(GL_LINE_STRIP);
		glPoint3(p1);
		glPoint3(p2);
		glPoint3(p2 + p3 - p1);
		glPoint3(p3);
		glPoint3(p1);
		glPoint3(p4);
		glPoint3(p4 + p3 - p1);
		glPoint3(p3);
		glPoint3(p3 + p2 - p1);
		glPoint3(p3 + p2 - p1 + p4 - p1);
		glPoint3(p3 + p4 - p1);
		glPoint3(p4);
		glPoint3(p4 + p2 - p1);
		glPoint3(p2);
		glPoint3(p4 + p2 - p1);
		glPoint3(p3 + p2 - p1 + p4 - p1);
		glOver3();
	}
	void drawCube(const cube& c) {
		drawCube(c[0], c[1], c[2], c[3]);
	}
	void drawCube(const mat4& model) {
		setModel(model);
		drawCube(vec3(0.5, 0.5, 0.5), vec3(0.5, -0.5, 0.5), vec3(-0.5, 0.5, 0.5), vec3(0.5, 0.5, -0.5));
		setModel(mat4(1.0f));
	}

	void drawSphere(const vec3& o, float r, float precision = 36.0f) {
		drawSphere(ball(o, r), precision);
	}
	void drawSphere(const ball& b, float precision = 36.0f) {
		float deg = radians(360.0f / precision);
		vector<pair<float, float>> v;
		const int ed = precision + 1.0f;
		float i = 0.0f; int j = 0;
		float r = b.r + 0.01f;
		for (; j < ed; i += deg, ++j) {
			v.push_back({ sin(i) * r,cos(i) * r });
		}
		glStart3(GL_LINE_LOOP);
		for (j = 0; j < ed; ++j) {
			glPoint3(vec3(0, v[j].first, v[j].second) + b.o);
		}
		for (j = 0; j < ed; ++j) {
			glPoint3(vec3(v[j].first, 0, v[j].second) + b.o);
		}
		glOver3();
		glStart3(GL_LINE_LOOP);
		for (j = 0; j < ed; ++j) {
			glPoint3(vec3(v[j].first, v[j].second, 0) + b.o);
		}
		glOver3();
	}

	void fillTriangle(point<float> p1, point<float> p2, point<float> p3);
	//绘制平行四边形，逆时针
	void fillParallelogram(point<float> p1, point<float> p2, point<float> p3) {
		setNormal(getNormal(p1, p2, p3));
		glStart3(GL_TRIANGLES);
		glPoint3(p1);
		glPoint3(p2);
		glPoint3(p3);

		glPoint3(p1);
		glPoint3(p3);
		glPoint3(p1 + p3 - p2);
		glOver3();
	}
	void fillCube(point<float> p1, point<float> p2, point<float> p3, point<float> p4) {
		fillParallelogram(p3, p2, p1);
		fillParallelogram(p1, p2, p4);
		fillParallelogram(p4, p2, p3);
		fillParallelogram(p1 + p3 - p2, p4 + p1 - p2 + p3 - p2, p4 + p3 - p2);
		fillParallelogram(p1 + p4 - p2, p4 + p1 - p2 + p3 - p2, p1 + p3 - p2);
		fillParallelogram(p3 + p4 - p2, p4 + p1 - p2 + p3 - p2, p1 + p4 - p2);
	}
	void fillCube(const mat4& model) {
		setModel(model);
		fillCube(vec3(0.5, -0.5, -0.5), vec3(0.5, 0.5, -0.5), vec3(-0.5, 0.5, -0.5), vec3(0.5, 0.5, 0.5));
		setModel(mat4(1.0f));
	}

	void fillTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
};
___global(Painter3, ptr3);
#define ptr3 _get_ptr3()
