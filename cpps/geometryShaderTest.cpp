//#include"WGen.h"
//
//#include"stbi/stb_image.h"
//#include"stbi/stb_image_resize.h"
//
//mat4 model = scale(mat4(1.0f) , 0.1f);
//Cube cub;
//
//ScrollBar bar;
//Shader my;
//Shader reff;
//
//int main() {
//
//	PhongRender phong;
//	cub.setColor(vec4(1.0 , 0.4 , 0.1 , 1.0));
//	canvas.showFrame();
//
//	uint textsky;
//	glGenTextures(1 , &textsky);
//	glActiveTexture(textsky);
//	glBindTexture(GL_TEXTURE_CUBE_MAP , textsky);
//
//	int width , height , nrChannels;
//	unsigned char* data;
//	string textures[6] = {
//		"right.jpg" , "left.jpg",
//		"top.jpg"   , "bottom.jpg",
//		"front.jpg" , "back.jpg"
//	};
//	for (unsigned int i = 0; i < 6; i++)
//	{
//		data = stbi_load(("imgs/skybox/" + textures[i]).c_str() , &width , &height , &nrChannels , 0);
//		glTexImage2D(
//			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i ,
//			0 , GL_RGB , width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , data
//		);
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_R , GL_CLAMP_TO_EDGE);
//
//	float cubeVertices[] = {
//		// positions          // normals
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//	};
//
//	uint vao; uint vbo;
//	glGenVertexArrays(1 , &vao);
//	glBindVertexArray(vao);
//	glGenBuffers(1 , &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER , vbo);
//	glBufferData(GL_ARRAY_BUFFER , sizeof(cubeVertices) , cubeVertices , GL_STATIC_DRAW);
//	glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 6 * 4 , 0);
//	glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 6 * 4 , (void*)12);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//
//
//	CameraBlock b;
//	mat4 model = scale(mat4(1.0) , 0.1f);
//
//	my.parseShader("cubemap.shader");
//	reff.parseShader("ref_geo.shader" , true);
//	//glActiveTexture(textsky);
//	glBindTexture(GL_TEXTURE_CUBE_MAP , textsky);
//	glDepthFunc(GL_LEQUAL);
//
//	Cube cub;
//
//	Model mo("models/objs/nanosuit.obj");
//	mat4 mi = scale(mat4(1.0) , 0.1f);
//	auto& mod = mi;
//	mat4 board = scale(mat4(1.0) , vec3(10 , 10 , 0.1));
//
//	float rr = 0.8; bar.moveto(400 , 300);
//	bar.onscroll = [= , &rr](me& e) {
//		rr += deltaX * 0.001;
//		reff.setFloat("rr" , rr);
//	};
//
//	reff.setFloat("rr" , rr);
//	float val = 0.0;
//	Shader ms;
//	ms.parseShader("loader.shader");
//	//glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
//
//	my.use();
//	glBindVertexArray(vao);
//	GLuint ivbo;
//	glGenBuffers(1 , &ivbo);
//	glBindBuffer(GL_ARRAY_BUFFER , ivbo);
//	vec3 npos[10000];
//	for (int i = 0; i < 10000; ++i) {
//		npos[i].rand(-500 , 500);
//	}
//	glBufferData(GL_ARRAY_BUFFER , sizeof(vec3) * 10000 , npos , GL_STATIC_DRAW);
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);
//	glVertexAttribDivisor(2 , 1);
//
//	main_win.loop([&]() {
//
//	b = ca.getBlock();
//	glBindBuffer(GL_ARRAY_BUFFER , vbo); glBindVertexArray(vao);
//	//ms.use();
//	//ms.setMat4("transform" , b.mPVTransform* mod);
//	//ms.setMat4("model" , mod);
//	//ms.setVec3("viewPos" , b.mCameraPosition);
//	//mo.Draw(ms.id);
//
//	reff.use();
//	reff.setMat4("transform" , b.mPVTransform * mod);
//	reff.setMat4("model" , mod);
//	reff.setVec3("viewPos" , b.mCameraPosition);
//	reff.setFloat("time" ,val += 0.001);
//	mo.Draw(reff.id);
//	//phong.bindToMesh(cub);
//	//phong.renderMesh(b);
//	//glDrawArrays(GL_TRIANGLES , 0 , 36);
//
//	drawString(20 , win_h - 100 , to_string(rr));
//	my.use(); my.setMat4("transform" , b.mPVTransform * model);
//
//	//my.setInt("cube" , textsky);
//	glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER , vbo);
//	glDrawArraysInstanced(GL_TRIANGLES , 0 , 36,10000);
//			  });
//}