//#pragma once
//
//#include"../base/global_values.h"
//#include"../event/events.h"
//#include"../animation/animation.h"
//#include"../physics/collision_dectect.h"
//
//#include"function/render/texture.h"
//#include<fstream>
//#include<array>
//using namespace globals;
//
//using pt = point<float>;
//
//#define IS_BORDER 0
//
///*--------------------------------------------*/
////Warning: д���ļ��Ľṹ��Ҫ����������ݳ��ֵ�˳��
///*--------------------------------------------*/
//
//
//struct edge {
//	edge() {}
//	edge(us origin_vertex, us next_edge, us face) {
//		vert = origin_vertex; next = next_edge; this->face = face;
//	}
//	us vert;
//	us next;
//	us opp = -1;
//	us face;
//
//	void set(us which, bool val) {
//		bitSet(bit, which, val);
//	}
//	bool check(us which) {
//		return bitTest(bit, which);
//	}
//	us bit = 0;
//};
//
//struct face {
//	face() {}
//	union { us e; us mEdgeIndex; };
//	vec3 mNormal;
//};
//
////������Ƭ���ɶ�����������
//class MeshPatch
//{
//public:
//	string				mName;
//	vector<vertex>      mVertices;//�����
//	vector<uint>		mIndices;//������
//	uint				mVAO, mVBO, mEBO;
//	vector<Texture*>	mTextures;//�����
//
//	vector<face>		mFaces;//���
//	vector<edge>		mEdges;//�߱�
//	using pa = pair<us, us>;
//	map<pa, us>			mVertexEdgeMap;
//	bool isComplete() const {
//		return mFaces.size() * 3 == mEdges.size() &&
//			mVertexEdgeMap.size() == mEdges.size();
//	}
//
//	void addTexture(Texture& tex) {
//		mTextures.push_back(&tex);
//	}
//	void resetData();
//	bool empty() const {
//		return mVertices.size() == 0;
//	}
//
//	bool hasTexture() const {
//		return mTextures.size() != 0;
//	}
//	~MeshPatch() {
//		/*glDeleteBuffers(1, &mVAO);
//		glDeleteBuffers(1, &mVBO);
//		glDeleteBuffers(1, &mEBO);*/
//	}
//	MeshPatch() {}
//
//	MeshPatch(vector<vertex>& mVertices, vector<uint>& mIndices, vector<Texture*>& mTextures, bool post_process = false)
//	{
//		parseVector(mVertices, mIndices, mTextures, post_process);
//	}
//
//	void parseVector(vector<vertex>& mVertices, vector<us>& mIndices, vector<Texture*>& mTextures, bool post_process = false) {
//		clear();
//		this->mVertices.swap(mVertices);
//		this->mIndices.swap(mIndices);
//		this->mTextures.swap(mTextures);
//		setup();
//	}
//
//	void parseOFF(const string& filePath, bool post_process = false) {
//		clear();
//		FILE* f = fopen(filePath.c_str(), "r");
//		if (f == 0)excep(WERROR_FILE_LOAD, "Failed to open file : " + filePath);
//		char c[100] = {};
//		fscanf(f, "%s", c);
//		int Vnum, Fnum; float x, y, z;
//		fscanf(f, "%d%d%f", &Vnum, &Fnum, &x);
//		while (Vnum--)
//		{
//			fscanf_s(f, "%f%f%f", &x, &y, &z);
//			mVertices.push_back(vertex(x, y, z));
//		}
//		int o, p, q;
//		int idx = -1;
//		while (Fnum--)
//		{
//			fscanf_s(f, "%d%d%d%d", &o, &o, &p, &q);
//			createFace(o, p, q, mFaces, mEdges, mVertexEdgeMap, mVertices);
//		}
//		calcuNormal(false);
//		fclose(f);
//
//		if (post_process) {
//			markVertexAndEdge();
//			deg3Clean();
//			makeIndices();
//		}
//
//		setup();
//	}
//
//	void parseArray(float* mVertices, int num_vertex, uint* mIndices, int num_face) {
//		clear();
//		float* v = mVertices;
//		for (int i = 0; i < num_vertex; ++i) {
//			this->mVertices.push_back(vertex(v[i * 3], v[i * 3 + 1], v[i * 3 + 2]));
//		}
//		this->mIndices = vector<uint>(mIndices, mIndices + num_face * 3);
//		for (int i = 0; i < num_face; ++i) {
//			createFace(mIndices[i * 3], mIndices[i * 3 + 1], mIndices[i * 3 + 2], mFaces, mEdges, mVertexEdgeMap, this->mVertices);
//		}
//		markVertexAndEdge();
//		calcuNormal();
//		setup();
//	}
//	void parseArray(float* mVertices, int num_vertex) {
//		clear();
//		float* v = mVertices;
//		for (int i = 0; i < num_vertex; ++i) {
//			this->mVertices.push_back(vertex(v[i * 3], v[i * 3 + 1], v[i * 3 + 2]));
//			this->mIndices.push_back(i);
//		}
//		for (int i = 0; i < num_vertex / 3; ++i) {
//			createFace(mIndices[i * 3], mIndices[i * 3 + 1], mIndices[i * 3 + 2], mFaces, mEdges, mVertexEdgeMap, this->mVertices);
//		}
//		markVertexAndEdge();
//		calcuNormal();
//		setup();
//	}
//
//	//dataÿһ������ĸ�ʽӦ����[ vec3 pos, vec3 normal , vec2 texcoord ]
//	void parseData(const float* data, int num_vtx, const uint* mIndices, int num_ids) {
//		clear();
//		const float* p = data;
//		for (int i = 0; i < num_vtx; ++i, p += 8) {
//			vertex vt(p, p + 3, p + 6);
//			mVertices.push_back(vt);
//		}
//		this->mIndices.assign(mIndices, mIndices + num_ids);
//		/*auto& id = this->mIndices;
//		for (int i = 0; i < id.size(); i += 3) {
//			createFace(id[i], id[i + 1], id[i + 2], mFaces, mEdges, mVertexEdgeMap, this->mVertices);
//		}*/
//		//markVertexAndEdge();
//		//calcuTB();
//		setup();
//	}
//
//	void markVertexAndEdge() {
//		for (int i = 0; i < mEdges.size(); ++i) {
//			us v1 = mEdges[i].vert; us v2 = mEdges[mEdges[i].next].vert;
//			if (mVertexEdgeMap.find(pa(v2, v1)) == mVertexEdgeMap.end())mEdges[i].set(IS_BORDER, true);
//			mVertices[v1].set(IS_BORDER, true); mVertices[v2].set(IS_BORDER, true);
//		}
//	}
//
//	void swap(MeshPatch& otr) {
//		mVertices.swap(otr.mVertices);
//		mIndices.swap(otr.mIndices);
//		mTextures.swap(otr.mTextures);
//		mFaces.swap(otr.mFaces);
//		mEdges.swap(otr.mEdges);
//		mVertexEdgeMap.swap(otr.mVertexEdgeMap);
//		mName.swap(otr.mName);
//		std::swap(mVAO, otr.mVAO);
//		std::swap(mVBO, otr.mVBO);
//		std::swap(mEBO, otr.mEBO);
//	}
//
//	//ϸ��
//	void tessellate();
//
//	//��
//	void simplify();
//
//	void clear() {
//		mFaces.clear(); mVertexEdgeMap.clear(); mEdges.clear(); mVertices.clear(); mIndices.clear(); mTextures.clear();
//	}
//
//	void draw(uint shader_id, int primitive = GL_TRIANGLES) const;
//
//	//���������棬��������߱�map
//	void createFace(us a, us b, us c, vector<face>& f, vector<edge>& eg, map<pa, us>& m, vector<vertex>& mVertices);
//
//	//���㶥��ķ�����
//	void calcuNormal(bool flip_normal = false, bool sync = false);
//
//	void calcuTB() {
//		auto& vt = mVertices;
//		for (int i = 0; i < mIndices.size(); i += 3) {
//			us v1 = mIndices[i]; us v2 = mIndices[i + 1]; us v3 = mIndices[i + 2];
//			float u1 = vt[v3].mTexCoord.x - vt[v1].mTexCoord.x;
//			float w1 = vt[v3].mTexCoord.y - vt[v1].mTexCoord.y;
//			float u2 = vt[v2].mTexCoord.x - vt[v1].mTexCoord.x;
//			float w2 = vt[v2].mTexCoord.y - vt[v1].mTexCoord.y;
//			float d = u1 * w2 - u2 * w1;
//			vec4 v;
//			v.x = w2 / d; v.y = -u2 / d; v.z = -w1 / d; v.w = u1 / d;
//			u1 = v.x; w1 = v.y; u2 = v.z; w2 = v.w;
//			vec3 p = vt[v3].mPosition - vt[v1].mPosition; vec3 q = vt[v2].mPosition - vt[v1].mPosition;
//			vec3 t(u1 * p.x + w1 * q.x, u1 * p.y + w1 * q.y, u1 * p.z + w1 * q.z);
//			vec3 b(u2 * p.x + w2 * q.x, u2 * p.y + w2 * q.y, u2 * p.z + w2 * q.z);
//			t = normalize(t); b = normalize(b);
//			vt[v1].mTangent = t; vt[v1].mBitangent = b;
//			vt[v2].mTangent = t; vt[v2].mBitangent = b;
//			vt[v3].mTangent = t; vt[v3].mBitangent = b;
//		}
//		resetData();
//	}
//
//	//�������ݵ��Կ�
//	void setup();
//	//������ͬ�����Կ��������µ����ݷ��͵��Կ�
//	void syncData() {
//		glBindVertexArray(mVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//
//		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(vertex), &mVertices[0], GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint), &mIndices[0], GL_STATIC_DRAW);
//	}
//
//protected:
//	//ɾ������Ϊ���Ķ���
//	void deg3Clean();
//
//	//����������������
//	void makeIndices();
//
//	ll hash(ll a, ll b) {
//		return a * b * 6170729 + (a + b) * 1254745 + 51155471 * (a * a + b * b) + a * 158547 / (b + 8131657) + b * 158547 / (a + 8131657);
//	}
//
//	//query oppsite vertex index
//	us qov(us e)
//	{
//		return mEdges[mEdges[mEdges[mEdges[e].opp].next].next].vert;
//	}
//
//	//query adjacent vertex mIndices
//	void qav(us v, vector<us>& ad) {
//		auto& vt = mVertices;
//		us ce = vt[v].out;
//		ad.push_back(mEdges[mEdges[ce].next].vert);
//
//		us of = mEdges[vt[v].out].face;
//		us cf = mEdges[mEdges[ce].opp].face;
//
//		while (cf != of) {
//			us adj = qov(ce);
//			ad.push_back(adj);
//			ce = mEdges[mEdges[ce].opp].next;
//			cf = mEdges[mEdges[ce].opp].face;
//		}
//	}
//
//	//��ģ��ʱ�����µ�������
//	void SPFMakeFace(us a, us b, us c, map<us, vertex>& mv, map<us, face>& mf, map<us, edge>& mee, us sz);
//};
//
////����ģ�ͣ��ɶ��������Ƭ���
//class Mesh
//{
//public:
//	Array<Texture, 100>		mTextures;
//	vector<MeshPatch>		mMeshes;
//	string					mDirectory;//�ļ�Ŀ¼
//	string					mName;//�ļ���
//	bool					mIsGammaCorection = false;
//	bool					mIsReverse = true;//�Ƿ�����Ⱦģ��
//
//	Mesh() {}
//	virtual ~Mesh() {
//		for (int i = 0; i < mTextures.size(); ++i) {
//			glDeleteTextures(1, &mTextures[i].mId);
//		}
//	}
//
//	string format() {
//		size_t p = mName.find_last_of('.');
//		if (p != string::npos)return mName.substr(p + 1);
//		return "Unknown";
//	}
//
//	bool hasTexture() const {
//		return mTextures.size() > 0;
//	}
//
//	//to_whom ��ʾ��˭�������-1��������Ƭ��0~i,��ʾ��ĳһ����Ƭ,����mMeshes�Ĵ�Сʱ�������һ�����
//	void addTexture(const string& path, TextureType tp, int to_whom);
//	void addTexture(const Texture& tex, int to_whom);
//
//	virtual void clear() {
//		mMeshes.resize(0);
//		mTextures.resize(0);
//		mDirectory = ""; mName = "";
//	}
//
//	virtual void draw(uint shader_id, int primitive = GL_TRIANGLES) const
//	{
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			int idx = mIsReverse ? mMeshes.size() - 1 - i : i;
//			mMeshes[idx].draw(shader_id, primitive);
//		}
//	}
//
//	void scaleTexture(int which = -1, float s = 1.0) {
//		s = 1 / s;
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			if (which != -1 && which != i)continue;
//			auto& v = mMeshes[i].mVertices;
//			for (auto& y : v) {
//				y.mTexCoord *= s;
//			}
//			mMeshes[i].syncData();
//		}
//	}
//	void scaleTexture(int which = -1, vec2 s = 1.0) {
//		s = vec2(1 / s.x, 1 / s.y);
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			if (which != -1 && which != i)continue;
//			auto& v = mMeshes[i].mVertices;
//			for (auto& y : v) {
//				y.mTexCoord *= s;
//			}
//			mMeshes[i].syncData();
//		}
//	}
//
//
//	void putToOrigin() {
//		vec3 cen(0.0f); int total = 0;
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			auto& v = mMeshes[i].mVertices; total += v.size();
//			for (int j = 0; j < v.size(); ++j) {
//				cen += v[j].mPosition;
//			}
//		}
//		cen /= total;
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			auto& v = mMeshes[i].mVertices;
//			for (int j = 0; j < v.size(); ++j) {
//				v[j].mPosition -= cen;
//			}
//			mMeshes[i].resetData();
//		}
//	}
//	void rotateOnVertex(qua q) {
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			auto& v = mMeshes[i].mVertices;
//			for (int j = 0; j < v.size(); ++j) {
//				v[j].mPosition = q.rotate(v[j].mPosition);
//			}
//			mMeshes[i].resetData();
//		}
//	}
//	int queryTexture(const string& mName) {
//		for (int i = 0; i < mTextures.size(); ++i) {
//			if (mTextures[i].mName == mName)return i;
//		}
//		return -1;
//	}
//
//	void pushMesh(MeshPatch& mesh) {
//		mMeshes.resize(mMeshes.size() + 1);
//		mMeshes.back().swap(mesh);
//	}
//
//	virtual void swap(Mesh& m) {
//		mDirectory.swap(m.mDirectory);
//		mName.swap(m.mName);
//		mTextures.swap(m.mTextures);
//		mMeshes.swap(m.mMeshes);
//		std::swap(mIsGammaCorection, m.mIsGammaCorection);
//	}
//	void loadTextures() {
//		for (int i = 0; i < mTextures.size(); ++i) {
//			Image img(mDirectory + '/' + mTextures[i].mName);
//			mTextures[i].setData(img);
//		}
//	}
//
//	void calcuNormal(bool flip_normal = false, bool sync = false) {
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			mMeshes[i].calcuNormal(flip_normal, sync);
//		}
//	}
//
//	void calcuTB() {
//		for (int i = 0; i < mMeshes.size(); ++i) {
//			mMeshes[i].calcuTB();
//		}
//	}
//
//protected:
//	// ע������Ľṹ�嶼��ֱ��д���ļ��ģ���Ҫ�����޸����ݳ��ֵ�����
//	friend class Importer;
//	static mat4 curPose[500];
//	struct Joints {
//		char mName[60];
//		int mParentId; mat4 mOffsetTransform;
//	};
//
//	struct JointHead {
//		int nAnims;
//		int nJoints;
//	};
//
//	struct AnimHead {
//		char mName[64] = {};
//		int frames;
//		float fps;
//		float during;
//		int channels;
//	};
//	struct ChannelHead {
//		char mName[64] = {};
//		int nQuas;
//		int nPoss;
//		int nScas;
//	};
//
//	struct DROModel {
//		int mesh_num;
//		char mDirectory[124] = {};
//		char mName[62] = {};
//		bool has_bone; bool gama_correction;
//	};
//	struct DROMeshHead {
//		char mName[64];
//		int ver_num;//������
//		int ids_num;//������
//		int tex_num;//������
//	};
//
//	//д���ļ���ֱ�ӿɶ�����
//	struct TexHead {
//		char mName[48] = {};
//		int w; int h; int channels; TextureType type;
//	};
//	//ֱ�ӿɶ�����
//	struct DROTexHead {
//		char obj_mName[28] = {};
//		int obj_nums;
//	};
//	TexHead GetTexHead(const Texture& tex) {
//		TexHead ret;
//		strcpy(ret.mName, tex.mName.c_str());
//		ret.w = tex.w; ret.h = tex.h; ret.channels = tex.mNumChannels; ret.type = tex.mType;
//		return ret;
//	}
//};
//
