//#include"WGen.h"
//
//MeshPatch m;
//
//int main() {
//	SkyBox box; Sphere sp;
//	sp.addTexture("asset/pbr/albedo.png", texture_diffuse, -1);
//	sp.addTexture("asset/pbr/metallic.png", texture_diffuse, -1);
//	sp.addTexture("asset/pbr/roughness.png", texture_diffuse, -1);
//	sp.addTexture("asset/pbr/normal.png", texture_diffuse, -1);
//	float metallic = 0.5; float roughness = 0.5;
//	/*ScrollBar bar1;
//	ScrollBar bar2;
//	bar1.onscroll = [&](me& e) {
//		metallic = bar1.val;
//	};
//	bar2.onscroll = [&](me& e) {
//		roughness = bar2.val;
//	};*/
//	const float shine = 1600;
//	vec3 lightPos[4] = { {10.5,20.8,3.7},{80.5,20.8,-3.7},{10.5,29.8,30.7},{10.5,2.8,-60.7} };
//	vec3 lightColor[4] = { vec3(shine),vec3(shine),vec3(shine),vec3(shine) };
//
//	Shader sh;
//	sh.parseShader("source/shader/pbr.shader");
//	sh.setFloat("ao", 1.0);
//	glUniform3fv(glGetUniformLocation(sh.id, "lightPos"), 4, value_ptr(lightPos[0]));
//	glUniform3fv(glGetUniformLocation(sh.id, "lightColor"), 4, value_ptr(lightColor[0]));
//
//
//	CameraBlock b;
//	//ca.mSpeed = 5.0;
//	PhongRender phong;
//
//	main_win.loop([&]() {
//		b = ca.getBlock();
//		phong.setBlock(b);
//		sh.setMat4("transform", b.mPVTransform * sp.mModelTransform);
//		sh.setMat4("model", sp.mModelTransform);
//		sh.setVec3("camPos", b.mCameraPosition);
//		sp.mTextures[0].bindToShader(sh.id, "albedo_t", 1);
//		sp.mTextures[1].bindToShader(sh.id, "metallic_t", 2);
//		sp.mTextures[2].bindToShader(sh.id, "roughness_t", 3);
//		sp.mTextures[3].bindToShader(sh.id, "normal_t", 4);
//
//		sp.draw(sh.id);
//		phong << box;
//
//		});
//}