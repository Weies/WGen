//#include"WGen.h"
//float t = 0.00;
//float speed = 0.00003;
//
//int main()
//{
//	float p; float o;
//	timer(1 , [=]() {
//		if (t < 10.0f)
//			t += speed;
//		else t = 0.0001;
//	});
//	canvas.setWindowSize(800 , 800);
//	canvas.setKeyFunc([=](ke& e) {
//		if (e->key == KEY_A)
//		{
//			speed += 0.00005;
//		}
//		else speed -= 0.00005;
//	});
//	canvas.showFrame();
//	main_win.loop([&]() {
//		glStart(GL_POINTS);
//		for (float o = 0.0f; o < 30.0f; o += 0.002)
//		{
//			p = sin(t * o) * sin(t * o) * 200 + 100;
//			glPixel(400 + p * cos(o) , 400 + p * sin(o));
//		}
//		glOver();
//		});
//}