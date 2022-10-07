#pragma once
#include"component.h"
#include"function/animation/animation.h"

class AnimationComponent :public Component {
public:

	RegisterComponent(Animation);

	Skeleton mSkeleton;
	vector<Animation> mAnim;
	uint mAnimIndex{ 0 };
	Pose mPose;

	bool play(const string& name, float speed = -1.0f) {
		for (int i = 0; i < mAnim.size(); ++i) {
			if (mAnim[i].mName == name) {
				mAnim[i].play(speed);
				mAnimIndex = i;
				return true;
			}
		}
		return false;
	}
	virtual void tick(float deltaTime)override {
		mPose = mAnim[mAnimIndex].poseAt(mSkeleton);
	}
	virtual void destory()override {}
	Pose getPose()const {
		return mPose;
	}
};