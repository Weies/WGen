#pragma once
#include"component.h"
#include"function/base/render_base.h"
#include"animation_comp.h"
#include"resource/res_type/components/mesh.h"

class MeshComponent :public Component {
public:

	MeshCompRes				mMesh;
	RegisterComponent(Mesh);

	virtual void serial(Archive& ar)
	{
		Component::serial(ar);
		ar << mMesh;
	}

	MeshComponent() {}

	//��mRawMeshes���س�GameObjectDesc�ŵ�SceneManager��
	virtual void tick(float deltaTime)override;

};
