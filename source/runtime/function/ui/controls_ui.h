#pragma once

// 一些常用的控件

#include"widget.h"
#include"painter.h"
#include"font.h"
using namespace events;


namespace ui {

	class ScrollBar :public Widget {
	public:
		ScrollBar(bWid* father = 0) :bar(this) {
			mType = t_ScrollBar;
			setParent(father);
			setBGC(Color(220, 220, 220, 0.7));
			setPosAs(CENTER);
			onmove = [=](me& e)->bool {
				if (mIsMovable)translate(deltaX, deltaY);
				return true;
			};
			setCenter(mFather->w / 2, mFather->h / 2);
			bar.setPriority(mPriority + 1);
			val = 0.0;
			bar.w = 10;
			resize(400, 80);
		}

		void resize(float ww, float hh) {
			bar.resize(bar.w * ww / w, hh);
			bar.setCenter((val - 0.5) * (ww - bar.w), 0);
			w = ww; h = hh;
		}

		void draw() {
			ptr.setCenter(0, 0);
			ptr.setColor(mBackgroundColor);
			ptr.cfillRect(this->w, this->h);

			ptr.setColor(Color(255, 255, 255, 0.98));
			ptr.cfillRect(this->w, 10);
		}
		void setVal(float _val) {
			ASSERT(_val >= 0 && _val <= 1);
			val = _val;
			bar.setCenter((val - 0.5) * w, 0);
		}

		float val = 0.5;
		function<void(me& e)> onscroll = 0;
		class Bar :public Widget {
		public:
			Bar(bWid* father = 0) {
				setParent(father); setPosAs(CENTER);
				setBGC(Color(0.4, 0.4, 0.4, 0.6));
				resize(20, 30);
				mType = t_Bar;
				onmove = [this](me& e)->bool {
					ScrollBar* ft = cast(ScrollBar*, mFather);
					mPosition.x += deltaX;
					float v = mPosition.x / (ft->w - w) + 0.5;
					if (v < 0) mPosition.x = -(ft->w - w) * 0.5, ft->val = 0;
					if (v > 1.0)mPosition.x = (ft->w - w) * 0.5, ft->val = 1.0;
					else ft->val = v;
					if (ft->onscroll)ft->onscroll(e);
					return true;
				};
			}
			void draw() {
				ptr.setColor(mBackgroundColor);
				ptr.setCenter(0, 0);
				ptr.cfillRect(this->w, this->h);
			}
		};
		Bar  bar;
	};

	class Button :public Widget {
	public:

		Button(const string& s, bWid* father = 0) :fontColor(25, 25, 220), borderColor(20, 20, 20, 0.6)
		{
			mType = t_Button;
			setParent(father);
			setPriority(1000);
			setPosAs(CENTER);
			moveto(400, 300);
			setBGC(255, 255, 255, 0.6);
			setText(s);
		}
		void slowIn(float alpha = 0.8, double time = 1000, double delay = 0) {
			timer(delay, [=]()->bool {
				int st = gameTime; setAlpha(0); show(1);
				timer(0.0, [=]()->bool {
					setAlpha(alpha * (gameTime - st) / time);
					if (gameTime - st > time)return true;
					return false;
					});
				return true;
				});
		}
		void slowOut(double time = 1000, double delay = 0) {
			timer(delay, [=]()->bool {
				int st = gameTime; float a = mBackgroundColor.a; show(1);
				timer(0.0, [=]()->bool {
					setAlpha(a - (gameTime - st) / time);
					if (gameTime - st > time) {
						show(0);
						return true;
					}
					return false;
					});
				return true;
				});
		}
		void setAlpha(float a) {
			mBackgroundColor.a = a; fontColor.a = a; borderColor.a = a;
		}
		void draw()
		{
			ptr.fix();
			ptr.setCenter(0, 0);
			ptr.setColor(borderColor);
			ptr.cdrawRect(this->w + 2, this->h + 2);
			ptr.setColor(mBackgroundColor);
			ptr.cfillRect(this->w, this->h);
			ptr.stopfix();
			font.setColor(fontColor);
			rcdrawString(0, 0, str);
		}
		Color fontColor; Color borderColor;
		void setText(const string& s, bool resize = true)
		{
			str = s;
			if (resize)this->resize(max<float>(font.testWidth(s) + 40, 80), 40);
		}

		string str;
	};



	struct state {
		state()
		{
			x = rand() % (int)win_w + 10;
			y = rand() % (int)win_h + 10;
			w = rand() % (int)win_w;
			h = rand() % (int)win_h;
		}
		int x;
		int y;
		int w;
		int h;
	};

	class Tailor : public Widget {
	public:
		vector<Line> lines;
		Tailor(int w, int h) :Widget(w, h) {
			onstick = [=](me& e)->bool {
				if (e.mBtn == GLFW_MOUSE_BUTTON_LEFT && this->h < win_h)
				{
					resize(this->w *= 1.02, this->h *= 1.02);
				}
				else if (e.mBtn == GLFW_MOUSE_BUTTON_RIGHT && this->h > win_h * 0.1)
				{
					resize(this->w *= 0.98, this->h *= 0.98);
				}
			};
			onmove = [=](me& e) ->bool {
				this->setPriority(1024);
				moveto(e.x, e.y);
			};
		}

		void draw()
		{
			ptr.setColor(mBackgroundColor);
			ptr.fillRect(mPosition.x, mPosition.y, this->w, this->h);
			ptr.setColor(255, 0, 0);

			for (int i = 0; i < lines.size(); i++)
			{
				Line l = cut(lines[i].p1, lines[i].p2);
				if (l.need)
				{
					ptr.drawLine(l.p1.x, l.p1.y, l.p2.x, l.p2.y);
					ptr.fillCircle(l.p1.x, l.p1.y, 5);
					ptr.fillCircle(l.p2.x, l.p2.y, 5);
				}
			}
		}

		Line cut(point<float> p1, point<float> p2)
		{
			point<float> pp[6]; pp[0] = p1; pp[1] = p2;
			float k = (p2.y - p1.y) / (p2.x - p1.x);
			float kinver;
			if (k != 0)kinver = 1 / k;
			else kinver = 1e10;
			//对四条直线求交
			pp[2] = point<float>(mPosition.x, p2.y - k * (p2.x - mPosition.x));
			pp[3] = point<float>(p1.x - kinver * (p1.y - mPosition.y), mPosition.y);
			pp[4] = point<float>(mPosition.x + this->w, p1.y - k * (p1.x - mPosition.x - this->w));
			pp[5] = point<float>(p2.x - kinver * (p2.y - mPosition.y - this->h), mPosition.y + this->h);
			sort(pp, pp + 6);
			point<float> mid((pp[2].x + pp[3].x) / 2, (pp[3].y + pp[2].y) / 2);
			if (mPosition.x < mid.x && mid.x < mPosition.x + this->w
				&& mPosition.y < mid.y && mid.y < mPosition.y + this->h)
			{
				Line l(pp[2].x, pp[2].y, pp[3].x, pp[3].y);
				l.need = true;
				return l;
			}
			return Line(0, 0, 0, 0);
		}

		void gotoState(state s)
		{
			moveto(mPosition.x + (s.x - mPosition.x) * 0.02, mPosition.y + (s.y - mPosition.y) * 0.02);
			resize(this->w + (s.w - this->w) * 0.02, this->h + (s.h - this->h) * 0.02);
		}
	};
}