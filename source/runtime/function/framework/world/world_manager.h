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
	void clear() {
		for (auto& v : mLevels) {
			delete v;
		}
		mLevels.resize(0);
	}
	//º”‘ÿWorld
	void initialize() {}
	void loadPendingLevel() {
		if (mPendingLevelURL.empty())return;
	}
	string mPendingLevelURL;
	vector<Level*> mLevels;
	Level* mCurLevel;
};