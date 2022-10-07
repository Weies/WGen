#pragma once
#include"../log/exception.h"


template<class T , int capacity>
class Array {
public:
	Array() {
		_size = 0;
		//arr = new T[capacity];
	}
	void push_back(const T& a) {
		arr[_size] = a;
		++_size;
		if (_size > capacity)excep(WERROR_BAD_POINTER , "Array over flow;");
	}
	void pop_back() {
		--_size;
	}
	T& back() {
		return arr[_size - 1];
	}
	T& last() {
		return arr[_size++];
	}
	const T& back()const {
		return arr[_size - 1];
	}
	const T& operator[](int i)const {
		return arr[i];
	}
	T& operator[](int i)
	{
		return arr[i];
	}
	void resize(uint new_size) {
		if (new_size > capacity)excep(WERROR_ARGUMENT , "Index out of range;");
		_size = new_size;
	}
	size_t size() const {
		return _size;
	}
	void swap(Array<T , capacity>& otr) {
		std::swap(_size , otr._size);
		T tp[capacity]; const int sz = sizeof(T) * capacity;
		memcpy(tp, arr, sz);
		memcpy(arr, otr.arr, sz);
		memcpy(otr.arr, tp, sz);
		//std::swap(arr , otr.arr);
	}
private:
	int _size;//T* arr;
	T arr[capacity];
};

struct sarray
{

};

struct darray
{
	size_t mSize;
	uchar* mData;
	size_t mCapacity;
	size_t mIndex{};

	darray() :mSize(0), mCapacity(0), mData(0) {}
	darray(size_t size) :mSize(size), mCapacity(size), mData(new uchar[size]) {}
	darray(size_t size, uchar val) :mSize(size), mCapacity(size), mData(new uchar[size]) { memset(mData, val, size); }
	~darray() { delete[] mData; }

	void write(const void* data, size_t size)
	{
		size_t new_size = size + mSize;

		if (mCapacity < new_size)
		{
			mCapacity += new_size + size << 1;

			uchar* new_data = (uchar*)malloc(mCapacity);
			memcpy(new_data, mData, mSize);
			free(mData);
			mData = new_data;
		}

		memcpy(mData + mSize, (void*)data, size);
		mSize = new_size;
	}

	void read(void* data, size_t size)
	{
		size_t new_index = mIndex + size;
		if (new_index > mSize)
		{
			debug("array>>val is out of memory");
		}
		else
		{
			memcpy((void*)data, (void*)(mData + mIndex), size);
		}
		mIndex = new_index;
	}

	void write_size(const void* data, size_t size)
	{
		size_t new_size = size + mSize + sizeof(size_t);

		if (mCapacity < new_size)
		{
			mCapacity += new_size + size << 1;

			uchar* new_data = (uchar*)malloc(mCapacity);
			memcpy(new_data, mData, mSize);
			free(mData);
			mData = new_data;
		}
		memcpy(mData + mSize, (void*)&size, sizeof(size_t));
		memcpy(mData + mSize + sizeof(size_t), (char*)data, size);
		mSize = new_size;
	}

	void read_size(void* data, size_t& size)
	{
		size_t new_index = mIndex + size + sizeof(size_t);
		if (new_index > mSize)
		{
			debug("array>>val is out of memory");
		}
		else
		{
			memcpy(&size, mData + mIndex, sizeof(size_t));
			memcpy(data, mData + mIndex + sizeof(size_t), size);
		}
		mIndex = new_index;
	}

	void swap(darray& a)
	{
		std::swap(mSize, a.mSize);
		std::swap(mData, a.mData);
		std::swap(mCapacity, a.mCapacity);
		std::swap(mIndex, a.mIndex);
	}

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

		write(a.mData, a.mSize);
		return *this;
	}

	template<class T>
	darray& operator<<(const T& val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	darray& operator<<(const string& str)
	{
		write(str.c_str(), str.length());
		return *this;
	}

	void byte_swap(void* pp, size_t size)
	{
		uchar* p = (uchar*)pp;
		size >>= 1;
		size_t mid = size;
		while (size)
		{
			std::swap(p[mid + size - 1], p[mid - size]);
			size >>= 1;
		}
	}

	template<class T>
	darray& operator>>(T& val)
	{
		if (mIndex + sizeof(T) > mSize)
		{
			val = {};
			debug("array>>val is out of memory");
		}
		else
		{
			memcpy((void*)&val, (void*)(mData + mIndex), sizeof(T));
			mIndex += sizeof(val);
		}
		return *this;
	}

	template<class T>
	darray& operator>>(vector<T>& val)
	{
		size_t new_index = mIndex + sizeof(T) * val.size();
		if (new_index > mSize)
		{
			debug("array>>val is out of memory");
		}
		else
		{
			memcpy((void*)val.data(), mData + mIndex, sizeof(T));
		}
		mIndex = new_index;
		return *this;
	}




	uchar* data() { return mData; }
	const uchar* data() const { return mData; }
	size_t size() const { return mSize; }
	size_t capacity() const { return mCapacity; };


};
