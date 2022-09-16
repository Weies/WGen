//#include"graphBasic.h"
//#include"widget.h"
//
//void drawGrid(int width)
//{
//	canvas.setColor(250 , 250 , 250);
//	glStart(GL_LINES);
//	int lines = win_w / width * 20;
//	for (int i = -lines; i <= lines; i++)
//	{
//		glPixel(i * 30 + 1 , -win_height());
//		glPixel(i * 30 + 1 , 2 * win_height());
//	}
//	for (int i = -lines; i <= lines; i++)
//	{
//		glPixel(-win_height() , i * 30);
//		glPixel(2 * win_width() , i * 30);
//	}
//	glOver();
//}
//
//void DDA(int x1 , int y1 , int x2 , int y2)
//{
//	float k = (y2 - y1) * 1.0 / (x2 - x1);
//	float x = x1; float y = y1;
//	canvas.setColor(25 , 100 , 255);
//	if (abs(k) <= 1)
//	{
//		for (int i = x1; i <= x2; i += 30)
//		{
//			ptr.fillRect(i , int(y + 0.5) * 30 , 30 , 30);
//			y += k;
//		}
//	}
//	else {
//		k = 1 / k;
//		for (int i = y1; i <= y2; i += 30)
//		{
//			ptr.fillRect(int(x + 0.5) * 30 , i , 30 , 30);
//			x += k;
//		}
//
//	}
//}
//
//void bresenham(int x1 , int y1 , int x2 , int y2)
//{
//	int dx = x2 - x1;
//	int dy = y2 - y1;
//	float k = dy * 1.0 / dx;
//	canvas.setColor(25 , 255 , 150);
//	int total = 600;
//	int x = 0; int y = 0; int e = -dx;
//
//	if (abs(k) < 1)
//	{
//		for (int i = 0; i <= dx; i += 30)
//		{
//			ptr.fillRect(x , y , 30 , 30);
//			x += 30; e += 2 * dy;
//			if (e >= 0) {
//				y += 30; e -= 2 * dx;
//			}
//		}
//	}
//	else {
//		e = -dy;
//		for (int i = 0; i <= dy; i += 30)
//		{
//			ptr.fillRect(x , y , 30 , 30);
//			y += 30; e += 2 * dx;
//			if (e >= 0) {
//				x += 30; e -= 2 * dy;
//			}
//		}
//	}
//}
//
//void circlePoints(int x , int y , int x0 , int y0)
//{
//	ptr.fillRect(x0 + x , y0 + y , 30 , 30);
//	ptr.fillRect(x0 + x , y0 - y , 30 , 30);
//	ptr.fillRect(x0 - x , y0 + y , 30 , 30);
//	ptr.fillRect(x0 - x , y0 - y , 30 , 30);
//	ptr.fillRect(x0 + y , y0 + x , 30 , 30);
//	ptr.fillRect(x0 - y , y0 + x , 30 , 30);
//	ptr.fillRect(x0 + y , y0 - x , 30 , 30);
//	ptr.fillRect(x0 - y , y0 - x , 30 , 30);
//}
//
//void drawCir(int x , int y , int r)
//{
//	int d = 5 - 4 * r;
//	int t = r * sqrt(2) / 2 + 1;
//	glStart(GL_POINTS);
//	int px = 0; int py = r;
//	circlePoints(px , py , x , y);
//	while (px < t) {
//		if (d <= 0)
//		{
//			circlePoints(px += 30 , py , x , y);
//			d += 8 * px + 12;
//		}
//		else
//		{
//			circlePoints(px += 30 , py -= 30 , x , y);
//			d += 8 * (px - py) + 20;
//		}
//	}
//	glOver();
//}
//
//void draw()
//{
//	DDA(0 , 0 ,- 1800 , 3000);
//	bresenham(0 , 0 , 3000 , 1500);
//	drawGrid(30);
//	canvas.setColor(255 , 0 , 0);
//	drawCir(1200 , 1200 , 1200);
//}
//
//int main(int ac , char** av)
//{
//	Button btn("Big");
//	btn.moveto(400 , 400);
//	Button btn2("Small");
//	btn2.moveto(400 , 450);
//	btn2.resize(80 , 40);
//	btn.resize(80 , 40);
//
//	btn.onclick = [= , &btn](me* e) {
//		thread td([=]() {
//			int i = 100;
//			while (i--)
//			{
//				this_thread::sleep_for(20ms);
//				canvas.scaleCenter(1.02 , mouseX , mouseY);
//			}
//		});
//		td.detach();
//	};
//	btn2.onclick = [= , &btn](me* e) {
//		thread td([=]() {
//			int i = 100;
//			while (i--)
//			{
//				this_thread::sleep_for(20ms);
//				canvas.scaleCenter(0.98 , mouseX , mouseY);
//			}
//		});
//		td.detach();
//	};
//
//	canvas.setWindowSize(600 , 600);
//	canvas.setBGC(200 , 200 , 200);
//	canvas.setDisplayFunc(draw);
//	canvas.setDragging();
//	canvas.setStickScale();
//	eventLoop();
//}