//#include"WGen.h"
//#include<stdlib.h>
//#include<string.h>
//#include<conio.h>
// 
//# define num_frame 552
////125 for kun&taiguo    552 for guo 
//float start;
//float fps = 30;
//bool next_tick() {
//	float cur = clock();
//	if (cur - start > 1000 / fps) {
//		start = cur;
//		return true;
//	}
//	return false;
//}
//
//
//inline vector<string> split(const string& s, char delma) {
//	int last = 0; vector<string> ret;
//	for (int i = 0; i < s.size(); ++i) {
//		if (delma == s[i]) {
//			ret.push_back(string(s.begin() + last, s.begin() + i));
//			last = i + 1;
//		}
//	}
//	ret.push_back(string(s.begin() + last, s.end()));
//	return ret;
//}
//
//
//
//int main() {
//	//_wchdir((const wchar_t*)"G:/grade3/up/openpose/build/");
//	//debug<<WinExec("./x64/Release/OpenPoseDemo.exe --video C:/Users/22393/Desktop/guo.mp4 --write_json C : /Users/22393/Desktop/guo", SW_HIDE);
//	Render3D ren;
//	PhongRender phong;
//	ca.moveto(vec3(100.0, 0.0, 4.0));
//	phong.addLights();
//	CameraBlock b;
//	main_win.setBGC(DARK);
//	main_win.set(SHOW_FPS, true);
//	main_win.bind();
//	CameraBorad board(ca); board.bar.val = 1.0; board.sync();
//	board.moveto(200, 200);
//
//	MeshObject m;
//	m.readDRO("C:/Learnnotes/CG/WGen/models/objs/girl/Hgirl.dro");
//	m.play("Hip pop dance", 0.4);
//	//m.scale(0.5);
//	m.reverse = true;
//	//m.scale(0.08);// m.rotate(180 , vec3(0 , 0 , 1));
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_BACK);
//	Cube cub;
//	cub.scale(vec3(1000, 1000, 5));
//	cub.addTexture("imgs/brickwall.jpg", texture_diffuse, -1);
//	cub.addTexture("imgs/brickwall_normal.jpg", texture_height, -1);
//	main_win.setBGC(GRAY);
//	Button btn("0"); int idx = 0;
//
//
//
//	/*ScrollBar bar;
//	bar.onscroll = [&](me& e)->bool {
//		return true;
//	};*/
//
//	btn.onclick = [&](me& e)->bool {
//		idx = (idx + 1) % 5;
//		btn.setText(str(idx));
//		m.play(idx, 0.4);
//		return true;
//	};
//
//	start = clock();
//	vec3 p = ca.mCameraPosition;
//	float t = 0;
//
//
//	vector<SQT> pose;
//	pose.resize(65);
//
//	vector<vector<vec2>> lis;
//	for (int k = 0; k < num_frame; ++k) {
//		lis.push_back(vector<vec2>());
//		string kk = to_string(k);
//		if (k < 10)kk = "00" + kk;
//		if (k >= 10 && k < 100)kk = "0" + kk;
//		string s = "C:/Learnnotes/CG/WGen/models/dat/guo_000000000" + kk + "_keypoints.json";
//		fstream f;
//		f.open(s.c_str(), ios::in);
//		string str;
//		f >> str;
//		str = str.substr(str.find("2d\":[") + 5);
//		vector<string> sl = split(str, ',');
//
//		for (int i = 0; i < sl.size(); ) {
//			if (sl[i].find(']') != string::npos)break;
//			float x, y;
//			x = stof(sl[i]); y = stof(sl[i + 1]);
//			lis[k].push_back({ x,y });
//			i += 3;
//		}
//		f.close();
//	}
//
//	int ma[65];
//	memset(ma, -1, 4 * 65);
//#define p(x,y) ma[x]=y;
//	p(10, 0); p(7, 1); p(0, 8); p(12, 2); p(11, 5); p(22, 3);
//	p(21, 6); p(24, 4); p(23, 7); p(3, 9); p(2, 12); p(6, 10);
//	p(5, 13); p(9, 11); p(8, 14); p(14, 22); p(13, 19);
//
//
//	int idxx = 0;
//	SQT def[65];
//	for (int i = 0; i < 65; ++i) {
//		if (!m.anims[0].testChannel(i))continue;
//		def[i] = inverse(m.jos[i].off_set);
//	}
//
//	//m.textures.resize(0);
//
//	SkyBox sky;
//	sky.scale(6, 6, 6);
//	main_win.loop([&]() {
//		phong.setBlock(b = ca.getBlock());
//		ptr3.drawCoordinate(1000, 10);
//		//ptr3.setColor(RED);
//
//		/*for (int i = 0; i < lis[idxx].size(); ++i) {
//			ptr.fillRect(lis[idxx][i] * 0.8, (lis[idxx][i] * 0.8 + vec2(10, 10)));
//		}*/
//
//		if (next_tick()) {
//			idxx = (idxx + 1) % num_frame;
//		}
//
//		for (int i = 0; i < 65; ++i) {
//			if (!m.anims[0].testChannel(i))continue;
//			auto& li = lis[idxx];
//			pose[i] = def[i];
//			if (ma[i] == -1) {
//				if (i == 1 || i == 4)
//				{
//					pose[i].p = vec3(li[8] + (li[1] - li[8]) * (i * 0.15 + 0.2), 0);
//
//				}
//				else if (i >= 25)
//				{
//					if (m.jos[i].name.find("Left") == string::npos) {
//						pose[i].p = vec3(li[4] + 20.0f * vec2(Randf(), Randf()), 0);
//					}
//					else {
//						pose[i].p = vec3(li[7] + 20.0f * vec2(Randf(), Randf()), 0);
//					}
//				}
//				else if (i == 15) {
//					pose[i].p = vec3((li[15] + li[16]) * 0.5, 0);
//					pose[i].p.y += 40;
//
//				}
//			}
//			else {
//				if (i == 10)
//				{
//					vec2& v = li[ma[i]];
//					pose[i].p = vec3(v.x, v.y + 40, 0);
//				}
//				else
//				{
//					vec2& v = li[ma[i]];
//					pose[i].p = vec3(v.x, v.y, 0);
//				}
//
//			}
//
//			pose[i].p *= 0.12;
//			pose[i].p.y = 60 - pose[i].p.y;
//			pose[i].p.y += 80;
//		}
//
//		pose[17].p = pose[12].p * 0.9 + pose[22].p * 0.1;
//		//pose[17].q = pose[17].q * qua(1.57-atan((pose[22].p.y - pose[12].p.y) / (pose[22].p.x - pose[12].p.x)), vec3(0, 0, -1));
//		pose[16].p = pose[11].p * 0.9 + pose[21].p * 0.1;
//		m.setPose(pose);
//
//		//phong << sky;
//		phong << sky << m << cub;
//
//		m.visualizeBones(b);
//		ren.renderList(b);
//		});
//
//	main_win.terminate();
//}
//
////#include"WGen.h"
////#include<stdlib.h>
////#include<string.h>
////#include<conio.h>
////
////float start;
////bool next_tick() {
////	float cur = clock();
////	if (cur - start > 1000 / 60.0) {
////		start = cur;
////		return true;
////	}
////	return false;
////}
////
////int main() {
////
////	Render3D ren;
////	PhongRender phong;
////	ca.moveto(vec3(100.0, 0.0, 4.0));
////	phong.addLights();
////	CameraBlock b;
////	main_win.setBGC(DARK);
////	main_win.set(SHOW_FPS, true);
////	main_win.bind();
////	CameraBorad board(ca); board.bar.val = 1.0; board.sync();
////	board.moveto(200, 200);
////
////	MeshObject m;
////	m.readDRO("C:/Learnnotes/CG/WGen/models/objs/girl/Hgirl.dro");
////	m.play("Hip pop dance", 0.4);
////	m.reverse = true;
////	//m.scale(0.08);// m.rotate(180 , vec3(0 , 0 , 1));
////	//glEnable(GL_CULL_FACE);
////	//glCullFace(GL_BACK);
////	Cube cub;
////	SkyBox sky;
////	cub.scale(vec3(80, 80, 0.08));
////	cub.addTexture("imgs/brickwall.jpg", texture_diffuse, -1);
////	cub.addTexture("imgs/brickwall_normal.jpg", texture_height, -1);
////	main_win.setBGC(GRAY);
////	Button btn("0"); int idx = 0;
////
////	/*ScrollBar bar;
////	bar.onscroll = [&](me& e)->bool {
////		return true;
////	};*/
////
////	btn.onclick = [&](me& e)->bool {
////		idx = (idx + 1) % 5;
////		btn.setText(str(idx));
////		m.play(idx, 0.4);
////		return true;
////	};
////	start = clock();
////	vec3 p = ca.mCameraPosition;
////	float t = 0;
////
////	vector<SQT> pose;
////	pose.resize(65);
////	Srand(time(0));
////	for (int i = 0; i < 65; ++i) {
////		if (!m.anims[0].testChannel(i))continue;
////		SQT s(1.0, qua(mat3(1.0)), vec3());
////
////		//设置关节点i的位置
////		s.p = vec3((Randf() + 1) * 30, (Randf() + 1) * 30, (Randf() + 1) * 30);
////
////		pose[i] = s;
////	}
////
////	m.setPose(pose);
////
////	main_win.loop([&]() {
////		phong.setBlock(b = ca.getBlock());
////		ptr3.drawCoordinate(1000, 10);
////		/*if (next_tick()) {
////			t += 0.1;
////			p = rotate(mat4(1.0), 1, vec3(0, 1, 0)) * vec4(p, 1.0);
////			p.rand();
////			ca.moveto(p*1000);
////			ca.lookTo(vec3(0, 50, 0));
////		}*/
////		//phong << cub;//<< sky
////
////		phong << sky << cub;
////		//m.visualizeBones(b);
////		ren.renderList(b);
////		});
////
////	main_win.terminate();
////}
