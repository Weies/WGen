#pragma once

#include"core/core.h"
#include"resource/basis.h"

class SubMeshData
{
public:
	string					mName;
	Transform				mTransfrom;
	vector<vertex>			mVertices;
	vector<uint>			mIndices;
	vector<ImportTexHead>	mTextures;

};

class MeshData
{
public:
	string				mName;
	string				mPath;
	Transform			mTransform;
	vector<SubMeshData> mMeshes;

};