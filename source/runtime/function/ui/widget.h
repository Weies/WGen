#pragma once
#include"../event/events.h"
#include"../base/ui_base.h"
#include"painter.h"
#include"window.h"
using namespace std;
using namespace events;
using namespace globals;

namespace ui {
	//带有事件的窗口对象
	class EventWidget : public BaseWidget {
	public:
		//按下又快速弹起才叫click，否则只会触发mousedown
		function<bool(MouseEvent& e)>	onclick = 0;
		function<bool(MouseEvent& e)>	onmove = 0;
		function<bool(MouseEvent& e)>	onstick = 0;
		function<bool(MouseEvent& e)>	onmouseup = 0;
		function<bool(MouseEvent& e)>	onmousedown = 0;
		function<bool(MouseEvent& e)>	onmousedclick = 0;
		function<bool(MouseEvent& e)>	onhover = 0;
		function<bool(KeyEvent& e)>		onkeydown = 0;
		function<bool(KeyEvent& e)>		onkeyup = 0;
		function<bool(KeyEvent& e)>		onkeystick = 0;
		function<bool(KeyEvent& e)>		onkeydclick = 0;

		void setOnClick(function<	bool(MouseEvent& e)> func) {
			onclick = func;
		}
		void setOnMouseUp(function<	bool(MouseEvent& e)> func) {
			onmouseup = func;
		}
		void setOnMove(function<	bool(MouseEvent& e)> func) {
			onmove = func;
		}
		void setOnStick(function<	bool(MouseEvent& e)> func) {
			onstick = func;
		}
		void setOnKeyDown(function<	bool(KeyEvent& e)> func) {
			onkeydown = func;
		}
		void setOnKeyUp(function<	bool(KeyEvent& e)> func) {
			onkeyup = func;
		}
		void setOnKeyStick(function<bool(KeyEvent& e)> func) {
			onkeystick = func;
		}

		EventWidget() {
			mType = t_EventWidget;
		}
		~EventWidget() {}

		void translate(float x, float y)
		{
			mPosition.x += x; mPosition.y += y;
		}
		virtual void rotate(float deg) {};
	protected:
		bool handleKeyEvent(void* ee, bool flow = false) {
			ke e = *(ke*)ee;
			if (flow)for (int i = 0; i < mSons.size(); ++i) {
				EventWidget* son = (EventWidget*)mSons[i];
				if (son->handleKeyEvent(&e))return true;
			}
			switch (e.type) {
			case KeType::KeyUp:
				if (onkeyup && onkeyup(e))return true;
				break;
			case KeType::KeyDown:
				if (onkeydown && onkeydown(e))return true;
				break;
			case KeType::KeyStick:
				if (onkeystick && onkeystick(e))return true;
				break;
			case KeType::KeyDoubleClick:
				if (onkeydclick && onkeydclick(e))return true;
				break;
			default:
				return false;
				break;
			}
			return false;
		}

		bool handleMouseEvent(void* ee, bool flow = true) {
			me e = *(me*)ee; e.x -= mPosition.x; e.y -= mPosition.y;
			if ((!inArea(e.x, e.y) && cur != this) || !mIsShowing)return false;
			if (e.type == MouseHover)return false;
			if (flow)for (int i = 0; i < mSons.size(); ++i)
				if (mSons[i]->handleMouseEvent(&e))return true;
			switch (e.type) {
			case  MouseUp:
				if (onmouseup && onmouseup(e)) return true;
			case  MouseClick:
				if (onclick && onclick(e))setFocus();
				return true;
			case  MouseMove:
				cur = this;
				if (onmove && onmove(e))setFocus();
				return true;
			case  MouseStick:
				if (onstick && onstick(e)) return true;
			case  MouseHover:
				if (onhover && onhover(e)) return true;
			case  MouseDoubleClick:
				if (onmousedclick && onmousedclick(e)) return true;
			case  MouseDown:
				if (onmousedown && onmousedown(e))setFocus();
				return true;
			default:
				return false;
			}
			return false;
		}
	};

	//其他UI控件应该继承自Widget或FixedWidget
	class Widget : public EventWidget {
	public:

		Widget(bWid* father = 0) {
			setParent(father);
			mIsFixed = true;
			addEvent();
			mType = t_Widget;
		}
		Widget(int w, int h, bWid* father = 0) {
			setParent(father);
			resize(w, h);
			addEvent();
			mType = t_Widget;
			mIsFixed = true;
		}

		void addEvent() {
			onmove = [this](me& e)->bool {
				this->setPriority(1024);
				translate(deltaX, deltaY);
				return true;
			};
			onmouseup = [this](me& e)->bool {
				resetPri();	return true;
			};
		}
		virtual void draw() {
			ptr.setColor(mBackgroundColor);
			ptr.fillRect(mPosition.x, mPosition.y, w, h);
		}
		void setStickScale(bool yes = true)
		{
			if (yes)
				onstick = [=](MouseEvent& e)->bool {
				if (e.mBtn == GLFW_MOUSE_BUTTON_LEFT)
					scale(1.03);
				else if (e.mBtn == GLFW_MOUSE_BUTTON_RIGHT)
					scale(0.97);
				return true;
			};
			else onstick = 0;
		}

		~Widget() {}
	private:

	};

	//不可以动对象
	class FixedWidget : public BaseWidget {
	public:
		FixedWidget(bWid* father = 0) {
			setParent(father);
			setPriority(0);
			mPosition.set(100, 100);
			mType = t_FixedWidget;
		}

		void setPriority(float pri)
		{
			mPriority = pri;
		}
		void setDefaultPri(float pri)
		{
			mDefaultPriority = pri;
		}
		void resetPri()
		{
			mPriority = mDefaultPriority;
		}
		virtual void rotate(float deg) {};
	};


}
