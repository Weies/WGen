#pragma once
#include"../base/global_values.h"
#include"core/math/math_include.h"
#include"function/base/animation_base.h"
using namespace globals;




class Animation {
public:
	string			mName;
	vector<channel> mChannels;//通道的数目不一定等于骨骼的数目
	vector<int>		mIds;//遍历顺序
	int				mNumBones;
	float			mNumFrames;//总帧数
	float			mFps;//帧率
	float			mDuring = 1000.0f;//持续时间：毫秒
	float			mSpeed = 1.0f;//播放速度
	double			mStartTime = 0;

	/*Animation() :mFrames(0), mFps(0) {
		mStartTime = gameTime;
	}
	Animation(float total_mFrames, float mFps) :mFrames(total_mFrames), mFps(mFps) {}*/

	//数据填充完毕后务必调用genID()
	void genID() {
		mIds.resize(mNumBones); memset(&mIds[0], -1, 4 * mNumBones);
		for (int i = 0; i < mChannels.size(); ++i) {
			mIds[mChannels[i].mBoneId] = i;
		}
	}

	void play(float mSpeed = 1.0) {
		this->mSpeed = mSpeed;
		mStartTime = gameTime;
	}

	// 要更改播放速度时，请调用这个函数，不要直接更改mSpeed
	void setPlaySpeed(float mSpeed = 1.0f) {
		float time = (gameTime - mStartTime) * this->mSpeed;
		time = fmod(time, mDuring);
		mStartTime = gameTime - time / mSpeed;
		this->mSpeed = mSpeed;
	}

	void swap(Animation& otr) {
		mChannels.swap(otr.mChannels);
		mName.swap(otr.mName);
		mIds.swap(otr.mIds);
		std::swap(mNumBones, otr.mNumBones);
		std::swap(mDuring, otr.mDuring);
		std::swap(mFps, otr.mFps);
		std::swap(mNumFrames, otr.mNumFrames);
		std::swap(mSpeed, otr.mSpeed);
		std::swap(mStartTime, otr.mStartTime);
	}

	//获取局部姿势
	Pose localPoseAt(Skeleton& jos, float time = -1.0f)const {
		Pose po(LocalPose, mNumBones);
		for (int i = 0; i < mNumBones; ++i) {
			po[i] = (mIds[i] > 0) ? sqt(mIds[i], time) : jos[i].mLocalTransform;
		}
		return po;
	}
	//获取局部姿势
	//Pose localPoseAt(float time = -1.0f)const {
	//	Pose po(LocalPose, nBones);
	//	for (int i = 0; i < nBones; ++i) {
	//		po[i] = sqt(id[i], time);
	//	}
	//	return po;
	//}

	Pose globalPoseAt(Skeleton& jos, float time = -1.0f)const {
		Pose po(GlobalPose, mNumBones);
		jos[0].mCurTransform = sqt(mIds[0], time);
		po[0] = jos[0].mCurTransform * jos[0].mOffsetTransform;
		for (int i = 1; i < mNumBones; ++i) {
			SQT local = (mIds[i] > 0) ? sqt(mIds[i], time) : jos[i].mLocalTransform;
			jos[i].mCurTransform = jos[jos[i].mParentId].mCurTransform * local;
			po[i] = jos[i].mCurTransform;
		}
		return po;
	}

	Pose offsetPoseAt(Skeleton& jos, float time = -1.0f)const {
		Pose po(OffsetPose, mNumBones);
		jos[0].mCurTransform = sqt(mIds[0], time);
		po[0] = jos[0].mCurTransform * jos[0].mOffsetTransform;
		for (int i = 1; i < mNumBones; ++i) {
			SQT local = (mIds[i] > 0) ? sqt(mIds[i], time) : jos[i].mLocalTransform;
			jos[i].mCurTransform = jos[jos[i].mParentId].mCurTransform * local;
			po[i] = jos[i].mCurTransform * jos[i].mOffsetTransform;
		}
		return po;
	}

	// 根据给定的骨架，获取给定时间点的偏移姿态
	Pose poseAt(Skeleton& jos, float time = -1.0f) const {
		return offsetPoseAt(jos, time);
	}

	void removeShift() {
		const int  i = mIds[0];
		auto& v = mChannels[i].mPositions;
		for (int k = 0; k < v.size(); ++k) {
			v[k].v = v[0].v;
		}
	}

	SQT sqt(int which, float time = -1.0f) const {
		if (time < 0)time = (gameTime - mStartTime) * mSpeed;
		time = fmod(time, mDuring); if (time < 0)time += mDuring;
		return SQT(bfind(mChannels[which].mScales, time), bfind(mChannels[which].mQuaternions, time), bfind(mChannels[which].mPositions, time));
	}

	mat4 mat(int which, float time = -1.0f) const {
		if (time < 0)time = (gameTime - mStartTime) * mSpeed;
		time = fmod(time, mDuring); if (time < 0)time += mDuring;
		return SQT(bfind(mChannels[which].mScales, time), bfind(mChannels[which].mQuaternions, time), bfind(mChannels[which].mPositions, time)).mat4();
	}

	template<class T>
	T bfind(const vector<pai<T>>& v, float t) const {
		if (v.size() == 0) return T();
		int s = 0; int e = v.size() - 1; int mid = (s + e) / 2;
		while (s < e) {
			if (t == v[mid].t)break;
			else if (v[mid].t < t)s = mid + 1;
			else e = mid - 1;
			mid = (s + e) / 2;
		}
		if (mid < 1 || mid > v.size() - 3)
			return v[mid].v;

		if (t > v[mid + 1].t) mid += 1;
		else if (t < v[mid].t) mid -= 1;
		float t1 = v[mid].t; float t3 = v[mid + 1].t;
		t1 = (t - t1) / (t3 - t1);
		return lerp(v[mid].v, v[mid + 1].v, t1);
	}
};