//#include"WGen.h"
//using namespace glm;
//using namespace std;
//
//float datas[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//};
//
//int main(void)
//{
//	gm::vec3 cubePositions[] = {
//		gm::vec3(0.0f,  0.0f,  0.0f),
//		gm::vec3(2.0f,  5.0f, -15.0f),
//		gm::vec3(-1.5f, -2.2f, -2.5f),
//		gm::vec3(-3.8f, -2.0f, -12.3f),
//		gm::vec3(2.4f, -0.4f, -3.5f),
//		gm::vec3(-1.7f,  3.0f, -7.5f),
//		gm::vec3(1.3f, -2.0f, -2.5f),
//		gm::vec3(1.5f,  2.0f, -2.5f),
//		gm::vec3(1.5f,  0.2f, -1.5f),
//		gm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//	VAOBuffer vao; VBOBuffer vbo;
//	//VBO管理在GPU上的数据
//	vbo.setData(sizeof(datas) , datas);
//	//索引（location），一个点的长度，步长，偏移
//
//	Image img1("imgs/1.jpeg");
//	Image img2("imgs/2.jpg");
//
//	Texture text1;
//	text1.active(1);
//	text1.setData(img1);
//	text1.bindToShader(ca.shader , "texture1");
//
//	Texture text2;
//	text2.active(2);
//	text2.setData(img2);
//	text2.bindToShader(ca.shader , "texture2");
//	img1.free();
//	img2.free();
//	mat4 start(1.0);
//	canvas.setWindowSize(800 , 800);
//	canvas.showFrame();
//	text1.bind();
//	float dats[] = {
//		-10000, 0,    0,   10000,   1,   1,
//		 0,     0, -10000,    1 ,   1, 10000,
//		 0,  -10000, 0,     1,   10000, 1
//	};
//
//	VBOBuffer vbo1;
//	vbo1.setData(6 * 3 * 4 , dats);
//	ca.speed = 0.5;
//
//	//timer(50, [=]() {
//	//	//ca.down(1.0);
//	//});
//	vbo.setAttribPointer(0 , 3 , 5 * sizeof(float) , 0);
//	vbo.setAttribPointer(1 , 2 , 5 * sizeof(float) , (void*)12);
//	main_win.loop([&]() {//while循环中的内容
//				vao.bind();
//				ca.use();//VAO不包含texture的数据
//				vbo.bind();
//				text1.bind();//只需要绑定texture和VAO即可
//				for (int i = 0; i < 10; i++)
//				{
//					mat4 model = start;
//					model = translate(model, cubePositions[i]);
//					model = rotate(model, radians(36.0f * i), vec3(1.0, 1.0, 0));
//					ca.uniform();
//					ca.setModel(model);
//					glDrawArrays(GL_TRIANGLES, 0, 36);//点的数量
//				}
//				vbo1.setAttribPointer(0, 3, 3 * 4, 0);
//				glDrawArrays(GL_LINES, 0, 6);
//				//ca.shader.setVec4();
//
//			  });
//
//	glfwTerminate();
//	return 0;
//}