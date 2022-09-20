#pragma once

#include"WGen.h"
#include"function/audio/audio.h"
#include"function/scene/scene_manager.h"
#include"function/framework/world/world_manager.h"
#include"function/framework/component/mesh.h"
#include"function/render/mrender.h"
#include"function/model/model_include.h"


class Engine :public Singleton<Engine> {
public:
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