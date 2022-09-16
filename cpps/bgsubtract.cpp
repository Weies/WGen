//#include"WGen.h"
//
//int main() {
//	Texture tex1; Texture tex2;
//	tex1.setData(Image("imgs/cv/02.jpg"));
//	tex2.setData(Image("imgs/cv/02_bg.jpg"));
//	Shader shader; shader.parseShader("sub.shader");
//	tex1.bindToShader(shader , "tex1");
//	tex2.bindToShader(shader , "tex2");
//
//	float data[] = {
//	-1.0, -1.0,0.0,0.0,
//	-1.0, 1.0,0.0,1.0,
//	1.0, 1.0,1.0,1.0,
//	1.0, 1.0,1.0,1.0,
//	1.0, -1.0,1.0,0.0,
//	-1.0 ,-1.0,0.0,0.0
//	};
//
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
//
//	
//	main_win.loop([&]() {
//
//	glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER , vbo);
//	shader.use();
//	tex1.bindToShader(shader , "tex1");
//	tex2.bindToShader(shader , "tex2");
//	glDrawArrays(GL_TRIANGLES , 0 , 6);
//
//			  });
//}