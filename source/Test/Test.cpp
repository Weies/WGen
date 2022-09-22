#include"Engine.h"
#include"function/physics/collision_dectect.h"

int main()
{
	//SceneManager::get().addMesh()
	debug << ComponentHelper::get().mComponents.begin()->first << endl;

	main_win.loop([]() {

		ptr3.drawCoordinate();
		ptr.drawCircle(300, 300, 200);
		Engine::get().tick(frameTime);


		});
}