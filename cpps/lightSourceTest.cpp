//#include"WGen.h"
//
//MeshObject m;
//Cube cub;
//int main() {
//
//	LightSource l; l.moveto(vec3(0 , 0 , 4));//l.setShiness(1.2);
//	LightSource l1 = l; l1.moveto(vec3(0 , 4 , 0)); l1.setLightColor(0 , 1.0 , 0);
//	LightSource l2 = l; l2.moveto(vec3(4 , 0 , 0)); l2.setLightColor(0 , 0.0 , 1.0);
//	SpotLight s; s.moveto(vec3(4 , 4 , 0)); s.setLightDir(vec3(-4 , -4 , 0)); s.setShiness(1.8);
//	ParallelLight pa; pa.setLightColor(vec3(1 , 1 , 1));
//	m.init("offs/bunny.off");
//	m.scale(20);
//	ca.moveto(vec3(15 , 0 , 2));
//	PhongRender r;
//	Render3D ren;
//	canvas.showFrame();
//	m.setColor(255.0 , 255.0 , 255.0);
//	r.bindToMesh(m);
//
//	r.bindToLight(l); r.bindToLight(l1); r.bindToLight(l2);
//	r.bindToLight(s);
//	r.bindToLight(pa);
//	cub.scale(100 , 100 , 0.01); cub.setColor(210 , 210 , 210);
//
//	SkySphere sky;
//
//	CameraBlock b;
//
//	r.bind();
//
//	Texture tex; tex.genMipmap();
//	tex.setData(Image("imgs/sky.jpg"));
//
//	Texture tex2;
//	tex2.setData(Image("imgs/1.jpg"));
//	tex2.genMipmap();
//
//	canvas.setBGC(DARK);
//	canvas.setKeyFunc([=](ke& e) {
//		if (e->key == KEY_LEFT) {
//			m.translate(0 , -1 , 0);
//		}
//		if (e->key == KEY_RIGHT) {
//			m.translate(0 , 1 , 0);
//		}
//		if (e->key == KEY_UP) {
//			m.translate(0 , 0 , 1);
//		}
//		if (e->key == KEY_DOWN) {
//			m.translate(0 , 0 , -1);
//		}
//	});
//	//r.useTexture(false);
//	r.useTexture(true);
//
//	//glDepthMask(GL_FALSE);
//	glCullFace(GL_BACK);
//
//
//	main_win.loop([&]() {
//	//glDepthFunc(GL_LESS);
//	b = ca.getBlock();
//	r.bindToMesh(m);
//	r.renderMesh(b);
//
//
//	r.setCoordType(SPHERE_COORD);
//	r.bindToMesh(sky);
//	tex2.bindToShader(r.id , "text");
//	r.renderMesh(b);
//
//	r.setCoordType(CUBIC_COORD);
//	r.bindToMesh(cub);
//	tex.bindToShader(r.id , "text");
//	r.renderMesh(b);
//
//	//glDepthFunc(GL_ALWAYS);
//	r.renderLight(b);
//	ptr3.drawCoordinate(10 , 0.4);
//	ren.renderList(b.mPVTransform);
//			  });
//}