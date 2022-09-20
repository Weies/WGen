#pragma once
#include"scene_buffer.h"

//场景直接对接渲染
class Scene {
public:
	Scene() {
		mModels.push_back({});
		//mModels.back().
	}
	void addModel(const RenderModel& model) {
		mModels.push_back(model);
	}
	void addMesh(const RenderMesh& mesh) {
		mModels[0].mMeshes.push_back(mesh);
	}
	void clear() {
		mModels.resize(1);
		mModels[0].mMeshes.resize(0);
	}

	vector<RenderModel> mModels;
	Camera* mCamera;
	RenderModel mAxis;
};


