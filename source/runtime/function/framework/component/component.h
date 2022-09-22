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
	template<class T>
	Register(const char* ComponentName, void(*func)(T* p))
	{
		ComponentHelper::get().mComponents.insert({ string(ComponentName), func });
	}
};

#define RegisterTypeName(name) 


#define RegisterComponent(name) \
const string& type() override\
{\
	static const string type_name(#name);\
	return type_name;\
};\
private:\
static inline const  auto lambda = []()->name##Component*{return new name##Component();};\
static inline const Register __register##name = Register(#name,lambda);\
public:



using Transform = SQT;
class TransformComponent :public Component {
public:
	TransformComponent() {}
	void Construct() {}

	//RegisterComponent(Transform);

	static inline const  auto lambda = []()->TransformComponent* { return new TransformComponent(); };

	virtual void tick(float deltaTime) {
		//Render::get().contex.mModelTransform = mTransform;
	}
	Transform mTransform;
};



