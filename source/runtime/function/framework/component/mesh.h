#pragma once
#include"component.h"
#include"function/base/render_base.h"
#include"../object/GObject.h"
#include"animation.h"
#include"function/scene/scene_manager.h"
class MeshComponent :public Component {
public:
	vector<MeshCompDesc>	mRawMeshes;
	string					mMeshFile;

	MeshComponent() :Component("MeshComponent") {}

	//将mRawMeshes加载成GameObjectDesc放到SceneManager中
	virtual void tick(float deltaTime)override {
		auto trans_comp = mParent->tryGetComp(TransformComponent);
		auto anim_comp = mParent->tryGetComp(AnimationComponent);

		GameObjectDesc ret;
		ret.mName = mParent->mName;
		ret.mMeshFile = mMeshFile;
		ret.mGOID = mParent->mId;
		mat4 go_trans = trans_comp->mTransform;
		if (anim_comp)
		{
			ret.mHasAnim = true;
			//ret.mPose = anim_comp->getPose();
		}
		for (auto& comp : mRawMeshes) {
			mat4 tp = comp.mTransDesc.mTransform;
			comp.mTransDesc.mTransform = go_trans * comp.mTransDesc.mTransform;
			ret.mCompDescs.push_back(comp);
			comp.mTransDesc.mTransform = tp;
		}

		SceneManager::get().addObject(move(ret));
	}

};
