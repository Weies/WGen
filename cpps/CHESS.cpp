//#include"WGen.h"
//
//float w = 40;
//enum direction {
//	up, down, left, right
//};
//int main() {
//
//	vector<vec2> li;
//	li.push_back({ 10,10 });
//	main_win.setWindowSize(600, 600);
//	direction dir = up;
//	timer(300, [&]() {
//		if (dir == up) {
//			li[0].y -= 1;
//		}
//		else if (dir == down) {
//			li[0].y += 1;
//		}
//		else if (dir == direction::left) {
//			li[0].x -= 1;
//		}
//		else li[0].x += 1;
//		});
//	main_win.setKeyFunc([&](ke& e)->bool {
//		switch (e->key) {
//		case KEY_UP:
//			dir = up;
//			break;
//		case KEY_DOWN:
//			dir = down;
//			break;
//		case KEY_LEFT:
//			dir = direction::left;
//			break;
//		case KEY_RIGHT:
//			dir = direction::right;
//			break;
//		}
//
//		return true;
//		});
//	main_win.loop([&]() {
//		ptr.setColor(100, 100, 100);
//		for (int i = 0; i < win_w / 30; i++) {
//			ptr.drawLine(0, i * w, win_w, i * w);
//			ptr.drawLine(i * w, 0, i * w, win_h);
//		}
//		ptr.setColor(255, 0, 0);
//		ptr.fillCircle(li[0].x * w - w / 2, li[0].y * w - w / 2, w / 2);
//
//		});
//}