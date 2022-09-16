#pragma once

//Waring: This file should only be included 
//in the source file that main() func inside 

// this engine 1 means 1 meter

#include"function/ui/ui_include.h"
#include"function/audio/audio.h"
#include"function/scene/scene_manager.h"
#include"function/framework/world/world_manager.h"
#include"function/framework/component/mesh.h"
#include"function/render/mrender.h"
#include"function/model/model_include.h"

Window main_win(800, 600, "Weies's Drawing", true);


class __initer {
public:
	__initer() {
		mainwin = main_win.win;

		main_win.setWindowSizeCallback(ReshapeCallback);
		main_win.setCursorCallback(MouseCursorCallback);
		main_win.setMouseCallback(MouseCallback);
		main_win.setKeyCallback(KeyCallback);
		main_win.setScrollCallback(MouseScrollCallback);
		main_win.setFoucusCallback(FocusCallback);

		main_win.setFont(font);
		font.init("asset/fonts/msyh.ttc");
		ui::win = &main_win;
	}
};
__initer __initial;


class Engine :public Singleton<Engine> {
public:
	void tick(float delta_time) {
		logicalTick(delta_time);
		renderTick();
	}
	virtual void logicalTick(float delta_time) {

		WorldManager::get().tick(delta_time);

		SceneManager::get().tick();
	}
	virtual void renderTick() {

		mRedner.tick();

	}
	mutex mut;
protected:

	Render mRedner;
};