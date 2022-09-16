//#include"WGen.h"
//float p = 0.466 * 300 * 2; float b = -2.0;
//int main() {
//	canvas.setWindowSize(1000 , 800);
//	canvas.setBGC(Color(150 , 150 , 150));
//	canvas.setStickScale(true);
//	canvas.setDragging(true);
//	float ycord = 100;
//	glLineWidth(3);
//	glPointSize(2.0);
//
//	
//
//	canvas.setKeyFunc([=](ke& e) {
//		auto k = e->key;
//		if (k == KEY_UP) {
//			b += 5.0;
//		}
//		if (k == KEY_DOWN) {
//			b -= 5.0;
//		}
//		if (k == KEY_RIGHT) {
//			p += 5.0;
//		}
//		if (k == KEY_LEFT) {
//			p -= 5.0;
//		}
//	});
//
//
//	main_win.loop([&]() {
//
//	ptr.setColor(RED);
//	ptr.drawLine(0 ,ycord , 1000 , ycord);
//	ptr.setColor(GREEN);
//	ptr.drawLine(500 , 0 , 500 , 800);
//	ptr.setColor(Color(200,220,230));
//	ptr.drawArc(500 , 300 + ycord , 300 , -asin(5.0 / 6) ,  PI + asin(5.0 / 6));
//	ptr.setColor(BLUE);
//	ptr.drawArc(500 , 300 + ycord , 300 , PI + acos(5.0 / 6) , 2 * PI - acos(5.0 / 6));
//	ptr.fillCircle(500 , 300 + ycord , 5);
//	ptr.setColor(PINK);
//	for (float x = -150.0f; x <= 0; x += 0.2) {
//		ptr.drawPoint(500 + x , x * x / (2 * p) - b + ycord);
//		ptr.drawPoint(500 - x , x * x / (2 * p) - b + ycord);
//	}
//	ptr.setColor(Color(235,200,200));
//	for (float x = -500.0f; x <= -150; x += 0.2) {
//		ptr.drawPoint(500 + x , x * x / (2 * p) - b + ycord);
//		ptr.drawPoint(500 - x , x * x / (2 * p) - b + ycord);
//	}
//	font.setModel(canvas.transform);
//	drawString(500,400,"Ô²ÐÄ");
//	ptr.fillCircle(500 , ycord + 1 / (2.0 * p) - b + p / 2.0 , 5);
//	drawString(500 - 60 , ycord + 1 / (2.0 * p) - b + p / 2.0 , "½¹µã");
//	ptr.setColor(BLACK);
//	ptr.fillCircle(500 , ycord + 0.466 * 300 , 5);
//	drawString(500 + 20 , ycord + 0.466 * 300 , "À¡Ô´²Õ");
//			  });
//}