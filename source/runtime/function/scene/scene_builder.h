#pragma once
#include"scene_buffer.h"
#include"resource/asset_manager.h"

//SceneBuilder 一定会分配新内存，但是SceneManager可能不分配新内存
//Build scene的两种方式：从文件生成 vs. 代码直接生成
class SceneBuilder {
public:

	static ModelHandle loadModel(const ModelDesc& desc) {
		auto& model_file = desc.mModelFile;
		ModelHandle model_handle;
		if (model_file.empty())return model_handle;


		/*预定义对象，直接用代码生成*///[Sphere{36}]
		if (model_file[0] == '[')
		{
			return parsePreDefModel(desc);
		}


		/*从文件中加载模型*/

		MeshData* data = AssetManager::get().loadAsset<MeshData>(desc.mModelFile);

		model_handle.mMeshHandles.resize(desc.mMeshDescs.size());
		auto& mhd = model_handle.mMeshHandles;
		for (int i = 0; i < mhd.size(); ++i)
		{
			mhd[i].mVBH = SceneBuffer::genVertexBuffer(data->mMeshes[i].mVertices);
			mhd[i].mIBH = SceneBuffer::genIndexBuffer(data->mMeshes[i].mIndices);
			//mhd[i].mMTH = loadMaterial(desc.mMeshDescs[i].mMaterialDescs);
		}

		return model_handle;
	}

	static ModelHandle parsePreDefModel(const ModelDesc& desc)
	{
		ModelHandle model_handle;
		const string& model_file = desc.mModelFile;
		int p = model_file.find('{');
		string ob = string(model_file.begin() + 1, model_file.begin() + p);
		if (ob == "Sphere") {
			int seg = stoi(model_file.substr(p + 5));
			MeshHandle mesh_handle = buildSphere(seg);

			//model_handle.mMeshHandles[0].
			if (desc.mMeshDescs.size() != 0)
				mesh_handle.mMTH = loadMaterial(desc.mMeshDescs[0].mMaterialDescs);

			model_handle.mMeshHandles.push_back(mesh_handle);
			return model_handle;
		}

		return ModelHandle{};
	}

	static ModelHandle loadModel(const string& model_file)
	{

		if (model_file.empty())return ModelHandle();

		if (model_file[0] == '[') {
			//const char* p = &mesh_file[1];
			int p = model_file.find('{');
			string ob = string(model_file.begin() + 1, model_file.begin() + p);
			if (ob == "Sphere") {
				int seg = stoi(model_file.substr(p + 5));
				MeshHandle hand = buildSphere(seg);
				return ModelHandle{ {hand} };
			};
		}
		return ModelHandle{};
	}



	static TextureHandle loadTexture(const string& texture_file)
	{
		if (texture_file.empty())return {};

		Image img;
		img.load(texture_file);
		TextureHandle hand = SceneBuffer::genTextureBuffer(img);
		img.free();
		return hand;
	}

	static MaterialHandle loadMaterial(const MaterialDesc& mat_desc)
	{
		MaterialHandle handle;
		handle.mBaseColor = mat_desc.mBaseColor;
		handle.mDiffuse = mat_desc.mDiffuse;
		handle.mSpecular = mat_desc.mSpecular;
		handle.mMetallic = mat_desc.mMetallic;
		handle.mRoughness = mat_desc.mRoughness;
		handle.mOcculusion = mat_desc.mOcculusion;

		handle.mBaseColorHandle = loadTexture(mat_desc.mBaseColorFile);
		handle.mSpecularMapHandle = loadTexture(mat_desc.mSpecularMapFile);
		handle.mDiffuseMapHandle = loadTexture(mat_desc.mDiffuseMapFile);
		handle.mOcculusionMapHandle = loadTexture(mat_desc.mOcculusionMapFile);
		handle.mMetallicMapHandle = loadTexture(mat_desc.mMetallicMapFile);
		handle.mRoughnessMapHandle = loadTexture(mat_desc.mRoughnessMapFile);

		return handle;
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

	static MeshHandle buildMesh(const vector<vertex>& vt, const vector<uint> id)
	{
		MeshHandle hand;
		hand.mVBH = SceneBuffer::genVertexBuffer(vt);
		hand.mIBH = SceneBuffer::genIndexBuffer(id);
		return hand;
	}

	//private:
	static MeshHandle buildSphere(int seg = 36)
	{
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

	static vector<MeshHandle> buildCube()
	{
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

	static MeshHandle buildSkyBox()
	{
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


