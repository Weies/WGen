//#include"WGen.h"
//
//const int seg = 30;
//
//int main() {
//	Render3D ren;
//	ren.setColor(vec3(1.0 , 0 , 0));
//	float max = 10.0f; float interval = 0.4f;
//	vector<pt> list;
//	for (float b = 0.0f; b < 2 * PI - 0.0001; b += PI / (seg / 2))
//	{
//		for (float a = 0.0f; a < 2 * PI - 0.0001; a += PI / (seg / 2))
//		{
//			list.push_back(pt(cos(b) * sin(a) , sin(a) * sin(b) , cos(a)));
//		}
//	}
//	ca.backward(100.0f);
//	canvas.setBGC(0 , 0 , 0);
//	FlatRender render;
//
//	//glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
//	//glEnable(GL_CULL_FACE);
//
//	const int sq = seg * seg;
//	mat4 model = mat4(1.0f);
//
//
//	main_win.loop([&]() {
//		/*int idx = 0;
//	ptr3.setColor(255 , 255 , 255);
//	glStart3(GL_TRIANGLES);
//	for (int i = 0; i < seg; i++) {
//		idx += 2;
//		ptr3.fillTriangle(list[i * seg] , list[i * seg + 1] , list[(i * seg + seg + 1) % (sq)]);
//		ptr3.fillTriangle(list[i * seg + seg / 2 - 1] , list[i * seg + seg / 2] , list[(i * seg + seg + seg / 2 - 1) % (sq)]);
//
//		for (int j = 1; j < seg / 2 - 1; j++) {
//			idx += 2;
//			ptr3.fillTriangle(list[i * seg + j] , list[i * seg + 1 + j] , list[(i * seg + seg + j) % sq]);
//			ptr3.fillTriangle(list[i * seg + 1 + j] , list[(i * seg + j + seg + 1) % sq] , list[(i * seg + seg + j) % sq]);
//		}
//	}
//	glOver3();
//	debug(idx);
//	render.renderList(ca.proj * ca.viewMat() , ca.mCameraPosition , vec3(0.7 , 0.4 , 0.2) , vec3(1.0 , 1.0 , 1.0));
//
//	ren.bind();
//	ptr3.setColor(0 , 255 , 0);
//	ptr3.drawLine({ 0,1000,0 } , { 0, -1000,0 });
//	ptr3.setColor(255 , 0 , 0);
//	for (float i = -max; i < max; i += interval) {
//		ptr3.drawLine(pt(-max , 0.0f , i) , pt(max , 0.0f , i));
//	}
//	ptr3.setColor(0 , 0 , 255);
//	for (float i = -max; i < max; i += interval) {
//		ptr3.drawLine({ i ,0.0f,-max } , { i,0.0f,max });
//	}
//	ptr3.setColor(255 , 255 , 255);
//	ptr3.drawLine(ca.mCameraPosition + vec3(0.01 , -0.01 , 0.0) , ca.mCameraPosition + ca.frontv * 1000.0f);*/
//
//		for (int i = 0; i < 10; i++) {
//			ptr3.setModel(translate(model , vec3(i , 0 , 0)));
//			ptr3.setColor(25.5 * i , 25.5 * i , 25.5 * i , 1.0);
//			ptr3.fillTriangle(vec3(1.0 , 1.0 , 0.0) , vec3(0.0 , 1.0 , 0.0) , vec3(0.0 , 0.0 , 0.0));
//			ptr3.fillTriangle(vec3(1.0 , 1.0 , 0.0) , vec3(1.0 , 0.0 , 0.0) , vec3(0.0 , 0.0 , 0.0));
//		}
//
//		ren.renderList(ca.proj * ca.viewMat());
//
//	});
//}