#include"camera.h"
#include"../base/render_base.h"
#include"../ui/window.h"


Camera::Camera()
{
	mo.t = vec3(0, 0, -4.0);
	proj = perspective<float>(fovy, win_w / win_h, zNear, zFar);
	auto fun = [this](me& e)->bool {
		if (e.mBtn == MOUSE_BUTTON_LEFT)
			up(0.8);
		else down(0.8);
		return true;
	};

	evtor.mousemove() = [this](me& e)->bool {return processMouse(e); };
	evtor.mousestick() = fun;
	evtor.mousemove() = fun;
	evtor.keystick() = [this](ke& e)->bool {return processKey(e); };
	evtor.keydown() = [this](ke& e)->bool {return processKey(e); };
	evtor.mousescroll() = [this](me& e)->bool { debug(e.y); forward(e.y * 3); return true; };

	evtor.windowreshape() = ([this](int x, int y)->bool {
		proj = perspective<float>(fovy, win_w / win_h, zNear, zFar);
		return false;
		});
}

bool Camera::processKey(ke& e) {
	if (e.key == GLFW_KEY_W)
	{
		forward(1.0);
	}
	else if (e.key == GLFW_KEY_S)
	{
		backward(1.0);
	}
	else if (e.key == GLFW_KEY_A)
	{
		left(1.0);
	}
	else if (e.key == GLFW_KEY_D)
	{
		right(1.0);
	}
	else if (e.key == GLFW_KEY_Q)
	{
		up(1.0);
	}
	else if (e.key == GLFW_KEY_E)
	{
		down(1.0);
	}
	else return false;
	return true;
}

bool Camera::processMouse(me& e) {
	mYawAngle -= deltaX * mSensity;
	mPitchAngle -= deltaY * mSensity;
	if (mPitchAngle > 1.57f)
		mPitchAngle = 1.57f;
	if (mPitchAngle < -1.57f)
		mPitchAngle = -1.57f;
	makeQua();
	return true;
}








