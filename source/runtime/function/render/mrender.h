#pragma once
#include"render.h"
#include"function/scene/scene_manager.h"

class RenderBase {
public:
	RenderStrategy strategy{ RenderStrategy::Undefined };
	virtual void render(const RenderModel& m) {}// = 0;
};
class NonPBRRenderBase :public RenderBase {
public:
	Shader shader;
	NonPBRRenderBase() {
		strategy = RenderStrategy::NonPBR_PhongShading;
		shader.parseShader("source/shader/render.shader");
	}
	virtual void render(const RenderModel& m) {
		if (m.mMeshes.size() == 0)return;
		auto& cam = SceneManager::get().mScene->mCamera;
		shader.setMat4("transform", cam->getBlock().mPVTransform * m.mModelTransform);


		for (auto& mesh : m.mMeshes) {
			SceneBuffer::memory(mesh.mVBH)->bind();
			SceneBuffer::memory(mesh.mIBH)->bind();
			shader.setMat4("model", m.mModelTransform * mesh.mTransform);
			int bind_tex = 1; const auto& mate = mesh.mMaterial;

			if (mate.mBaseColorHandle.mHandle) {
				glActiveTexture(GL_TEXTURE0 + bind_tex);
				SceneBuffer::memory(mate.mBaseColorHandle)->bind();
				shader.setInt("tex_base_color", bind_tex++);
				shader.setVec4("base_color", vec4(0.0));
			}
			else
			{
				shader.setInt("tex_base_color", 0);
				shader.setVec4("base_color", mate.mBaseColor);
			}
			//if (mate.mSpecularMapHandle.mHandle) {
			//	glActiveTexture(GL_TEXTURE0 + bind_tex);
			//	SceneBuffer::memory(mate.mSpecularMapHandle)->bind();
			//	shader.setInt("tex_specular_map", bind_tex++);
			//}
			//if (mate.mDiffuseMapHandle.mHandle) {
			//	glActiveTexture(GL_TEXTURE0 + bind_tex);
			//	SceneBuffer::memory(mate.mDiffuseMapHandle)->bind();
			//	shader.setInt("tex_diffuse_map", bind_tex++);
			//}
			if (mate.mNormalMapHandle.mHandle) {
				glActiveTexture(GL_TEXTURE0 + bind_tex);
				SceneBuffer::memory(mate.mNormalMapHandle)->bind();
				shader.setInt("tex_normal_map", bind_tex++);
			}
			glDrawElements(GL_TRIANGLES, SceneBuffer::memory(mesh.mIBH)->mSize / 4, GL_UNSIGNED_INT, 0);
		}
	}
};
class PBRRenderBase :public RenderBase {
public:
};
class RayTracingRenderBase :public RenderBase {
public:
};

class Render {
public:

	vector<RenderBase*> mRenders;

	Render() {}

	~Render() {
		for (auto v : mRenders)
			delete v;
		mRenders.clear();
	}
	virtual void tick() {
		tick_ui();
		tick_world();
	}
	virtual void tick_ui() {

	}
	virtual void tick_world() {
		render();
	}
	void render() {
		drawModel();
		drawSkybox();
		drawAxis();
		drawParticle();
		drawUI();
	}

	void drawUI()
	{
		auto scene = SceneManager::get().mScene.get();
		static Render3D ren;
		ren.renderList(scene->mCamera->getBlock());
	}

	void drawModel() {
		auto scene = SceneManager::get().mScene;
		for (const auto& mo : scene->mModels) {
			if (mo.mMeshes.size() < 1)continue;

			RenderBase* rd = nullptr;
			if (mo.desired == RenderStrategy::Undefined && mRenders.size())
			{
				mRenders[0]->render(mo); continue;
			}
			for (auto p : mRenders)
			{
				if (p->strategy == mo.desired) {
					rd = p; break;
				}
			}
			if (rd) { rd->render(mo); continue; }
			else
			{
				switch (mo.desired)
				{
				case RenderStrategy::Undefined:
				case RenderStrategy::NonPBR_PhongShading:
					mRenders.push_back(new NonPBRRenderBase);
					break;
				default:
					break;
				}
				mRenders.back()->render(mo);
			}
		}
	}

	void drawSkybox() {

	}
	void drawAxis() {

	}
	void drawParticle() {

	}



};

