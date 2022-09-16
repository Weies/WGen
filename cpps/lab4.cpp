//#include"WGen.h"
//
//int main() {
//	Image img;
//	img.load("C:\\Users\\Weies\\Desktop\\2.gif");
//	Cube c; c.setColor(255, 255, 255);
//	Texture text(GL_TEXTURE_2D);
//	text.setData(img);
//	c.addTexture(text, -1);
//	PhongRender phong; phong.addLights();
//	Mat<cvec4> m = img.mat4();
//	main_win.loop([&]() {
//		phong.setBlock(ca.getBlock());
//		phong << c;
//		float w = win_w / m.cols; float h = win_h / m.rows;
//		for (int i = 0; i < m.rows * 3; i += 3) {
//			for (int j = 0; j < m.cols; j++) {
//				//cvec4 v = m(i, j);
//				//ptr.setColor(Color(v.x, v.y, v.z));
//				ptr.setColor(Color(m(i, j)[0], m(i + 1, j)[1], m(i + 2, j)[2]));
//				ptr.fillRect(j * w, i * h, w, h);
//			}
//		}
//		});
//}