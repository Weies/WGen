#pragma once
#include"component.h"
#include"function/base/render_base.h"
#include"../object/GObject.h"
#include"animation.h"
#include"function/scene/scene_manager.h"


//将mRawMeshes加载成GameObjectDesc放到SceneManager中
void MeshComponent::tick(float deltaTime)
{

	auto trans_comp = mParent->tryGetComp(Transform);
	auto anim_comp = mParent->tryGetComp(Animation);

	GameObjectDesc ret;
	ret.mName = mParent->mName;
	ret.mGOID = mParent->mId;

	ret.mModelDesc.mModelFile = mMeshFile;

	mat4 go_trans = trans_comp->mTransform;
	ret.mModelTransform = go_trans;
	if (anim_comp)
	{
		ret.mHasAnim = true;
		//ret.mPose = anim_comp->getPose();
	}
	for (auto& mesh : mRawMeshes) {
		mat4 tp = mesh.mTransform;
		mesh.mTransform = go_trans * mesh.mTransform;
		ret.mModelDesc.mMeshDescs.push_back(mesh);
		mesh.mTransform = tp;
	}
	SceneManager::get().addObject(move(ret));
}

void MeshComponent::finalize(const Json& j)
{
	mMeshFile = j["Ref"].string_value();


	Json::array meshes = j["Meshes"].array_items();
	for (auto& mesh : meshes)
	{
		MeshDesc desc;
		desc.mMeshName = mesh["MeshName"].string_value();
		desc.mTransform = JsonHelper::parseTransform(mesh["Transform"]);
		desc.mMaterialDescs = JsonHelper::parseMaterial(mesh["MaterialDesc"]);

		mRawMeshes.push_back(desc);
	}

}


