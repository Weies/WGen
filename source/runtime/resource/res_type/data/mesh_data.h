#pragma once

#include"core/core.h"
#include"asset_data.h"
#include"resource/basis.h"
#include"resource/serializer.h"
#include"texture_data.h"

//P位置，N法线，T纹理坐标，T正切（同时包含余切），B骨骼（索引加权重）
enum VertexFormat {
	Vertex_Invalid = 0, Vertex_PNTTB, Vertex_PNT, Vertex_PNTB, Vertex_PNTT, Vertex_P, Vertex_PN
};


struct vertex_pnt {
public:
	vertex_pnt() {}
	vertex_pnt(float pos_x, float pos_y, float pos_z) {
		mPosition.x = pos_x; mPosition.y = pos_y; mPosition.z = pos_z;
	}
	vertex_pnt(const vec3& pos) {
		this->mPosition = pos;
	}
	vertex_pnt(const vec3& pos, const vec3& norm, const vec2& tex_coord) {
		mPosition = pos; mNormal = norm; mTexCoord = tex_coord;
	}
	vec3 mPosition;
	vec3 mNormal;
	vec2 mTexCoord;
};
struct vertex_pntb {
public:
	vertex_pntb() {}
	vertex_pntb(float pos_x, float pos_y, float pos_z) {
		mPosition.x = pos_x; mPosition.y = pos_y; mPosition.z = pos_z;
	}
	vertex_pntb(const vec3& pos) {
		this->mPosition = pos;
	}
	vertex_pntb(const vec3& pos, const vec3& norm, const vec2& tex_coord) {
		mPosition = pos; mNormal = norm; mTexCoord = tex_coord;
	}
	vec3 mPosition;
	vec3 mNormal;
	vec2 mTexCoord;
	ivec4 mBoneIds;
	vec4 mBoneWeights;
};
struct vertex {
public:
	vertex() {}
	vertex(float pos_x, float pos_y, float pos_z) {
		mPosition.x = pos_x; mPosition.y = pos_y; mPosition.z = pos_z;
	}
	vertex(const vec3& pos) {
		this->mPosition = pos;
	}
	vertex(const vec3& pos, const vec3& norm, const vec2& tex_coord) {
		mPosition = pos; mNormal = norm; mTexCoord = tex_coord;
	}
	vec3 mPosition;
	vec3 mNormal;
	vec2 mTexCoord;
	vec3 mTangent;
	vec3 mBitangent;
	ivec4 mBoneIds;
	vec4 mBoneWeights;

	void set(us which, bool val) {
		bitSet(bit, which, val);
	}
	bool check(us which) {
		return bitTest(bit, which);
	}
	us bit = 0; us out = -1;
};

struct ImportTexHead
{
	std::string mPath;
	TextureType mType{ TextureType::texture_unknown };
};

class SubMeshData
{
public:

	string					mName;
	vector<vertex>			mVertices;
	vector<uint>			mIndices;
	vector<ImportTexHead>	mTextures;

};

class MeshData :public Asset
{
public:
	RegisterAsset(MeshData);

	vector<SubMeshData>		mMeshes;
	vector<ImportTexHead>	mTextures;
};

inline Archive& operator<<(Archive& ar, ImportTexHead& v)
{
	ar << v.mPath << v.mType;
	return ar;
}

inline Archive& operator<<(Archive& ar, vertex& v)
{
	ar << v.mPosition << v.mNormal << v.mTexCoord << v.mTangent << v.mBitangent << v.mBoneIds << v.mBoneWeights;
	return ar;
}

inline Archive& operator<<(Archive& ar, SubMeshData& v)
{
	ar << v.mName << v.mVertices << v.mIndices << v.mTextures;
	return ar;
}

inline Archive& operator<<(Archive& ar, MeshData& v)
{
	ar << v.mName << v.mPath << v.mMeshes;
	return ar;
}