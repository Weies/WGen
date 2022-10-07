#pragma once
#include"core/core.h"
#include"../component/component.h"
#include"../component/animation_comp.h"
#include"../component/mesh_comp.h"


#define INVAILID_ID
class GObject {
public:
	uint				mId;
	string				mName;
	string				mFilePath;
	string				mDefinitionUrl;
	vector<Component*>	mComponents;

	GObject() :mId(INVAILID_ID) {}
	GObject(uint id) :mId(id) {}
	~GObject() {
		for (auto& co : mComponents) {
			delete co;
		}
		mComponents.resize(0);
	}
	void tick(float delta_time)const {
		for (auto& co : mComponents) {
			co->tick(delta_time);
		}
	}

	virtual void serial(Archive& ar)
	{
		ar << mId << mName << mFilePath << mDefinitionUrl;

		int comp_size = mComponents.size();
		ar << comp_size;
		if (ar.isLoading())
		{
			for (int i = 0; i < comp_size; ++i)
			{
				string tp;
				ar << tp;
				Component* comp = ComponentHelper::get().newComponent(tp);
				comp->serial(ar);
				addComponent(comp);
			}
		}
		else
		{
			for (auto& comp : mComponents)
			{
				string tp = comp->type();
				ar << tp;
				comp->serial(ar);
			}
		}
	}

	void addComponent(Component* sptr) {
		sptr->mParent = this;
		mComponents.push_back(sptr);
	}

	template<class TComponent>
	TComponent* tryGetComp(const string& comp_type) const {
		for (auto& v : mComponents) {
			if (v->type() == comp_type) {
				return (TComponent*)v;
			}
		}
		return nullptr;
	}
#define tryGetComp(comp_name) tryGetComp<comp_name##Component>(#comp_name)
};