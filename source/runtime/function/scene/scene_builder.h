#pragma once
#include"scene_buffer.h"
#include"model_importer.h"


//SceneBuilder 一定会分配新内存，但是SceneManager可能不分配新内存
class SceneBuilder {
public:
	static Importer imp;

	static MeshHandle loadMesh(const string& mesh_file) {
		if (mesh_file.empty())return MeshHandle{};
		if (mesh_file[0] == '[') {
			//const char* p = &mesh_file[1];
			int p = mesh_file.find('{');
			string ob = string(mesh_file.begin() + 1, mesh_file.begin() + p);

		}
		return MeshHandle();
	}



	static ModelDesc loadModel(const GameObjectDesc& desc) {
		auto& model_file = desc.mMeshFile;
		ModelDesc ret;
		if (model_file.empty())return ret;
		/*预定义对象，直接用代码生成*///[Sphere{36}]
		if (model_file[0] == '[') {
			//const char* p = &mesh_file[1];
			int p = model_file.find('{');
			string ob = string(model_file.begin() + 1, model_file.begin() + p);
			if (ob == "Sphere") {
				int seg = stoi(model_file.substr(p + 5));
				ret.mHandles.push_back(buildSphere(seg));
				if (desc.mCompDescs.size() != 0)
					ret.mMaterials.push_back(desc.mCompDescs[0].mMaterialDesc);
				else ret.mMaterials.push_back({});
				return ret;
			}
			return ModelDesc{};
		}
		string s = desc.mMeshFile;

		/*从文件中加载模型*/

		if (s.substr(s.find_last_of('.') + 1) == "dro") {
			imp.readDRO(ret, s);
		}
		else imp.Import(ret, desc.mMeshFile);
		return ret;
	}

	static ModelDesc loadModel(const string& model_file) {
		if (model_file.empty())return ModelDesc();
		if (model_file[0] == '[') {
			//const char* p = &mesh_file[1];
			int p = model_file.find('{');
			string ob = string(model_file.begin() + 1, model_file.begin() + p);
			if (ob == "Sphere") {
				int seg = stoi(model_file.substr(p + 5));
				auto hand = buildSphere(seg);
				return ModelDesc{ {hand},{MaterialDesc()} };
			}
			return ModelDesc{};
		}

		/*从文件中加载模型*/
	}

	static TextureHandle loadTexture(const string& texture_file) {
		Image img;
		img.load(texture_file);
		TextureHandle hand = SceneBuffer::genTextureBuffer(img);
		img.free();
		return hand;
	}
	static TextureHandle loadCubeMap(const string& directory, const string  path[6]) {
		int mTarget = GL_TEXTURE_CUBE_MAP; uint mId;
		glGenTextures(1, &mId);
		glBindTexture(mTarget, mId);
		Image img;
		for (unsigned int i = 0; i < 6; i++)
		{
			img.load(directory + path[i], false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
				img.w, img.h, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data());
		}

		TextureMemory* mem = new TextureMemory;
		mem->mData = img.data(); mem->mNumChannels = 3; mem->mSize = img.w * img.h * img.mNumChannels;
		mem->mTarget = GL_TEXTURE_CUBE_MAP; mem->mTID = mId;
		mem->h = img.h; mem->w = img.w;
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		return TextureHandle{ mem };
	}
	static MeshHandle buildMesh(const vector<vertex>& vt, const vector<uint> id) {
		MeshHandle hand;
		hand.mVBH = SceneBuffer::genVertexBuffer(vt);
		hand.mIBH = SceneBuffer::genIndexBuffer(id);
		return hand;
	}
	//private:
	static MeshHandle buildSphere(int seg = 36) {
		vector<vertex> vt; vector<uint> id;
		vt.reserve((seg + 1) * (seg + 1) / 2 + 10);
		id.reserve((seg + 1) * (seg + 1) + 10);
		float a = 0; float x = 0;
		const float ax = 1.0f / seg; const float ay = 2.0f / seg;
		const float aa = 2 * PI / seg;
		for (int i = 0; i <= seg; ++i) {
			float b = -PI * 0.5; float y = 0;
			for (int j = 0; j <= seg / 2; ++j) {
				vertex v(vec3(cos(b) * sin(a), sin(b), cos(b) * cos(a)));
				v.mTexCoord = { x,y };
				v.mNormal = v.mPosition;
				vt.push_back(v);
				b += aa; y += ay;
			}
			a += aa; x += ax;
		}
		int segg = seg / 2 + 1;
		for (int i = 1; i <= seg; ++i) {
			for (int j = 1; j <= seg / 2; ++j) {
				id.push_back((i - 1) * segg + j - 1);
				id.push_back(i * segg + j - 1);
				id.push_back(i * segg + j);

				id.push_back((i - 1) * segg + j - 1);
				id.push_back(i * segg + j);
				id.push_back((i - 1) * segg + j);
			}
		}
		return buildMesh(vt, id);
	}

	static vector<MeshHandle> buildCube() {
		static float data[] = {
			// positions          // normals           //texCoords
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0, 1.0,//back
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0, 0.0,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0, 0.0,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0, 1.0,

			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0, 1.0,//left
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0, 0.0,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0, 0.0,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0, 1.0,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   0.0, 1.0,//right
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   0.0, 0.0,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   1.0, 0.0,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   1.0, 1.0,

			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   0.0, 1.0,//front
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   0.0, 0.0,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0, 0.0,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0, 1.0,

			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   0.0, 1.0,//top
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0, 0.0,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   1.0, 0.0,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   1.0, 1.0,

			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0, 1.0,//bottom
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   0.0, 0.0,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   1.0, 0.0,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   1.0, 1.0,
		};

		vector<vertex> vt; vector<uint> id{ 0,2,3,    1,2,0 };
		vector<MeshHandle> ret;
		float* p = data;
		for (int i = 0; i < 6; ++i) {
			vertex v;
			for (int j = 0; j < 4; ++j) {
				v.mPosition.set(p[0], p[1], p[2]);
				v.mNormal.set(p[3], p[4], p[5]);
				v.mTexCoord.set(p[6], p[7]);
				p += 8;
				vt.push_back(v);
			}
			ret.push_back(buildMesh(vt, id));
			vt.resize(0);
		}
		return ret;
	}

	static MeshHandle buildSkyBox() {
		static float data[] = {
			// positions
			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f
		};
		vector<vertex> vt;
		float* p = data;
		for (int i = 0; i < 8; ++i) {
			vt.push_back({ p[0], p[1], p[2] }); p += 3;
		}
		vector<uint> id{ 1,3,0,1,2,3,0,3,5,5,3,4,1,0,5,1,5,6,2,4,3,2,1,4,7,5,4,7,6,5,1,7,2,1,6,7 };
		return buildMesh(vt, id);
	}

};