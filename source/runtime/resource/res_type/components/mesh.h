#pragma once

#include"component_data.h"
#include"resource/serializer.h"



class SubMeshRes :public CompRes
{
public:
	string		mName;
	Transform	mTransform;
	uint		mResIndex;
};

class MeshCompRes :public CompRes
{
public:

	string		mOriginalFilePath;
	Transform	mTransform;

	vector<SubMeshRes> mMeshes;

};

inline Archive& operator<<(Archive& ar, SubMeshRes& v)
{
	ar << v.mType << v.mResIndex << v.mResIndex;
	return ar;
}

inline Archive& operator<<(Archive& ar, MeshCompRes& v)
{
	ar << v.mType << v.mOriginalFilePath << v.mTransform << v.mMeshes;
	return ar;
}