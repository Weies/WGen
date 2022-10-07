#pragma once

#include"core/core.h"

class Linker
{
public:
	darray arr;

	Linker() {}
	virtual ~Linker() {}
	void clear() { arr.mSize = 0; arr.mIndex = 0; }
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
	virtual ~Archive() { delete mLinker; }

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

	void clear() { mLinker->clear(); };
	virtual bool isLoading() { return mLinker->isLoading(); }

	virtual bool isSaving() { return mLinker->isSaving(); }

};

template<class T>
typename std::enable_if<std::is_enum<T>::value, Archive>::type& operator<<(Archive& ar, T& v)
{
	ar << (int&)v;
	return ar;
}

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

