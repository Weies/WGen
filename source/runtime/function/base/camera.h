#pragma once
#include"core/math/math_include.h"
#include"../base/baseClass.h"
#include"../event/events.h"

using namespace events;

//Camera主要负责3D
class Camera {//注意3D绘图全部使用0~1
public:
	Camera();

	mat4 viewMat()const {
		if (mTransEndTime > gameTime)
			mo = mos.lerp(mot, (gameTime - mTransStartTime) / (mTransEndTime - mTransStartTime));
		return  gm::lookAt(mo.t, mo.q.rotate(vec3(0, 0, 1)));
	}
	vec3 p()const { return mo.p; }
	vec3 frontv() { return mo.q.rotate(vec3(0, 0, 1)); }

	void makeQua() {
		mo.q = qua(vec3(0, 1, 0), mYawAngle) * qua(vec3(1, 0, 0), -mPitchAngle);
	}

	void moveto(float x, float y, float z) { mo.t = vec3(x, y, z); }
	void moveto(const vec3& v) { mo.t = v; }
	void lookTo(const vec3& p) {
		vec3 frontv = normalize(p - mo.t);
		vec2 py = PitchYaw(frontv);
		mPitchAngle = py.x; mYawAngle = py.y;
		makeQua();
	}
	void lookToDirection(const vec3& dir) {
		vec3 frontv = normalize(dir);
		vec2 py = PitchYaw(frontv);
		mPitchAngle = py.x; mYawAngle = py.y;
		makeQua();
	}

	void forward(float len = 1.0) { mo.t += mSpeed * frontv() * len; }
	void backward(float len = 1.0) { forward(-len); }
	void left(float len = 1.0) { mo.t += mo.q.rotate(vec3(1, 0, 0)) * (len * mSpeed); }
	void right(float len = 1.0) { left(-len); }
	void up(float len = 1.0) { mo.t += vec3(0, 1, 0) * mSpeed * len; }
	void down(float len = 1.0) { up(-len); }

	bool processKey(ke& e);
	bool processMouse(me& e);
	void setSpeed(float _speed) {
		mSpeed = _speed;
	}

	void rotateByAxis(const vec3& axis, float degrees)
	{
		/*	mat4 r = gm::rotate(mat4(1.0f), radians(degrees), axis);
			mCameraPosition = r * vec4(mCameraPosition, 1.0);
			frontv = vec3(0, 1, 0) - mCameraPosition;*/
			//frontv = gm::inverse(r) * vec4(frontv , 1.0);
	}

	CameraBlock getBlock()const {
		CameraBlock b;
		b.mPVTransform = proj * viewMat();
		b.mCameraPosition = mo.t;
		return b;
	}
	mat4 proj;

	float zNear = 0.5; float zFar = 10000;
	float fovy = 40.5; float aspect = 1.5;

	mutable SQT mo;
	SQT mos;
	SQT mot;

	void transit(const SQT& target, double during = 2000) {
		mos = mo; mot = target;
		mTransStartTime = gameTime;
		mTransEndTime = gameTime + during;
	}
	void transit(const vec3& p, const qua& q, double during = 2000) {
		mos = mo; mot = SQT(1.0, q, p);
		mTransStartTime = gameTime;
		mTransEndTime = gameTime + during;
	}
	//镜头来回切换
	void anim(const SQT& target, double transition = 2000, double stay = 2000, float dis = 0.12) {
		eventAble = false;
		SQT now = mo; SQT t = target;
		t.t += (mo.t - t.t) * dis;
		transit(t, transition);
		timer(transition + stay, [=]()->bool {
			transit(now, transition);
			return true;
			});
		timer(transition * 2 + stay, [=]()->bool {
			eventAble = true;
			return true; });
	}

	void anim(const vec3& p, const qua& q, double transition = 2000, double stay = 2000, float dis = 0.12) {
		anim(SQT(1.0, q, p), transition, stay, dis);
	}
	void anim(const vec3& p, double transition = 2000, double stay = 2000, float dis = 0.12) {
		anim(SQT(1.0, dirvQua(normalize(p - mo.p)), p), transition, stay, dis);
	}
	float mSpeed = 0.08;//前进速度
	float mSensity = 0.0015;//鼠标灵敏度
	float mPitchAngle = 0; float mYawAngle = 0; float mRollAngle = 0;
	double mTransStartTime = 0; double mTransEndTime = 0;
};
___global(Camera, ca);
#define ca _get_ca()