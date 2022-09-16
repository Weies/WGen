//#include"WGen.h"
//#include<fstream>
//float datas[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//};
//
//int main()
//{
//	canvas.setStickScale();
//	VAOBuffer vao;
//	VBOBuffer vbo;
//	vbo.setData(sizeof(datas) , datas);
//	vbo.setAttribPointer(0 , 3 , 6 * sizeof(float) , 0);
//	vbo.setAttribPointer(1 , 3 , 6 * sizeof(float) , (void*)12);
//	Texture tex;
//	tex.setData(Image("1.jpeg"));
//	//tex.bindToShader(ca.shader, "texture1");
//	//tex.active(1);
//	canvas.showFrame();
//	canvas.setBGC(20 , 20 , 20);
//	ca.speed *= 3;
//	float plane[] = {
//		-2.0f,-2.0f,-5.0f,0.,0.0,1.0f,
//		2.0f,2.0f,-5.0f,0.,0.0,1.0f,
//		2.0f,0.0f,-5.0f,0.,0.0,1.0f,
//
//		-2.0f,-2.0f,-5.0f,0.,0.0,1.0f,
//		2.0f,2.0f,-5.0f,0.,0.0,1.0f,
//		0.0f,2.0f,-5.0f,0.,0.0,1.0f
//	};
//	canvas.setMouseStick([=](me& e) {
//		if (e->mBtn == GLFW_MOUSE_BUTTON_LEFT)
//		{
//			ca.forward(0.2);
//		}
//		else ca.backward(0.2);
//	});
//	VAOBuffer vao2;
//	VBOBuffer vbo2;
//	vbo2.setData(sizeof(plane) , plane);
//	vbo2.setAttribPointer(0 , 3 , 6 * sizeof(float) , 0);
//	vbo2.setAttribPointer(1 , 3 , 6 * sizeof(float) , (void*)12);
//
//
//	main_win.loop([&]() 
//		{
//			vao.bind();
//			tex.bind();
//			ca.uniform();//统一观察矩阵
//			ca.shader.setVec3("lightColor", vec3(1.0, 0.2, 0.3));//光源颜色
//			ca.shader.setVec3("lightPos", vec3(0.2, 0, -3.0));//光源位置
//			ca.shader.setVec3("viewPos", ca.mCameraPosition);
//			
//			vbo.bind();
//			//绘制方块
//			ca.setModel(translate(mat4(1.0), vec3(0, 0, -5.0f)));
//			ca.shader.setVec3("objectColor", vec3(0.8, 0.7, 0.0));
//			vbo.bind();
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//
//			//绘制光源
//			mat4 m(1.0f);
//			m = translate(m, vec3(0.2, 0, -3.0));
//			m = scale(m, vec3(0.2, 0.2, 0.2));
//			ca.setModel(m);
//			ca.shader.setVec3("objectColor", vec3(1.0, 1.0, 1.0));
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//			ca.shader.setVec3("objectColor", vec3(0.25,0.25,1.0));
//			ca.setModel(mat4(1.0f));
//			vao2.bind();
//			vbo2.bind();
//			glDrawArrays(GL_TRIANGLES, 0, 6);
//		}
//	);
//}