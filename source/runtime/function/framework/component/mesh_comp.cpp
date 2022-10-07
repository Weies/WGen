#pragma once
#include"component.h"
#include"function/base/render_base.h"
#include"../object/GObject.h"
#include"animation_comp.h"
#include"function/scene/scene_manager.h"
#include"resource/asset_manager.h"

//将mRawMeshes加载成GameObjectDesc放到SceneManager中
void MeshComponent::tick(float deltaTime)
{
	auto trans_comp = mParent->tryGetComp(Transform);
	auto anim_comp = mParent->tryGetComp(Animation);

	GameObjectDesc ret;
	ret.mName = mParent->mName;
	ret.mGOID = mParent->mId;

	ret.mModelDesc.mModelFile = mMesh.mPath;
	mat4 go_trans = trans_comp->mTransform;
	ret.mModelTransform = go_trans;
	if (anim_comp)
	{
		ret.mHasAnim = true;
		//ret.mPose = anim_comp->getPose();
	}

	for (auto& mesh : mMesh.mMeshes) {
		MeshDesc mdesc;
		mdesc.mMeshName = mesh.mName;
		mdesc.mTransform = mesh.mTransform;
		ret.mModelDesc.mMeshDescs.push_back(mdesc);
	}
	SceneManager::get().addObject(move(ret));
}


