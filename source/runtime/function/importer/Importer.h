#pragma once
#include"mesh.h"
#include"../base/encoder.h"

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
	bool Import(SkeletalMesh& m, const string& filePath, ll mask = Import_Mask);
	bool Import(const string& filePath, SkeletalMesh& m, bool load_texture = true,
		bool load_meshes = true, bool load_anims = true, bool flip_uv = false) {
		ll mask = (Triangulate | GenNormals);
		if (load_texture)mask |= LoadTextures;
		if (flip_uv)mask |= FlipUV;
		if (load_meshes)mask |= LoadMeshes;
		if (load_anims)mask |= LoadAnimations;
		return Import(m, filePath, mask);
	}

	static Json jsonlize(const vec3& v)
	{
		Json::object obj;
		obj.insert({ "x",v.x });
		obj.insert({ "y",v.y });
		obj.insert({ "z",v.z });
		return obj;
	}
	static Json jsonlize(const vec2& v)
	{
		Json::object obj;
		obj.insert({ "x",v.x });
		obj.insert({ "y",v.y });
		return obj;
	}

	static Json jsonlize(const vec4& v)
	{
		Json::object obj;
		obj.insert({ "x",v.x });
		obj.insert({ "y",v.y });
		obj.insert({ "z",v.z });
		obj.insert({ "w",v.w });
		return obj;
	}

	static Json jsonlize(const ivec4& v)
	{
		Json::object obj;
		obj.insert({ "x",v.x });
		obj.insert({ "y",v.y });
		obj.insert({ "z",v.z });
		obj.insert({ "w",v.w });
		return obj;
	}

	static Json jsonlize(const Transform& t)
	{
		Json::object obj;
		obj.insert({ "Translate"	,jsonlize(t.t) });
		obj.insert({ "Scale"		,jsonlize(t.s) });
		obj.insert({ "Rotation"		,jsonlize(t.q.vec4()) });
		return obj;
	}

	static Json jsonlize(const vertex& v)
	{
		Json::object obj;
		obj.insert({ "Position",jsonlize(v.mPosition) });
		obj.insert({ "Normal",jsonlize(v.mNormal) });
		obj.insert({ "TexCoord",jsonlize(v.mTexCoord) });
		obj.insert({ "Tangent",jsonlize(v.mTangent) });
		obj.insert({ "Bitangent",jsonlize(v.mBitangent) });
		obj.insert({ "BoneIds",jsonlize(v.mBoneIds) });
		obj.insert({ "BoneWeights",jsonlize(v.mBoneWeights) });
		return obj;
	}

	static Json jsonlize(const ImportTexHead& h)
	{
		Json::object obj;
		obj.insert({ "Path",h.mPath });
		obj.insert({ "Type",int(h.mType) });
		return obj;
	}

	static Json jsonlize(const MeshPatch& m)
	{
		Json::object obj;

		obj.insert({ "Name",m.mName });
		obj.insert({ "Transform",jsonlize(m.mTransform) });

		{
			Json::array vt;
			for (int i = 0; i < m.mVertices.size(); ++i)
			{
				vt.push_back(jsonlize(m.mVertices[i]));
			}
			obj.insert({ "Vertices",vt });
		}

		{
			Json::array id;
			for (int i = 0; i < m.mIndices.size(); ++i)
			{
				id.push_back({ int(m.mIndices[i]) });
			}
			obj.insert({ "Indices",id });
		}


		{
			Json::array tx;
			for (int i = 0; i < m.mTextures.size(); ++i)
			{
				tx.push_back(jsonlize(m.mTextures[i]));
			}
			obj.insert({ "Textures",tx });
		}
		return obj;
	}

	Json jsonlize(const SkeletalMesh& m)
	{
		Json::object obj;
		obj.insert({ "Id"			,0 });
		obj.insert({ "Name"			,m.mName });
		obj.insert({ "Directory"	,m.mDirectory });
		obj.insert({ "DefinitionUrl","" });
		obj.insert({ "IsGammaCorection",m.mIsGammaCorection });

		Json::array comps;

		//mesh component
		{
			Json::object mesh;
			mesh.insert({ "Type","Mesh" });

			Json::array meshes;
			for (int i = 0; i < m.mMeshes.size(); ++i)
			{
				meshes.push_back(jsonlize(m.mMeshes[i]));
			}
			mesh.insert({ "Meshes",meshes });

			comps.push_back(mesh);
		}

		//transform component
		{
			Json::object trans;
			trans.insert({ "Type","Transform" });
			trans.insert({ "Transform",jsonlize(m.mTransform) });
			comps.push_back(trans);
		}

		obj.insert({ "Components",comps });
		return obj;
	}

	// 导出时为了满足软件的读取需求，可以单独指定编码格式
	bool Export(const string& filePath, ll mask = Export_Mask, CodeType tp = gb2312);
	//导出一个MeshModel对象
	static bool Export(const SkeletalMesh& m, const string& filePath, ll mask = Export_Mask, CodeType tp = gb2312);
	~Importer();
	void* imp;
	void* hand;
};