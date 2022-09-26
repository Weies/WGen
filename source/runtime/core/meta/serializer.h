#pragma once
#include"../log/debuger.h"

//class Serializer :public Singleton<Serializer> {
//	Serializer() {}
//	friend class Singleton<Serializer>;
//public:
//
//};

struct sarray
{

};

struct darray
{
	size_t mSize;
	uchar* mData;
	size_t mCapacity;


	darray() :mSize(0), mCapacity(0), mData(0) {}
	darray(size_t size) :mSize(size), mCapacity(size), mData(new uchar[size]) {}
	darray(size_t size, uchar val) :mSize(size), mCapacity(size), mData(new uchar[size]) { memset(mData, val, size); }

	size_t resize(size_t new_size)
	{
		if (new_size > mCapacity)
		{
			mCapacity = new_size + mSize;
			uchar* new_data = (uchar*)malloc(mCapacity);
			memcpy(new_data, mData, mSize);
			free(mData);
			mData = new_data;
			mSize = new_size;
		}
		else
		{
			mSize = new_size;
		}
		return new_size;
	}

	string str()
	{
		string r;
		r.resize(mSize);
		memcpy(&r[0], mData, mSize);
		return r;
	}

	operator uchar* () { return mData; };

	darray& operator=(const darray& a)
	{
		mSize = a.mSize; mCapacity = a.mCapacity;
		if (mData)delete mData;
		mData = (uchar*)malloc(a.mCapacity);
		memcpy(mData, a.mData, mSize);
		return *this;
	}

	darray& operator+=(const darray& a)
	{
		size_t new_size = a.mSize + mSize;

		if (new_size < mCapacity)
		{
			mSize = new_size;
			memcpy(mData + mSize, a.mData, a.mSize);
		}
		else
		{
			mCapacity = new_size + mCapacity + a.mCapacity;
			uchar* new_data = (uchar*)malloc(mCapacity);
			memcpy(new_data, mData, mSize);
			memcpy(new_data + mSize, a.mData, a.mSize);
			free(mData);
			mData = new_data;
			mSize = new_size;
		}
		return *this;
	}

	template<class T>
	darray& operator<<(const T& val)
	{
		size_t new_size = sizeof(T) + mSize;

		if (mCapacity < new_size)
		{
			mCapacity += new_size + sizeof(T) << 1;

			uchar* new_data = (uchar*)malloc(mCapacity);
			memcpy(new_data, mData, mSize);
			free(mData);
			mData = new_data;
		}

		memcpy(mData, &val, sizeof(T));
		mSize = new_size;
		return *this;
	}

	darray& operator<<(const string& str)
	{
		size_t new_size = str.size() + mSize;

		if (mCapacity < new_size)
		{
			mCapacity += new_size + str.capacity();

			uchar* new_data = (uchar*)malloc(mCapacity);
			memcpy(new_data, mData, mSize);
			free(mData);
			mData = new_data;
		}

		memcpy(mData, str.c_str(), str.size());
		mSize = new_size;
		return *this;

	}


	uchar* data() { return mData; }
	size_t size() { return mSize; }
	size_t capacity() { return mCapacity; };


};

class Archive
{
public:

};

class Serializer {
public:

};