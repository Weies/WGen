#pragma once

#include"../base/global_values.h"
#include"../event/events.h"
#include"../animation/animation.h"
#include"../physics/collision_dectect.h"

#include"function/render/texture.h"
#include<fstream>
#include<array>
using namespace globals;


using pt = point<float>;

#define IS_BORDER 0
#define TEXTURE_COORD	0
#define SPHERE_COORD	1
#define CUBIC_COORD		2

/*--------------------------------------------*/
//Warning: 写到文件的结构不要随意更改数据出现的顺序
/*--------------------------------------------*/

//三角面片，由多个三角形组成
class MeshPatch
{
public:
	string				mName;
	vector<vertex>      mVertices;//顶点表
	vector<uint>		mIndices;//索引表
	vector<Texture*>	mTextures;//纹理表
	Transform			mTransform;

	void addTexture(Texture& tex) {
		mTextures.push_back(&tex);
	}
	void resetData();
	bool empty() const {
		return mVertices.size() == 0;
	}

	bool hasTexture() const {
		return mTextures.size() != 0;
	}

	MeshPatch() {}

	MeshPatch(vector<vertex>& mVertices, vector<uint>& mIndices, vector<Texture*>& mTextures, bool post_process = false)
	{
		parseVector(mVertices, mIndices, mTextures, post_process);
	}

	void parseVector(vector<vertex>& mVertices, vector<us>& mIndices, vector<Texture*>& mTextures, bool post_process = false) {
		clear();
		this->mVertices.swap(mVertices);
		this->mIndices.swap(mIndices);
		this->mTextures.swap(mTextures);
	}

	void parseOFF(const string& filePath, bool post_process = false) {
		clear();
		FILE* f = fopen(filePath.c_str(), "r");
		if (f == 0)excep(WERROR_FILE_LOAD, "Failed to open file : " + filePath);
		char c[100] = {};
		fscanf(f, "%s", c);
		int Vnum, Fnum; float x, y, z;
		fscanf(f, "%d%d%f", &Vnum, &Fnum, &x);
		while (Vnum--)
		{
			fscanf_s(f, "%f%f%f", &x, &y, &z);
			mVertices.push_back(vertex(x, y, z));
		}
		calcuNormal(false);
		fclose(f);

	}

	void parseArray(float* mVertices, int num_vertex, uint* mIndices, int num_face) {
		clear();
		float* v = mVertices;
		for (int i = 0; i < num_vertex; ++i) {
			this->mVertices.push_back(vertex(v[i * 3], v[i * 3 + 1], v[i * 3 + 2]));
		}
		this->mIndices = vector<uint>(mIndices, mIndices + num_face * 3);

		calcuNormal();
	}

	void parseArray(float* mVertices, int num_vertex) {
		clear();
		float* v = mVertices;
		for (int i = 0; i < num_vertex; ++i) {
			this->mVertices.push_back(vertex(v[i * 3], v[i * 3 + 1], v[i * 3 + 2]));
			this->mIndices.push_back(i);
		}

		calcuNormal();
	}

	//data每一个顶点的格式应该是[ vec3 pos, vec3 normal , vec2 texcoord ]
	void parseData(const float* data, int num_vtx, const uint* mIndices, int num_ids) {
		clear();
		const float* p = data;
		for (int i = 0; i < num_vtx; ++i, p += 8) {
			vertex vt(p, p + 3, p + 6);
			mVertices.push_back(vt);
		}
		this->mIndices.assign(mIndices, mIndices + num_ids);
		auto& id = this->mIndices;
	}



	void swap(MeshPatch& otr) {
		mVertices.swap(otr.mVertices);
		mIndices.swap(otr.mIndices);
		mTextures.swap(otr.mTextures);
		mName.swap(otr.mName);
	}

	void clear() {
		mVertices.clear(); mIndices.clear(); mTextures.clear();
	}

	//计算顶点的法向量
	void calcuNormal(bool flip_normal = false, bool sync = false);

	void calcuTB() {
		auto& vt = mVertices;
		for (int i = 0; i < mIndices.size(); i += 3) {
			us v1 = mIndices[i]; us v2 = mIndices[i + 1]; us v3 = mIndices[i + 2];
			float u1 = vt[v3].mTexCoord.x - vt[v1].mTexCoord.x;
			float w1 = vt[v3].mTexCoord.y - vt[v1].mTexCoord.y;
			float u2 = vt[v2].mTexCoord.x - vt[v1].mTexCoord.x;
			float w2 = vt[v2].mTexCoord.y - vt[v1].mTexCoord.y;
			float d = u1 * w2 - u2 * w1;
			vec4 v;
			v.x = w2 / d; v.y = -u2 / d; v.z = -w1 / d; v.w = u1 / d;
			u1 = v.x; w1 = v.y; u2 = v.z; w2 = v.w;
			vec3 p = vt[v3].mPosition - vt[v1].mPosition; vec3 q = vt[v2].mPosition - vt[v1].mPosition;
			vec3 t(u1 * p.x + w1 * q.x, u1 * p.y + w1 * q.y, u1 * p.z + w1 * q.z);
			vec3 b(u2 * p.x + w2 * q.x, u2 * p.y + w2 * q.y, u2 * p.z + w2 * q.z);
			t = normalize(t); b = normalize(b);
			vt[v1].mTangent = t; vt[v1].mBitangent = b;
			vt[v2].mTangent = t; vt[v2].mBitangent = b;
			vt[v3].mTangent = t; vt[v3].mBitangent = b;
		}
		resetData();
	}
protected:

	ll hash(ll a, ll b) {
		return a * b * 6170729 + (a + b) * 1254745 + 51155471 * (a * a + b * b) + a * 158547 / (b + 8131657) + b * 158547 / (a + 8131657);
	}

};

//网格模型，由多个三角面片组成
class Mesh
{
public:
	Array<Texture, 100>		mTextures;
	vector<MeshPatch>		mMeshes;
	string					mDirectory;//文件目录
	string					mName;//文件名
	Transform				mTransform;
	bool					mIsGammaCorection = false;



	Mesh() {}
	virtual ~Mesh() {
		for (int i = 0; i < mTextures.size(); ++i) {
			glDeleteTextures(1, &mTextures[i].mId);
		}
	}

	string format() {
		size_t p = mName.find_last_of('.');
		if (p != string::npos)return mName.substr(p + 1);
		return "Unknown";
	}

	bool hasTexture() const {
		return mTextures.size() > 0;
	}

	//to_whom 表示对谁添加纹理，-1对所有面片，0~i,表示对某一个面片,大于mMeshes的大小时，对最后一个添加
	void addTexture(const string& path, TextureType tp, int to_whom);
	void addTexture(const Texture& tex, int to_whom);

	virtual void clear() {
		mMeshes.resize(0);
		mTextures.resize(0);
		mDirectory = ""; mName = "";
	}

	void scaleTexture(int which = -1, float s = 1.0) {
		s = 1 / s;
		for (int i = 0; i < mMeshes.size(); ++i) {
			if (which != -1 && which != i)continue;
			auto& v = mMeshes[i].mVertices;
			for (auto& y : v) {
				y.mTexCoord *= s;
			}
		}
	}
	void scaleTexture(int which = -1, vec2 s = 1.0) {
		s = vec2(1 / s.x, 1 / s.y);
		for (int i = 0; i < mMeshes.size(); ++i) {
			if (which != -1 && which != i)continue;
			auto& v = mMeshes[i].mVertices;
			for (auto& y : v) {
				y.mTexCoord *= s;
			}
		}
	}

	void putToOrigin() {
		vec3 cen(0.0f); int total = 0;
		for (int i = 0; i < mMeshes.size(); ++i) {
			auto& v = mMeshes[i].mVertices; total += v.size();
			for (int j = 0; j < v.size(); ++j) {
				cen += v[j].mPosition;
			}
		}
		cen /= total;
		for (int i = 0; i < mMeshes.size(); ++i) {
			auto& v = mMeshes[i].mVertices;
			for (int j = 0; j < v.size(); ++j) {
				v[j].mPosition -= cen;
			}
			mMeshes[i].resetData();
		}
	}
	void rotateOnVertex(qua q) {
		for (int i = 0; i < mMeshes.size(); ++i) {
			auto& v = mMeshes[i].mVertices;
			for (int j = 0; j < v.size(); ++j) {
				v[j].mPosition = q.rotate(v[j].mPosition);
			}
			mMeshes[i].resetData();
		}
	}
	int queryTexture(const string& mName) {
		for (int i = 0; i < mTextures.size(); ++i) {
			if (mTextures[i].mName == mName)return i;
		}
		return -1;
	}

	void pushMesh(MeshPatch& mesh) {
		mMeshes.resize(mMeshes.size() + 1);
		mMeshes.back().swap(mesh);
	}

	virtual void swap(Mesh& m) {
		mDirectory.swap(m.mDirectory);
		mName.swap(m.mName);
		mTextures.swap(m.mTextures);
		mMeshes.swap(m.mMeshes);
		std::swap(mIsGammaCorection, m.mIsGammaCorection);
	}
	void loadTextures() {
		for (int i = 0; i < mTextures.size(); ++i) {
			Image img(mDirectory + '/' + mTextures[i].mName);
			mTextures[i].setData(img);
		}
	}

	void calcuNormal(bool flip_normal = false, bool sync = false) {
		for (int i = 0; i < mMeshes.size(); ++i) {
			mMeshes[i].calcuNormal(flip_normal, sync);
		}
	}

	void calcuTB() {
		for (int i = 0; i < mMeshes.size(); ++i) {
			mMeshes[i].calcuTB();
		}
	}

protected:
	// 注意下面的结构体都是直接写入文件的，不要轻易修改数据出现的数据
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
	TexHead GetTexHead(const Texture& tex) {
		TexHead ret;
		strcpy(ret.mName, tex.mName.c_str());
		ret.w = tex.w; ret.h = tex.h; ret.channels = tex.mNumChannels; ret.type = tex.mType;
		return ret;
	}
};


class SkeletalMesh :public Mesh
{
public:

	vector<Animation>		mAnims;
	map<string, int>		mBoneIdMap;
	Skeleton				mSkeleton;
	int						mNumBones;

	SkeletalMesh(string const& path, bool gamma = false)
	{
		mIsGammaCorection = gamma;
		loadModel(path);
	}
	SkeletalMesh() {}
	virtual ~SkeletalMesh() {}

	// 路径中不要有中文
	void loadModel(string const& path, bool flip_UV = false, bool load_texture = true);

	bool hasBone() const {
		return  mNumBones > 0;
	}
	//应该保证 mBoneIdMap 不为空
	void addAnimation(SkeletalMesh& from, int which = -1, float scale = 1.0f) {
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
		mBoneIdMap.clear();
		mNumBones = 0;
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

	void removeSkeleton() {
		mNumBones = 0; mSkeleton.mJoints.resize(0);
	}
	Skeleton& skeleton() {
		return mSkeleton;
	}
	const Skeleton& skeleton()const {
		return mSkeleton;
	}
	virtual void swap(SkeletalMesh& m) {
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
	}

};