#pragma once
#include"component.h"
#include"function/base/render_base.h"
#include"animation.h"


#include"function/scene/model_importer.h"

class MeshComponent :public Component {
public:
	vector<MeshCompDesc>	mRawMeshes;
	string					mMeshFile;

	RegisterComponent(Mesh);

	virtual void finalize(const Json& j) override;

	MeshComponent() {}

	//将mRawMeshes加载成GameObjectDesc放到SceneManager中
	virtual void tick(float deltaTime)override;

};
