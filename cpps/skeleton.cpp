//#include"WGen.h"
//#include<stdlib.h>
//#include<string.h>
//#include<conio.h>
//
//
//int main() {
//
//	PhongRender phong;
//	/*MeshObject m;
//	m.readDRO("E:/Learnnotes/CG/WGen/models/objs/girl/Hgirl.dro");*/
//	Render3D ren;
//	ca.moveto(vec3(3.0, 0.0, 0.8));
//	phong.addLights();
//	CameraBlock b;
//	main_win.set(SHOW_FPS, true);
//	main_win.bind();
//	CameraBorad board(ca); board.bar.val = 1; board.sync();
//	board.moveto(200, 200);
//	Actor m;
//	glLineWidth(1); float deg = 1.0f;
//	int tick = 0;
//	Button btn(str(tick));
//	btn.onclick = [&tick, &btn, &m](me& e)->bool {
//		tick += 1; btn.setText(str(tick));
//		m.play(tick % m.anims.size());
//		return true;
//	};
//	SkyBox box;
//	m.has_bone = false;
//	ScrollBar bar;
//	bar.onscroll = [&](me& e) {
//		m.anims[m.anim_index].speed = bar.val;
//	};
//	m.reverse = true;
//
//	main_win.loop([&]() {
//		phong.setBlock(b = ca.getBlock());
//		phong << box;
//
//
//		//m.syncBones(phong.id);
//		/*for (int i = 0; i < m.meshes.size() && i < tick; ++i) {
//			m.meshes[i].draw(phong.id);
//		}*/
//		m.visualizeBones(b);
//		ptr3.setColor(WHITE);
//		ptr3.fillCube(scale(mat4(1.0), vec3(400, 0.1, 400)));
//		ptr3.drawCoordinate(100, 1);
//		ptr3.drawLine(m.model[3] - m.frontv() * 30, m.model[3] + m.frontv() * 30);
//		ren.renderList(b);
//		phong << m;
//		});
//
//	main_win.terminate();
//}