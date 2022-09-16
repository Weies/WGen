#pragma once
#include"scene_builder.h"
#include"scene.h"

class SceneManager :public Singleton<SceneManager> {
protected:
	friend class Singleton<SceneManager>;
	SceneManager() :mScene(new Scene) {
		mScene->mCamera.reset(&ca);
		auto hand = SceneBuilder::buildSphere(36);
		mMeshHandleMap.insert({ "[Sphere{seg=36;}]",hand });
	}
public:
	MeshHandle getMeshHandle(const string& mesh_file) {
		auto it = mMeshHandleMap.find(mesh_file);
		if (it != mMeshHandleMap.end())
		{
			return it->second;
		}
		MeshHandle hand = SceneBuilder::loadMesh(mesh_file);
		mMeshHandleMap.insert({ mesh_file,hand });
		return hand;
	}
	ModelHandle getModelHandle(const GameObjectDesc& desc) {
		auto it = mModelHandleMap.find(desc.mMeshFile);
		if (it != mModelHandleMap.end()) {
			return it->second;
		}
		ModelDesc hd = SceneBuilder::loadModel(desc);
		/*string s = desc.mMeshFile;
		string dir(s.begin(), s.begin() + s.find_last_of('/') + 1);*/
		ModelHandle hand(move(hd));
		for (int i = 0; i < hd.mMaterials.size(); ++i) {
			MaterialHandle mhand;
			/*mhand.mBaseColorHandle = getTextureHandle(hd.mMaterials[i].mBaseColorFile);
			mhand.mSpecularMapHandle = getTextureHandle(hd.mMaterials[i].mSpecularMapFile);
			mhand.mDiffuseMapHandle = getTextureHandle(hd.mMaterials[i].mDiffuseMapFile);
			mhand.mOcculusionMapHandle = getTextureHandle(hd.mMaterials[i].mOcculusionMapFile);
			mhand.mMetallicMapHandle = getTextureHandle(hd.mMaterials[i].mMetallicMapFile);
			mhand.mRoughnessMapHandle = getTextureHandle(hd.mMaterials[i].mRoughnessMapFile);*/
			hand.mMaterials.push_back(mhand);
		}
		mModelHandleMap.insert({ desc.mMeshFile,hand });
		return hand;
	}

	TextureHandle getTextureHandle(const string& texture_file) {
		if (texture_file.empty())return TextureHandle{};
		auto it = mTextureHandleMap.find(texture_file);
		if (it != mTextureHandleMap.end())
		{
			return it->second;
		}
		TextureHandle hand = SceneBuilder::loadTexture(texture_file);
		mTextureHandleMap.insert({ texture_file,hand });
		return hand;
	}
	void addMesh(const string& mesh_desc, const MeshHandle& hand) {
		mMeshHandleMap.insert({ mesh_desc, hand });
		//mScene->addMesh()
	}
	virtual void tick() {
		syncObejct();
	}
	void addObject(GameObjectDesc&& go_desc) {
		mGODescs.push_back(move(go_desc));
	}
	//将mGODesc中的描述符加载成RenderModel放到Scene中
	void syncObejct() {
		mScene->clear();
		for (auto& go : mGODescs) {
			RenderModel model;
			ModelHandle mhd = getModelHandle(go);
			const uint sz = mhd.mHandles.size();

			{
				go.mCompDescs.resize(sz);
			}

			model.mMeshes.resize(sz);

			for (uint i = 0; i < sz; ++i) {
				model.mMeshes[i].mVBH = mhd.mHandles[i].mVBH;
				model.mMeshes[i].mIBH = mhd.mHandles[i].mIBH;
				auto& desc = go.mCompDescs[i].mMaterialDesc;
				auto& mate = model.mMeshes[i].mMaterial;
				auto& mat = mhd.mMaterials[i];

				mate.mBaseColor = desc.mBaseColor;
				mate.mDiffuse = desc.mDiffuse;
				mate.mSpecular = desc.mSpecular;
				mate.mMetallic = desc.mMetallic;
				mate.mRoughness = desc.mRoughness;
				mate.mOcculusion = desc.mOcculusion;

				mate.mBaseColorHandle = mat.mBaseColorHandle;
				mate.mDiffuseMapHandle = mat.mDiffuseMapHandle;
				mate.mSpecularMapHandle = mat.mSpecularMapHandle;
				mate.mMetallicMapHandle = mat.mMetallicMapHandle;
				mate.mRoughnessMapHandle = mat.mRoughnessMapHandle;
				mate.mOcculusionMapHandle = mat.mOcculusionMapHandle;
			}

			if (go.mHasAnim) {
				/*mat4* p = model.mJointMat;
				for (const auto& sqt : go.mPose.mPoses)
					*p++ = sqt.mat4();
				model.mNumJoints = go.mPose.mNumJoints;*/
			}
			model.mModelTransform = go.mModelTransform;
			mScene->addModel(model);
		}
		mGODescs.clear();
	}

	vector<GameObjectDesc>					mGODescs;
	unordered_map<string, TextureHandle>	mTextureHandleMap;
	unordered_map<string, MeshHandle>		mMeshHandleMap;
	unordered_map<string, ModelHandle>		mModelHandleMap;
	shared_ptr<Scene>						mScene;
};
