#pragma once
/*--------------------------------------------*/
//Warning: д���ļ��Ľṹ��Ҫ����������ݳ��ֵ�˳��
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
	string mName;//ͨ��/�ؽ�����
	vector<qua_t> mQuaternions;//���ͨ������Ԫ��
	vector<pos_t> mPositions;//λ��
	vector<sca_t> mScales;//����
	int mBoneId = 0;//���ͨ����Ӧ����һ�����
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
	//     �ֲ�����		ȫ������   ����ƫ�ƾ��������ƣ�����ֱ�����ɾ���������Ⱦ
	NonePose, LocalPose, GlobalPose, OffsetPose
};

// ͨ�������������ؽڣ�����
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