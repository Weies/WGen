#pragma once
#include"function/base/base_include.h"

class GObject;
class Component {
public:
	GObject* mParent{ nullptr };
	string	mType;
	bool	mIsTickInEditorMode{ false };
	Component() {}
	Component(const string& type) :mType(type) {}
	Component(GObject* parent) :mParent(parent) {}
	void setParent(GObject* par) {
		mParent = par;
	}

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

using Transform = SQT;
class TransformComponent :public Component {
public:
	TransformComponent() :Component("TransformComponent") {}
	virtual void tick(float deltaTime) {
		//Render::get().contex.mModelTransform = mTransform;
	}
	Transform mTransform;
};



