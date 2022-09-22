#pragma once
#include"function/base/base_include.h"

class GObject;

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

private:
	friend class GObject;
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
	map<string, void*> mComponents;


};

class Register
{
public:
	Register(const char* ComponentName)
	{
		ComponentHelper::get().mComponents.insert({ string(ComponentName), nullptr });
	}
};

#define RegisterTypeName(name) private:\
static inline const Register __register##name = Register(#name);\
public:


#define RegisterComponent(name) \
const string& type() override\
{\
	static const string type_name(#name);\
	return type_name;\
};\
RegisterTypeName(name)



using Transform = SQT;
class TransformComponent :public Component {
public:
	TransformComponent() {}

	RegisterComponent(Transform);



	virtual void tick(float deltaTime) {
		//Render::get().contex.mModelTransform = mTransform;
	}
	Transform mTransform;
};



