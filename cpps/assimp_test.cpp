//#include"WGen.h"
//
//mat4 model = scale(mat4(1.0f) , 0.1f);
//Cube cub;
//int main() {
//
//	Model m("models/objs/Nanosuit.obj");
//
//	PhongRender phong;
//	Render3D rr;
//	//canvas.setBGC(DARK);
//	CameraBlock b;
//
//	LightSource l; l.moveto(vec3(0 , 0 , 4));//l.setShiness(1.2);
//	LightSource l1 = l; l1.moveto(vec3(0 , 4 , 0)); l1.setLightColor(0 , 1.0 , 0);
//	LightSource l2 = l; l2.moveto(vec3(4 , 0 , 0)); l2.setLightColor(0 , 0.0 , 1.0);
//	SpotLight s; s.moveto(vec3(4 , 4 , 0)); s.setLightDir(vec3(-4 , -4 , 0)); s.setShiness(1.2);
//	ParallelLight pa; pa.setLightColor(vec3(1 , 1 , 1));
//
//	//LightSource l; l.moveto(vec3(0 , 0 , 4));//l.setShiness(1.2);
//	//LightSource l1 = l; l1.moveto(vec3(0 , 4 , 0)); l1.setLightColor(1 , 1.0 , 1);
//	//LightSource l2 = l; l2.moveto(vec3(4 , 0 , 0)); l2.setLightColor(1 , 1.0 , 1.0);
//	//SpotLight s; s.moveto(vec3(4 , 4 , 0)); s.setLightDir(vec3(-4 , -4 , 0)); s.setShiness(3);
//	//s.setLightColor(1 , 1 , 1);
//	//ParallelLight pa; pa.setLightColor(vec3(1 , 1 , 1));
//	auto& r = phong;
//	r.bindToLight(l); r.bindToLight(l1); r.bindToLight(l2);
//	r.bindToLight(s);
//	r.bindToLight(pa);
//	phong.setInt("light_num" , phong.lts.size());
//
//
//	b = ca.getBlock();
//	//glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
//
//	canvas.setKeyFunc([=](ke& e) {
//		if (e->key == KEY_LEFT) {
//			model = translate(model , vec3(-1 , 0 , 0));
//		}
//		if (e->key == KEY_RIGHT) {
//			model = translate(model , vec3(1 , 0 , 0));
//		}
//		if (e->key == KEY_UP) {
//			cub.translate(0 , 0 , 1);
//			//model = translate(model , vec3(0 , 1 , 0));
//		}
//		if (e->key == KEY_DOWN) {
//			model = translate(model , vec3(0 , -1 , 0));
//		}
//	});
//	glEnable(GL_STENCIL_TEST);
//	Shader my; my.parseShader("singleColor.shader");
//
//	glViewport(200 , 200 , 400 , 400);
//	glEnable(GL_CULL_FACE);
//	//glCullFace(GL_FRONT);
//	canvas.showFrame();
//	main_win.loop([&]() {
//		glClear(GL_STENCIL_BUFFER_BIT);
//		glStencilFunc(GL_ALWAYS , 1 , 0xff);
//		glStencilMask(0xff);
//		glStencilOp(GL_KEEP , GL_KEEP , GL_REPLACE);
//		b = ca.getBlock();
//		phong.bind();
//		phong.setState(RENDER_MESH);
//		phong.bindToMesh(cub);
//		phong.renderMesh(b);
//		my.use();
//		glDisable(GL_DEPTH_TEST);
//		glStencilFunc(GL_ALWAYS , 1 , 0xff);
//		my.setMat4("transform" , b.mPVTransform * scale(cub.model , vec3(1.1)));
//		glDrawElements(GL_TRIANGLES , cub.getFaceNum() * 3 , GL_UNSIGNED_INT , 0);
//		glEnable(GL_DEPTH_TEST);
//
//		phong.renderLight(b);
//		ptr3.drawCoordinate();
//		rr.renderList(b.mPVTransform);
//	});
//}