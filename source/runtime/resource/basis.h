#pragma once

#include"core/math/math_include.h"
#define INVAILID_HANDLE 0

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


using Transform = SQT;
class MeshDesc {
public:
	string mMeshName;
};
class MaterialDesc {
public:
	vec4	mBaseColor{ 1.0,1.0,1.0,1.0 };
	vec3	mDiffuse{ 1.0,1.0,1.0 };
	vec3	mSpecular{ 1.0,1.0,1.0 };
	float	mMetallic{ 0.5f };
	float	mRoughness{ 0.5f };
	float	mOcculusion{ 1.0f };

	string	mBaseColorFile;
	string	mDiffuseMapFile;
	string	mSpecularMapFile;
	string	mNormalMapFile;
	string	mMetallicMapFile;
	string	mRoughnessMapFile;
	string	mOcculusionMapFile;
};
class TransformDesc {
public:
	Transform mTransform;
};
class SkeletonBindingDesc {
public:

};
class AnimationResult {
public:

};

class MeshCompDesc {
public:
	MeshDesc			mMeshDesc;
	MaterialDesc		mMaterialDesc;
	TransformDesc		mTransDesc;
};


class GameObjectDesc {
public:
	uid						mGOID;
	string					mName;
	string					mMeshFile;
	vector<MeshCompDesc>	mCompDescs;
	mat4					mModelTransform;
	bool					mHasAnim{ false };
	//Pose mPose;
};
