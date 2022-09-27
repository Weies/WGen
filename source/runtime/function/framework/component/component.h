#pragma once
#include"function/base/base_include.h"
#include"resource/json_helper.h"

class GObject;
class ComponentHelper;

class Component {
public:
	GObject* mParent{ nullptr };
	bool	mIsTickInEditorMode{ false };
	Component() {}
	Component(GObject* parent) :mParent(parent) {}
	void setParent(GObject* par) {
		mParent = par;
	}

	virtual const string& type() = 0;
	virtual ~Component() {}
	virtual void tick(float deltaTime) {}
	virtual void destory() {}

	virtual void serial(Archive& ar)
	{

	}

private:

	friend class GObject;
	friend class ComponentHelper;

	virtual void finalize(const Json& j) = 0;

	void _tick(float deltaTime) {
		if (mIsTickInEditorMode || !isEditorMode)
			tick(deltaTime);
	}
};
template<class T>
using sptr = shared_ptr<T>;

class ComponentHelper :public Singleton<ComponentHelper>
{
public:
	map<string, void* (*)()> mComponents;



	Component* initComponent(const Json& comp_json)
	{
		const string& type = comp_json["Type"].string_value();

		Component* comp = (Component*)mComponents[type]();

		comp->finalize(comp_json);

		return comp;
		//if()
	}
};

class __ComponentRegister
{
public:

	__ComponentRegister(const char* ComponentName, void* (*func)())
	{
		ComponentHelper::get().mComponents.insert({ string(ComponentName), func });
		debug << "Registered component: " << ComponentName << endl;
	}
};


#define RegisterComponent(name) \
const string& type() override\
{\
	static const string type_name(#name);\
	return type_name;\
};\
private:\
static inline void* __construct(){return new name##Component();};\
static inline const __ComponentRegister __register##name = __ComponentRegister(#name,__construct);\
public:




class TransformComponent :public Component {
public:
	TransformComponent() {}

	virtual void finalize(const Json& j) override
	{
		mTransform = JsonHelper::parseTransform(j);
	}
	virtual void serial(Archive& ar) override
	{
		Component::serial(ar);

	}

	RegisterComponent(Transform);

	virtual void tick(float deltaTime) {
		//Render::get().contex.mModelTransform = mTransform;
	}
	Transform mTransform;
};



