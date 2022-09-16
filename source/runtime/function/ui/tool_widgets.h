#pragma once
#include"widget.h"
#include"input_ui.h"
#include"controls_ui.h"
#include"../base/camera.h"

namespace ui {

	class CameraBoard :public Widget {
	public:
		CameraBoard(Camera& c) :cam(c), in(200, 40), in1(200, 40) {
			setPosAs(UPPERLEFT);
			in.setParent(this);
			in.hint = "camera go to"; in.mIsMovable = false;
			in.moveto(0, 90); in.resize(380, 60);
			in.onenter = [&](ke& e) {
				stringstream o; o << in.text;
				vec3 v;
				o >> v.x >> v.y >> v.z;
				cam.moveto(v);
			};
			in1.hint = "camera look to";
			in1.setParent(this);
			in1.moveto(0, 185); in1.mIsMovable = false; in1.resize(380, 60);

			in1.onenter = [&](ke& e) {
				stringstream o; o << in1.text;
				vec3 v;
				o >> v.x >> v.y >> v.z;
				cam.lookTo(v);
			};
			bar.mIsMovable = false;
			bar.setParent(this);
			bar.onscroll = [&](me& e) {
				cam.mSpeed = 0.02 + bar.val * 1.0f;
			};
			mBackgroundColor = Color(255, 255, 255, 0.9);
			bar.resize(360, 60); resize(400, 300);
			in.setCenter(w / 2, 120); in1.setCenter(w / 2, 188); bar.setCenter(w / 2, 258);
			onclick = [this](me& e)->bool {
				if (e.x > right() - 30 && e.y < 20) {
					hide(maxinum);
					return true;
				}
				return false;
			};
			hide(true);
		}
		bool maxinum;

		void hide(bool _hide = true) {
			in.mIsShowing = !_hide;
			in1.mIsShowing = !_hide;
			bar.mIsShowing = !_hide;
			maxinum = !_hide;
			if (_hide)setRange(w - 30, 0, 30, 20);
			else setRange(0, 0, w, h);
		}
		void sync() {
			bar.setVal(bar.val);
			cam.mSpeed = 0.02 + bar.val * 10.0;
		}
		void draw() {
			if (maxinum)
			{
				ptr.setColor(mBackgroundColor);
				ptr.fillRect(0, 0, w, h);
				font.setColor(SKYBLUE);
				rcdrawString(center().x, 25, "位置: " + cam.p().str());
				rcdrawString(center().x, 50, "方向: " + cam.frontv().str());
				rcdrawString(center().x, 75, "速度: " + ftos(cam.mSpeed));
			}
			ptr.setColor(80, 80, 80, 0.6);
			ptr.fillRect(right() - 30, 0, 30, 20);
		}
		Camera& cam; InputBox in; InputBox in1; ScrollBar bar;
	};

}
