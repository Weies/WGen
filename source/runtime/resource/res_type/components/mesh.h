#pragma once

#include"component_data.h"
#include"resource/serializer.h"



class SubMeshRes
{
public:
	string		mName;
	Transform	mTransform;
};

class MeshCompRes :public CompRes
{
public:
	string		mPath;
	Transform	mTransform;

	vector<SubMeshRes> mMeshes;
};

inline Archive& operator<<(Archive& ar, SubMeshRes& v)
{
	return ar << v.mName << v.mTransform;
}

inline Archive& operator<<(Archive& ar, MeshCompRes& v)
{
	return ar << v.mType << v.mPath << v.mTransform << v.mMeshes;
}