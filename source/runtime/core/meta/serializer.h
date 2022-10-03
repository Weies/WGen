#pragma once
#include"../log/debuger.h"
#include"core/core.h"
using namespace std;

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
			memcpy((void*)val.data(), (void*)mData + mIndex, sizeof(T));
		}
		mIndex = new_index;
		return *this;
	}




	uchar* data() { return mData; }
	const uchar* data() const { return mData; }
	size_t size() const { return mSize; }
	size_t capacity() const { return mCapacity; };


};

class Linker
{
public:
	darray arr;

	Linker() {}

	size_t size() const { return arr.size(); }
	uchar* data() { return arr.data(); }
	const uchar* data() const { return arr.data(); }
	void resize(size_t size) { arr.resize(size); }
	virtual bool isLoading() { return true; }

	virtual bool isSaving() { return false; }

	virtual void swap(Linker& l) { arr.swap(l.arr); }

	virtual void serial(int& val) = 0;
	virtual void serial(float& val) = 0;
	virtual void serial(double& val) = 0;
	virtual void serial(uint& val) = 0;
	virtual void serial(long& val) = 0;
	virtual void serial(ulong& val) = 0;
	virtual void serial(bool& val) = 0;
	virtual void serial(char& val) = 0;
	virtual void serial(ullong& val) = 0;
	virtual void serial(void* data, size_t size) = 0;
	virtual void serial(string& s) = 0;

};

class LinkerLoad :public Linker
{
public:


	virtual bool isLoading() { return true; }

	virtual bool isSaving() { return false; }

	virtual void serial(int& val) { arr >> val; };
	virtual void serial(float& val) { arr >> val; };
	virtual void serial(double& val) { arr >> val; };
	virtual void serial(uint& val) { arr >> val; };
	virtual void serial(long& val) { arr >> val; };
	virtual void serial(ulong& val) { arr >> val; };
	virtual void serial(bool& val) { arr >> val; };
	virtual void serial(char& val) { arr >> val; };
	virtual void serial(ullong& val) { arr >> val; };
	virtual void serial(void* data, size_t size) { arr.read(data, size); };
	virtual void serial(string& s)
	{
		size_t size;
		arr >> size;
		s.resize(size);
		arr.read(&s[0], size);
	}
};

class LinkerSave :public Linker
{
public:
	virtual bool isLoading() { return false; }

	virtual bool isSaving() { return true; }

	virtual void serial(int& val) { arr << val; };
	virtual void serial(float& val) { arr << val; };
	virtual void serial(double& val) { arr << val; };
	virtual void serial(uint& val) { arr << val; };
	virtual void serial(long& val) { arr << val; };
	virtual void serial(ulong& val) { arr << val; };
	virtual void serial(bool& val) { arr << val; };
	virtual void serial(char& val) { arr << val; };
	virtual void serial(ullong& val) { arr << val; };
	virtual void serial(void* data, size_t size) { arr.write(data, size); };
	virtual void serial(string& s)
	{
		arr.write_size(&s[0], s.size());
	}
};

class Archive
{
public:
	Linker* mLinker;
	string mFilePath;
	Archive(Linker* link) :mLinker(link) {}
	Archive(Linker* link, const string& file_path) :mLinker(link), mFilePath(file_path) {}


	Archive& operator<<(int& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(float& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(double& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(uint& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(long& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(ulong& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(bool& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(char& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(ullong& val) { mLinker->serial(val);	return*this; };
	Archive& operator<<(string& val) { mLinker->serial(val); return*this; };

	Archive& operator<<(void* data)
	{
		size_t size;
		if (mLinker->isLoading())
		{
			size = *(size_t*)(mLinker->arr.mData + mLinker->arr.mIndex - sizeof(size_t));
		}
		else
		{
			size = *(size_t*)(mLinker->arr.mData + mLinker->arr.mSize - sizeof(size_t));
		}
		mLinker->serial(data, size);
		return*this;
	};

	void load(const string& file_path = "")
	{
		std::fstream f(file_path.empty() ? mFilePath : file_path, ios::in | ios::binary);
		if (!f.is_open())debug("Wrong when open file for read!!");
		size_t size = 0;
		f.read((char*)&size, sizeof(size_t));
		mLinker->resize(size);
		f.read((char*)mLinker->data(), size);
		f.close();
	}

	void save(const string& file_path = "")
	{
		if (mLinker->size() == 0)return;
		std::fstream f(file_path.empty() ? mFilePath : file_path, ios::out | ios::binary);
		if (!f.is_open())debug("Wrong when open file for write!!");
		size_t size = mLinker->size();
		f.write((char*)&size, sizeof(size_t));
		f.write((char*)mLinker->data(), mLinker->size());
		f.close();
	}

	virtual bool isLoading() { return mLinker->isLoading(); }

	virtual bool isSaving() { return mLinker->isSaving(); }

};


template<class T>
Archive& operator<<(Archive& ar, vector<T>& val)
{
	size_t size = val.size();
	ar << size;
	if (ar.isLoading())
	{
		val.resize(size);
	}
	if constexpr (std::is_trivially_constructible<T>::value)
	{
		ar << &val[0];
	}
	else
	{
		for (T& v : val)
		{
			ar << v;
		}
	}
	return ar;
};

template<class T>
inline typename std::enable_if<std::is_enum<T>::value, Archive>::type& operator<<(Archive& ar, T& v)
{
	ar << (int&)v;
	return ar;
}