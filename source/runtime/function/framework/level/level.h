#pragma once
#include"../object/GObject.h"
class Level {
public:
	virtual ~Level() {
		for (auto& p : mGObjects) {
			p.second->~GObject();
		}
		mGObjects.clear();
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

	uint mNextGOId{ 1 };
	unordered_map<uint, GObject*> mGObjects;
};