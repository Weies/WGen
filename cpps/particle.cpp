//#include"WGen.h"
//
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
//	if ((p - c + vv).len() < (p - c).len())
//		return vv;
//	return -vv;
//}
//int delay = 3;
//int sz = 360;
//
//int main()
//{
//	up = point2(0 , sqrt(3) / 3 * r);
//	lt = point2(-r / 2 , -sqrt(3) / 6 * r);
//	rt = point2(r / 2 , -sqrt(3) / 6 * r);
//	point2 v = { 0,1 };
//	for (int i = 0; i <= sz; i++)
//	{
//		l.push_back({ {500,500},v });
//		l.back().co = Color::getRandColor();
//		v.rot(360.0/sz);
//	}
//	canvas.showFrame();
//	canvas.setKeyFunc([=](ke& e) {
//		if (e->key == KEY_A)
//			delay -= 5;
//		else delay += 5;
//	});
//
//
//	Thread td([=]() {
//		while (true)
//		{
//			for (int i = 0; i <= sz; i++)
//			{
//				auto& p = l[i].p;
//				p += l[i].v;
//				if (checkdown(p))
//				{
//					l[i].v = getV(up , l[i].p , l[i].v);
//					continue;
//				}
//
//				if (checkleft(p))
//				{
//					l[i].v = getV(rt , l[i].p , l[i].v);
//					continue;
//				}
//
//				if (checkright(p))
//				{
//					l[i].v = getV(lt , l[i].p , l[i].v);
//					continue;
//				}
//			}
//			this_thread::sleep_for(chrono::milliseconds(delay));
//		}
//	});
//
//	canvas.setWindowSize(1000 , 1000);
//
//	main_win.loop([&]() 
//		{
//			point2 p;
//			for (int i = 0; i <= sz; i++)
//			{
//				p = l[i].p - point2(500 , 500);
//				ptr.setColor((p.len() + 100) / 2,255 - abs((p.y + p.x) / 2),205 - abs(p.x));
//				ptr.fillCircle(l[i].p.x , l[i].p.y , 3 , 4);
//			}
//			drawString(500 , 500 , "haha");
//			ptr.setColor(255 , 125 , 25);
//			ptr.fillCircle(500,500,3);
//			ptr.setColor(25 , 125 , 255);
//			ptr.drawArc(500,500 + sqrt(3) / 3 * r,r,240,300);
//			ptr.drawArc(500 - r / 2 , 500 - sqrt(3) / 6 * r , r , 0, 60);
//			ptr.drawArc(500 + r / 2 , 500 - sqrt(3) / 6 * r , r , 120 , 180);
//		}
//	);
//}