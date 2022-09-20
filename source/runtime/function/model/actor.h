#pragma once
#include"3DObject.h"
#include"../base/camera.h"

enum ActorState {
	Forward = 0, Backward = 1, Run = 2, Dance = 3,
	Idle = 4, Jump = 5, Fire = 6, Boxing = 7
};

class Actor :public SkeletonObject {
public:
	Camera* mCamera = 0;
	vec3		mCamOffset = vec3(0, 0, 0);//vec3(0, 4, -18);//
	vec3		mViewpoint = vec3(0, 2.0, 0);
	ActorState	mCurState = Idle;

	float   mHP = 100;
	float	mCamDistance = 5.0;//相机距离任务的距离
	float	mVelocity = 0.0;
	float	mAcceleration = 0.0;
	float	mMaxVelocity = 10.0;
	float	mMaxAcceleration = 20.0;
	float	mSensity = 0.16 / 57.0;
	bool	mHasGun = false;

	//mEyeDirection.x 水平旋转  mEyeDirection.y 竖直方向旋转
	vec2	mEyeDirection;
	vec2	mFrontDirection;

	Actor() {
		readDRO("asset/models/yuan/ying/ying.dro");
		bindCamera(ca);
		removeAnimationShift(43);
		removeAnimationShift(49);
		removeAnimationShift(42);

		evtor.mousemove() = ([=](me& e)->bool {
			if (!mCamera)return false;
			mEyeDirection.x -= deltaX * mSensity;
			mFrontDirection.x -= deltaX * mSensity;
			if ((mEyeDirection.y < 0.3 && mEyeDirection.y>-0.5) || (mEyeDirection.y > 0.2999 && deltaY > 0) || (mEyeDirection.y < -0.499 && deltaY < 0))
				mEyeDirection.y -= deltaY * mSensity;
			if (mCurState == Fire)
				mModelTransform.q = qua(vec3(0, 1, 0), mFrontDirection.x);
			syncCamera();
			return false;
			});
		evtor.mousestick() = [&](me& e)->bool {
			if (!mCamera)return false;
			if (e.mBtn == BUTTON_LEFT) {
				mCamOffset.y += 0.05;
			}
			ef(e.mBtn == BUTTON_RIGHT) {
				mCamOffset.y -= 0.05;
			}
			syncCamera();
			return true;
		};
		evtor.keystick() = [&](ke& e)->bool {
			if (!mCamera)return false;
			return false;
		};
		evtor.keyup() = [&](ke& e)->bool {
			if (e.key == KEY_W || e.key == KEY_S || e.key == KEY_A || e.key == KEY_D)
				setState(Idle);
			return true;
		};
		evtor.keydown() = [&](ke& e)->bool {
			int idx = mCurAnimIndex;
			ActorState st = mCurState;
			if (!mCamera)return false;
			switch (e.key) {
			case KEY_W:
				setState(Run);
				break;
			case KEY_S:
				setState(Backward);
				break;
			case KEY_A:
				setState(Forward);
				break;
			case KEY_D:
				setState(Forward);
				break;
			case KEY_F:
				return false;
				//setState(Dance);
				break;
			case KEY_SPACE:
				play(42, 1.43, 100);
				mCurState = Run;
				mVelocity = 50; //mMaxVelocity = 20;
				timer((mAnims[42].mDuring + 100) / 1.43, [=]()->bool {
					if (mCurState != Run)return true;
					setState(st);
					return true;
					});
				break;
			default: return false;
			}
			return true;
		};
		evtor.mousescroll() = [&](me& e)->bool {
			mCamDistance -= e.y * 0.6;
			//mCamDistance = max(mCamDistance, 1.0f);
			//mCamDistance = min(mCamDistance, 10.0f);
			syncCamera();
			return true;
		};

		initBody();
		play(14);
		updatePose();
	}

	void moveto(const vec3& pos) {
		StaticObject::moveto(pos);
		syncCamera();
	}
	vec3 mEyeDirectionv() {
		return eulerDir(mEyeDirection.y, mEyeDirection.x);
	}
	vec3 mFrontDirectiontv() {
		return eulerDir(mFrontDirection.y, mFrontDirection.x);
	}
	vec3 leftv() {
		return qua(vec3(0, 1, 0), radians(90)).rotate(mFrontDirectiontv());
	}
	void syncCamera() {
		if (!mCamera)return;
		vec3 mEyeDirection = mEyeDirectionv();
		mCamera->moveto(mModelTransform * (mCamOffset + mViewpoint) - mEyeDirection * mCamDistance);
		mCamera->lookToDirection(mEyeDirection);
	}
	vec3 camerap() {
		return mModelTransform * (mCamOffset + mViewpoint) - mEyeDirectionv() * mCamDistance;
	}

	const int total = 40;
	void drawmHP() {
		float hp_w = 200;
		float hp_h = 15;
		float r = mHP / 100;
		float x = (win_w - hp_w) * 0.5; float y = win_h - 30;
		ptr.setColor(WHITE);
		ptr.fillRect(vec2(x, y), vec2(x + hp_w, y + hp_h));
		ptr.setColor(vec3(1 - r, r, 0));
		ptr.fillRect(vec2(x, y), vec2(x + hp_w * mHP * 0.01, y + hp_h));
	}
	void simulate(bool cd = false) {
		//drawmHP();
		if (cd) {
			mVelocity = 0;
			if (mCurState != Boxing)mCurState = Idle;
			return;
		}
		if (mCurState == Run) {
			mModelTransform.q = qua(vec3(0, 1, 0), mEyeDirection.x);
			mAcceleration = (mMaxVelocity - mVelocity) * 0.5;
			mVelocity = mVelocity + mAcceleration;
		}
		ef(mCurState == Idle) {
			mAcceleration = -mVelocity / 8.0;
			mVelocity = max(0.0f, mVelocity + mAcceleration);
		}
		ef(mCurState == Backward) {
			mModelTransform.q = qua(vec3(0, 1, 0), mEyeDirection.x);
			mAcceleration = -(mMaxVelocity - mVelocity) / 2.0;
			mVelocity = max((mVelocity + mAcceleration), -mMaxVelocity / 4.0f);
		}
		ef(mCurState == Forward) {
			mModelTransform.q = qua(vec3(0, 1, 0), mEyeDirection.x);
			mAcceleration = (mMaxVelocity - mVelocity) / 2.0;
			mVelocity = max((mVelocity + mAcceleration), mMaxVelocity / 4.0f);
		}
		ef(mCurState == Fire) {
			mAcceleration = (mMaxVelocity * 0.1 - mVelocity) * 0.05;
			mVelocity = min(mVelocity, mVelocity + mAcceleration);
		}
		if (abs(mVelocity) > 0.01) {
			forward(mVelocity / frameps);
		}
		else if (mCurState != Fire)mCurState = Idle;
	}

	void setState(ActorState s) {
		double transt = 150;
		mCurState = s;
		switch (s) {
		case Idle:
			play(14, 1.0, transt);
			break;
		case Forward:
			play(49, 1.0, transt);
			break;
		case Backward:
			play(49, -1.0, transt);
			break;
		case Dance:
			play(0, 1.0, transt);
			break;
		case Run:
			play(43, 1.43, transt);
			break;
		case Jump:
			play(30, 1.0, transt);
			break;
		case Boxing:

			break;
		default: break;
		}
	}

	void setCameraOffset(const vec3& offset) {
		if (!mCamera)return;
		vec3 t = mModelTransform * (offset + mViewpoint) - mEyeDirectionv() * mCamDistance;
		mCamera->transit(SQT(1.0, mCamera->mo.q, t), 200);
		timer(200.0, [=]()->bool {
			mCamOffset = offset;
			syncCamera();
			return true;
			});
	}

	//沿当前前进方向前进len长度
	void forward(float len) {
		vec3 mFrontDirectiont = len * mFrontDirectiontv();
		mModelTransform.t += mFrontDirectiont;
		if (mCamera)mCamera->mo.t += mFrontDirectiont;
	}
	void backward(float len) {
		forward(-len);
	}
	void leftward(float len) {
		vec3 lv = len * leftv();
		mModelTransform.t += lv;
		if (mCamera)mCamera->mo.t += lv;
	}
	void rightward(float len) {
		leftward(-len);
	}

	void bindCamera(Camera& cam) {
		this->mCamera = &cam;
		syncCamera();
	}
	void unbind() {
		this->mCamera = 0;
	}
private:
	void initBody() {
		mColliBody.initBody(Colli_Cube);
		mColliBody.body<cube>() = cube(vec3(-0.5, 1.8, -0.5), vec3(0.5, 1.8, -0.5), vec3(-0.5, 1.8, 0.5), vec3(-0.5, 0, -0.5));
	}

};