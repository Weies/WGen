#include"events.h"
using namespace events;
using namespace globals;
#include"../ui/window.h"

winptr events::mainwin = 0;
bool events::capslock = false;
bool events::moveHandled = false;
bool events::stickHandled = false;
bool events::dclicked = false;
bool events::event_handled = false;
bool events::isFocus = true;
BaseWidget* ui::cfocus = 0;
BaseWidget* ui::cur = 0;
bool mouseReleased = true;
bool click_timeout = false;
#define event_track 0

bool just_up = false;

void events::MouseScrollCallback(winptr p, double x, double y) {
	if (!eventAble)return;
	MouseEvent e(y);
	doWhenMouseScroll(e);
}
void events::MouseCursorCallback(winptr w, double x, double y)
{
	if (!eventAble)return;
	deltaX = x - oldX; deltaY = y - oldY;//每次移动相当于上一次的变化量
	mouseX = x; mouseY = y;//鼠标的真实位置
	MouseEvent e(MeType::MouseHover, mouseX, mouseY);
	if (glfwGetMouseButton(mainwin, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
		doWhenMouseHover(e);
	}
	else
	{
		e.type = MeType::MouseMove;
		moveHandled = false; mouseMoved = true;
		doWhenMouseMove(e);
	}
	oldX = mouseX; oldY = mouseY;
}
void events::MouseCallback(winptr p, int btn, int action, int mod)
{
	if (!eventAble)return;
	double x, y;
	glfwGetCursorPos(mainwin, &x, &y);
	mouseX = x; mouseY = y; mBtn = btn;
	oldX = x; oldY = y;
	MouseEvent e(MeType::MouseUp, mouseX, mouseY, btn);
	sticking = true;
	mouseMoved = false;

	if (action == GLFW_RELEASE) {
		if (!click_timeout && !mouseMoved) {
			e.type = MeType::MouseClick;
			clickX = x; clickY = y;
			doWhenMouseClick(e);
		}
		e.type = MeType::MouseUp;
		mouseReleased = true; just_up = true;
		timer(30.0, [&]()->bool {just_up = false; return true; });
		sticking = false; cur = 0;
		doWhenMouseUp(e);
	}
	else if (action == GLFW_PRESS)
	{
		e.type = MouseDown;
		doWhenMouseDown(e);
		click_timeout = false;
		timer(180.0, [&]()->bool {click_timeout = true; return true; });

		timer(200.0, [=]()->bool {
			MouseEvent ev = e; ev.type = MouseStick;
			doWhenMouseStick(ev);
			return true;
			});
	}
}
void events::KeyCallback(winptr p, int key, int scancode, int action, int mods)
{
	if (!eventAble) return;
	//if (!eventAble || just_up) return;
	KeyEvent e(key, KeType::KeyDown);
	if (action == GLFW_PRESS) {
		doWhenKeyDown(e);
	}
	ef(action == GLFW_RELEASE) {
		e.type = KeyUp;
		doWhenKeyUp(e);
	}
	ef(action == GLFW_REPEAT) {
		e.type = KeyStick;
		doWhenKeyStick(e);
	}
}
void events::FocusCallback(winptr win, int is_focus) {
	if (!eventAble)return;
	isFocus = is_focus;
	doWhenFocusChange(is_focus);
}
void events::ReshapeCallback(winptr win, int w, int h) {
	win_w = w; win_h = h;
	if (transViewport)glViewport(0, 0, w, h);
	doWhenWindowReshape(win, w, h);
}

void events::doWhenMouseUp(MouseEvent& e) {
	if (event_track)debug("mouse release");
	if (!((Window*)win)->processEvent(e)) {
		for (auto& y : MouseUps)if (y.second(e))return;
	}
}
void events::doWhenMouseClick(MouseEvent& e) {
	if (event_track)debug("mouse click");
	if (!((Window*)win)->processEvent(e)) {
		for (auto& y : MouseClicks)if (y.second(e))return;
		if (cfocus)cfocus->setFocus(false);
	}
}
void events::doWhenMouseMove(MouseEvent& e) {
	if (event_track)debug("mouse move");
	if (!((Window*)win)->processEvent(e)) {
		if (!moveHandled)
			for (auto& y : MouseMoves)if (y.second(e))return;
	}
}
void events::doWhenMouseStick(MouseEvent& e) {
	if (sticking && !mouseMoved) {
		if (event_track)debug("mouse stick");
		if (!((Window*)win)->processEvent(e)) {
			if (!stickHandled) {
				for (auto& y : MouseSticks)if (y.second(e))break;
			}
		}
		timer(40.0, [=]()->bool {MouseEvent ev = e; doWhenMouseStick(ev); return true; });
	}
}
void events::doWhenMouseHover(MouseEvent& e) {
	if (event_track)debug("mouse hover");
	if (!((Window*)win)->processEvent(e))
		for (auto& y : MouseHovers)if (y.second(e))return;
}
void events::doWhenMouseDoubleClick(MouseEvent& e) {
	if (event_track)debug("mouse double click");
	for (auto& y : MouseDoubleClicks)if (y.second(e))return;
}
void events::doWhenMouseDown(MouseEvent& e) {
	if (event_track)debug("mouse down");
	if (!((Window*)win)->processEvent(e)) {
		for (auto& y : MouseDowns)if (y.second(e))return;
	}
}
void events::doWhenMouseScroll(MouseEvent& e) {
	if (event_track)debug("mouse scroll");
	for (auto& y : MouseScrolls)if (y.second(e))return;
}


void events::doWhenKeyUp(KeyEvent& e) {
	if (event_track)debug("key up");
	if (!((Window*)win)->processEvent(e))
		for (auto& y : KeyUps)if (y.second(e))return;
}
void events::doWhenKeyDown(KeyEvent& e) {
	if (event_track)debug("key down");
	if (!((Window*)win)->processEvent(e)) {
		for (auto& y : KeyDowns)if (y.second(e))return;
	}
}
void events::doWhenKeyStick(KeyEvent& e) {
	if (event_track)debug("key stick");
	if (!((Window*)win)->processEvent(e))
		for (auto& y : KeySticks)if (y.second(e))return;
}

void events::doWhenkeyDoubleClick(KeyEvent& e) {
	if (event_track)debug("key doubleclick");
	for (auto& y : KeyDoubleClicks)if (y.second(e))return;
}

void events::doWhenWindowReshape(winptr win, int w, int h) {
	if (event_track)debug("window reshape");
	for (auto& y : WindowReshapes)
		if (y.second(w, h))return;
}

void events::doWhenFocusChange(bool is_focus) {
	for (auto& y : FocusChanges) {
		if (y.second(is_focus))return;
	}
}


