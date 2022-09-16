//#include"WGen.h"
//
//float dx = 0.01;
//Sphere m(36);
//MeshObject bunny;
//Tetrahedron t;
////Cube c;
////Cube c1;
//auto& o = m;
//
//int main()
//{
//	bunny.init("offs/bunny.off");
//	bunny.scale(10 , 10 , 10);
//	canvas.showFrame();
//
//	PhongRender render;
//	Render3D rend3;
//	using pt = point<float>;
//	float max = 10.0f; float interval = 0.5f;
//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POLYGON_SMOOTH);
//	o.setColor(Color(255 , 125 , 42));
//
//	LightSource light(36);
//	light.scale(10);
//	light.setLightColor(vec3(1.0 , 0.4 , 0.2));
//	t.setColor(Color(255.0 , 0 , 0));
//	light.moveto(vec3(40.0 , 1.0 , 5.0));
//
//	canvas.setKeyFunc([=](ke& e) {
//		if (e->key == KEY_G) {
//			o.LoopTessellate();
//		}
//		if (e->key == KEY_F) {
//			o.simplify();
//		}
//	});
//
//	canvas.setBGC(DRAK);
//
//	render.bindToLight(light);
//	CameraBlock b;
//
//	bool show = false;
//	m.setColor(Color(255 , 125 , 100));
//
//	main_win.loop([&]() {
//
//	b = ca.getBlock();
//	//debug << toString(b.mPVTransform);
//	glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
//
//	//render.setLightPos(b.mCameraPosition);
//	render.bindToMesh(o);
//	render.renderMesh(b);
//	//render.bindToMesh(m);
//	//render.renderMesh(b);
//	/*render.bindToMesh(t);
//	render.renderMesh(b);*/
//	//render.bindToMesh(c);
//	//render.renderMesh(b);
//	render.renderLight(b);
//	ptr3.drawCoordinate(max , interval);
//	rend3.renderList(b.mPVTransform);
//
//			  });
//}
