#pragma once
#include"../level/level.h"
#include"resource/res_type/common/world.h"

class WorldManager :public Singleton<WorldManager> {
public:

	string mPendingLevelURL;
	vector<Level*> mLevels;
	Level* mCurLevel{};


	void tick(float delta_time) {
		loadPendingLevel();

		for (auto& p : mLevels) {
			p->tickAll(delta_time);
		}
	}

	const unordered_map<uint, GObject*>& getAllObjects()
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

	//º”‘ÿWorld
	void loadWorld(const string& world_path/*asset/default_world.world*/)
	{
		WorldRes res;
		Archive ar(new LinkerLoad);
		ar.load(world_path);
		ar << res;

		ar.load(res.mDefaultLevelUrl);

		mCurLevel = new Level;
		mCurLevel->serial(ar);
		mLevels.push_back(mCurLevel);
	}

	void saveWorld(const string& world_path)
	{
		WorldRes res;

		res.mPath = world_path;
		res.mDefaultLevelUrl = mCurLevel->mPath;

		Archive ar(new LinkerSave);

		for (auto& p : mLevels)
		{
			res.mLevelUrls.push_back(p->mPath);
			p->serial(ar);
			ar.save(p->mPath);
			ar.clear();
		}

		ar << res;
		ar.save(world_path);
	}

	void loadPendingLevel() {
		if (mPendingLevelURL.empty())return;
	}
};