//#include"WGen.h"
//
//float dx = 0.01;
//Sphere m;
//MeshObject bunny;
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
//	float max = 200.0f; float interval = 4.0f;
//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POLYGON_SMOOTH);
//	/*glHint(GL_LINE_SMOOTH_HINT , GL_NICEST);
//	glHint(GL_POLYGON_SMOOTH_HINT , GL_NICEST);*/
//
//	glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
//
//	LightSource light(108);
//
//	light.setLightColor(vec3(1.0 , 0.4 , 0.2));
//	light.moveto(vec3(0.0 , 1.0 , 100.0));
//	ca.moveto(0 , 0.5 , 2.5);
//
//	Texture tex;
//	tex.bindToShader(render.id , "text");
//	tex.setData(Image("imgs/earth.jpg"));
//	tex.active();
//	canvas.setKeyFunc([=](ke& e) {
//		if (e->key == KEY_F) {
//			bunny.tessellate();
//		}
//	});
//	debug(tex.id);
//	
//	m.moveto({ 0 , 1 , 0 });
//	canvas.setBGC(0 , 0 , 0);
//	light.scale(1000 , 1000 , 1000);
//
//	main_win.loop([&]() {
//	tex.bind();
//	render.bindToLight(light);
//	render.renderLight(ca.getBlock());
//	render.useTexture(1);
//	render.bindToMesh(m);
//	render.renderMesh(ca.getBlock());
//	//render.bindToMesh(bunny);
//	//render.renderMesh(ca.getBlock());
//
//	ptr3.drawCoordinate(max , interval);
//	ptr3.setColor(255 , 255 , 255);
//	ptr3.drawLine(ca.mCameraPosition + vec3(0.01,-0.01,0.0) , ca.mCameraPosition + ca.frontv * 1000.0f);
//	rend3.renderList(ca.proj * ca.viewMat());
//			  });
//}
