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

	virtual void finalize(const Json& j) override
	{
		mMeshFile = j["Ref"].string_value();
		/*auto& m = mRawMeshes.back();
		m.mMeshDesc.mMeshName =*/ 
	}

	MeshComponent() {}

	//��mRawMeshes���س�GameObjectDesc�ŵ�SceneManager��
	virtual void tick(float deltaTime)override;

};
