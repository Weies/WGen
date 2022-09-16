#pragma once
#include"core/base/basis.h"
#include<unordered_set>
#include"../component/component.h"
#define INVAILID_ID
class GObject {
public:
	uint				mId;
	string				mName;
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

	void addComponent(Component* sptr) {
		sptr->mParent = this;
		mComponents.push_back(sptr);
	}
	template<class TComponent>
	TComponent* tryGetComp(const string& comp_type) const {
		for (auto& v : mComponents) {
			if (v->mType == comp_type) {
				return (TComponent*)v;
			}
		}
		return nullptr;
	}
#define tryGetComp(comp_name) tryGetComp<comp_name>(#comp_name)
};