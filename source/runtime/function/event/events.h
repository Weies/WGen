#pragma once
#include<functional>
#include<future>

#include"../base/global_values.h"
#include"../base/ui_base.h"
#include"../ui/keys_btns.h"
#include"timor.h"


using namespace ui;
using namespace std;
using namespace globals;


class Thread {
public:
	Thread() {}
	Thread(function<void(void)> fun)
	{
		func = fun;
		static thread td(func);
		hand = td.native_handle();
		td.detach();
	}
	void startLater(function<void(void)> fun)
	{
		func = fun;
		thread td([=]() {
			this_thread::sleep_for(200ms);
			thread th(func);
			hand = th.native_handle();
			th.detach();
			});
		td.detach();
	}
	static void sleepFor(int mil)
	{
		this_thread::sleep_for(chrono::milliseconds(mil));
	}
	void terminate()
	{
		//TerminateThread(hand, 0);
	}
	thread::native_handle_type hand;
	function<void(void)> func;
};

namespace events {
	enum EventType {
		NoEvent = -1,

		MouseUp = 0, MouseClick = 1, MouseMove = 2, MouseStick = 3, MouseHover = 4,
		MouseDoubleClick = 5, MouseDown = 6, MouseScroll = 7,

		KeyUp = 33, KeyDown = 34, KeyStick = 35, KeyDoubleClick = 36,

		Repaint = 65,

		WindowReshape = 80,
		FocusChange = 100
	};

	class Event {
	public:
		Event(EventType tp = NoEvent) :type(tp) {}
		string typeStr() {
			switch (type) {
			case NoEvent:				return "NoEvent";
			case MouseUp:				return "MouseUp";
			case MouseClick:			return "MouseClick";
			case MouseMove:				return "MouseMove";
			case MouseStick:			return "MouseStick";
			case MouseHover:			return "MouseHover";
			case MouseDoubleClick:		return "MouseDClick";
			case MouseDown:				return "MouseDown";
			case MouseScroll:			return "MouseScroll";
			case KeyUp:					return "KeyUp";
			case KeyDown:				return "KeyDown";
			case KeyStick:				return "KeyStick";
			case KeyDoubleClick:		return "KeyDClick";
			case Repaint:				return "Repaint";
			default:					return "NoEvent";
			}
			return "NoEvent";
		}
		string describe() {
			return "EventType: " + typeStr() + ", x= " + itos(x) + ", y= " + itos(y);
		}
		EventType type;
		//以父亲为参考系的相对坐标
		int x = 0; int y = 0;
		//以窗口为原点的全局坐标
		int global_x = 0; int global_y = 0;
		//以屏幕左上角为原点的屏幕坐标
		int screen_x = 0; int screen_y = 0;
	};

	class RepaintEvent :public Event {
	public:
		RepaintEvent() :Event(Repaint) {}
	};

	class MouseEvent :public Event {
	public:
		MouseEvent() :Event(NoEvent) { }
		MouseEvent(EventType t) :Event(t) {}
		MouseEvent(int xx, int yy) :Event(MouseMove) { x = xx; y = yy; }
		MouseEvent(EventType t, int xx, int yy, int mbtn = MOUSE_BUTTON_LEFT) :Event(t)
		{
			x = xx; y = yy; mBtn = mbtn;
		}
		MouseEvent(int mbtn, EventType t = MouseStick) :Event(t) {
			mBtn = mbtn; type = t;
		}
		MouseEvent(double y) :Event(MouseScroll) { this->y = y; }
		int mBtn = 0;
	};

	class KeyEvent :public Event {
	public:
		KeyEvent() :Event(NoEvent) { }
		KeyEvent(EventType t) :Event(t) {
			type = t;
		}
		KeyEvent(int thekey, EventType thetype = KeyDown) :Event(thetype) {
			key = thekey;
		}
		int key = -1;
	};

	using me = MouseEvent;
	using ke = KeyEvent;
	using re = RepaintEvent;
	using MeType = EventType;
	using KeType = EventType;

	extern winptr mainwin;
	extern bool capslock;
	extern bool moveHandled;
	extern bool stickHandled;
	extern bool dclicked;
	extern bool event_handled;
	extern bool isFocus;

	using KeyFunctions = unordered_map<int, function<bool(ke& e)>>;
	using MouseFunctions = unordered_map<int, function<bool(me& e)>>;
	using FocusFunctions = unordered_map<int, function<bool(bool)>>;
	using ReshapeFunctions = unordered_map<int, function<bool(int w, int h)>>;

	___global(MouseFunctions, MouseUps);
	___global(MouseFunctions, MouseClicks);
	___global(MouseFunctions, MouseMoves);
	___global(MouseFunctions, MouseSticks);
	___global(MouseFunctions, MouseHovers);
	___global(MouseFunctions, MouseDoubles);
	___global(MouseFunctions, MouseDowns);
	___global(MouseFunctions, MouseScrolls);

	___global(KeyFunctions, KeyUps);
	___global(KeyFunctions, KeyDowns);
	___global(KeyFunctions, KeySticks);
	___global(KeyFunctions, KeyDoubles);

	___global(FocusFunctions, FocusChanges);

	___global(ReshapeFunctions, WindowReshapes);

#define		MouseUps		_get_MouseUps()
#define 	MouseClicks		_get_MouseClicks()
#define 	MouseMoves		_get_MouseMoves()
#define 	MouseSticks		_get_MouseSticks()
#define 	MouseHovers		_get_MouseHovers()
#define 	MouseDoubleClicks	_get_MouseDoubles()
#define 	MouseDowns		_get_MouseDowns()
#define 	MouseScrolls	_get_MouseScrolls()
#define		KeyUps			_get_KeyUps()
#define 	KeyDowns		_get_KeyDowns()
#define 	KeySticks		_get_KeySticks()
#define 	KeyDoubleClicks		_get_KeyDoubles()
#define 	FocusChanges	_get_FocusChanges()
#define 	WindowReshapes	_get_WindowReshapes()

	//需要直接绑定glfw函数的是其他参数，否则是Event对象
	//鼠标事件分发下去的都是相对坐标
	void ReshapeCallback(winptr win, int w, int h);
	void MouseCursorCallback(winptr w, double x, double y);
	void MouseCallback(winptr p, int btn, int action, int mod);
	void KeyCallback(winptr p, int key, int scancode, int action, int mods);
	void MouseScrollCallback(winptr p, double x, double y);
	void FocusCallback(winptr win, int is_focus);



	//事件先传递给UI树，如果事件未被处理，再传递给绑定的处理函数
	void doWhenMouseUp(MouseEvent& e);
	void doWhenMouseClick(MouseEvent& e);
	void doWhenMouseMove(MouseEvent& e);
	void doWhenMouseStick(MouseEvent& e);
	void doWhenMouseHover(MouseEvent& e);
	void doWhenMouseDoubleClick(MouseEvent& e);
	void doWhenMouseDown(MouseEvent& e);
	void doWhenMouseScroll(MouseEvent& e);


	void doWhenKeyUp(KeyEvent& e);
	void doWhenKeyDown(KeyEvent& e);
	void doWhenKeyStick(KeyEvent& e);
	void doWhenkeyDoubleClick(KeyEvent& e);

	void doWhenFocusChange(bool is_focus);

	void doWhenWindowReshape(winptr win, int w, int h);

	class Evtor {
	public:
		Evtor() { eventAble = false; }
		int setMouseMove(function<bool(MouseEvent& e)> move)
		{
			MouseMoves.insert({ ++handles[MouseMove],move });
			return handles[MouseMove];
		}
		int setMouseClick(function<bool(MouseEvent& e)>move)
		{
			MouseClicks.insert({ ++handles[MouseClick],move });
			return handles[MouseClick];
		}
		int setMouseStick(function<bool(MouseEvent& e)>stick)
		{
			MouseSticks.insert({ ++handles[MouseStick],stick });
			return handles[MouseStick];
		}
		int setMouseHover(function<bool(MouseEvent& e)>handler) {
			MouseHovers.insert({ ++handles[MouseHover],handler });
			return handles[MouseHover];
		}
		int setMouseUp(function<bool(MouseEvent& e)>handler)
		{
			MouseUps.insert({ ++handles[MouseUp],handler });
			return handles[MouseUp];
		}
		int setMouseDoubleClick(function<	bool(MouseEvent& e)>handler)
		{
			MouseDoubleClicks.insert({ ++handles[MouseDoubleClick],handler });
			return handles[MouseDoubleClick];
		}
		int setKeyUp(function<bool(KeyEvent& e)> func) {
			KeyUps.insert({ ++handles[KeyUp],func });
			return handles[KeyUp];
		}
		int setKeyDown(function<bool(KeyEvent& e)> func)
		{
			KeyDowns.insert({ ++handles[KeyDown],func });
			return handles[KeyDown];
		}
		int setKeyDoubleClick(function<	bool(KeyEvent& e)> func)
		{
			KeyDoubleClicks.insert({ ++handles[KeyDoubleClick],func });
			return handles[KeyDoubleClick];
		}
		int setKeyStickFunc(function<bool(KeyEvent& e)> func)
		{
			KeySticks.insert({ ++handles[KeyStick],func });
			return handles[KeyStick];
		}
		int setWindowReshape(function<bool(int, int)> func)
		{
			WindowReshapes.insert({ ++handles[WindowReshape],func });
			return handles[WindowReshape];
		}
		int setFocusChange(function<bool(bool)> func) {
			FocusChanges.insert({ ++handles[FocusChange],func });
			return handles[FocusChange];
		}


		//失败返回0，成功返回handle
		int unbind(EventType which, int handle) {
			switch (which) {
			case MouseUp:
				return MouseUps.erase(handle);
			case MouseClick:
				return MouseClicks.erase(handle);
			case MouseMove:
				return MouseMoves.erase(handle);
			case MouseStick:
				return MouseSticks.erase(handle);
			case MouseHover:
				return MouseHovers.erase(handle);
			case MouseDoubleClick:
				return MouseDoubleClicks.erase(handle);
			case MouseDown:
				return MouseDowns.erase(handle);
			case MouseScroll:
				return MouseScrolls.erase(handle);
			case KeyUp:
				return KeyUps.erase(handle);
			case KeyStick:
				return KeySticks.erase(handle);
			case KeyDoubleClick:
				return KeyDoubleClicks.erase(handle);
			case WindowReshape:
				return WindowReshapes.erase(handle);
			case FocusChange:
				return FocusChanges.erase(handle);
			default:return 0;
			}
			return 0;
		}


		function<bool(MouseEvent& e)>& mouseup() {
			MouseUps.insert({ ++handles[MouseUp],{} });
			return MouseUps[handles[MouseUp]];
		}
		function<bool(MouseEvent& e)>& mouseclick() {
			MouseClicks.insert({ ++handles[MouseClick],{} });
			return MouseClicks[handles[MouseClick]];
		}
		function<bool(MouseEvent& e)>& mousemove() {
			MouseMoves.insert({ ++handles[MouseMove],{} });
			return MouseMoves[handles[MouseMove]];
		}
		function<bool(MouseEvent& e)>& mousestick() {
			MouseSticks.insert({ ++handles[MouseStick],{} });
			return MouseSticks[handles[MouseStick]];
		}
		function<bool(MouseEvent& e)>& mousehover() {
			MouseHovers.insert({ ++handles[MouseHover],{} });
			return MouseHovers[handles[MouseHover]];
		}
		function<bool(MouseEvent& e)>& mousedoubleclick() {
			MouseDoubleClicks.insert({ ++handles[MouseDoubleClick],{} });
			return MouseDoubleClicks[handles[MouseDoubleClick]];
		}
		function<bool(MouseEvent& e)>& mousedown() {
			MouseDowns.insert({ ++handles[MouseDown],{} });
			return MouseDowns[handles[MouseDown]];
		}
		function<bool(MouseEvent& e)>& mousescroll() {
			MouseScrolls.insert({ ++handles[MouseScroll],{} });
			return MouseScrolls[handles[MouseScroll]];
		}

		function<bool(KeyEvent& e)>& keyup() {
			KeyUps.insert({ ++handles[KeyUp],{} });
			return KeyUps[handles[KeyUp]];
		}
		function<bool(KeyEvent& e)>& keydown() {
			KeyDowns.insert({ ++handles[KeyDown],{} });
			return KeyDowns[handles[KeyDown]];
		}
		function<bool(KeyEvent& e)>& keystick() {
			KeySticks.insert({ ++handles[KeyDown],{} });
			return KeySticks[handles[KeyDown]];
		}
		function<bool(KeyEvent& e)>& keydoubleclick() {
			KeyDoubleClicks.insert({ ++handles[KeyDoubleClick],{} });
			return KeyDoubleClicks[handles[KeyDoubleClick]];
		}
		function<bool(int, int)>& windowreshape() {
			WindowReshapes.insert({ ++handles[WindowReshape],{} });
			return WindowReshapes[handles[WindowReshape]];
		}
		function<bool(bool)>& focuschange() {
			FocusChanges.insert({ ++handles[FocusChange],{} });
			return FocusChanges[handles[FocusChange]];
		}

		int handles[128] = {};
	};

	___global(Evtor, evtor);
#define evtor _get_evtor()
}
