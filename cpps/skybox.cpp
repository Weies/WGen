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
//	glEnable(GL_MULTISAMPLE);
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
//	mat4 model = scale(mat4(1.0) , 2000.0f);
//
//	my.parseShader("cubemap.shader");
//	reff.parseShader("reflectcube.shader");
//	//glActiveTexture(textsky);
//	glBindTexture(GL_TEXTURE_CUBE_MAP , textsky);
//	glDepthFunc(GL_LEQUAL);
//
//	Cube cub;
//
//	MeshModel mo("models/objs/nanosuit.obj");
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
//
//	main_win.loop([&]() {
//
//	b = ca.getBlock();
//	reff.use(); glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER , vbo);
//	reff.setMat4("transform" , b.mPVTransform * mod);
//	glActiveTexture(GL_TEXTURE2);
//	glBindTexture(GL_TEXTURE_CUBE_MAP,textsky);
//	reff.setInt("texture_cubemap1" , 2);
//	reff.setMat4("model" , mod);
//	reff.setVec3("viewPos" , b.mCameraPosition);
//	mo.draw(reff.id);
//	//phong.bindToMesh(cub);
//	//phong.renderMesh(b);
//	//glDrawArrays(GL_TRIANGLES , 0 , 36);
//
//	drawString(20 , win_h - 100 , to_string(rr));
//	my.use(); my.setMat4("transform" , b.mPVTransform * model);
//	my.setInt("texture_cubemap1" , 2);
//	glBindBuffer(GL_ARRAY_BUFFER , vbo);
//	glBindVertexArray(vao);
//	glDrawArrays(GL_TRIANGLES , 0 , 36);
//		});
//}