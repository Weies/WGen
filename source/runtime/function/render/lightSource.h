#pragma once
#include"core/core.h"
enum LightType {
	LightTypeNone,
	InfiniteFarLightSource,
	PointLightSource,
	SpotLightSource
};


using gm::vec3;

class BaseLight {
public:
	BaseLight() :mLightColor(1.0f, 1.0f, 1.0f) {
		mType = LightTypeNone; mShiness = 1.0;
		setEffectiveRange(100);
	}
	void setLightColor(const vec3& light_color) {
		mLightColor = light_color;
	}
	void setLightColor(float r, float g, float b) {
		mLightColor = vec3(r, g, b);
	}
	vec3 getLightColor() const {
		return mLightColor;
	}
	virtual vec3 getLightPos() const = 0;
	virtual void moveto(const vec3& p) {
		mLightPos = p;
	}
	void setEffectiveRange(float d) {
		mDumpVector[0] = 0.459f; mDumpVector[1] = 0.525f / d; mDumpVector[2] = 1.37 * pow(1.278f / d, 2);
		//mDumpVector[0] = 0.5; mDumpVector[1] = 4.625f / d; mDumpVector[2] = 0.5 * pow(7.0f / d , 2);
		//mDumpVector[0] = 0.0f; mDumpVector[1] = 0.0f / d; mDumpVector[2] = 1.0f;
	}
	void setShiness(float val) {
		mShiness = val;
	}
	vec3 mDumpVector;//damp vector-
	float mShiness;
protected:
	vec3 mLightColor; LightType mType; vec3 mLightPos;
};

class InfiniteLightSource :public BaseLight {//无限远的平行光，适合模拟太阳
public:
	InfiniteLightSource() :mLightDir(0.0f, 1.0f, 0.0f) {
		mType = InfiniteFarLightSource;
	}
	void setLightDir(const vec3& dir) {
		mLightDir = gm::normalize(dir);
	}
	vec3 getLightDir() const {
		return mLightDir;
	}
	vec3 getLightPos() const {
		return mLightDir * -100000.0f;
	}
protected:
	vec3 mLightDir;
};


class PointLightSource :public BaseLight {//点光源
public:
	PointLightSource() {
		mType = LightType::PointLightSource;
		mLightPos = vec3(10, 0, 4.0);

	}
	virtual void moveto(const vec3& pos) {
		mLightPos = pos;
	}
	vec3 getLightPos() const {
		return mLightPos;
	}
protected:
};

class SpotLightSource :public BaseLight {//聚光光源
public:
	SpotLightSource() {
		mType = LightType::SpotLightSource;
		mCutoffAngle = 0.32f;//约为PI/6
		mLightDir = vec3(0.0f, 0.0f, -1.0f);
		mLightPos = vec3(10.0, 0, 4.0);
	}
	void setLightDir(const vec3& dir) {
		mLightDir = gm::normalize(dir);
	}
	vec3 getLightDir() const {
		return mLightDir;
	}
	void setDegree(float deg) {
		mCutoffAngle = gm::radians(deg);
	}
	vec3 getLightPos() const {
		return mLightPos;
	}
	float mCutoffAngle;
protected:
	vec3 mLightDir;
};

//class RenderableLight :public BaseLight, public Sphere {
//public:
//	using Sphere::mModelTransform;
//	using Sphere::draw;
//	using Mesh::hasTexture;
//
//	RenderableLight(int seg = 18) :Sphere(seg) {
//		scale(0.04, 0.04, 0.04);
//		moveto(vec3(10.0f, 0.0f, 4.0f));
//	}
//	void translate(float x, float y, float z) {
//		//model = gm::translate(model , vec3(x , y , z).tvec());
//		StaticObject::translate(x, y, z);
//		mLightPos = mModelTransform.t;
//	}
//	void moveto(const vec3& pos) {
//		mLightPos = vec3(pos);
//		mModelTransform.t = mLightPos;
//	}
//};
//
//
//class LightSource :public RenderableLight {//可绘制的点光源
//public:
//	LightSource() {
//		mType = LightType::PointLightSource;
//	}
//	vec3 getLightPos() const {
//		return mLightPos;
//	}
//};
//
//class  SpotLight :public RenderableLight {
//public:
//	SpotLight() {
//		mType = LightType::SpotLightSource;
//		mCutoffAngle = 0.52f;//约为PI/6
//		mLightDir = vec3(0.0f, 0.0f, -1.0f);
//	}
//	void setLightDir(const vec3& dir) {
//		mLightDir = gm::normalize(dir);
//	}
//	vec3 getLightDir() const {
//		return mLightDir;
//	}
//	vec3 getLightPos() const {
//		return mLightPos;
//	}
//	void setDegree(float deg) {
//		mCutoffAngle = gm::radians(deg);
//	}
//	float mCutoffAngle;
//protected:
//	vec3 mLightDir;
//};
//
//class  ParallelLight :public RenderableLight {
//public:
//	ParallelLight() {
//		mType = InfiniteFarLightSource;
//		scale(500);
//		moveto(vec3(0, 0, 1000));
//		setLightDir(vec3(0, 0, -1));
//		setLightColor(vec3(1, 1, 1));
//	}
//	void setLightDir(const vec3& dir) {
//		mLightDir = gm::normalize(dir);
//		moveto(mLightDir * -100.f);
//	}
//	vec3 getLightDir() const {
//		return mLightDir;
//	}
//	vec3 getLightPos() const {
//		return mLightDir * -100.0f;
//	}
//protected:
//	vec3 mLightDir;
//};