#pragma once
#include"core/log/debuger.h"
#include"core/log/exception.h"
#include"core/math/matrix.h"

using namespace gm;

class Image {
public:
	Image() {
		mData = 0;
	}
	Image(const string& filepath, bool flip = true)
	{
		load(filepath, flip);
	}
	~Image() {
		//free();
	}
	void load(const string& filepath, bool flip = true);

	void free()
	{
		std::free(mData);
		mData = 0;
	}
	unsigned char* data() const
	{
		if (!mData)excep(WERROR_FILE_LOAD, "The data is null cannot be returned");
		return mData;
	}
	Mat<cvec3> mat3() {
		ASSERT(mNumChannels == 3);
		return Mat<cvec3>(w, h, mData);
	}
	Mat<uchar> mat() {
		ASSERT(mNumChannels == 1);
		return Mat<uchar>(w, h, mData);
	}
	Mat<cvec4> mat4() {
		ASSERT(mNumChannels == 4);
		return Mat<cvec4>(w, h, mData);
	}
	union { int w; int mWidth; };
	union { int h; int mWdith; };
	int mNumChannels;
	uchar* mData = 0;
private:

};




