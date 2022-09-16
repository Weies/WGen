//#include"WGen.h"
//#include"collision_dectect.h"
//#include"Importer.h"
//#include<io.h>
//MeshObject anim;
//MeshObject tmp;
//PhongRender phong;
//Render3D ren;
//Importer imp;
//int main() {
//
//	imp.Import(tmp, "models/yuan/ying/anim/Snake Hip Hop Dance.fbx");
//
//	//anim.readDRO("models/yuan/ying/ying.dro");
//	//float hi = -anim.jos[0].off_set.t.y;
//	//for (int i = 0; i < 39/*anim.anims.size()*/; ++i) {
//	//	auto& an = anim.anims[i];
//	//	float fa = hi / an.chans[an.id[0]].poss[0].v.y;
//	//	for (int j = 0; j < an.chans.size(); ++j) {
//	//		auto& p = an.chans[j].poss;
//	//		for (int k = 0; k < p.size(); ++k) {
//	//			p[k].v *= 1 / 1.13;
//	//		}
//	//	}
//	//}
//
//	//anim.makeAnimDRO("models/yuan/ying/ying.droa");
//	//Button bn("1"); int cur = 0;
//	//bn.onclick = [&](me& e)->bool {
//	//	cur = (cur + 1) % anim.anims.size();
//	//	/*if (cur % 2)anim.play(14, 0.2);
//	//	else anim.play(43, 0.2);*/
//	//	anim.play(cur, 0.2);
//	//	bn.setText(itos(cur));
//	//	return true;
//	//};
//	//phong.addLights();
//	//ca.moveto(3, 3, 3);
//	//ca.lookTo({ 0, 0, 0 });
//
//	//anim.play(0, 0.2);
//
//	main_win.loop([&]() {
//		phong.setBlock(ca.getBlock());
//		ptr3.drawCoordinate();
//		//ptr3.drawLine(vec3(), qs[int(tt += 0.1) % qs.size()].rotate(vec3(0, 0, 1)));
//		phong << anim;
//		ren.renderList(ca.getBlock());
//
//		});
//}
//
//
////vector<string> getFileList(string dir)
////{
////	intptr_t handle; _finddata_t findData;
////	if (dir.find('*') == string::npos)dir += "/*";
////	handle = _findfirst(dir.c_str(), &findData);    // 查找目录中的第一个文件
////	if (handle == -1)return {};
////	vector<string> ret;
////	do
////	{	//判断是否是是目录,并且不为"."或".."
////		if (findData.attrib & _A_SUBDIR
////			|| strcmp(findData.name, ".") == 0
////			|| strcmp(findData.name, "..") == 0);
////		else ret.push_back(findData.name);// << "\t" << findData.size << endl;	
////	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
////	_findclose(handle);    // 关闭搜索句柄
////	return ret;
////}
//
////Importer imp;
////imp.Import(ying, "models/yuan/ying/ying.pmx");
////ying.nBones = 0;
////ying.jos.jo.resize(0);
////phong.addLights();
//////imp.Export(ying, "models/yuan/ying/ying.obj", utf8);
////imp.Import(anim, "models/yuan/ying/dance.fbx", Triangulate | GenNormals | JoinIdenticalVertices);
////for (int i = 0; i < anim.meshes.size(); ++i) {
////	anim.meshes[i].name = ying.meshes[i].name;
////	anim.meshes[i].addTexture(*ying.meshes[i].textures[0]);
////}
////for (int i = 0; i < ying.textures.size(); ++i) {
////	anim.textures.push_back(ying.textures[i]);
////}
////anim.meshes[20].addTexture(*ying.meshes[22].textures[0]);
////anim.textures.push_back(*ying.meshes[22].textures[0]);
////auto ret = getFileList("models/yuan/ying/anim");
////for (int i = 0; i < ret.size(); ++i) {
////	imp.Import("models/yuan/ying/anim/" + ret[i], tmp, false);
////	string name = ret[i].substr(0, ret[i].find_last_of('.'));
////	anim.addAnimation(tmp);
////	anim.anims.back().name = name;
////	debug << "Finished : " << i << " , " << tmp.anims[0].chans.size() << endl;;
////}
////qua q(vec3(1, 0, 0), radians(-90.0f)); qua qi(q.inv());
////for (int i = 0; i < anim.nBones; ++i) {
////	anim.jos[i].off_set.s = 1.0;
////	anim.jos[i].off_set.t *= 0.01f;
////	anim.jos[i].off_set.q = anim.jos[i].off_set.q * qi;
////}
////for (int i = 0; i < anim.anims.size(); ++i) {
////	auto& an = anim.anims[i];
////	for (int j = 0; j < an.chans.size(); ++j) {
////		auto& p = an.chans[j].poss;
////		for (int k = 0; k < p.size(); ++k) {
////			p[k].v *= 0.01f;
////		}
////	}
////}
////for (int i = 0; i < anim.meshes.size(); ++i) {
////	auto& v = anim.meshes[i].vertices;
////	for (int j = 0; j < v.size(); ++j) {
////		v[j].p = q.rotate(v[j].p);
////		v[j].normal = q.rotate(v[j].normal);
////	}
////	anim.meshes[i].syncData();
////}
////anim.normalizeCharacter();
////anim.name = "ying.fbx";
////anim.makeDRO();
////anim.play(0);
