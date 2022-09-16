//#include"WGen.h"
//
//
//float contrast = 5.0;
//float sigmoid(float x) {
//	return 1 / (1 + (exp(contrast - 2 * contrast * x)));
//}
//ScrollBar bar;
//int main() {
//
//	canvas.setDragging(true);
//	canvas.setStickScale(true);
//	float hafw; float hafh;
//
//	bar.onscroll = [=](me& e) {
//		contrast += deltaX * 0.025;
//	};
//
//	main_win.loop([&]() {
//	hafw = win_w / 2; hafh = win_h / 2;
//	ptr.setColor(255 , 0 , 0);
//	ptr.drawLine(0 , hafh , win_w , hafh);
//	ptr.setColor(0 , 0 , 255);
//	ptr.drawLine(hafw , 0 , hafw , win_h);
//	ptr.setCenter(hafw , hafh);
//	ptr.setColor(0 , 0 , 0);
//	for (float i = 0; i < 1.0; i += 0.001)
//		ptr.cdrawPoint(i * hafw , sigmoid(i) * hafh);
//	font.setModel(canvas.transform);
//	drawString(hafw - 40 , win_h - 20 , "1.0");
//	drawString(win_w - 20 , hafh - 20 , "1.0");
//	cdrawString(bar.pos.x , bar.pos.y , to_string(contrast));
//	vec3 v = canvas.transform * vec3(mouseX , mouseY , 1.0);
//	ptr.setColor(0 , 255 , 0);
//	if (abs(mouseY - hafh - sigmoid((v.x - hafw) / hafw) * hafh) < 20) {
//		ptr.fillCircle(mouseX , sigmoid((mouseX - hafw) / hafw) * hafh + hafh , 15);
//	}
//
//			  });
//}