//#include"WGen.h"
//#include"collision_dectect.h"
//#include"Importer.h"
//#include<io.h>
//vector<string> getFileList(string dir)
//{
//	intptr_t handle; _finddata_t findData;
//	if (dir.find('*') == string::npos)dir += "/*";
//	handle = _findfirst(dir.c_str(), &findData);    // 查找目录中的第一个文件
//	if (handle == -1)return {};
//	vector<string> ret;
//	do
//	{	//判断是否是是目录,并且不为"."或".."
//		if (findData.attrib & _A_SUBDIR
//			|| strcmp(findData.name, ".") == 0
//			|| strcmp(findData.name, "..") == 0);
//		else ret.push_back(findData.name);// << "\t" << findData.size << endl;	
//	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
//	_findclose(handle);    // 关闭搜索句柄
//	return ret;
//}
//
//
//PhongRender phong;
//Render3D ren;
//int main() {
//	MeshObject m; MeshObject qiu; MeshObject tmp;
//	Importer imp;
//	imp.Import(m, "models/yuan/qiuqiu/Punching.fbx");
//	imp.Import(qiu, "models/yuan/qiuqiu/qiuqiu.pmx");
//	vector<string> ret = getFileList("models/yuan/qiuqiu/anim");
//	for (int i = 0; i < ret.size(); ++i) {
//		imp.Import("models/yuan/qiuqiu/anim/" + ret[i], tmp, false, false);
//		string name = ret[i].substr(0, ret[i].find_last_of('.'));
//		m.addAnimation(tmp, -1);
//		m.anims.back().name = name;
//		debug << "Finished : " << i << " , " << tmp.anims[0].chans.size() << endl;;
//	}
//	auto& anim = m;
//	qua q(vec3(1, 0, 0), radians(-90.0f)); qua qi(q.inv());
//	for (int i = 0; i < anim.nBones; ++i) {
//		anim.jos[i].off_set.s = 1.0;
//		anim.jos[i].off_set.t *= 0.01f;
//		anim.jos[i].off_set.q = anim.jos[i].off_set.q * qi;
//	}
//	anim.makeLocal();
//	for (int i = 0; i < anim.anims.size(); ++i) {
//		auto& an = anim.anims[i];
//		for (int j = 0; j < an.chans.size(); ++j) {
//			auto& p = an.chans[j].poss;
//			for (int k = 0; k < p.size(); ++k) {
//				p[k].v *= 0.01f;
//			}
//		}
//	}
//	for (int i = 0; i < anim.meshes.size(); ++i) {
//		auto& v = anim.meshes[i].vertices;
//		for (int j = 0; j < v.size(); ++j) {
//			v[j].p = q.rotate(v[j].p);
//			v[j].normal = q.rotate(v[j].normal);
//		}
//	}
//	m.name = "qiuqiu.fbx";
//	m.play(1);
//	for (int i = 0; i < m.meshes.size(); ++i) {
//		m.meshes[i].name = qiu.meshes[i].name;
//		if (qiu.meshes[i].textures.size() > 0) {
//			m.meshes[i].addTexture(*qiu.meshes[i].textures[0]);
//			if (m.queryTexture(qiu.meshes[i].textures[0]->name) < 0)
//				m.textures.push_back(*qiu.meshes[i].textures[0]);
//		}
//	}
//	m.normalizeCharacter();
//	m.makeDRO();
//	ca.setSpeed(0.5);
//	evtor.keydown() = [&](ke& e)->bool {
//		if (e.key == KEY_C)
//			m.play((m.anim_index + 1) % m.anims.size());
//		return true;
//	};
//	m.play(0);
//	//m.scale(vec3(0.02));
//	//m.play(-1);
//	main_win.loop([&]() {
//		ptr3.drawCoordinate();
//
//		phong.setBlock(ca.getBlock());
//		phong << m;
//		m.visualizeBones(ca.getBlock());
//		ren.renderList(ca.getBlock());
//		});
//}