//#include"WGen.h"
//struct city {
//	string name;
//	float x , y;
//	int hours[12];
//	float aver = 0;
//	void caculAver() {
//		for (int i = 0; i < 12; ++i)
//			aver += hours[i];
//		aver /= 12;
//	}
//};
//
//inline vector<string> split(const string& s , char delma) {
//	int last = 0; vector<string> ret;
//	for (int i = 0; i < s.size(); ++i) {
//		if (delma == s[i]) {
//			ret.push_back(string(s.begin() + last , s.begin() + i));
//			last = i + 1;
//		}
//	}
//	ret.push_back(string(s.begin() + last , s.end()));
//	return ret;
//}
//
//vec3 toVec3(float x , float y) {
//	vec3 v;
//	v.y = sin(radians(y));
//	v.x = -sin(radians(x)) * cos(radians(y));
//	v.z = -cos(radians(x)) * cos(radians(y));
//	return v;
//}
//vec2 toSc(float  x , float y) {
//	return vec2((x + 1) / 2 * win_w , win_h - (y + 1) / 2 * win_h);
//}
//int main() {
//	Sphere ss;
//	PhongRender phong;
//	phong.addLights();
//	ss.addTexture("imgs/earth.jpg" , texture_diffuse , -1);
//	phong.setCoordType(SPHERE_COORD);
//	Render3D r3;
//	fstream f;
//	f.open("imgs/sunshine.csv" , ios::in);
//	string s; f >> s;
//	city ct[6];
//	int idx = 0;
//	char crs[1000] = {}; f.getline(crs , 10);
//	float max = 0.0; float min = 15654;
//	while (idx < 6) {
//		for (int i = 0; i < 12; ++i) {
//			f.getline(crs , 1000); s = crs;
//			auto v = split(s , ',');
//			ct[idx].name = v[0];
//			ct[idx].x = stof(v[1]);
//			ct[idx].y = stof(v[2]);
//			ct[idx].hours[i] = stoi(v[5]);
//		}
//		ct[idx].caculAver();
//		if (ct[idx].aver > max)max = ct[idx].aver;
//		if (ct[idx].aver < min)min = ct[idx].aver;
//		++idx;
//	}
//	float dif = max - min;
//	vec3 p1(0.1 , -0.1 , -0.15); vec3 p2(0.1 , 0.2 , 0.0); vec3 p3(0.1 , -0.1 , 0.15);
//	vec3 cen;
//	ca.moveto(vec3(0.0 , 3.0 , 3.0)); ca.lookToDirection(vec3(0 , -1 , -1));
//	CameraBlock b;
//	main_win.loop([&]() {
//		b = ca.getBlock();
//		phong.setBlock(b);
//		phong << ss;
//		phong.renderLight(b);
//		ptr3.drawCoordinate();
//		for (int i = 0; i < 6; ++i) {
//			cen = toVec3(ct[i].x , ct[i].y);
//			ptr3.setColor(Color((ct[i].aver - min) * 255 / dif));
//			ptr3.fillTriangle(cen + p1 , cen + p2 , cen + p3);
//			vec4 p = b.mPVTransform * vec4(cen , 1.0);
//			p /= p.w; vec2 pp = toSc(p.x , p.y);
//			cdrawString(pp.x , pp.y + 10 , ct[i].name);
//			string str = to_string(ct[i].x); str.resize(5);
//			cdrawString(pp.x - 30 , pp.y - 10 , str);
//			str = to_string(ct[i].y); str.resize(5);
//			cdrawString(pp.x + 30 , pp.y - 10 , str);
//			str = to_string(ct[i].aver); str.resize(5);
//			cdrawString(pp.x , pp.y + 35 , "average sunshine: " + str);
//		}
//
//		r3.renderList(b.mPVTransform);
//	});
//}