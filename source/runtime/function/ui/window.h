#pragma once
#include"../event/events.h"
#include"../render/render.h"
#include"../base/ui_base.h"
#include"../event/timor.h"

#include"font.h"
#include"hintor.h"
using namespace events;
using namespace globals;
using namespace ui;
using namespace std;

#define SHOW_FPS 0



//一个独立的窗口,包含独立的上下文
class Window :public BaseWidget {
public:
	Window(int w = 800, int h = 600, const string& title = "", bool border = false) {
		if (!first_win) {
			ASSERT(glfwInit(), "failed init glfw");
			win_w = w; win_h = h;
		}
		glfwWindowHint(GLFW_SAMPLES, 16);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		win = glfwCreateWindow(w, h, title.c_str(), 0, NULL);//= canvas.createWindow(640 , 480 , "new window");
		if (!win) {
			char* str[10];
			for (int i = 0; i < 10; ++i) {
				str[i] = new char[100];
			}
			int ers = glfwGetError((const char**)str);
			for (int i = 0; i < min(ers, 10); ++i)debug << str[i];
			ASSERT(win, "failed when GLFW create window");
		}
		if (!border)setNoBorder();
		glEnable(GL_MULTISAMPLE);
		glfwMakeContextCurrent(win);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//取消四字节对齐

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glfwSwapInterval(0);
		glViewport(0, 0, w, h);
		moveto(400, 400);
		//建立上下文之后才可以init glew
		if (!first_win) {
			ASSERT(glewInit() == GLEW_OK, "Wrong when glew init");
			first_win = true;
			WindowReshapes.clear();
		}
		mBackgroundColor = GRAY;
		_render = new Render2D; _render->setProjM(ortho<float>(0, w, 0, h));
		this->w = w; this->h = h;
		evtor.windowreshape() = [&](int ww, int hh)->bool {
			this->w = ww; this->h = hh;
			_render->setProjM(ortho<float>(0, ww, 0, hh));
			return false;
		};
		transform = mat3(1.0); mPriority = 300.0; mIsShowing = true; mPosition.set(0, 0);
		fps_str = "FPS: 60";

		set(SHOW_FPS, true);
	}

	void setNoBorder() {
		auto hWnd = GetActiveWindow();
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & (~WS_CAPTION) & ~(WS_BORDER) & ~WS_THICKFRAME);
	}
	void setWindowSize(int ww, int hh) {
		resize(ww, hh);
	}
	void resize(int w, int h) {
		glfwSetWindowSize(win, w, h);
		BaseWidget::resize(w, h);
	}
	void bind() {
		glfwMakeContextCurrent(win);
	}
	void moveto(int w, int h) {
		glfwSetWindowPos(win, w, h);
		Pos.set(w, h);
	}
	void setTitle(const string& title) {
		glfwSetWindowTitle(win, title.c_str());
	}

	void setMouseCallback(void (*mouse)(GLFWwindow*, int, int, int)) {
		glfwSetMouseButtonCallback(win, mouse);
	}
	void setKeyCallback(void (*key)(GLFWwindow*, int, int, int, int)) {
		glfwSetKeyCallback(win, key);
	}
	void setCursorCallback(void (*cursor)(GLFWwindow*, double, double)) {
		glfwSetCursorPosCallback(win, cursor);
	}
	void setWindowSizeCallback(void (*size)(GLFWwindow*, int, int)) {
		glfwSetWindowSizeCallback(win, size);
	}
	void setScrollCallback(void(*scroll)(GLFWwindow*, double xoffset, double yoffset)) {
		glfwSetScrollCallback(win, scroll);
	}
	void setFoucusCallback(void(*focus)(winptr win, int)) {
		glfwSetWindowFocusCallback(win, focus);
	}
	void setSwapInterval(int interval) {
		glfwSwapInterval(interval);
	}

	void loop(const std::function<void(void)>& fun) {
		clockTime = clock(); lastTime = gameTime;
		eventAble = true; 
		while (!glfwWindowShouldClose(win))
		{
			timor.updateTime();
			while (!isFocus) {
				this_thread::sleep_for(100ms);
				glfwPollEvents();
			}
			clockTime = ::clock();
			timor.exec();
			glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			fun();
			repaint();

			if (_render)_render->renderList(transform);
			++tick;
			if (lastTime + 1000 < gameTime) {
				double fps = tick * 1000.0 / (gameTime - lastTime);
				//frameps = frameps * 0.56 + fps * 0.44;
				frameps = fps;
				tick = 0; lastTime = gameTime;
				if (check(SHOW_FPS))fps_str = "FPS: " + to_string(int(frameps + 0.5));
			}

			if (check(SHOW_FPS) && ft) {
				ft->setColor(Color(255, 12, 12));
				ft->pushString(15, 30, fps_str);
			}
			hintor.renderHint();
			if (ft)ft->renderLiveText();
			debug.flush();
			glfwSwapBuffers(win);
			glfwPollEvents();
		};
		destroy();
	}

	void setViewportResize(bool able)
	{
		transViewport = able;
	}

	void setStickScale(bool yes)
	{
		static int hand = -1;
		if (yes) {
			hand = evtor.setMouseStick([=](me& e)->bool {
				if (e.mBtn == GLFW_MOUSE_BUTTON_LEFT && scaleTimes < supper)
					scaleCenter(1.05, e.x, e.y);
				else if (e.mBtn == GLFW_MOUSE_BUTTON_RIGHT && scaleTimes > slower)
					scaleCenter(0.95, e.x, e.y);
				return false;
				});
		}
		else if (hand > 0)MouseSticks.erase(hand);
	}
	void setDragging(bool yes)
	{
		if (yes)
			evtor.mousemove() = ([=](me& e)->bool {
			translate(deltaX, -deltaY);
			return true;
				}
		);
		//else mouseStickHandler = 0;
	}
	void translate(float x, float y, float z = 0)
	{
		transform = mat3(1.0, 0.0, 0,
			0.0, 1.0, 0,
			x, y, 1.0) * transform;
		translateX += x; translateY += y;
	}
	void scaleCenter(float times, float x, float y)
	{
		transform = mat3(
			times, 0.0, 0.0,
			0.0, times, 0.0,
			x * (1 - times), y * (1 - times), 1.0) * transform;
		scaleTimes *= times;
	}
	void killTimer() {
		timerAble = false;
	}
	void killEvent() {
		eventAble = false;
	}
	void repaint() {
		RepaintEvent e;
		curPriority = 1.0;
		handleRepaintEvent(&e);
	}
	void setFont(Font& ft) {
		this->ft = &ft;
	}
	void lock() {
		while (_lock);
		_lock = true;
	}
	void unlock() {
		_lock = false;
	}
	bool _lock = false;
	void destroy() {
		//glfwDestroyWindow(win);
	}
	void terminate() {
		glfwTerminate();
	}
	bool processEvent(Event& e) {
		int type = e.type;
		if (type == MeType::NoEvent)return true;//空事件直接返回
		if (type <= MouseScroll) //鼠标事件
		{
			if (cur) {
				vec2 g = cur->mFather->queryGlobalPosition();
				me ee = *(me*)&e;
				ee.x -= g.x; ee.y -= g.y;
				cur->handleMouseEvent(&ee);
				return true;
			}
			for (int i = 0; i < mSons.size(); ++i) {
				if (mSons[i]->handleMouseEvent(&e))return true;
			}
			if (cfocus && type == MouseClick)cfocus->setFocus(false);
		}
		ef(type <= KeType::KeyDoubleClick) {//键盘事件
			if (cfocus) {
				if (cfocus->handleKeyEvent(&e, false))return true;
			}
		}
		ef(type > 64) {
			for (int i = 0; i < mSons.size(); ++i) {
				if (mSons[i]->handleRepaintEvent(&e)) return true;
			}
		}
		return false;
	}
	string fps_str;
	Font* ft = 0; vec2 Pos;
	Render2D* _render = 0; mat3 transform;
	winptr win;
	int tick = 0; double lastTime;
	float supper = 10.0; float slower = 0.1;//缩放倍数上下限
	//bool isFocus = true;
	using bWid::handleRepaintEvent;
protected:
	using bWid::mIsFocus;
	using bWid::handleKeyEvent;
	using bWid::handleMouseEvent;

private:
	static bool first_win;
	using BaseWidget::setParent; using BaseWidget::mPosition;
};
extern Window main_win;

