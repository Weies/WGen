#include"Engine.h"
#include"function/physics/collision_dectect.h"
#include"resource/importer/importer.h"
#include"resource/asset_manager.h"


#include<iostream>

int main()
{
	LinkerLoad load;
	LinkerSave save;
	Archive ar(&save);
	Importer imp;
	MeshData m;
	imp.Import(m, "asset/models/yuan/ying/ying.pmx");
	AssetManager::get().saveAsset<MeshData>("asset/ying_mesh.asset", m);
	MeshData* mesh = AssetManager::get().loadAsset<MeshData>("asset/ying_mesh.asset");
	GObject* go = new GObject;
	go->addComponent(new TransformComponent);
	auto* mc = new MeshComponent;
	mc->setMesh(*mesh);
	mc->mIsTickInEditorMode = true;
	go->addComponent(mc);
	auto& world = WorldManager::get();
	Level* mCurLevel = new Level;
	mCurLevel->addGObject(go);
	mCurLevel->mName = "Level01";
	mCurLevel->mPath = "asset/default_level.level";
	world.mCurLevel = mCurLevel;
	world.mLevels.push_back(mCurLevel);
	world.saveWorld("asset/default_world.world");



	Engine::get().engineInit();
	ca.moveto(vec3(100, 100, 100));
	ca.lookTo({ 0,0,0 });


	main_win.loop([]() {

		ptr3.drawCoordinate();
		ptr.drawCircle(300, 300, 200);

		//SceneManager::get().
		Engine::get().tick(frameTime);


		});
}