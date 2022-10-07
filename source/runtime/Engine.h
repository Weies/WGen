#pragma once

#include"WGen.h"
#include"function/ui/ui_include.h"
#include"function/audio/audio.h"
#include"function/render/mrender.h"
#include"function/framework/world/world_manager.h"
#include"core/meta/json.h"

class EngineConfig
{
public:
	string mPath;//config/engine.config
	string mDefaultWorld;//asset/default_world.world
};

inline Archive& operator<<(Archive& ar, EngineConfig& conf)
{
	return ar << conf.mPath << conf.mDefaultWorld;
}

class Engine :public Singleton<Engine> {
public:

	bool engineInit()
	{
		Archive ar(new LinkerLoad);
		ar.load("config/engine.config");
		EngineConfig cfg;

		ar << cfg;

		WorldManager::get().loadWorld(cfg.mDefaultWorld);

		WorldManager::get().mPendingLevelURL = "asset/level.json";

		return true;
	}

	void tick(float delta_time) {
		logicalTick(delta_time);
		renderTick();
	}
	virtual void logicalTick(float delta_time) {

		WorldManager::get().tick(delta_time);

		SceneManager::get().tick();
	}
	virtual void renderTick() {

		mRedner.tick();

	}
	mutex mut;
protected:


	Render mRedner;
};