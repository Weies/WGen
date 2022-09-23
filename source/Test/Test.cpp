#include"Engine.h"
#include"function/physics/collision_dectect.h"

int main()
{

	Engine::get().engineInit();
	ca.moveto(vec3(100,100,100));
	ca.lookTo({ 0,0,0 });


	main_win.loop([]() {

		ptr3.drawCoordinate();
		ptr.drawCircle(300, 300, 200);
		Engine::get().tick(frameTime);


		});
}