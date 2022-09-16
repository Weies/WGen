//#include"WGen.h"
//Cube cub;
//ScrollBar bar;
//Shader my;
//Shader reff;
//
//int main() {
//
//	PhongRender phong;
//	cub.setColor(vec4(1.0 , 0.4 , 0.1 , 1.0));
//
//	SkyBox sky;
//
//	CameraBlock b;
//
//	my.parseShader("cubemap.shader");
//	reff.parseShader("reflectcube.shader");
//	glDepthFunc(GL_LEQUAL);
//
//	Cube cub; cub.moveto(vec3(3 , 3 , 0));
//
//	float rr = 0.8; bar.moveto(300 , 300);
//	bar.onscroll = [= , &rr](me& e) {
//		rr += deltaX * 0.001;
//		reff.setFloat("rr" , rr);
//	};
//	reff.setFloat("rr" , rr);
//
//	//ca.speed *= 50;
//	canvas.setBGC(DARK);
//
//	LightSource l; l.moveto(vec3(10 , 10 , 10.0)); l.setLightColor(1.0 , 1.0 , 1.0);
//	l.setEffectiveRange(30000); l.setShiness(1.0); l.scale(10.0f);
//	phong << l;
//
//	Render3D r3d;
//	ca.moveto(vec3(6 , 0 , 0));
//
//	main_win.loop([&]() {
//
//		b = ca.getBlock();
//		phong.setBlock(b);
//		reff.use();
//		sky.text.bindToShader(reff.id , "texture_cubemap1" , 2);
//		reff.setMat4("transform" , b.mPVTransform);
//		reff.setMat4("model" , mat4(1.0));
//		reff.setVec3("viewPos" , b.mCameraPosition);
//		cub.draw(reff.id);
//
//		my.setMat4("transform" , b.mPVTransform * sky.model);
//		sky.draw(my.id);
//		ptr3.drawCoordinate();
//		r3d.renderList(b.mPVTransform);
//	});
//}
