#pragma once
#include"component.h"
#include"function/base/render_base.h"
#include"animation_comp.h"
#include"resource/res_type.h"

class MeshComponent :public Component {
public:

	MeshCompRes				mMesh;
	RegisterComponent(Mesh);

	void setMesh(const MeshData& mesh)
	{
		mMesh.mType = "Mesh";
		mMesh.mTransform = Transform();
		mMesh.mPath = mesh.mPath;
		for (const auto& m : mesh.mMeshes)
		{
			SubMeshRes res;
			res.mTransform = m.mTransform;
			res.mName = m.mName;
			mMesh.mMeshes.push_back(res);
		}
	}

	virtual void serial(Archive& ar)
	{
		Component::serial(ar);
		ar << mMesh;
	}

	MeshComponent() {}

	//将mRawMeshes加载成GameObjectDesc放到SceneManager中
	virtual void tick(float deltaTime)override;

};
