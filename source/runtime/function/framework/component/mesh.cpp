#pragma once
#include"component.h"
#include"function/base/render_base.h"
#include"../object/GObject.h"
#include"animation.h"
#include"function/scene/scene_manager.h"


//将mRawMeshes加载成GameObjectDesc放到SceneManager中
void MeshComponent::tick(float deltaTime) {

	auto trans_comp = mParent->tryGetComp(Transform);
	auto anim_comp = mParent->tryGetComp(Animation);

	GameObjectDesc ret;
	ret.mName = mParent->mName;
	ret.mMeshFile = mMeshFile;
	ret.mGOID = mParent->mId;
	mat4 go_trans = trans_comp->mTransform;
	ret.mModelTransform = go_trans;
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

void MeshComponent::finalize(const Json& j)
{
	mMeshFile = j["Ref"].string_value();

	mRawMeshes;
	Json::array meshes = j["Meshes"].array_items();
	for (auto& mesh : meshes)
	{
		MeshCompDesc desc;
		desc.mMeshDesc.mMeshName = mesh["MeshDesc"]["MeshName"].string_value();
		desc.mTransDesc.mTransform = JsonHelper::parseTransform(mesh["TransformDesc"]);
		desc.mMaterialDesc = MaterialDesc();
	}

	//SceneManager::get().

	/*auto& m = mRawMeshes.back();
	m.mMeshDesc.mMeshName =*/
}


