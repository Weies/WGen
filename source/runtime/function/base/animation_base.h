#pragma once
/*--------------------------------------------*/
//Warning: 写到文件的结构不要随意更改数据出现的顺序
/*--------------------------------------------*/
#include"core/core.h"

template<class T>
struct pai {
	pai() {}
	pai(const T& vv, float time) {
		v = vv; t = time;
	}
	T v;
	float t;
};

using qua_t = pai<qua>;
using pos_t = pai<vec3>;
using sca_t = pai<float>;

struct channel {
public:
	void swap(channel& ch) {
		std::swap(mBoneId, ch.mBoneId);
		mName.swap(ch.mName);
		mQuaternions.swap(ch.mQuaternions);
		mPositions.swap(ch.mPositions);
		mScales.swap(ch.mScales);
	}
	string mName;//通道/关节名字
	vector<qua_t> mQuaternions;//这个通道的四元数
	vector<pos_t> mPositions;//位置
	vector<sca_t> mScales;//缩放
	int mBoneId = 0;//这个通道对应的哪一块骨骼
};

struct Joint {
	string mName;
	SQT mCurTransform;
	SQT mOffsetTransform;
	SQT mTransform;
	SQT mLocalTransform;
	int mParentId;
	bool mIsGood = true;
};

struct Skeleton {
public:
	Skeleton() : mNumJoints(65) { mJoints.resize(65); }
	Skeleton(int n_Joints) :mNumJoints(n_Joints) { mJoints.resize(n_Joints); }
	Skeleton(const Joint* j, int n_Joints) :mNumJoints(n_Joints) {
		mJoints.resize(n_Joints);
		for (int i = 0; i < n_Joints; ++i) {
			mJoints[i] = j[i];
		}
	}
	Skeleton(const Skeleton& s) {
		(*this) = s;
	}
	Skeleton& operator=(const Skeleton& k) {
		mJoints = k.mJoints;
		mNumJoints = k.mNumJoints;
		for (int i = 0; i < mNumJoints; ++i) {
			mJoints[i] = k.mJoints[i];
		}
		return *this;
	}
	Joint& operator[](int i) {
		return mJoints[i];
	}
	const Joint& operator[](int i)const {
		return mJoints[i];
	}

	vector<Joint>	mJoints;
	int				mNumJoints = 0;
};

enum PoseType {
	//     局部姿势		全局姿势   乘以偏移矩阵后的姿势，可以直接生成矩阵用于渲染
	NonePose, LocalPose, GlobalPose, OffsetPose
};

// 通道数即骨骼（关节）数量
struct Pose {
public:
	Pose() :mNumJoints(0) { }
	Pose(PoseType tp, int nJoints) :mType(tp), mNumJoints(nJoints) {
		mPoses.resize(nJoints);
	}
	Pose(const SQT* q, PoseType tp, int n_Joints) :mType(tp), mNumJoints(n_Joints) {
		mPoses.resize(n_Joints);
		memcpy(&mPoses[0], q, sizeof(n_Joints * sizeof(SQT)));
	}
	Pose(const Pose& p) {
		(*this) = p;
	}
	Pose& operator=(const Pose& p) {
		mPoses = p.mPoses;
		mNumJoints = p.mNumJoints; mType = p.mType;
		return *this;
	}

	SQT& operator[](int i) {
		return mPoses[i];
	}
	const SQT& operator[](int i)const {
		return mPoses[i];
	}

	Pose lerp(const Pose& p, float p_coff) {
		Pose pp(mType, mNumJoints);
		for (int i = 0; i < mNumJoints; ++i) {
			pp[i] = mPoses[i].lerp(p[i], p_coff);
		}
		return pp;
	}

	Pose toLocalPose(Skeleton& jos)const {
		ASSERT(mType != NonePose, "Unknown Pose type cannot be transformed");
		if (mType == LocalPose)return (*this);
		else
		{
			Pose p(LocalPose, mNumJoints);
			if (mType == GlobalPose) {
				jos[0].mCurTransform = mPoses[0];
				p[0] = jos[0].mCurTransform;
				for (int i = 1; i < mNumJoints; ++i) {
					p[i] = jos[jos[i].mParentId].mCurTransform.inv() * mPoses[i];
					jos[i].mCurTransform = mPoses[i];
				}
				return p;
			}
			else if (mType == OffsetPose)
			{
				for (int i = 0; i < mNumJoints; ++i) {
					p[i] = mPoses[i] * jos[i].mOffsetTransform.inv();
				}
				jos[0].mCurTransform = p[0];
				for (int i = 1; i < mNumJoints; ++i) {
					jos[i].mCurTransform = p[i];
					p[i] = jos[jos[i].mParentId].mCurTransform.inv() * p[i];
				}
				return p;
			}
		}
	}

	Pose toGlobalPose(Skeleton& jos)const {
		ASSERT(mType != NonePose, "Unknown Pose type cannot be transform");
		if (mType == GlobalPose)return (*this);
		else
		{
			Pose p(GlobalPose, mNumJoints);
			if (mType == LocalPose) {
				jos[0].mCurTransform = mPoses[0];
				p[0] = jos[0].mCurTransform * jos[0].mOffsetTransform;
				for (int i = 1; i < mNumJoints; ++i) {
					jos[i].mCurTransform = jos[jos[i].mParentId].mCurTransform * mPoses[i];
					p[i] = jos[i].mCurTransform;
				}
				return p;
			}
			else if (mType == OffsetPose)
			{
				for (int i = 0; i < mNumJoints; ++i) {
					p[i] = mPoses[i] * jos[i].mOffsetTransform.inv();
				}
				return p;
			}
		}
	}

	Pose toOffsetPose(Skeleton& jos)const {
		ASSERT(mType != NonePose, "Unknown Pose type cannot be transform");
		if (mType == OffsetPose)return (*this);
		else
		{
			Pose p(OffsetPose, mNumJoints);
			if (mType == LocalPose) {
				jos[0].mCurTransform = mPoses[0];
				p[0] = jos[0].mCurTransform * jos[0].mOffsetTransform;
				for (int i = 1; i < mNumJoints; ++i) {
					jos[i].mCurTransform = jos[jos[i].mParentId].mCurTransform * mPoses[i];
					p[i] = jos[i].mCurTransform * jos[i].mOffsetTransform;
				}
				return p;
			}
			else if (mType == GlobalPose)
			{
				for (int i = 0; i < mNumJoints; ++i) {
					p[i] = mPoses[i] * jos[i].mOffsetTransform;
				}
				return p;
			}
		}
	}

	//SQT* po = 0;
	vector<SQT> mPoses;
	int			mNumJoints = 0;
	PoseType	mType = NonePose;
};