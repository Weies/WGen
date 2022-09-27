#pragma once
#include"core/base/basis.h"
#include<unordered_set>
#include"../component/component.h"
#include"../component/animation_comp.h"
#include"../component/mesh_comp.h"
#include"resource/json_helper.h"

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

	void initialize(const string& object_path)
	{
		mFilePath = object_path;
		Json obj = JsonHelper::load(object_path);

		mId = obj["Id"].int_value();
		mName = obj["Name"].string_value();
		mDefinitionUrl = obj["DefinitionUrl"].string_value();

		Json::array comps = obj["Components"].array_items();

		for (auto& comp : comps)
		{
			addComponent(ComponentHelper::get().initComponent(comp));
		}
	}

	virtual void serial(Archive& ar)
	{
		ar << mId << mName << mFilePath << mDefinitionUrl;

		for (auto& comp : mComponents)
		{
			comp->;
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