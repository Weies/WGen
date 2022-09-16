//#include<iostream>
//#include<vector>
//#include<fstream>
//#include<map>
//#include<glut.h>
//using namespace std;
//struct point {
//	float x, y, z;
//};
//
//
//struct edge {
//	edge() {}
//	edge(int x, int y, int z, int w) {
//		point_idx = x;
//		next_edge = y;
//		opp_edge = z;
//		face_idx = w;
//	}
//	int point_idx;
//	int next_edge;
//	int opp_edge;
//	int face_idx;
//};
//struct face {
//	int edge_idx;
//};
//
//vector<point> points;//点表
//
//vector<face> faces;//面表
//
//vector<edge> edges;//半边表
//map<pair<int, int>, int> ma;
//
//void readOff(const string& filepath) {
//	fstream f;
//	f.open(filepath.c_str(), ios::in);
//	string s;
//	f >> s;
//	int n_vertex, n_face, un;
//	f >> n_vertex >> n_face >> un;
//	for (int i = 0; i < n_vertex; ++i) {
//		float x, y, z;
//		f >> x >> y >> z;
//		points.push_back({ x,y,z });
//	}
//	int i = 0;
//	while (i < n_face) {
//		int n, a, b, c;
//		f >> n >> b >> c; //默认n==3
//		for (int j = 2; j < n; ++j) {
//			a = b; b = c; f >> c;
//			edge e(a, i * 3 + 1, 0, i);
//			if (ma.find({ b,a }) != ma.end()) {
//				int opp_idx = ma[{b, a}];
//				e.opp_edge = opp_idx;
//				edges[opp_idx].opp_edge = i * 3;
//			}
//			else ma.insert({ {a,b},i * 3 });
//			edges.push_back(e);
//
//
//			e = edge(b, i * 3 + 2, 0, i);
//			if (ma.find({ c,b }) != ma.end()) {
//				int opp_idx = ma[{c, b}];
//				e.opp_edge = opp_idx;
//				edges[opp_idx].opp_edge = i * 3 + 1;
//			}
//			else ma.insert({ {b,c},i * 3 + 1 });
//			edges.push_back(e);
//
//
//			e = edge(c, i * 3, 0, i);
//			if (ma.find({ a,c }) != ma.end()) {
//				int opp_idx = ma[{a, c}];
//				e.opp_edge = opp_idx;
//				edges[opp_idx].opp_edge = i * 3 + 2;
//			}
//			else ma.insert({ {c,a},i * 3 + 2 });
//			edges.push_back(e);
//			faces.push_back({ i * 3 });
//
//			++i;
//		}
//		n_face += n - 3;
//	}
//}
//void display() {
//
//	glClearColor(0, 0, 0, 1);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glShadeModel(GL_SMOOTH);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(1.0, 800 / 600.0, 0.1, 1000);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslatef(0, 0, -200);
//	//glScalef(0.2, 0.2, 0.2);
//
//	glColor3f(1.0, 0.0, 0.0);
//	glBegin(GL_TRIANGLES);
//	for (int i = 0; i < faces.size(); ++i)
//	{
//		auto& f = faces;
//		int e = faces[i].edge_idx;
//		int p1 = edges[e].point_idx;
//		e = edges[e].next_edge;
//		int p2 = edges[e].point_idx;
//		e = edges[e].next_edge;
//		int p3 = edges[e].point_idx;
//		auto& v = points;
//		glVertex3f(v[p1].x, v[p1].y, v[p1].z);
//		glVertex3f(v[p2].x, v[p2].y, v[p2].z);
//		glVertex3f(v[p3].x, v[p3].y, v[p3].z);
//	}
//	glEnd();
//	glFlush();
//}
//
//
//int main(int argc, char* argv[])
//{
//	readOff("models/cube.off");
//	auto& p = points;
//	auto& e = edges;
//	glutInit(&argc, argv);//对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次
//	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); //设置显示方式
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	glutInitWindowPosition(500, 100);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("图形学"); //根据前面设置的信息创建窗口。参数将被作为窗口的标题。
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glutDisplayFunc(&display);
//	glutMainLoop();
//
//}
