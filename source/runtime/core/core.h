#pragma once
#include"math/math_include.h"
#include"meta/serializer.h"
#include"log/debuger.h"
#include"log/exception.h"
#include"base/singleton.h"
#include"meta/json.h"


#include<fstream>
using Transform = SQT;

template<class key, class value>
using umap = unordered_map<key, value>;

#define Invalid_ID (uid{0})
//uid==0 means invalid id
class UIDHelper :public Singleton<UIDHelper>
{
public:
	uid mNextID{};

	uid getNextID()
	{
		return ++mNextID;
	}
	uid getLastID()
	{
		return mNextID;
	}
};



class NameHelper :public Singleton<NameHelper>
{
public:
	umap<uid, string> mIDNameMap;
	umap<string, uid> mNameIDMap;

	const string& getNameByID(uid id)
	{
		return mIDNameMap[id];
	}

	const uid& getIDByName(const string& name)
	{
		return mNameIDMap[name];
	}

	uid registerName(const string& name)
	{
		auto it = mNameIDMap.find(name);
		if (it != mNameIDMap.end())return it->second;

		uid id = UIDHelper::get().getNextID();

		mIDNameMap.insert({ id,name });
		mNameIDMap.insert({ name,id });
		return id;
	}

	uid unregisterName(const string& name)
	{
		if (!mNameIDMap.count(name))
			return Invalid_ID;

		uid id = mNameIDMap[name];
		
		mIDNameMap.erase(id);
		mNameIDMap.erase(name);
		return id;
	}
};

class FName
{
public:
	string*	mName;
	uid		mId;


};