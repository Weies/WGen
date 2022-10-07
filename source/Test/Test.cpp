#include"Engine.h"
#include"function/physics/collision_dectect.h"
#include"resource/importer/importer.h"



#include<iostream>

int main()
{

	Importer imp;
	MeshData m;
	imp.Import(m, "asset/models/yuan/ying/ying.pmx");



	LinkerLoad load;
	LinkerSave save;

	Archive ar(&save);



	//WorldManager::get().l

	//ar.load("asset/1.asset");
	//ar << m;

	////ar.save("asset/1.asset");

	//load.arr.swap(save.arr);

	//ar.mLinker = &load;

	//MeshData mm;

	//ar << mm;



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