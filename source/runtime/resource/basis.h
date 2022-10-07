#pragma once

#include"core/math/math_include.h"
using namespace gm;

//_____________________________________
// Asset will be save as .asset file
// Every level will be save as map file
//_____________________________________

#define INVAILID_HANDLE 0



using Transform = SQT;

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

class SkeletonBindingDesc {
public:

};
class AnimationResult {
public:

};

class MeshDesc {
public:
	string				mMeshName;
	Transform			mTransform;
	MaterialDesc		mMaterialDescs;
};

struct ModelDesc {

	string					mModelFile;
	vector<MeshDesc>		mMeshDescs;

};


class GameObjectDesc {
public:
	uid						mGOID;
	string					mName;
	ModelDesc				mModelDesc;
	mat4					mModelTransform;
	bool					mHasAnim{ false };
	//Pose mPose;
};
