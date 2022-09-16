//#include"WGen.h"
//float r = 500;
//struct particle {
//	particle(point2 p1 , point2 p2) :p(p1) , v(p2)
//	{
//	}
//	Color co;
//	point2 p;
//	point2 v;
//};
//vector<particle> l;
//
//bool checkleft(const point2& p)
//{
//	float x = p.x - 500; float y = p.y - 500;
//	if (x * x + y * y - x * r + sqrt(3) / 3 * r * y < r * r * 2 / 3)
//		return false;
//	return true;
//}
//
//bool checkright(const point2& p)
//{
//	float x = p.x - 500; float y = p.y - 500;
//	if (x * x + y * y + x * r + sqrt(3) / 3 * r * y < r * r * 2 / 3)
//		return false;
//	return true;
//}
//
//bool checkdown(const point2& p)
//{
//	float x = p.x - 500; float y = p.y - 500;
//	if (x * x + y * y - 2 * sqrt(3) / 3 * r * y < r * r * 2 / 3)
//		return false;
//	return true;
//}
//point2 up;
//point2 lt;
//point2 rt;
//inline point2 getV(const point2& c , point2 p , const point2& v)
//{
//	p += point2(-500 , -500);
//	float ver = (p.y - c.y) / (p.x - c.x);
//	float k = v.y / v.x;
//	k = tan(2 * atan(ver) - atan(k));
//	point2 vv = { 1 / (sqrt(1 + k * k)),k / sqrt(1 + k * k) };
//	if ((p - c + vv).length() < (p - c).length())
//		return vv;
//	return -vv;
//}
//int delay = 10;
//int sz = 3600;
//
//Circle co;
//
//int main()
//{
//	up = point2(0 , sqrt(3) / 3 * r);
//	lt = point2(-r / 2 , -sqrt(3) / 6 * r);
//	rt = point2(r / 2 , -sqrt(3) / 6 * r);
//
//
//	canvas.setWindowSize(1000 , 1000);
//
//	co.moveto(520 , 560);
//	co.setColor(SKYBLUE);
//
//	/*timer(1 , [=]() {
//		point2 p = point2({ co.pos.x,co.pos.y }) - point2(500 , 500);
//		p.rot(0.005);
//		co.moveto(500+p.x , 500+p.y);
//	});*/
//	main_win.loop([&]() 
//		{
//
//	point2 v = point2(co.pos.x,co.pos.y) - point2(500,500);
//	v *= 1 / v.length();
//	point2 p(500 , 500);
//	point2 q = p;
//	for (int i = 0; i < 100-0; i++)
//	{
//		while (true)
//		{
//			p += v;
//			if (checkdown(p))
//			{
//				v = getV(up , p , v);
//				ptr.drawLine(q.x , q.y , p.x , p.y);
//				q = p;
//				break;
//			}
//			if (checkleft(p))
//			{
//				v = getV(rt , p , v);
//				ptr.drawLine(q.x , q.y , p.x , p.y);
//				q = p;
//				break;
//			}
//			if (checkright(p))
//			{
//				v = getV(lt , p , v);
//				ptr.drawLine(q.x , q.y , p.x , p.y);
//				q = p;
//				break;
//			}
//		}
//	}
//			ptr.setColor(255 , 125 , 25);
//			ptr.fillCircle(500,500,3);
//			ptr.setColor(25 , 125 , 255);
//			ptr.drawArc(500,500 + sqrt(3) / 3 * r,r,240,300);
//			ptr.drawArc(500 - r / 2 , 500 - sqrt(3) / 6 * r , r , 0, 60);
//			ptr.drawArc(500 + r / 2 , 500 - sqrt(3) / 6 * r , r , 120 , 180);
//		}
//	);
//}