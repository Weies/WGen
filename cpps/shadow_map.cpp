//#include"WGen.h"
//
//
//int main() {
//
//	Cube c;
//	c.scale(100 , 0.1 , 100);
//	PhongRender ren;
//	MeshObject moo; moo.loadModel("models/objs/nanosuit.obj");
//	moo.translate(vec3(4 , 4 , 0.2));
//	moo.scale(0.1); moo.rotate(240 , vec3(0 , 0 , 1));
//	ca.speed *= 2;
//	c.setColor(vec4(1.0 , 1.0 , 1.0 , 1.0));
//	LightSource l; l.moveto(vec3(0 , 0 , 3.0)); l.setLightColor(1.0 , 1.0 , 1.0);
//	LightSource l1 = l; l1.moveto(vec3(1 , 4 , 1)); l1.setLightColor(1.0 , 1.0 , 1.0);
//	LightSource l2 = l; l2.moveto(vec3(4 , 1 , 1)); l2.setLightColor(1.0 , 1.0 , 1.0);
//	SpotLight s; s.moveto(vec3(6 , 6 , 3.0)); s.setLightDir(vec3(0 , 0 , -1));
//	s.setLightColor(1.0 , 1.0 , 1.0);
//
//	l.setEffectiveRange(30000); l.setShiness(1.0); l.scale(1.0f);
//	l.setShiness(1.0);
//	ParallelLight pl;
//	ren << l << pl << l1 << l2 << s;
//
//	ren.setInt("light_num" , ren.lts.size());
//	canvas.setBGC(0 , 0 , 0 , 1.0);
//	Cube cub;
//	cub.translate(vec3(100.0 , 100.0 , 00.0)); cub.scale(40);
//	Cube cub1;
//	cub1.translate(vec3(3.0 , 4.8 , 1.0));
//	Cube cub2;
//	cub2.translate(vec3(1.0 , 2.0 , 0.5));
//	ca.moveto(vec3(3 , 3 , 1));
//	canvas.showFrame();
//
//	uint width = 8024; uint height = 8024;
//	FBOBuffer fbo;
//	Texture depth(GL_TEXTURE_2D);
//	depth.setVoid(GL_DEPTH_ATTACHMENT , width , height , GL_FLOAT);
//
//	fbo.attach(GL_DEPTH_ATTACHMENT , depth);
//	fbo.noColorBuffer();
//
//	mat4 view = lookAt<float>(l.getLightPos() , vec3(5 , 5 , 0) , vec3(0 , 0 , 1));
//	mat4 proj = ortho<float>(-5.0 , 5.0 , -5.0 , 5.0 , 0.0 , 20.0);
//	Shader d_shader; d_shader.parseShader("depth.shader");
//	d_shader.setMat4("pv_mat" , proj * view);
//
//	CameraBlock b;
//
//	ren.setInt("shadow" , depth.id);
//	ren.setMat4("ltTrans" , proj * view);
//
//
//	//Basic3DObject* p = &moo;
//	//canvas.setKeyFunc([=](ke& e) {
//	//	if (e->key == KEY_LEFT) {
//	//		p->translate(vec3(0 , -1 , 0));
//	//	}
//	//	if (e->key == KEY_RIGHT) {
//	//		p->translate(vec3(0 , 1 , 0));
//	//	}
//	//	if (e->key == KEY_UP) {
//	//		p->translate(vec3(0 , 0 , 1));
//	//		//model = translate(model , vec3(0 , 1 , 0));
//	//	}
//	//	if (e->key == KEY_DOWN) {
//	//		p->translate(vec3(0 , 0 , -1));
//	//	}
//	//});
//
//	cub.addTexture("imgs/brickwall_normal.jpg" , texture_height , -1);
//	cub.addTexture("imgs/brickwall.jpg" , texture_diffuse , -1);
//	c.addTexture("imgs/brickwall_normal.jpg" , texture_height , -1);
//	c.addTexture("E:/Learnnotes/CG/WGen/imgs/brickwall.jpg" , texture_diffuse , -1);
//	cub1.addTexture("imgs/brickwall_normal.jpg" , texture_height , -1);
//	cub1.addTexture("imgs/brickwall.jpg" , texture_diffuse , -1);
//	cub2.addTexture("imgs/brickwall_normal.jpg" , texture_height , -1);
//	cub2.addTexture("E:/Learnnotes/CG/WGen/imgs/brickwall.jpg" , texture_diffuse , -1);
//
//	glViewport(0 , 0 , width , height);
//
//	fbo.bind();
//	glClear(GL_DEPTH_BUFFER_BIT);
//	glActiveTexture(GL_TEXTURE0);
//	depth.bind();
//
//	Basic3DObject* p = &cub;
//	d_shader.setMat4("model" , p->model);
//	p->draw(d_shader.id);
//
//	p = &cub2;
//	d_shader.setMat4("model" , p->model);
//	p->draw(d_shader.id);
//
//	p = &cub1;
//	d_shader.setMat4("model" , p->model);
//	p->draw(d_shader.id);
//
//	p = &c;
//	d_shader.setMat4("model" , p->model);
//	p->draw(d_shader.id);
//
//	p = &moo;
//	d_shader.setMat4("model" , p->model);
//	p->draw(d_shader.id);
//
//	glViewport(0 , 0 , win_w , win_h);
//	fbo.zero();
//
//	main_win.loop([&]() {
//
//	b = ca.getBlock();
//	ren.setBlock(b);
//	depth.bindToShader(ren.id , "shadow" , 0);
//	ren << cub << cub2 << cub1 << c << moo;
//	ren.renderLight(b);
//
//		});
//}
//
