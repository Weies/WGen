#pragma once
#include"core/math/math_include.h"
#include"../base/encoder.h"
#include"resource/resource_handle.h"
#include"scene_buffer.h"
#include"function/animation/animation.h"
#include"function/render/texture.h"

#define JoinIdenticalVertices		2ll
#define Triangulate					8ll
#define GenNormals					32ll
#define GenSmoothNormals			64ll
#define LimitBoneWeights			512ll
#define OptimizeMeshes				2097152ll
#define FlipUV						8388608ll
#define LoadTextures				(1ll << 33)
#define LoadMeshes					(1ll << 34)
#define LoadAnimations				(1ll << 35)

#define Import_Mask  (Triangulate | GenNormals | LoadTextures| LoadMeshes| LoadAnimations)
#define Export_Mask 0

class Importer {
public:
	Importer();
	// 导入时Windows默认使用GBK编码，所以会自动将文件导入为GBK
	bool Import(ModelHandle& m, const string& filePath, ll mask = Import_Mask);
	bool Import(const string& filePath, ModelHandle& m, bool load_texture = true,
		bool load_meshes = true, bool load_anims = true, bool flip_uv = false) {
		ll mask = (Triangulate | GenNormals);
		if (load_texture)mask |= LoadTextures;
		if (flip_uv)mask |= FlipUV;
		if (load_meshes)mask |= LoadMeshes;
		if (load_anims)mask |= LoadAnimations;
		return Import(m, filePath, mask);
	}

	////直接可读对象，将当前的模型写成dro文件,注意filemName直接填文件名不填路径
	//void makeDRO(string filemName = "") {
	//	DROModel m;
	//	m.mesh_num = mMeshes.size();
	//	strcpy(m.mDirectory, mDirectory.c_str());
	//	strcpy(m.mName, mName.c_str());
	//	m.gama_correction = mIsGammaCorection;
	//	if (filemName == "")filemName = mDirectory + '/' + mName.substr(0, mName.find_last_of('.'));
	//	else {
	//		filemName = filemName.substr(0, filemName.find_last_of('.'));
	//		ll p = filemName.find_last_of('/');
	//		if (p != string::npos) filemName = mDirectory + '/' + filemName.substr(p + 1);
	//	}
	//	fstream f; f.open(filemName + ".dro", ios::out | ios::binary);
	//	if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + mName);
	//	f.write((char*)&m, sizeof(DROModel));
	//	for (int i = 0; i < mMeshes.size(); ++i) {
	//		DROMeshHead h; auto& ms = mMeshes[i];
	//		strcpy(h.mName, mMeshes[i].mName.c_str());
	//		h.ver_num = ms.mVertices.size();
	//		h.ids_num = ms.mIndices.size();
	//		h.tex_num = ms.mTextures.size();
	//		f.write((char*)&h, sizeof(DROMeshHead));
	//		f.write((char*)&ms.mVertices[0], sizeof(vertex) * ms.mVertices.size());
	//		f.write((char*)&ms.mIndices[0], sizeof(int) * ms.mIndices.size());
	//		for (int j = 0; j < ms.mTextures.size(); ++j) {
	//			TexHead hd = GetTexHead(*ms.mTextures[j]);
	//			f.write((char*)&hd, sizeof(TexHead));
	//		}
	//	}
	//	f.close();
	//	if (mTextures.size() > 0)makeDROTexture(filemName + ".drot");
	//	if (mAnims.size() > 0)makeAnimDRO(filemName + ".droa");
	//}
	//
	//应该读取.dro文件

	void readDRO(ModelHandle& model, const string& filePath) {
		//m.

		fstream f; f.open(filePath, ios::in | ios::binary);
		if (filePath.substr(filePath.find_last_of('.') + 1) != "dro")excep(WERROR_FILE_LOAD, "File format not support: " + filePath);
		if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + filePath);
		DROModel m;
		f.read((char*)&m, sizeof(DROModel));

		vector<vertex> mVertices; vector<uint> mIndices;
		for (int i = 0; i < m.mesh_num; ++i) {
			DROMeshHead h;
			f.read((char*)&h, sizeof(DROMeshHead));

			mVertices.resize(h.ver_num); mIndices.resize(h.ids_num);
			f.read((char*)&mVertices[0], sizeof(vertex) * h.ver_num);
			f.read((char*)&mIndices[0], sizeof(int) * h.ids_num);
			MaterialDesc mat;
			for (int j = 0; j < h.tex_num; ++j) {
				TexHead hd;
				f.read((char*)&hd, sizeof(TexHead));
				switch (hd.type)
				{
				case texture_base_color:
					mat.mBaseColorFile = hd.mName;
					break;
				case texture_diffuse:
					mat.mDiffuseMapFile = hd.mName;
					break;
				case texture_specular:
					mat.mSpecularMapFile = hd.mName;
					break;
				case texture_metalness:
					mat.mMetallicMapFile = hd.mName;
					break;
				case texture_normal:
					mat.mNormalMapFile = hd.mName;
					break;
				case texture_abient_occlusion:
					mat.mOcculusionMapFile = hd.mName;
					break;
				case texture_diffuse_roughness:
					mat.mRoughnessMapFile = hd.mName;
					break;
				default:
					__debugbreak();
					break;
				}
			}
			auto vbh = SceneBuffer::genVertexBuffer(mVertices);
			auto ibh = SceneBuffer::genIndexBuffer(mIndices);

			model.mMeshHandles.push_back({ vbh,ibh,nullptr });
		}
		f.close();
		//readDROTexture(filePath.substr(0, filePath.find_last_of('.')) + ".drot");
		//readAnimDRO(filePath.substr(0, filePath.find_last_of('.')) + ".droa");
	}

	//void makeDROTexture(string filemName = "") {
	//	auto& ts = mTextures;
	//	if (filemName == "")filemName = mDirectory + '/' + mName.substr(0, mName.find_last_of('.')) + ".drot";
	//	if (filemName.substr(filemName.find_last_of('.') + 1) != "drot")excep(WERROR_FILE_LOAD, "File format not support: " + mName);
	//	fstream f; f.open(filemName, ios::out | ios::binary);
	//	if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + mName);
	//	DROTexHead head;
	//	head.obj_nums = ts.size();
	//	if (mName.size() > 27)mName.resize(27);
	//	strcpy(head.obj_mName, mName.c_str());
	//	f.write((char*)&head, sizeof(DROTexHead));
	//	for (int i = 0; i < ts.size(); ++i) {
	//		TexHead h;
	//		strcpy(h.mName, ts[i].mName.c_str());
	//		Image img; img.load(mDirectory + "/" + ts[i].mName);
	//		h.w = img.w; h.h = img.h; h.channels = img.mNumChannels; h.type = ts[i].mType;
	//		f.write((char*)&h, sizeof(TexHead));
	//		f.write((char*)img.data(), h.w * h.h * h.channels);
	//	}
	//	f.close();
	//}
	//当加载模型没有选择load_texture时，可以用readDROTexture
	void readDROTexture(const string& filemName = "") {
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
			SceneBuffer::genTextureBuffer(img);
			delete[] data;
		}
		f.close();
	}

	////将动画写成dro文件，-1表示把所有动画写到文件
	//void makeAnimDRO(string filemName = "", int idx = -1) {
	//	fstream f;
	//	if (filemName == "")filemName = mDirectory + '/' + mName.substr(0, mName.find_last_of('.')) + ".droa";
	//	else if (filemName.substr(filemName.find_last_of('.') + 1) != "droa")excep(WERROR_FILE_LOAD, "File format not support: " + mName);
	//	int nAnims; int start;
	//	if (idx < 0)nAnims = mAnims.size(), start = 0;
	//	else nAnims = 1, start = idx;
	//	const int const end = start + nAnims;
	//	f.open(filemName, ios::out | ios::binary);
	//	if (!f.is_open())excep(WERROR_FILE_LOAD, "Failed to open file: " + mName);
	//	JointHead jh; jh.nAnims = nAnims; jh.nJoints = mNumBones;
	//	f.write((char*)&jh, sizeof(jh));
	//	for (int i = 0; i < mNumBones; ++i) {
	//		Joints mJoints;
	//		strcpy(mJoints.mName, mSkeleton[i].mName.c_str());
	//		mJoints.mParentId = mSkeleton[i].mParentId; mJoints.mOffsetTransform = mSkeleton[i].mOffsetTransform;
	//		f.write((char*)&mJoints, sizeof(mJoints));
	//	}
	//	for (int i = start; i < end; ++i) {
	//		AnimHead h; auto& an = mAnims[i];
	//		strcpy(h.mName, an.mName.c_str());
	//		h.frames = an.mNumFrames;
	//		h.during = an.mDuring;
	//		h.fps = an.mFps;
	//		h.channels = an.mChannels.size();
	//		f.write((char*)&h, sizeof(h));
	//		for (int j = 0; j < h.channels; ++j) {
	//			ChannelHead ch;
	//			strcpy(ch.mName, an.mChannels[j].mName.c_str());
	//			ch.nPoss = an.mChannels[j].mPositions.size();
	//			ch.nQuas = an.mChannels[j].mQuaternions.size();
	//			ch.nScas = an.mChannels[j].mScales.size();
	//			f.write((char*)&ch, sizeof(ChannelHead));
	//			if (ch.nQuas != 0)f.write((char*)(&an.mChannels[j].mQuaternions[0]), sizeof(qua_t) * an.mChannels[j].mQuaternions.size());
	//			if (ch.nPoss != 0)f.write((char*)(&an.mChannels[j].mPositions[0]), sizeof(pos_t) * an.mChannels[j].mPositions.size());
	//			if (ch.nScas != 0)f.write((char*)(&an.mChannels[j].mScales[0]), sizeof(sca_t) * an.mChannels[j].mScales.size());
	//		}
	//	}
	//	f.close();
	//}

	void readAnimDRO(const string& filemName = "") {
		fstream f; f.open(filemName, ios::in | ios::binary);
		if (!f.is_open())return;
		JointHead jh;
		f.read((char*)&jh, sizeof(jh));
		char* unused = new char[1000000];
		int mNumBones = jh.nJoints;
		for (int i = 0; i < jh.nJoints; ++i) {
			Joints mJoints;
			f.read((char*)&mJoints, sizeof(mJoints));
			/*mBoneIdMap[mJoints.mName] = i;
			mSkeleton[i].mName = mJoints.mName;
			mSkeleton[i].mParentId = mJoints.mParentId;
			mSkeleton[i].mOffsetTransform = mJoints.mOffsetTransform;
			if (i > 0) {
				if (string(mJoints.mName).find("4") != string::npos || string(mJoints.mName).find("End") != string::npos) {
					mSkeleton[i].mLocalTransform = mSkeleton[mSkeleton[i].mParentId].mLocalTransform; mSkeleton[i].mIsGood = false;
				}
				else mSkeleton[i].mLocalTransform = mSkeleton[mSkeleton[i].mParentId].mOffsetTransform * mSkeleton[i].mOffsetTransform.inv();
			}
			else mSkeleton[i].mLocalTransform = mSkeleton[i].mOffsetTransform.inv();*/
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
				/*auto it = mBoneIdMap.find(ch.mName);
				if (it != mBoneIdMap.end())
					anim.mChannels[id].mBoneId = it->second;
				else anim.mChannels[id].mBoneId = 0, debug("Unmapped bone: " + string(ch.mName));*/
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
			//pushAnims(anim);
		}
		delete[] unused;
		f.close();
		if (jh.nAnims > 0) {
			//mPose = mAnims[0].localPoseAt(mSkeleton, 0);
		}
	}

	friend class Importer;
	static mat4 curPose[500];
	struct Joints {
		char mName[60];
		int mParentId; mat4 mOffsetTransform;
	};

	struct JointHead {
		int nAnims;
		int nJoints;
	};

	struct AnimHead {
		char mName[64] = {};
		int frames;
		float fps;
		float during;
		int channels;
	};
	struct ChannelHead {
		char mName[64] = {};
		int nQuas;
		int nPoss;
		int nScas;
	};

	struct DROModel {
		int mesh_num;
		char mDirectory[124] = {};
		char mName[62] = {};
		bool has_bone; bool gama_correction;
	};
	struct DROMeshHead {
		char mName[64];
		int ver_num;//顶点数
		int ids_num;//索引数
		int tex_num;//纹理数
	};

	//写到文件的直接可读纹理
	struct TexHead {
		char mName[48] = {};
		int w; int h; int channels; TextureType type;
	};
	//直接可读对象
	struct DROTexHead {
		char obj_mName[28] = {};
		int obj_nums;
	};
	// 导出时为了满足软件的读取需求，可以单独指定编码格式
	//bool Export(const string& filePath, ll mask = Export_Mask, CodeType tp = gb2312);

	//导出一个MeshModel对象
	//static bool Export(const SkeletonObject& m, const string& filePath, ll mask = Export_Mask, CodeType tp = gb2312);
	//~Importer();
	void* imp;
	void* hand;
};