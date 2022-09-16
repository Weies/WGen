//#include"widget.h"
//#include"graphOBJ.h"
//#include<queue>
//#include"shader.h"
//using namespace std;
//class theRect :public Rect {
//public:
//	theRect() :Rect() {
//	}
//
//	void truedraw()
//	{
//		ptr.setPriority(prior);
//		Rect::draw();
//		font.setPriority(prior);
//		drawString(posx, posy, itos(depth));
//	}
//	void draw()
//	{
//		//Rect::draw();
//	}
//	float depth;
//};
//
//bool great(theRect* r1,theRect* r2)
//{
//	return r1->depth<r2->depth;
//}
//
//theRect rect[10];
//theRect* recs[10];
//int curpri = 0;
//
//int main()
//{
//	srand(time(0)-1E14);
//	canvas.setWindowSize(800, 800);
//	font.setColor(0, 0, 0);
//	
//	for (int i = 0; i<10; i++)
//	{
//		rect[i].setColor(rand()%255, rand()%255, rand()%255);
//		rect[i].moveto(rand()%600+100, rand()%600+100);
//		rect[i].depth = i*100; recs[i] = &rect[i];
//	}
//
//	for (int i = 0; i<10; i++)
//	{
//		rect[i].onclick = [=](me* e) {
//			rect[i].depth = 1000+curpri++;
//			sort(recs, recs+10, great);
//		};
//	}
//
//	glDisable(GL_DEPTH_TEST);
//
//	canvas.showFrame();
//
//	eventLoop(
//		for (int i = 0; i<10; i++)
//		{
//			recs[i]->truedraw();
//		}
//	);
//}