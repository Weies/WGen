#pragma once

//Waring: This file should only be included 
//in the source file that main() func inside 

// this engine 1 means 1 meter

#include"function/ui/ui_include.h"
#include"function/audio/audio.h"
#include"function/scene/scene_manager.h"
#include"function/framework/world/world_manager.h"
#include"function/framework/component/mesh.h"
#include"engine.h"


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
