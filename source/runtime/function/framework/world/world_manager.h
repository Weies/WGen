#pragma once
#include"../level/level.h"

class WorldManager :public Singleton<WorldManager> {
public:
	void tick(float delta_time) {
		loadPendingLevel();

		for (auto& p : mLevels) {
			p->tickAll(delta_time);
		}
	}

	const unordered_map<uint, GObject*>&  getAllObjects()
	{
		return mCurLevel->mGObjects;
	}

	GObject* getGOById(uint id)
	{
		return mCurLevel->getGOById(id);
	}

	GObject* getGOByName(const string& name)
	{
		return nullptr;//mCurLevel->getGOById(id);
	}

	void clear() {
		for (auto& v : mLevels) {
			delete v;
		}
		mLevels.resize(0);
	}

	//¼ÓÔØWorld
	void initialize(const string& world_config_path)
	{
		Json world = JsonHelper::load(world_config_path);

		string default_level = world["default_level"].string_value();

		mCurLevel = new Level;
		mCurLevel->initialize(default_level);
		mLevels.push_back(mCurLevel);
	}

	void loadPendingLevel() {
		if (mPendingLevelURL.empty())return;
	}
	string mPendingLevelURL;
	vector<Level*> mLevels;
	Level* mCurLevel{};
};