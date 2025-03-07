#include "Engine.h"
#include "function/network/network.h"
#include "function/physics/collision_dectect.h"
#include "json11/json11.hpp"
#include "resource/asset_manager.h"
#include "resource/importer/importer.h"

#define de std::cout
#include <iostream>

void visSkeleton(const Skeleton& s)
{
	int i = 0;
	for (auto& joint : s.mJoints)
	{
		if (joint.mParentId != -1)
		{
			ptr3.setColor(RED);

			ptr3.drawLine(joint.mTransform.t, s.mJoints[joint.mParentId].mTransform.t);

			std::ostringstream o;
			o << "[" << joint.mName << "] T: " << joint.mTransform.t << ", R: " << joint.mLocalTransform.q << ", JO: " << joint.preRotation << endl;
			// drawString(100, 25 * i + 100, o.str());
		}
		ptr3.setColor(BLUE);
		ptr3.drawCube(joint.mTransform);
		++i;
	}
}

using namespace json11;
Skeleton fromJson(const string& jsonString)
{
	string err;
	Json j = json11::Json::parse(jsonString.c_str(), err);
	map<string, int> nameIdMap;

	Json::array joints = j["joints"].array_items();
	Skeleton s(joints.size());
	for (int i = 0; i < joints.size(); ++i)
	{
		Json& j = joints[i];

		s[i].mName = j["name"].string_value();

		s[i].mLocalTransform.t[0] = j["translate"][0].number_value();
		s[i].mLocalTransform.t[1] = j["translate"][1].number_value();
		s[i].mLocalTransform.t[2] = j["translate"][2].number_value();

		s[i].mLocalTransform.q[0] = j["rotation"][0].number_value();
		s[i].mLocalTransform.q[1] = j["rotation"][1].number_value();
		s[i].mLocalTransform.q[2] = j["rotation"][2].number_value();
		s[i].mLocalTransform.q[3] = j["rotation"][3].number_value();

		s[i].preRotation[0] = j["preRotation"][0].number_value();
		s[i].preRotation[1] = j["preRotation"][1].number_value();
		s[i].preRotation[2] = j["preRotation"][2].number_value();
		s[i].preRotation[3] = j["preRotation"][3].number_value();

		if (nameIdMap.find(j["parent"].string_value()) != nameIdMap.end())
		{
			s[i].mParentId = nameIdMap[j["parent"].string_value()];
		}
		else
			s[i].mParentId = -1;
		nameIdMap.insert({ s[i].mName, i });
	}
	s.updateWorld();
	return s;
}

// Skeleton rev(const Skeleton &s) { Skeleton a; }

int main()
{
	// LinkerLoad load;
	// LinkerSave save;
	// Archive ar(&save);
	// Importer imp;
	// MeshData m;
	// imp.Import(m, "asset/models/yuan/ying/ying.pmx");
	// AssetManager::get().saveAsset<MeshData>("asset/ying_mesh.asset", m);
	// MeshData* mesh =
	// AssetManager::get().loadAsset<MeshData>("asset/ying_mesh.asset"); GObject*
	// go = new GObject; go->addComponent(new TransformComponent); auto* mc = new
	// MeshComponent; mc->setMesh(*mesh); mc->mIsTickInEditorMode = true;
	// go->addComponent(mc);
	// auto& world = WorldManager::get();
	// Level* mCurLevel = new Level;
	// mCurLevel->addGObject(go);
	// mCurLevel->mName = "Level01";
	// mCurLevel->mPath = "asset/default_level.level";
	// world.mCurLevel = mCurLevel;
	// world.mLevels.push_back(mCurLevel);
	// world.saveWorld("asset/default_world.world");

	quaternion<float> q(vec3(1, 2, 3).normalize(), Degree(90));

	debug(q * vec3(1, 2, 3));
	debug(-q * vec3(1, 2, 3));

	Skeleton skeleton(3);

	skeleton[1].mLocalTransform.t = { 10, 10, 0 };
	skeleton[2].mLocalTransform.t = { 20, 0, 0 };

	skeleton.updateWorld();

	SVRSocket so(45869);
	so.listen();

	// Socket sok("127.0.0.1", 45869);
	// sok.connect();

	Engine::get().engineInit();
	ca.moveto(vec3(20, 140, -40));
	ca.lookTo({ 0, 100, 0 });

	ca.mSpeed *= 5;

	string all;
	int index = 0;

	int cnt = 0;
	map<string, Skeleton> sks;

	InputBox in;
	int show = 0;
	in.onenter = [&](ke& e) { show = std::stoi(in.text); };

	main_win.loop(
		[&]()
		{
			// if (so.connected())
			// {
			// 	auto soc = so.getUserSocket();
			// 	if (soc && soc->valid)
			// 	{
			// 		auto str = soc->receieve();
			// 		if (str.size())
			// 		{
			// 			all += str;
			// 			int end = all.find("[#END]", index);
			//
			// 			if (end != string::npos)
			// 			{
			// 				int head_end = all.find(']', index + 2);
			// 				string obj_name = all.substr(index + 2, head_end - index - 2);
			//
			// 				string new_obj = all.substr(head_end + 1, end - head_end - 1);
			// 				debug(new_obj);
			//
			// 				index = end + 6;
			// 				all = all.substr(index);
			// 				index = 0;
			//
			// 				skeleton = fromJson(new_obj);
			// 				//if (sks.count(obj_name) == 0)
			// 					sks[obj_name] = skeleton;
			// 			}
			// 		}
			// 	}
			// }
			// cnt++;
			// if (show < sks.size() && cnt)
			// {
			// 	auto it = sks.begin();
			// 	int n = 0;
			// 	while (n < show)
			// 	{
			// 		++n; ++it;
			// 	}
			// 	visSkeleton(it->second);
			// }
			// int i = 0;
			// for (auto it = sks.begin(); it != sks.end(); ++it)
			// {
			// 	++i;
			// 	drawString(100, 800 + i * 25, it->first);
			// }

			// visSkeleton(sks[(cnt >> 6) % sks.size()]);

			visSkeleton(skeleton);

			ptr3.drawCoordinate(200);

			//// SceneManager::get().
			Engine::get().tick(frameTime);
		});
}
