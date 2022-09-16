//#include"WGen.h"
//vector<string> split(const string& s , char delima) {
//	vector<string> ret; int last = 0;
//	for (int i = 0; i < s.size(); ++i) {
//		if (s[i] == delima) {
//			ret.push_back(string(s.begin() + last , s.begin() + i));
//			last = i + 1;
//		}
//	}
//	ret.push_back(string(s.begin() + last , s.end()));
//	return ret;
//}
//Sphere ball;
//LightSource ls;
//int main()
//{
//	fstream f;
//	f.open("E:/Learnnotes/数学建模/A/附件1.csv" , ios::in);
//	map<string , int> vlist;
//	string s; f >> s;
//	pt* p = new pt[2226 * 3 + 100]; int idx = -1;
//	while (!f.eof()) {
//		f >> s; vector<string> l = split(s , ',');
//		vlist.insert({ l[0],vlist.size() });
//		p[++idx].x = stof(l[1]); p[idx].y = stof(l[2]); p[idx].z = stof(l[3]);
//	}
//	f.close();
//	f.open("E:/Learnnotes/数学建模/A/附件3.csv" , ios::in); f >> s;
//	uint* indices = new uint[4300 * 3 + 100]; idx = -1;
//	while (!f.eof()) {
//		f >> s; vector<string> l = split(s , ',');
//		indices[++idx] = vlist[l[0]]; indices[++idx] = vlist[l[1]]; indices[++idx] = vlist[l[2]];
//	}
//	Render3D render;
//	CameraBlock b;
//	//glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
//	FlatRender flat;
//	ls.moveto(vec3(0 , 0 , -0.5));
//	ls.setLightColor(vec3(1.0));
//
//
//	ptr3.setColor(RED);
//	canvas.setBGC(GRAY);
//	mat4 model = scale(mat4(1.0f) , vec3(1.0 / 300));
//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POLYGON_SMOOTH);
//	canvas.setKeyFunc([=](ke& e) {
//		if (e->key == KEY_G)ls.translate(10 , 10 , 0);
//		else if (e->key == KEY_F) ls.translate(-10 , -10 , 0);
//	});
//
//	float aa = radians(36.795); float bb = radians(78.169);
//	pt dir = pt(cos(aa) * cos(bb) , cos(bb) * sin(aa) , sin(bb));
//
//	main_win.loop([&]() {
//
//	b = ca.getBlock();
//
//
//	ptr3.setModel(model);
//	ptr3.setColor(185 , 125 , 155);
//	for (int i = 0; i < 4300; ++i) {
//		pt p1 = p[indices[i * 3]]; pt p2 = p[indices[i * 3 + 1]]; pt p3 = p[indices[i * 3 + 2]];
//		if (cross(p1 - p2) , p1 - p3).z > 0)
//			ptr3.fillTriangle(p1 , p2 , p3);
//		else ptr3.fillTriangle(p3 , p2 , p1);
//	}
//	flat.bindToLight(ls);
//	flat.renderList(b);
//	flat.renderLight(b);
//	//flat.bindToMesh(ball);
//	//flat.renderMesh(b);
//	ptr3.setModel(mat4(1.0));
//	ptr3.setColor(RED);
//	ptr3.drawLine(dir * -100.0 , dir * 100);
//	ptr3.drawPoint(pt(0 , 0 , -1.0));
//	ptr3.drawCoordinate();
//
//	render.renderList(b.mPVTransform);
//
//			  });
//}