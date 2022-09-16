//#include<widget.h>
//#include<math.h>
//#include"graphOBJ.h"
////BSplineCurve bs(6 , 3);
//BezierCurve bezier(6);
//BezierCurve be(6);
//bool hand = false;
//#define BE
//int main()
//{
//	canvas.showFrame();
//	canvas.setWindowSize(600 , 600);
//	ptr.setColor(255 , 0 , 0);
//#ifndef BE
//	canvas.setMouseStick([=](me* e) {
//		if (!hand)
//		{
//			if (e->mBtn == GLFW_MOUSE_BUTTON_LEFT)
//				bs.addPoint(e->x , e->y);
//			else bs.erasePoint();
//			hand = true;
//		}
//	});
//	canvas.setKeyFunc([=](ke* e) {
//		if (e->key == GLFW_KEY_H)
//		{
//			bs.showCtrl(false);
//		}
//		else if (e->key == GLFW_KEY_S)
//		{
//			bs.showCtrl(true);
//		}
//	});
//	bezier.show(false);
//#endif
//	for (int i = 0; i < 6; i++)
//	{
//		be.c[i]->posx = bezier.c[5 - i]->posx;
//		be.c[i]->posy = bezier.c[5 - i]->posy;
//	}
//#ifdef BE
//	canvas.setMouseStick([=](me* e) {
//		if (!hand)
//		{
//			if (e->mBtn == GLFW_MOUSE_BUTTON_LEFT)
//				bezier.addPoint(e->x , e->y);
//			else bezier.erasePoint();
//			hand = true;
//		}
//	});
//	//bs.showCtrl(false);
//	//bs.show(false);
//#endif
//
//	canvas.setMouseUp([=](me* e) {
//		hand = false;
//	});
//
//	eventLoop(
//		bezier.draw();
//	be.draw();
//		//bs.draw();
//	);
//}