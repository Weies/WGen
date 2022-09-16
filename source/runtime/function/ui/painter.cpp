#include"painter.h"

void Painter::drawRect(float xx , float yy , float w , float h)
{
	glStart(GL_LINE_LOOP);
	glPixel(xx , yy);
	glPixel(xx , yy + h);
	glPixel(xx + w , yy + h);
	glPixel(xx + w , yy);
	glOver();
}

void Painter::drawLine(const Line& l)
{
	glStart(GL_LINES);
	glPixel(l.p1.x , l.p1.y);
	glPixel(l.p2.x , l.p2.y);
	glOver();
}
void Painter::drawLine(float xx , float yy , float ex , float ey)
{
	glStart(GL_LINES);
	glPixel(xx , yy);
	glPixel(ex , ey);
	glOver();
}
void Painter::drawCircle(float x , float y , float r)
{
	int d = 5 - 4 * r;
	int t = r * sqrt(2) / 2 + 1;
	glStart(GL_POINTS);
	int px = 0; int py = r;
	circlePoints(px , py , x , y);
	while (px < t) {
		if (d <= 0)
		{
			d += 8 * px + 12;
			circlePoints(++px , py , x , y);
		}
		else
		{

			d += 8 * (px - py) + 20;
			circlePoints(++px , --py , x , y);
		}
	}
	glOver();
}
void Painter::drawArc(float cx , float cy , float p , float o1 , float o2)
{
	glStart(GL_POINTS);
	for (; o1 < o2; o1 += 0.01)
	{
		glPixel(cx + p * cos(o1) , cy + p * sin(o1));
	}
	glOver();
}

void Painter::fillCircle(float xx , float yy , float rr , float precision)
{
	point2 p1(xx , yy + rr);
	float rotdeg = 360.0f / precision;
	point2 p2 = rotc(xx , yy , p1.x , p1.y , rotdeg);
	glStart(GL_TRIANGLES);
	for (float i = 0; i < precision; i++)
	{
		glPixel(xx , yy);
		glPoint(p1);
		glPoint(p2);
		p1 = rotc(xx , yy , p1.x , p1.y , rotdeg);
		p2 = rotc(xx , yy , p2.x , p2.y , rotdeg);
	}
	glOver();
}
void Painter::fillRect(float x , float y , float b)
{
	x = round(x); y = round(y);
	glStart(GL_TRIANGLES);
	glPixel(x * 30 , y * 30 + b);
	glPixel(x * 30 + 30 , y * 30 + 30 + b);
	glPixel(x * 30 + 30 , y * 30 + b);

	glPixel(x * 30 , y * 30 + b);
	glPixel(x * 30 + 30 , y * 30 + 30 + b);
	glPixel(x * 30 , y * 30 + 30 + b);
	glOver();
	drawPoint(x * 30 , y * 30 + b);
}
void Painter::fillRect(float x , float y , float width , float height)
{
	glStart(GL_TRIANGLES);
	glPixel(x , y);
	glPixel(x + width , y + height);
	glPixel(x , y + height);

	glPixel(x , y);
	glPixel(x + width , y + height);
	glPixel(x + width , y);
	glOver();
}
void Painter::fillTriangle(float x1 , float y1 , float x2 , float y2 , float x3 , float y3)
{
	glStart(GL_TRIANGLES);
	glPixel(x1 , y1);
	glPixel(x2 , y2);
	glPixel(x3 , y3);
	glOver();
}
void Painter::drawTriangle(float x1 , float y1 , float x2 , float y2 , float x3 , float y3)
{
	glStart(GL_TRIANGLES);
	glPixel(x1 , y1);
	glPixel(x2 , y2);
	glPixel(x3 , y3);
	glOver();
}
void Painter::fillTriangle(point<int> p1 , point<int> p2 , point<int> p3)
{
	glStart(GL_TRIANGLES);
	glPixel(p1.x , p1.y);
	glPixel(p2.x , p2.y);
	glPixel(p3.x , p3.y);
	glOver();
}
void Painter::drawTriangle(point<int> p1 , point<int> p2 , point<int> p3)
{
	glStart(GL_LINES);
	glPixel(p1.x , p1.y);
	glPixel(p2.x , p2.y);
	glPixel(p3.x , p3.y);
	glOver();
}
void Painter::drawEllipse(float a , float b , float cx , float cy)
{
	if (cx < 0)
	{
		cx = win_w / 2;
		cy = win_h / 2;
	}
	float t1 = a * a; float t2 = b * b;
	float tx = sqrt(t1 * t1 / (t1 + t2));
	float d = -1 / t1 - (2 * b + 2) / t2;

	glStart(GL_POINTS);
	ellipsePoints(0 , b , cx , cy);
	float iy = b;
	float ix = 0.0f;
	while (ix <= tx)
	{
		if (d <= 0)
		{
			d += (2 * ix + 1) / t1;
			ellipsePoints(++ix , iy , cx , cy);
		}
		else
		{
			d += (2 * ix + 1) / t1 - (2 * iy + 2.0f) / t2;
			ellipsePoints(++ix , --iy , cx , cy);
		}
	}
	//__debugbreak();
	while (iy >= 0)
	{
		if (d <= 0)
		{
			d += (2 * iy + 1) / t2;
			ellipsePoints(ix , --iy , cx , cy);
		}
		else
		{
			d += (2 * iy + 1.0f) / t2 - (2 * ix + 2) / t1;
			ellipsePoints(++ix , --iy , cx , cy);
		}
	}
	glOver();
}
void Painter::cdrawRect(float w , float h)
{
	glStart(GL_LINE_LOOP);
	glPixel(cx + w / 2 , cy + h / 2);
	glPixel(cx + w / 2 , cy - h / 2);
	glPixel(cx - w / 2 , cy - h / 2);
	glPixel(cx - w / 2 , cy + h / 2);
	glOver();
}
void Painter::cdrawLine(float x , float y)
{
	glStart(GL_LINES);
	glPixel(cx + x / 2 , cy + y / 2);
	glPixel(cx - x / 2 , cy - y / 2);
	glOver();
}
void Painter::cdrawCircle(float r)
{
	float d = 5 - 4 * r;
	float t = r * sqrt(2) / 2 + 1;
	glStart(GL_POINTS);
	float px = 0; float py = r;
	circlePoints(px , py , cx , cy);
	while (px < t) {
		if (d <= 0)
		{
			d += 8 * px + 12;
			circlePoints(++px , py , cx , cy);
		}
		else
		{
			d += 8 * (px - py) + 20;
			circlePoints(++px , --py , cx , cy);
		}
	}
	glOver();
}
void Painter::cfillCircle(float r , float precision)
{
	point2 p1(cx , cy + r);
	float rotdeg = 360.0f / precision;
	point2 p2 = rotc(cx , cy , p1.x , p1.y , rotdeg);
	glStart(GL_TRIANGLES);
	for (float i = 0; i < precision; i++)
	{
		glPixel(cx , cy);
		glPoint(p1);
		glPoint(p2);
		p1 = rotc(cx , cy , p1.x , p1.y , rotdeg);
		p2 = rotc(cx , cy , p2.x , p2.y , rotdeg);
	}
	glOver();
}
void Painter::cfillRect(float w , float h)
{
	glStart(GL_TRIANGLES);
	glPixel(cx - w / 2 , cy - h / 2);
	glPixel(cx + w / 2 , cy - h / 2);
	glPixel(cx + w / 2 , cy + h / 2);

	glPixel(cx - w / 2 , cy - h / 2);
	glPixel(cx - w / 2 , cy + h / 2);
	glPixel(cx + w / 2 , cy + h / 2);
	glOver();
}

void Painter::cfillTriangle(float x1 , float y1 , float x2 , float y2 , float x3 , float y3)
{
	glStart(GL_TRIANGLES);
	glPixel(cx + x1 , cy + y1);
	glPixel(cx + x2 , cy + y2);
	glPixel(cx + x3 , cy + y3);
	glOver();
}
void Painter::cdrawTriangle(float x1 , float y1 , float x2 , float y2 , float x3 , float y3)
{
	glStart(GL_LINES);
	glPixel(cx + x1 , cy + y1);
	glPixel(cx + x2 , cy + y2);
	glPixel(cx + x3 , cy + y3);
	glPixel(cx + x1 , cy + y1);
	glOver();
}

void Painter::cfillTriangle(point<int> p1 , point<int> p2 , point<int> p3)
{
	glStart(GL_TRIANGLES);
	glPixel(cx + p1.x , cy + p1.y);
	glPixel(cx + p2.x , cy + p2.y);
	glPixel(cx + p3.x , cy + p3.y);
	glOver();
}
void Painter::cdrawTriangle(point<int> p1 , point<int> p2 , point<int> p3)
{
	glStart(GL_LINES);
	glPixel(cx + p1.x , cy + p1.y);
	glPixel(cx + p2.x , cy + p2.y);
	glPixel(cx + p3.x , cy + p3.y);
	glOver();
}
void Painter::initCir(float r)
{
	//float k1 = r * r;
	//for (float i = -r; i < r; i++)
	//{
	//	for (float j = -r; j < r; j++)
	//	{
	//		if (i * i + j * j <= k1)
	//		{
	//			//pie.push_back(point<int>(i , j));
	//		}
	//	}
	//}
}

void Painter3::drawLine(const pt& p1 , const pt& p2)
{
	glStart3(GL_LINES);
	glPoint3(p1);
	glPoint3(p2);
	glOver3();
}
void  Painter3::fillTriangle(point<float> p1 , point<float> p2 , point<float> p3)
{
	setNormal(getNormal(p1 , p2 , p3));
	glStart3(GL_TRIANGLES);
	glPoint3(p1);
	glPoint3(p2);
	glPoint3(p3);
	glOver3();
}
void  Painter3::fillTriangle(float x1 , float y1 , float z1 , float x2 , float y2 , float z2 , float x3 , float y3 , float z3)
{
	setNormal(vec3(getNormal(vec3(x1 , y1 , z1) , vec3(x2 , y2 , z2) , vec3(x3 , y3 , z3))));
	glStart3(GL_TRIANGLES);
	glPoint3(vec3(x1 , y1 , z1));
	glPoint3(vec3(x2 , y2 , z2));
	glPoint3(vec3(x3 , y3 , z3));
	glOver3();
}

Painter* _ptr;
Painter3* _ptr3;