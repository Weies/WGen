#pragma once
#include"../object/GObject.h"
#include"core/meta/json.h"

class Level {
public:


	virtual ~Level() {
		for (auto& p : mGObjects) {
			p.second->~GObject();
		}
		mGObjects.clear();
	}

	void serial(Archive& ar)
	{
		size_t size = mGObjects.size();
		ar << mName << mPath << size;
		if (ar.isLoading())
		{
			for (int i = 0; i < size; ++i)
			{
				addGObject(new GObject);
			}
		}

		for (auto& p : mGObjects)
		{
			p.second->serial(ar);
		}

	}

	void addGObject(GObject* go)
	{
		mGObjects.insert({ mNextGOId,go });
		++mNextGOId;
	}
	GObject* const getGOById(uint id)const
	{
		return mGObjects.find(id)->second;
	}
	const unordered_map<uint, GObject*>& getAllGObecjts()const
	{
		return mGObjects;
	}
	void tickAll(float delta_time)const {
		for (auto& p : mGObjects) {
			p.second->tick(delta_time);
		}
	}
	void load() {

	}
	void save()const {

	}

	string							mName;
	string							mPath;
	uint							mNextGOId{ 1 };
	unordered_map<uint, GObject*>	mGObjects;
};