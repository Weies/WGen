#pragma once
#include"scene_builder.h"
#include"scene.h"

class SceneManager :public Singleton<SceneManager> {
protected:
	friend class Singleton<SceneManager>;
	SceneManager() :mScene(new Scene) {
		mScene->mCamera = &ca;
		auto hand = SceneBuilder::buildSphere(36);
		mMeshHandleMap.insert({ "[Sphere{seg=36;}]",hand });
	}
public:

	vector<GameObjectDesc>					mGODescs;
	unordered_map<string, TextureHandle>	mTextureHandleMap;
	unordered_map<string, MeshHandle>		mMeshHandleMap;
	unordered_map<string, ModelHandle>		mModelHandleMap;
	shared_ptr<Scene>						mScene;



	ModelHandle getModelHandle(const ModelDesc& desc) {
		auto it = mModelHandleMap.find(desc.mModelFile);
		if (it != mModelHandleMap.end()) {
			return it->second;
		}

		/*string s = desc.mMeshFile;
		string dir(s.begin(), s.begin() + s.find_last_of('/') + 1);*/
		ModelHandle hand = SceneBuilder::loadModel(desc);

		mModelHandleMap.insert({ desc.mModelFile,hand });
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
	void syncObejct()
	{
		mScene->clear();
		for (auto& go_desc : mGODescs) {
			RenderModel render_model;

			ModelHandle model_handle = getModelHandle(go_desc.mModelDesc);

			const uint mesh_size = model_handle.mMeshHandles.size();
			render_model.mMeshes.resize(mesh_size);

			for (uint i = 0; i < mesh_size; ++i)
			{
				auto& render_mesh = render_model.mMeshes[i];

				render_mesh.mVBH = model_handle.mMeshHandles[i].mVBH;
				render_mesh.mIBH = model_handle.mMeshHandles[i].mIBH;
				render_mesh.mMaterial = model_handle.mMeshHandles[i].mMTH;

			}

			if (go_desc.mHasAnim)
			{
				/*mat4* p = model.mJointMat;
				for (const auto& sqt : go.mPose.mPoses)
					*p++ = sqt.mat4();
				model.mNumJoints = go.mPose.mNumJoints;*/
			}
			render_model.mModelTransform = go_desc.mModelTransform;
			mScene->addModel(render_model);
		}
		mGODescs.clear();
	}


};
