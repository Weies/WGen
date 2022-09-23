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

	void initialize(const string& level_config_path)
	{
		Json level = JsonHelper::load(level_config_path);
		Json::array objects = level["objects"].array_items();

		for (auto& obj : objects)
		{
			string obj_path = obj.string_value();
			GObject* obj = new GObject;
			obj->initialize(obj_path);
			
			addGObject(obj);
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

	uint mNextGOId{ 1 };
	unordered_map<uint, GObject*> mGObjects;
};