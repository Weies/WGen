#pragma once

#include"WGen.h"
#include"function/ui/ui_include.h"
#include"function/audio/audio.h"
#include"function/render/mrender.h"
#include"function/framework/world/world_manager.h"
#include"core/meta/json.h"



class Engine :public Singleton<Engine> {
public:

	bool engineInit()
	{
		Json engine_config = JsonHelpher::load("config/engine.config.jso");

		string world_url = engine_config["default_world"].string_value();

		WorldManager::get().initialize(world_url);
		//Json j;j.pa

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