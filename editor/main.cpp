//#include"../source/runtime/WGen.h"
//
//
//int main() {
//
//	Render3D ren;
//
//	GObject actor;
//	Level* level = new Level;
//	MeshComponent* mc = new MeshComponent;
//	//"*/Sphere/seg=36";
//	mc->mMeshFile = "[Sphere{seg=36;}]";
//	MeshCompDesc des;
//	des.mMeshDesc.mMeshName = "[Sphere{seg=36;}]";
//	des.mMaterialDesc.mBaseColorFile = "asset/imgs/ch.jpg";
//	des.mTransDesc.mTransform = SQT();
//
//	mc->mRawMeshes.push_back(des);
//
//	main_win.set(SHOW_FPS, 1);
//	actor.addComponent(new TransformComponent);
//	actor.addComponent(mc);
//	level->addGObject(&actor);
//	WorldManager::get().mLevels.push_back(level);
//
//
//	//td1.join();
//	main_win.loop([&]() {
//		ptr3.drawCoordinate();
//		Engine::get().tick(frameTime);
//		ren.renderList(ca.getBlock());
//		});
//}
//
//////comp.
////thread td1([] {while (true) { Engine::get().logicalTick(frameTime); } });
/////*thread td2([] {
////	while (true) {
////		clockTime = ::clock();
////		timor.exec();
////		glClearColor(0.8, 0.8, 0.8, 1.0);
////		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
////		Engine::get().renderTick();
////		glfwSwapBuffers(main_win.win);
////		glfwPollEvents();
////	}
////	});*/
////float tick = 0; string fps; float st = clock();
////while (true) {
////	clockTime = ::clock();
////	glClearColor(0.8, 0.8, 0.8, 1.0);
////	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
////	Engine::get().renderTick();
////	++tick;
////	if (tick == 5) {
////		fps = to_string(tick * 1000 / (clock() - st));
////		debug(fps);
////		tick = 0; st = clock();
////	}
////	font.pushString(10, 10, fps);
////	font.renderLiveText();
////	glfwSwapBuffers(main_win.win);
////	glfwPollEvents();
////}