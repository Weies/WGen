//// ComputerGraphics.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
////
//#include"widget.h"
//#include"graphOBJ.h"
//using namespace std;
//
//Circle pie(400, 300, 100);
//Triangle tri(200, 200);
//LineOBJ line1(0, 0, win_width(), win_height());
//LineOBJ line2(0, win_height(), win_width(), 0);
//Circle center(400, 200, 50);
//Rect rect(600, 200, 100, 200);
//Button btn("stop");
//Circle pp(200, 200, 30);
//
//void rotating()
//{
//	tri.rotate(1);
//	pie.rotate(1);
//	center.rotate(1);
//}
//
//bool label = true;
//
//int main(int argc, char* argv[])
//{
//
//	tri.setPriority(100);
//	timer(10, rotating);
//	btn.onmouseup = [=](me* e) {
//		if (label)
//		{
//			btn.str = ("start");
//			canvas.killTimer();
//			label = false;
//		}
//		else
//		{
//			timerAble = true;
//			timerFuncs.resize(0);
//			btn.str = ("stop");
//			timer(10, rotating);
//			label = true;
//		}
//	};
//	canvas.showFrame();
//	pp.onclick = 0;
//	pp.onmove = 0;
//	pie.onmove = [=](me* e)
//	{
//		pie.moveto(e->x, e->y);
//		pie.rx += deltaX;
//		pie.ry += deltaY;
//		center.rx += deltaX;
//		center.ry += deltaY;
//	};
//	canvas.setStickScale();
//	canvas.setMouseMove([=](me* e) {
//		canvas.translate(deltaX, deltaY);
//	});
//	canvas.setBGC(200, 200, 200);
//	center.rotate(180);
//	int i = 0;
//	eventLoop();
//	return 0;
//}
//
