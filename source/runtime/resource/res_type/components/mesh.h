#pragma once

#include"core/core.h"


//--------------------------------------------------
// Resource is editable and serializable
//--------------------------------------------------


class SubMeshRes
{
public:
	string		mName;
	Transform	mTransform;
	uint		mResIndex;
};

class MeshCompRes
{
public:

	string		mName;
	string		mOriginalFilePath;
	Transform	mTransform;

	vector<SubMeshRes> mMeshes;




};

inline Archive& operator<<(Archive& ar, SubMeshRes& v)
{
	ar << v.mName << v.mResIndex << v.mResIndex;
	return ar;
}

inline Archive& operator<<(Archive& ar, MeshCompRes& v)
{
	ar << v.mName << v.mOriginalFilePath << v.mTransform << v.mMeshes;
	return ar;
}