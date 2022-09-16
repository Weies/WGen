//#include"WGen.h"
//
//#include"stbi/stb_image.h"
//#include"stbi/stb_image_resize.h"
//
//mat4 model = scale(mat4(1.0f) , 0.1f);
//Cube cub;
//ScrollBar bar; Shader my;
//
//int main() {
//
//	PhongRender phong;
//	cub.setColor(vec4(1.0 , 0.4 , 0.1 , 1.0));
//	canvas.showFrame();
//	
//	//创建一个帧缓冲对象，帧缓冲对象包括三部分
//	uint fbo;
//	glGenFramebuffers(1 , &fbo);
//	glBindFramebuffer(GL_FRAMEBUFFER , fbo);
//
//	//创建一个纹理缓冲
//	uint text;
//	glGenTextures(1 , &text);
//	glActiveTexture(GL_TEXTURE0 + text);
//	glBindTexture(GL_TEXTURE_2D , text);
//	//分配空间但不给予数据
//	glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGB , 800 , 600 , 0 , GL_RGB , GL_UNSIGNED_BYTE , NULL);
//	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
//
//
//	//为帧缓冲依附颜色缓冲
//	glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D , text , 0);
//
//	//创建渲染对象
//	uint rbo;
//	glGenRenderbuffers(1 , &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER , rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER , GL_DEPTH24_STENCIL8 , 800 , 600);
//
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER , GL_DEPTH_STENCIL_ATTACHMENT , GL_RENDERBUFFER , rbo);
//
//	float data[] = {
//		-1.0, -1.0,0.0,0.0,
//		-1.0, 1.0,0.0,1.0,
//		1.0, 1.0,1.0,1.0,
//		1.0, 1.0,1.0,1.0,
//		1.0, -1.0,1.0,0.0,
//		-1.0 ,-1.0,0.0,0.0
//	};
//	uint vao; uint vbo;
//	glGenVertexArrays(1 , &vao);
//	glBindVertexArray(vao);
//	glGenBuffers(1 , &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER , vbo);
//	glBufferData(GL_ARRAY_BUFFER , sizeof(data) , data , GL_STATIC_DRAW);
//	glVertexAttribPointer(0 , 2 , GL_FLOAT , GL_FALSE , 16 , 0);
//	glVertexAttribPointer(1 , 2 , GL_FLOAT , GL_FALSE , 16 , (void*)8);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	my.parseShader("sample.shader");
//	my.setInt("text" , text);
//	//glEnable(GL_FRAMEBUFFER_SRGB);
//	Model m("models/objs/Nanosuit.obj");
//	LightSource l; l.moveto(vec3(0 , 0 , 4)); l.setShiness(20.8); l.setLightColor(1.0 , 1.0 , 1.0);
//	LightSource l1 = l; l1.moveto(vec3(0 , 4 , 0)); l1.setLightColor(1.0 , 1.0 , 1.0); l1.setShiness(20.8);
//	LightSource l2 = l; l2.moveto(vec3(4 , 0 , 0)); l2.setLightColor(1.0 , 1.0 , 1.0); l2.setShiness(20.8);
//	SpotLight s; s.moveto(vec3(4 , 4 , 0)); s.setLightDir(vec3(-4 , -4 , 0)); s.setShiness(20.8);
//	s.setLightColor(1.0 , 1.0 , 1.0);
//	ParallelLight pa; pa.setLightColor(vec3(1 , 1 , 1)); pa.setLightColor(1.0 , 1.0 , 1.0);
//	//pa.setShiness(10);
//	auto& r = phong;
//	r.bindToLight(l); r.bindToLight(l1); r.bindToLight(l2);
//	r.bindToLight(s);
//	r.bindToLight(pa);
//	phong.setInt("light_num" , phong.lts.size());
//
//	//canvas.setBGC(Color(100 , 100 , 100 , 1.0));
//	//glReadPixels(0,0,800,600,)
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
//		debug << "ok";
//	}
//	else debug << "false";
//
//	CameraBlock b;
//	mat4 model = scale(mat4(1.0) , 0.1f);
//	glActiveTexture(GL_TEXTURE0 + text);
//	float rr = 5.0;
//	bar.onscroll = [= , &rr](me& e) {
//		rr += deltaX * 0.025;
//		my.setFloat("contrast" , rr);
//	};
//
//	my.setFloat("contrast" , rr);
//
//	canvas.setBGC(DARK);
//
//	main_win.loop([&]() {
//
//	drawString(bar.pos.x - font.testWidth(to_string(rr)) / 2 , bar.pos.y - 60 , to_string(rr));
//	b = ca.getBlock();
//	phong.setState(RENDER_MESH);
//	glBindFramebuffer(GL_FRAMEBUFFER , fbo);
//	glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//	phong.use();
//	phong.setTransformM(b.mPVTransform * model);
//	phong.setModelM(model);
//	m.Draw(phong.id);
//	phong.renderLight(b);
//	debug.flush();
//	glDisable(GL_DEPTH_TEST);
//
//	glBindFramebuffer(GL_FRAMEBUFFER , 0);
//	my.use();
//	glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER , vbo);
//	glActiveTexture(GL_TEXTURE0 + text);
//	glBindTexture(GL_TEXTURE_2D , text);
//	glDrawArrays(GL_TRIANGLES , 0 , 6);
//
//
//			  });
//}