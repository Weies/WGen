#pragma once
#include"triangleMesh.h"
#include"../physics/collision_dectect.h"
#include"../ui/font.h"
#include"../ui/painter.h"

#define TEXTURE_COORD	0
#define SPHERE_COORD	1
#define CUBIC_COORD		2

class StaticObject :public Mesh {
public:
	StaticObject() :mModelTransform(SQT()), mColor(1.0, 1.0, 1.0, 1.0), mColliBody(Colli_None, mModelTransform) {}
	void setModel(const mat4& m) {
		mModelTransform = m;
	}
	void setModel(const SQT& sqt) {
		mModelTransform = sqt;
	}
	vec3 p() {
		return mModelTransform.p;
	}
	virtual void tranform(const SQT& s) {
		mModelTransform = mModelTransform * s;
	}
	virtual void translate(float x, float y, float z) {
		mModelTransform.t = mModelTransform.t + mModelTransform.s * mModelTransform.q.rotate({ x,y,z });
	}
	virtual void translate(vec3 v) {
		mModelTransform.t = mModelTransform.t + mModelTransform.s * mModelTransform.q.rotate(v);
	}
	virtual void moveto(const vec3& pos) {
		mModelTransform.t = pos;
	}
	virtual void scale(float x, float y, float z) {
		scale(vec3(x, y, z));
	}
	virtual void scale(const vec3& v) {
		/*for (int i = 0; i < meshes.size(); ++i) {
			auto& vt = meshes[i]..mVertices;
			for (int j = 0; j < meshes[i]..mVertices.size(); ++j) {
				vt[j].p *= v;
			}
			meshes[i].syncData();
		}
		for (int i = 0; i < anims.size(); ++i) {
			auto& an = anims[i];
			for (int j = 0; j < an.chans.size(); ++j) {
				auto& p = an.chans[j].poss;
				for (int k = 0; k < p.size(); ++k) {
					p[k].v *= v;
				}
			}
		}
		for (int i = 0; i < nBones; ++i) {
			jos[i].off_set.t *= v;
			jos[i].local.t *= v;
		}
		mColliBody.scale(v);*/
		mModelTransform.s *= v;
	}
	virtual void scale(float s) {
		mModelTransform.s *= s;
	}
	virtual void rotate(float degree, vec3 axis) {
		mModelTransform.q = mModelTransform.q * qua(axis, radians(degree), true);
	}
	virtual void setColor(const vec4& co) {
		mColor = co;
	}
	virtual void setColor(const Color& co) {
		mColor = co.vec4();
	}
	virtual void setColor(float r, float g, float b, float a = 1.0f) {
		mColor = Color(r, g, b, a).vec4();
	}

	virtual CDResult ColliDetect(const StaticObject& o)const {
		return mColliBody.detect(o.mColliBody);
	}
	virtual vec3 frontv() {
		return mModelTransform.q.rotate(vec3(0, 0, 1));
	}
	virtual vec3 leftv() {
		return mModelTransform.q.rotate(vec3(1, 0, 0));
	}

	void setCoordType(int texture_mTexCoordType) {
		mTexCoordType = texture_mTexCoordType;
	}
	void drawColliBody()const {
		mColliBody.applyModel();
		if (mColliBody.mType == Colli_Cube)
			ptr3.drawCube(mColliBody.body<cube>());
		ef(mColliBody.mType == Colli_Ball) {
			ptr3.drawSphere(mColliBody.body<ball>());
		}
	}
	vec4 mColor;
	SQT mModelTransform;
	mutable ColliBody mColliBody;
	int mTexCoordType = TEXTURE_COORD;
};

class SkeletonObject :public StaticObject {
public:
	vector<Animation>		mAnims;
	map<string, int>		mBoneIdMap;
	Skeleton				mSkeleton;
	Pose					mPose;//mPose保存的应该是偏移姿势
	Pose					mStartPose;//过渡开始的姿势，应该是局部姿势
	Pose					mTargetPose;
	double					mTransEndTime = 0.0;
	double					mTransStartTime;
	int						mNumBones;
	int						mCurAnimIndex = 0;
	bool					mIsPlaying = false;
	SkeletonObject(string const& path, bool gamma = false)
	{
		mIsGammaCorection = gamma;
		loadModel(path);
	}
	SkeletonObject() {}
	virtual ~SkeletonObject() {}

	// 路径中不要有中文
	void loadModel(string const& path, bool flip_UV = false, bool load_texture = true);

	bool hasBone() const {
		return  mNumBones > 0;
	}
	//应该保证 mBoneIdMap 不为空
	void addAnimation(SkeletonObject& from, int which = -1, float scale = 1.0f) {
		for (int i = 0; i < from.mAnims.size(); ++i) {
			if (which != -1 && which != i) continue;
			Animation an = from.mAnims[i];
			an.mNumBones = mNumBones;
			for (int j = 0; j < an.mChannels.size(); ++j) {
				auto it = mBoneIdMap.find(an.mChannels[j].mName);
				if (it != mBoneIdMap.end())
					an.mChannels[j].mBoneId = it->second;
				else an.mChannels[j].mBoneId = 0, debug("Unmapped bone : " + an.mChannels[j].mName);
			}
			if (scale != 1.0f) {
				for (int j = 0; j < an.mChannels.size(); ++j) {
					auto& pp = an.mChannels[j].mPositions;
					for (int k = 0; k < pp.size(); ++k) {
						pp[k].v *= scale;
					}
				}
			}
			an.genID();
			pushAnims(an);
		}
	}
	void addAnimation(const Animation& anim, float scale = 1.0f) {
		Animation an = anim;
		an.mNumBones = mNumBones;
		for (int j = 0; j < an.mChannels.size(); ++j) {
			auto it = mBoneIdMap.find(an.mChannels[j].mName);
			if (it != mBoneIdMap.end())
				an.mChannels[j].mBoneId = it->second;
			else an.mChannels[j].mBoneId = 0, debug("Unmapped bone : " + an.mChannels[j].mName);
		}
		if (scale != 1.0f) {
			for (int j = 0; j < an.mChannels.size(); ++j) {
				auto& pp = an.mChannels[j].mPositions;
				for (int k = 0; k < pp.size(); ++k) {
					pp[k].v *= scale;
				}
			}
		}
		an.genID();
		pushAnims(an);
	}
	virtual void clear() {
		Mesh::clear();
		mAnims.resize(0);
		mSkeleton.mJoints.resize(0);
		mPose.mPoses.resize(0);
		mBoneIdMap.clear();
		mNumBones = 0;
	}
	//动画过渡,target_mPose 是局部姿势
	void transit(const Pose& target_mPose, double time) {
		mTargetPose = target_mPose; mStartPose = mPose.toLocalPose(mSkeleton);
		for (int i = 0; i < mNumBones; ++i) {
			//debug << i << ", before: " << mPose[i].t << " , " << mStartPose[i].t << endl;
		}
		mTransEndTime = gameTime + time; mTransStartTime = gameTime;
	}

	void transit(const string& anim_mName, double time) {
		for (int i = 0; i < mAnims.size(); ++i) {
			if (anim_mName == mAnims[i].mName) {
				mTargetPose = mAnims[i].localPoseAt(mSkeleton, 0.001);
				break;
			}
		}
		mStartPose = mPose.toLocalPose(mSkeleton);
		mTransEndTime = gameTime + time; mTransStartTime = gameTime;
	}

	void applyPose(const Pose& p, bool sync_skeleton = false) {
		mPose = p.toOffsetPose(mSkeleton);
		if (!sync_skeleton)return;
		for (int i = 0; i < mNumBones; ++i) {
			mSkeleton[i].mCurTransform = mPose[i] * mSkeleton[i].mOffsetTransform.inv();
		}
	}

	//从当前播放的动画中提取姿态
	void updatePose() {
		if (mTransEndTime <= gameTime)mPose = mAnims[mCurAnimIndex].poseAt(mSkeleton);
		else
		{
			double val = (gameTime - mTransStartTime) / (mTransEndTime - mTransStartTime);
			mPose = mStartPose.lerp(mTargetPose, val).toOffsetPose(mSkeleton);
		}

	}
	// 将动画的矩阵调色板同步到显卡
	void syncPose(uint shader_id) {
		for (int i = 0; i < mNumBones; ++i) {
			curPose[i] = mPose[i].mat4();
		}
		int loc = glGetUniformLocation(shader_id, "curs");
		glUniformMatrix4fv(loc, mNumBones, GL_FALSE, value_ptr(curPose[0]));
	}

	//移除动画自带的位移
	bool removeAnimationShift(const string& anim_mName) {
		for (int i = 0; i < mAnims.size(); ++i) {
			if (mAnims[i].mName == anim_mName) {
				mAnims[i].removeShift();
				return true;
			}
		}
		return false;
	}
	bool removeAnimationShift(int an_index) {
		if (an_index > -1 && an_index < mAnims.size()) {
			mAnims[an_index].removeShift();
			return true;
		}
		return false;
	}

	//播放动画,填写一个不存在的动画名称将停止当前动画的播放.当transit_time大于0表示需要过渡
	bool play(const string& animation_mName, float speed = 1.0f, double transit_time = -1.0) {
		for (int i = 0; i < mAnims.size(); ++i) {
			if (mAnims[i].mName == animation_mName) {
				mCurAnimIndex = i;
				mIsPlaying = true;
				if (transit_time > 0) {
					transit(mAnims[i].localPoseAt(mSkeleton, 0.000), transit_time);
					static int hd = -1; timor.stop(hd);
					hd = timor.push(transit_time, [=]()->bool {
						mAnims[i].play(speed);
						return true;
						});
				}
				else mAnims[i].play(speed);
				return true;
			}
		}
		mIsPlaying = false;
		return false;
	}
	bool play(int animation_index, float speed = 1.0f, double transit_time = -1.0) {
		if (animation_index > -1 && animation_index < mAnims.size()) {
			mCurAnimIndex = animation_index;
			mIsPlaying = true;
			if (transit_time > 0) {
				transit(mAnims[mCurAnimIndex].localPoseAt(mSkeleton, 0.000), transit_time);
				static int hd = -1; timor.stop(hd);
				hd = timor.push(transit_time, [=]()->bool {
					mAnims[mCurAnimIndex].play(speed);
					return true;
					});
			}
			else mAnims[mCurAnimIndex].play(speed);
			return true;
		}
		mIsPlaying = false;
		return false;
	}
	void setPlaySpeed(float speed = 1.0f) {
		mAnims[mCurAnimIndex].setPlaySpeed(speed);
	}

	void stop() {
		mIsPlaying = false;
	}
	void removeSkeleton() {
		mNumBones = 0; mSkeleton.mJoints.resize(0);
	}
	Skeleton& skeleton() {
		return mSkeleton;
	}
	const Skeleton& skeleton()const {
		return mSkeleton;
	}
	virtual void swap(SkeletonObject& m) {
		Mesh::swap(m);
		mAnims.swap(m.mAnims);
		std::swap(mNumBones, m.mNumBones);
	}
	int queryAnim(const string& mName) {
		for (int i = 0; i < mAnims.size(); ++i)
			if (mAnims[i].mName == mName)return i;
		return -1;
	}
	int queryMesh(const string& mName) {
		for (int i = 0; i < mMeshes.size(); ++i)
			if (mMeshes[i].mName == mName)return i;
		return -1;
	}
	void pushAnims(Animation& anim) {
		mAnims.resize(mAnims.size() + 1);
		mAnims.back().swap(anim);
	}
	void addBones(bool normalize = true);
	void setupJoints();
	void makeLocal() {
		for (int i = 0; i < mNumBones; ++i) {
			auto& mJoints = mSkeleton[i];
			if (i > 0) {
				if (string(mJoints.mName).find("4") != string::npos || string(mJoints.mName).find("End") != string::npos) {
					mSkeleton[i].mLocalTransform = mSkeleton[mSkeleton[i].mParentId].mLocalTransform; mSkeleton[i].mIsGood = false;
				}
				else mSkeleton[i].mLocalTransform = mSkeleton[mSkeleton[i].mParentId].mOffsetTransform * mSkeleton[i].mOffsetTransform.inv();
			}
			else mSkeleton[i].mLocalTransform = mSkeleton[i].mOffsetTransform.inv();
		}
	}
	virtual void draw(uint shader_id)
	{
		if (mIsPlaying && mNumBones > 0)updatePose(), syncPose(shader_id);
		Mesh::draw(shader_id);
	}
	//将人物缩放到1.8米高,并将脚摆放至（0,0）点
	void normalizeCharacter(float height = 1.8) {
		//标准化模型
		float up_max = 0; float b_max = 10000; vec3 cen(0.0f); int total = 0;
		for (int i = 0; i < mMeshes.size(); ++i) {
			auto& v = mMeshes[i].mVertices; total += v.size();
			for (int j = 0; j < v.size(); ++j) {
				if (v[j].mPosition.y > up_max)up_max = v[j].mPosition.y;
				if (v[j].mPosition.y < b_max)b_max = v[j].mPosition.y;
				cen += v[j].mPosition;
			}
		}
		cen /= total;
		//标准人物高度1.8
		float scale_time = height / (up_max - b_max); cen *= scale_time;
		for (int i = 0; i < mMeshes.size(); ++i) {
			auto& v = mMeshes[i].mVertices;
			for (int j = 0; j < v.size(); ++j) {
				v[j].mPosition.y += b_max; v[j].mPosition *= scale_time;
				v[j].mPosition.x -= cen.x; v[j].mPosition.z -= cen.z;
			}
			mMeshes[i].syncData();
		}
		for (int i = 0; i < mNumBones; ++i) {
			mSkeleton[i].mOffsetTransform.t *= scale_time;
			mSkeleton[i].mLocalTransform.t *= scale_time;
		}
		for (int i = 0; i < mAnims.size(); ++i) {
			auto& an = mAnims[i];
			for (int j = 0; j < an.mChannels.size(); ++j) {
				auto& ch = an.mChannels[j];
				for (int k = 0; k < ch.mPositions.size(); ++k) {
					ch.mPositions[k].v *= scale_time;
				}
			}
		}
	}

	//直接可读对象，将当前的模型写成dro文件,注意filemName直接填文件名不填路径
	void makeDRO(string filemName = "") {
		DROModel m;
		m.mesh_num = mMeshes.size();
		strcpy(m.mDirectory, mDirectory.c_str());
		strcpy(m.mName, mName.c_str());
		m.gama_correction = mIsGammaCorection;
		if (filemName == "")filemName = mDirectory + '/' + mName.substr(0, mName.find_last_of('.'));
		else {
			filemName = filemName.substr(0, filemName.find_last_of('.'));
			ll p = filemName.find_last_of('/');
			if (p != string::npos) filemName = mDirectory + '/' + filemName.substr(p + 1);
		}
		fstream f; f.open(filemName + ".dro", ios::out | ios::binary);
		if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + mName);
		f.write((char*)&m, sizeof(DROModel));
		for (int i = 0; i < mMeshes.size(); ++i) {
			DROMeshHead h; auto& ms = mMeshes[i];
			strcpy(h.mName, mMeshes[i].mName.c_str());
			h.ver_num = ms.mVertices.size();
			h.ids_num = ms.mIndices.size();
			h.tex_num = ms.mTextures.size();
			f.write((char*)&h, sizeof(DROMeshHead));
			f.write((char*)&ms.mVertices[0], sizeof(vertex) * ms.mVertices.size());
			f.write((char*)&ms.mIndices[0], sizeof(int) * ms.mIndices.size());
			for (int j = 0; j < ms.mTextures.size(); ++j) {
				TexHead hd = GetTexHead(*ms.mTextures[j]);
				f.write((char*)&hd, sizeof(TexHead));
			}
		}
		f.close();
		if (mTextures.size() > 0)makeDROTexture(filemName + ".drot");
		if (mAnims.size() > 0)makeAnimDRO(filemName + ".droa");
	}
	//应该读取.dro文件
	void readDRO(const string& filePath) {
		fstream f; f.open(filePath, ios::in | ios::binary);
		if (filePath.substr(filePath.find_last_of('.') + 1) != "dro")excep(WERROR_FILE_LOAD, "File format not support: " + mName);
		if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + filePath);
		DROModel m;
		f.read((char*)&m, sizeof(DROModel));
		mDirectory = m.mDirectory;
		mName = m.mName;
		mIsGammaCorection = m.gama_correction;
		for (int i = 0; i < m.mesh_num; ++i) {
			DROMeshHead h;
			f.read((char*)&h, sizeof(DROMeshHead));
			MeshPatch mesh; mesh.mName = h.mName;
			mesh.mVertices.resize(h.ver_num); mesh.mIndices.resize(h.ids_num);
			f.read((char*)&mesh.mVertices[0], sizeof(vertex) * h.ver_num);
			f.read((char*)&mesh.mIndices[0], sizeof(int) * h.ids_num);
			for (int j = 0; j < h.tex_num; ++j) {
				TexHead hd;
				f.read((char*)&hd, sizeof(TexHead));
				Texture tex(GL_TEXTURE_2D);
				tex.mName = hd.mName; tex.h = hd.h; tex.w = hd.w; tex.mNumChannels = hd.channels;
				tex.mType = hd.type;
				int idx = queryTexture(tex.mName);
				if (idx > -1) {
					mesh.mTextures.push_back(&mTextures[idx]);
				}
				else {
					mTextures.push_back(tex);
					mesh.mTextures.push_back(&mTextures.back());
				}
			}
			mesh.setup();
			pushMesh(mesh);
		}
		f.close();
		readDROTexture(filePath.substr(0, filePath.find_last_of('.')) + ".drot");
		readAnimDRO(filePath.substr(0, filePath.find_last_of('.')) + ".droa");
	}

	void makeDROTexture(string filemName = "") {
		auto& ts = mTextures;
		if (filemName == "")filemName = mDirectory + '/' + mName.substr(0, mName.find_last_of('.')) + ".drot";
		if (filemName.substr(filemName.find_last_of('.') + 1) != "drot")excep(WERROR_FILE_LOAD, "File format not support: " + mName);
		fstream f; f.open(filemName, ios::out | ios::binary);
		if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + mName);
		DROTexHead head;
		head.obj_nums = ts.size();
		if (mName.size() > 27)mName.resize(27);
		strcpy(head.obj_mName, mName.c_str());
		f.write((char*)&head, sizeof(DROTexHead));
		for (int i = 0; i < ts.size(); ++i) {
			TexHead h;
			strcpy(h.mName, ts[i].mName.c_str());
			Image img; img.load(mDirectory + "/" + ts[i].mName);
			h.w = img.w; h.h = img.h; h.channels = img.mNumChannels; h.type = ts[i].mType;
			f.write((char*)&h, sizeof(TexHead));
			f.write((char*)img.data(), h.w * h.h * h.channels);
		}
		f.close();
	}
	//当加载模型没有选择load_texture时，可以用readDROTexture
	void readDROTexture(string filemName = "") {
		string nm = mName.substr(0, mName.find_last_of('.'));
		if (filemName == "")filemName = mDirectory + '/' + nm + ".drot";
		fstream f; f.open(filemName.c_str(), ios::in | ios::binary);
		if (!f.is_open())//excep(WERROR_FILE_LOAD, "Failed to open file: " + filemName);
			return;
		DROTexHead head;

		f.read((char*)&head, sizeof(DROTexHead));
		int num = head.obj_nums;
		TexHead h;
		for (int i = 0; i < num; ++i) {
			f.read((char*)&h, sizeof(TexHead));
			uchar* data = new uchar[h.w * h.h * h.channels];
			f.read((char*)data, h.w * h.h * h.channels);
			Image img;
			img.h = h.h; img.w = h.w; img.mNumChannels = h.channels; img.mData = data;
			int idx = queryTexture(h.mName); if (idx < 0)__debugbreak;
			mTextures[idx].setData(img); mTextures[idx].mType = h.type;
			delete[] data;
		}
		f.close();
	}

	//将动画写成dro文件，-1表示把所有动画写到文件
	void makeAnimDRO(string filemName = "", int idx = -1) {
		fstream f;
		if (filemName == "")filemName = mDirectory + '/' + mName.substr(0, mName.find_last_of('.')) + ".droa";
		else if (filemName.substr(filemName.find_last_of('.') + 1) != "droa")excep(WERROR_FILE_LOAD, "File format not support: " + mName);
		int nAnims; int start;
		if (idx < 0)nAnims = mAnims.size(), start = 0;
		else nAnims = 1, start = idx;
		const int const end = start + nAnims;
		f.open(filemName, ios::out | ios::binary);
		if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + mName);
		JointHead jh; jh.nAnims = nAnims; jh.nJoints = mNumBones;
		f.write((char*)&jh, sizeof(jh));
		for (int i = 0; i < mNumBones; ++i) {
			Joints mJoints;
			strcpy(mJoints.mName, mSkeleton[i].mName.c_str());
			mJoints.mParentId = mSkeleton[i].mParentId; mJoints.mOffsetTransform = mSkeleton[i].mOffsetTransform;
			f.write((char*)&mJoints, sizeof(mJoints));
		}
		for (int i = start; i < end; ++i) {
			AnimHead h; auto& an = mAnims[i];
			strcpy(h.mName, an.mName.c_str());
			h.frames = an.mNumFrames;
			h.during = an.mDuring;
			h.fps = an.mFps;
			h.channels = an.mChannels.size();
			f.write((char*)&h, sizeof(h));
			for (int j = 0; j < h.channels; ++j) {
				ChannelHead ch;
				strcpy(ch.mName, an.mChannels[j].mName.c_str());
				ch.nPoss = an.mChannels[j].mPositions.size();
				ch.nQuas = an.mChannels[j].mQuaternions.size();
				ch.nScas = an.mChannels[j].mScales.size();
				f.write((char*)&ch, sizeof(ChannelHead));
				if (ch.nQuas != 0)f.write((char*)(&an.mChannels[j].mQuaternions[0]), sizeof(qua_t) * an.mChannels[j].mQuaternions.size());
				if (ch.nPoss != 0)f.write((char*)(&an.mChannels[j].mPositions[0]), sizeof(pos_t) * an.mChannels[j].mPositions.size());
				if (ch.nScas != 0)f.write((char*)(&an.mChannels[j].mScales[0]), sizeof(sca_t) * an.mChannels[j].mScales.size());
			}
		}
		f.close();
	}

	void readAnimDRO(string filemName = "") {
		if (filemName == "")filemName = mDirectory + '/' + mName.substr(0, mName.find_last_of('.')) + ".drot";
		fstream f; f.open(filemName, ios::in | ios::binary);
		if (!f.is_open())return;
		JointHead jh;
		f.read((char*)&jh, sizeof(jh));
		mNumBones = jh.nJoints;
		char* unused = new char[1000000];
		for (int i = 0; i < jh.nJoints; ++i) {
			Joints mJoints;
			f.read((char*)&mJoints, sizeof(mJoints));
			mBoneIdMap[mJoints.mName] = i;
			mSkeleton[i].mName = mJoints.mName;
			mSkeleton[i].mParentId = mJoints.mParentId;
			mSkeleton[i].mOffsetTransform = mJoints.mOffsetTransform;
			if (i > 0) {
				if (string(mJoints.mName).find("4") != string::npos || string(mJoints.mName).find("End") != string::npos) {
					mSkeleton[i].mLocalTransform = mSkeleton[mSkeleton[i].mParentId].mLocalTransform; mSkeleton[i].mIsGood = false;
				}
				else mSkeleton[i].mLocalTransform = mSkeleton[mSkeleton[i].mParentId].mOffsetTransform * mSkeleton[i].mOffsetTransform.inv();
			}
			else mSkeleton[i].mLocalTransform = mSkeleton[i].mOffsetTransform.inv();
		}
		for (int i = 0; i < jh.nAnims; ++i) {
			AnimHead h;
			f.read((char*)&h, sizeof(AnimHead));
			Animation anim;
			anim.mName = h.mName; anim.mDuring = h.during; anim.mFps = h.fps;
			anim.mNumFrames = h.frames; anim.mChannels.resize(h.channels);
			anim.mNumBones = mNumBones;
			int id = 0;
			for (int j = 0; j < h.channels; ++j) {
				ChannelHead ch;
				f.read((char*)&ch, sizeof(ch));
				if (string(ch.mName) == string("")) {
					if (ch.nQuas != 0)f.read(unused, sizeof(qua_t) * ch.nQuas);
					if (ch.nPoss != 0)f.read(unused, sizeof(pos_t) * ch.nPoss);
					if (ch.nScas != 0)f.read(unused, sizeof(sca_t) * ch.nScas);
					continue;
				}
				anim.mChannels[id].mName = ch.mName;
				auto it = mBoneIdMap.find(ch.mName);
				if (it != mBoneIdMap.end())
					anim.mChannels[id].mBoneId = it->second;
				else anim.mChannels[id].mBoneId = 0, debug("Unmapped bone: " + string(ch.mName));
				anim.mChannels[id].mPositions.resize(ch.nPoss);
				anim.mChannels[id].mQuaternions.resize(ch.nQuas);
				anim.mChannels[id].mScales.resize(ch.nScas);
				if (ch.nQuas != 0)f.read((char*)&anim.mChannels[id].mQuaternions[0], sizeof(qua_t) * ch.nQuas);
				if (ch.nPoss != 0)f.read((char*)&anim.mChannels[id].mPositions[0], sizeof(pos_t) * ch.nPoss);
				if (ch.nScas != 0)f.read((char*)&anim.mChannels[id].mScales[0], sizeof(sca_t) * ch.nScas);
				++id;
			}
			anim.mChannels.resize(id);
			anim.genID();
			pushAnims(anim);
		}
		delete[] unused;
		f.close();
		if (jh.nAnims > 0) {
			mPose = mAnims[0].localPoseAt(mSkeleton, 0);
		}
	}

};
