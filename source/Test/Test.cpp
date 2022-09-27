#include"Engine.h"
#include"function/physics/collision_dectect.h"
#include"function/importer/importer.h"
#include"function/importer/mesh.h"



#include<iostream>

int main()
{

	Importer imp;
	SkeletalMesh m;
	imp.Import(m, "asset/models/yuan/ying/ying.pmx");

	LinkerLoad load;
	LinkerSave save;
	Archive ar(&save);

	ar << m;

	load.arr.swap(save.arr);

	ar.mLinker = &load;

	SkeletalMesh mm;

	ar << mm;



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