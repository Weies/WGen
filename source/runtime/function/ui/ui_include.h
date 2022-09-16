#pragma once

#include"widget.h"
#include"window.h"
#include"controls_ui.h"
#include"input_ui.h"
#include"tool_widgets.h"
#include"hintor.h"
using namespace ui;

inline void callback(winptr win , double x , double y) {
	static int gx = 0; static int gy = 0;
	static bool first = true; static int wx; static int wy;
	if (glfwGetMouseButton(win , MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (!first) {
			glfwSetWindowPos(win , wx + 9 + x - gx , wy + 38 + y - gy);
			wx += x - gx; wy += y - gy;
		}
		else
		{
			first = false;
			glfwGetWindowPos(win , &wx , &wy);
			gx = x; gy = y;
		}
	}
	else first = true;
}