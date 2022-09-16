//#include"WGen.h"
//#include"stdShaders.h"
//MeshObject mesh;
//MeshObject mesh1;
//MeshObject mesh2;
//int p = 0;
//
//int main()
//{
//	canvas.showFrame();
//	ptr3.setColor({ 125,155,255 });
//
//	mesh.init("offs/bunny.off");
//	mesh1.init("offs/bumpy.off");
//	//mesh2.init("offs/cube.off");
//	mesh.setModel(scale(mat4(1.0f) , vec3(1.85 , 1.85 , 1.85)));
//	mesh1.setModel(translate(scale(mat4(1.0f) , vec3(0.05 , 0.05 , 0.05)) , vec3(10.0 , 0 , 0.0)));
//	//mesh2.setModel(translate(scale(mat4(1.0f) , vec3(0.15 , 0.15 , 0.15)) , vec3(-6.0 , 0 , 0.0)));
//	glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
//	LightSource light;
//
//	PhongRender render;
//	
//	main_win.loop([&]() {
//	render.bindToMesh(mesh);
//	render.bindToLight(light);
//	render.renderMesh(ca.getBlock());
//			  });
//}