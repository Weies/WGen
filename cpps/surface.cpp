//#include"WGen.h"
//float inter(float k , float c , float a , float b , float d)
//{
//	return (-2 * k * c * a * a + d *
//			sqrt(4 * k * k * c * c * a * a * a * a - 4 *
//				 (b * b + a * a * k * k) * (a * a * c * c - a * a * b * b)))
//		/ (2 * (b * b + a * a * k * k));
//}
//Circle start;
//Circle endd;
//float speed = 0.25;
//int line = 20;
//bool quit = false;
//
//int main()
//{
//	canvas.setWindowSize(1000 , 1000); float y;
//	float a = 500.0f; float b = 400.0f;
//
//	float k = 0.5f;
//	float c;
//	float ver;
//	float tx; float ty;
//
//	start.moveto(550 , 500);
//	endd.moveto(700 , 600);
//	glEnable(GL_DEPTH_TEST);
//
//
//	canvas.setKeyFunc([=](ke& e) {
//		debug(e->key);
//		if (e->key == GLFW_KEY_UP)
//			speed += 0.05;
//		else if (e->key == GLFW_KEY_DOWN)
//			speed -= 0.05;
//		else if (e->key == GLFW_KEY_A)
//			line++;
//		else if (e->key == GLFW_KEY_S)
//			line--;
//		else if (e->key == KEY_Q)
//			quit = !quit;
//	});
//	//a *= 0.9; b *= 0.9;
//	float com = 0.0; int fin = 1;
//	float s = a * a;
//	point2 p = rotc(500 , 500 , start.pos.x , start.pos.y , 30);
//	start.moveto(p.x , p.y);
//
//	timer(10 , [= , &com , &fin]() {
//		if (quit)return;
//		point2 p = rotc(500 , 500 , endd.pos.x , endd.pos.y , speed);
//		endd.moveto(p.x , p.y);
//		/*p = rotc(500 , 500 , start.pos.x , start.pos.y , speed);
//		start.moveto(p.x , p.y);*/
//	});
//
//	main_win.loop([&]() {
//
//	ptr.setPriority(1024);
//	drawString(160,530,"Ωπµ„C1");
//	drawString(750,530,"Ωπµ„C2");
//	ptr.setColor(SKYBLUE);
//	glStart(GL_POINTS);
//	//for (float i = 0.0f; i < a; i += 1.0f)
//	//{
//	//	y = /*0.80 **/ sqrt(s - i * i);
//	//	glPixel(500 + i , 500 + y);
//	//	glPixel(500 + i , 500 - y);
//	//	glPixel(500 - i , 500 + y);
//	//	glPixel(500 - i , 500 - y);
//	//}
//	//ptr.drawCircle(500 , 500 , a);
//	ptr.drawEllipse(a,b,500,500);
//	glOver();
//	ptr.drawLine(0 , 500 , 1000 , 500);
//	ptr.drawLine(500 , 0 , 500, 1000);
//	ptr.fillCircle(200 , 500 , 20);
//	ptr.fillCircle(800 , 500 , 20);
//	ptr.setColor(GREEN);
//	ptr.fillCircle(200 , 500 , 4);
//	ptr.fillCircle(800 , 500 , 4);
//	ptr.setColor(SKYBLUE);
//	float x1 = start.pos.x; float x2 = endd.pos.x; float y1 = start.pos.y; float y2 = endd.pos.y;
//	k = (y2 - y1) / (x2 - x1);
//	c = (x2 * y1 - x1 * y2 + 500 * y2 - 500 * y1) / (x2 - x1) - 500;
//	float ix = inter(k , c , a , b , 1.0f);
//	if (start.pos.x > endd.pos.x)
//		ix = inter(k , c , a , b , -1.0f);
//	float iy = k * ix + c;
//	ptr.drawLine(start.pos.x , start.pos.y , 500 + ix , 500 + iy);
//	ptr.fillCircle(500 + ix , 500 + iy , 10);
//	for (int i = 0; i < line; i++)
//	{
//		ver = 1 / ((ix / iy) * (b * b) / (a * a));
//		ptr.setColor(RED);
//		float len = 80 / sqrt(1 + ver * ver);
//		ptr.drawLine(500 + ix + len , 500 + iy + len * ver , 500 + ix - len , 500 + iy - len * ver);
//		k = tan(2 * atan(ver) - atan(k));
//		c = -ix * k + iy;
//		tx = ix; ty = iy;
//		ix = inter(k , c , a , b , 1.0f);
//		if (abs(ix - tx) < 0.5f)
//			ix = inter(k , c , a , b , -1.0f);
//		iy = k * ix + c;
//		ptr.setColor(SKYBLUE);
//		ptr.drawLine(500 + tx , 500 + ty , 500 + ix , 500 + iy);
//		ptr.fillCircle(500 + ix , 500 + iy , 10);
//	}
//			  });
//}