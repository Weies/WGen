#pragma once
#include"shader.h"
#include"../base/render_base.h"
//#include"../model/lightSource.h"

#define RENDER_LIGHT	0
#define RENDER_MESH		1
#define RENDER_LIST		2
#define RENDER_SKY		3
#define RENDER_NORMAL	4
#define RENDER_DEPTH	5
#define RENDER_POLYGON	6

#define SPOTLIGHT		0
#define POINTLIGHT		1
#define PARALLELLIGHT	2

#define MAX_LIGHT_NUM 10

enum ShadingType {
	ShadingNone,
	Shading2D, Shading3D,//非光照着色
	FlatShading, PhongShading, GouraudShading//光照着色
};

extern class Camera;

class BaseRender :public Shader {
public:
	using Shader::id;
	BaseRender(ShadingType type) {
		_type = type;
		static const char* shader_2D = {
			"#version 460 core\n"
			"layout(location = 0) in vec2  pos;\n"
			"uniform mat3 transform;//变换矩阵\n"
			"uniform mat4 proj;//正射投影矩阵\n"
			"uniform float prior;"
			"void main()\n"
			"{\n"
			"	float prio = prior;"
			"	if(prior>1024)prio = 1024+log(prior);"
			"	prio = prio/(100+prio)*prio/1024;"
			"	gl_Position =proj* vec4((transform*vec3(pos,1.0)).xy,prio,1.0);\n"
			"}\n"
			"%\n"
			"#version 460 core\n"
			"out vec4 co;\n"
			"uniform vec4 color;\n"
			"void main() {\n"
			"\tco = color;\n"
			"}\n"
		};
		static const char* shader_3D = {
	"#version 460 core\n"
	"layout(location = 0) in vec3 pos;"
	"uniform mat4 transform;"
	"uniform mat4 model;"
	"uniform vec3 normal;"
	"out vec3 norm;"
	"out vec3 pp;"
	"void main(){"
	"	gl_Position = transform*vec4(pos,1.0);"
	"	if(normal.x>-100) {"
	"		norm = normalize(transpose(inverse(mat3(model)))*normal);"
	"		pp = vec3(model*vec4(pos,1.0));"
	"	}"
	"	else norm= normal;"
	"}"
	"  %  "
	"#version 460 core\n"
	"uniform vec4 color;"
	"uniform vec3 viewPos;"
	"in vec3 pp;"
	"in vec3 norm;"
	"out vec4 co;"
	"void main(){"
	"	float diff=1.0;float spec=0.0;"
	"	if(norm.x>-50){"
	"		vec3 viewDir=normalize(viewPos-pp);"
	"		diff=max(dot(norm,viewDir),0.0);"
	"		spec=diff*diff;spec *= spec*spec;spec*=spec*spec;spec*= spec*spec;"
	"	}"
	"	co = vec4(color.rgb*((diff+spec)/2.0+0.5),color.a);"
	"}"
		};
		if (type == FlatShading)
			parseShader("source/shader/flat.shader");
		else if (type == PhongShading)
			//parseShader("loader.shader");
			parseShader("source/shader/phong_shadow.shader");
		else if (type == GouraudShading)
			parseShader("source/shader/gouraud.shader");
		else if (type == Shading2D)
			parseFromString(shader_2D);
		else if (type == Shading3D)
			parseFromString(shader_3D);
		use();
	}
	virtual void bind(bool sync_VBO = true) {
		use();
		if (sync_VBO) {
			vao.bind();
			vbo.bind();
		}
	}
	virtual void setData(unsigned int bytes, const void* data, GLenum usage = GL_STATIC_DRAW) = 0;
	ShadingType _type = ShadingNone;
	VAOBuffer vao; VBOBuffer vbo;
};

class Render2D :public BaseRender {
public:
	Render2D();
	void setProjM(const mat4& m) {
		bind();
		glUniformMatrix4fv(proj, 1, GL_FALSE, value_ptr(m));
	}
	void setTransformM(const mat3& transform) {
		bind();
		glUniformMatrix3fv(this->transform, 1, GL_FALSE, value_ptr(transform));
	}
	void setColor(const vec4& color) {
		bind();
		glUniform4fv(this->color, 1, value_ptr(color));
	}
	void setPrior(float p) {
		bind();
		glUniform1f(prior, p);
	}
	void setData(unsigned int bytes, const void* data, GLenum usage = GL_STATIC_DRAW) {
		vao.bind();
		vbo.setData(bytes, data, usage);
		vbo.setAttribPointer(0, 2, 8, (const void*)0);
	}
	void Render(GLenum mode, int first, int count) {
		bind();
		glDrawArrays(mode, first, count);
	}
	void renderList(const mat3& transform);
	int transform; int proj; int prior; int color;
};

class Render3D :public BaseRender {
public:
	Render3D() : BaseRender(Shading3D) {
		bind();
		transform = glGetUniformLocation(id, "transform");
		color = glGetUniformLocation(id, "color");
		norm = glGetUniformLocation(id, "normal");
		viewPos = glGetUniformLocation(id, "viewPos");
		model = glGetUniformLocation(id, "model");
	}
	void setColor(const vec4& co) {
		bind();
		glUniform4fv(color, 1, value_ptr(co));
	}
	void setTransformM(const mat4& t) {
		bind();
		glUniformMatrix4fv(transform, 1, GL_FALSE, value_ptr(t));
	}
	void setNormal(const vec3& normal) {
		bind();
		glUniform3fv(norm, 1, value_ptr(normal));
	}
	void setModel(const mat4& m) {
		bind();
		glUniformMatrix4fv(model, 1, GL_FALSE, value_ptr(m));
	}
	void setViewPos(const vec3& p) {
		bind();
		glUniform3fv(viewPos, 1, value_ptr(p));
	}
	void setData(unsigned int bytes, const void* data, GLenum usage = GL_STATIC_DRAW) {
		vao.bind();
		vbo.setData(bytes, data, usage);
		vbo.setAttribPointer(0, 3, 12, (const void*)0);
	}
	void render(GLenum mode, int first, int count) {
		bind();
		glDrawArrays(mode, first, count);
	}
	void renderList(const CameraBlock& b);//渲染ptr3所绘制的内容 
	int transform; int color; int norm; int viewPos; int model;
};

//class BaseLightRender :public BaseRender {
//public:
//	BaseLightRender(ShadingType type) :BaseRender(type) {
//		transform = glGetUniformLocation(id, "transform");
//		model = glGetUniformLocation(id, "model");
//		objColor = glGetUniformLocation(id, "objectColor");
//		ltColor = glGetUniformLocation(id, "lightColor");
//		ltPos = glGetUniformLocation(id, "lightPos");
//		viewPos = glGetUniformLocation(id, "viewPos");
//		normal = glGetUniformLocation(id, "normal");
//		texture_enable = glGetUniformLocation(id, "texture_enable");
//		state = glGetUniformLocation(id, "state");
//		coord_type = glGetUniformLocation(id, "coord_type");
//		setCoordType(CUBIC_COORD); useShadow(false); useTexture(false);
//	}
//
//	void setCoordType(int type) {
//		setInt(coord_type, type);
//	}
//	void setTransformM(const mat4& MVP_transform) {
//		setMat4(transform, MVP_transform);
//	}
//	void setModelM(const mat4& model) {
//		setMat4(this->model, model);
//	}
//	void setColor(const vec4& objectColor) {
//		setVec4(objColor, objectColor);
//	}
//	void setLightColor(const vec3& lightColor, float shiness = 1.0f) {
//		setVec3(ltColor, lightColor * log(1.718 * shiness + 1.0));
//	}
//	void setLightPos(const vec3& lightPos) {
//		use();
//		glUniform3fv(ltPos, 1, value_ptr(lightPos));
//	}
//	void setViewPos(const vec3& pos) {
//		use();
//		glUniform3fv(this->viewPos, 1, value_ptr(pos));
//	}
//	void setNormal(const vec3& normal) {
//		use();
//		glUniform3fv(this->normal, 1, value_ptr(normal));
//	}
//	void setDampVec(const vec3& v) {
//		use();
//		glUniform3fv(dampVec, 1, value_ptr(v));
//	}
//	void setState(int state) {
//		setInt(this->state, state);
//	}
//	void forceRenderState(int render_state, bool force = true) {
//		if (RENDER_POLYGON == render_state) {
//			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); return;
//		}
//		force_render = force;
//		setInt(this->state, render_state);
//	}
//
//	void setData(unsigned int bytes, const void* data, GLenum usage = GL_STATIC_DRAW) {
//		vao.bind();
//		vbo.setData(bytes, data, usage);
//		vbo.setAttribPointer(0, 3, 24, (const void*)0);
//		vbo.setAttribPointer(1, 3, 24, (const void*)12);
//	}
//	void setElementArray(unsigned int bytes, const void* data, GLenum usage = GL_STATIC_DRAW) {
//		ibo.setData(bytes, data, usage);
//	}
//	virtual void renderList(const mat4& mPVTransform, const vec3& viewPos, const vec3& lightColor, const vec3& lightPos);
//	virtual void renderList(const CameraBlock& b);
//
//
//	void bind(bool sync_VBO = true) {
//		use();
//		if (sync_VBO) {
//			vao.bind();
//			vbo.bind();
//			ibo.bind();
//		}
//	}
//	void useTexture(bool use = false) {
//		setInt("texture_enable", use);
//	}
//	void useShadow(bool shadow = false) {
//		setInt("shadow_enable", shadow);
//	}
//	void useAnimation(bool use = false) {
//		setInt("anim_enable", use);
//	}
//
//	void setBlock(const CameraBlock& b) {
//		block = b;
//	}
//	void addLights() {
//		float range = 2000;
//		static LightSource l;   l.moveto(vec3(1000, 1000, 1000)); l.setEffectiveRange(range);
//		static LightSource l5; l5.moveto(vec3(1000, 1000, -1000)); l5.setEffectiveRange(range);
//		static LightSource l6; l6.moveto(vec3(1000, -1000, -1000)); l6.setEffectiveRange(range);
//		static LightSource l7; l7.moveto(vec3(1000, -1000, 1000)); l7.setEffectiveRange(range);
//		static LightSource l1; l1.moveto(vec3(-1000, 1000, -1000)); l1.setEffectiveRange(range);
//		static LightSource l2; l2.moveto(vec3(-1000, -1000, 1000)); l2.setEffectiveRange(range);
//		static LightSource l3; l3.moveto(vec3(-1000, -1000, -1000)); l3.setEffectiveRange(range);
//		static LightSource l4; l4.moveto(vec3(-1000, 1000, -1000)); l4.setEffectiveRange(range);
//		bindToLight(l);
//		bindToLight(l1); bindToLight(l2);  bindToLight(l3);
//		bindToLight(l4); bindToLight(l5); bindToLight(l6); bindToLight(l7);
//	}
//	void bindToLight(LightSource& lt) {
//		bind();
//		string str = "lts[" + itos(lts.size()) + "].";
//		setInt(str + "type", POINTLIGHT);
//		setVec3(str + "pos", lt.getLightPos());
//		setVec3(str + "color", lt.getLightColor());
//		setVec3(str + "dv", lt.mDumpVector);
//		setFloat(str + "shiness", lt.mShiness);
//		lts.push_back(&lt);
//	}
//	void bindToLight(SpotLight& lt) {
//		bind();
//		string str = "lts[" + itos(lts.size()) + "].";
//		setInt(str + "type", SPOTLIGHT);
//		setVec3(str + "pos", lt.getLightPos());
//		setVec3(str + "color", lt.getLightColor());
//		setVec3(str + "dir", lt.getLightDir());
//		setVec3(str + "dv", lt.mDumpVector);
//		setFloat(str + "theta", lt.mCutoffAngle);
//		setFloat(str + "shiness", lt.mShiness);
//		lts.push_back(&lt);
//	}
//	void bindToLight(ParallelLight& lt) {
//		bind();
//		string str = "lts[" + itos(lts.size()) + "].";
//		setInt(str + "type", PARALLELLIGHT);
//		setVec3(str + "dir", lt.getLightDir());
//		setVec3(str + "color", lt.getLightColor());
//		setVec3(str + "dv", lt.mDumpVector);
//		setFloat(str + "shiness", lt.mShiness);
//		lts.push_back(&lt);
//	}
//
//	//完成前置操作但不渲染
//	void bindMesh(const SkeletonObject& o) {
//		bind(false);
//		setCoordType(o.mTexCoordType);
//		setInt("light_num", lts.size());
//		if (!force_render)setState(RENDER_MESH);
//		setColor(o.mColor);
//		setModelM(o.mModelTransform);
//		setTransformM(block.mPVTransform * (o.mModelTransform));
//		setViewPos(block.mCameraPosition);
//		useTexture(o.hasTexture());
//		useAnimation(o.mNumBones > 0 && o.mIsPlaying);
//	}
//	virtual void renderMesh(SkeletonObject& o) = 0;
//	virtual void renderMesh(StaticObject& o) = 0;
//	virtual void renderLight() {
//		bind(); if (!force_render)setState(RENDER_LIGHT);
//		for (int i = 0; i < lts.size(); ++i) {
//			auto light = lts[i];
//			setLightColor(light->getLightColor(), light->mShiness);
//			setModelM((light->mModelTransform));
//			setTransformM(block.mPVTransform * (light->mModelTransform));
//			setViewPos(block.mCameraPosition);
//			useTexture(light->hasTexture());
//			useAnimation(false);
//			light->draw(id);
//		}
//	}
//	virtual void renderSky(SkyBox& box) {
//		bind(false);
//		if (!force_render)setState(RENDER_SKY);
//		setTransformM(block.mPVTransform * box.mModelTransform);
//		setModelM(box.mModelTransform); useTexture(true);
//		useAnimation(false);
//		box.draw(id);
//	}
//
//	BaseLightRender& operator<<(SkeletonObject& m) {
//		renderMesh(m);
//		return *this;
//	}
//	BaseLightRender& operator<<(StaticObject& m) {
//		renderMesh(m);
//		return *this;
//	}
//
//	BaseLightRender& operator<<(LightSource& lt) {
//		bindToLight(lt);
//		return *this;
//	}
//	BaseLightRender& operator<<(SpotLight& lt) {
//		bindToLight(lt);
//		return *this;
//	}
//	BaseLightRender& operator<<(ParallelLight& lt) {
//		bindToLight(lt);
//		return *this;
//	}
//	BaseLightRender& operator<<(SkyBox& box) {
//		renderSky(box);
//		return *this;
//	}
//
//	IBOBuffer ibo; vector<RenderableLight*> lts;
//	int state; int coord_type; CameraBlock block;
//	int model; int transform; int normal; int dampVec;
//	int ltPos; int ltColor; int objColor; int viewPos;
//	int light_rendering; int texture_enable; int texture_loc;
//	bool force_render = false;
//};
//
//class FlatRender : public BaseLightRender {
//public:
//	FlatRender() :BaseLightRender(FlatShading) {}
//	void renderMesh(const SkeletonObject& o) {
//		bind(false);
//		setCoordType(o.mTexCoordType);
//		setInt("light_num", lts.size());
//		if (!force_render)setState(RENDER_MESH);
//		setColor(o.mColor);
//		setModelM(o.mModelTransform);
//		setTransformM(block.mPVTransform * (o.mModelTransform));
//		setViewPos(block.mCameraPosition);
//		useAnimation(o.mNumBones > 0 && o.mIsPlaying);
//		//glDrawElements(GL_TRIANGLES , mesh->getFaceNum()*3 , GL_UNSIGNED_INT , mesh->getIndices());//当没有绑定IBO时可以直接放indices
//		//for (int i = 0; i < mesh->getFaceNum(); i++) {
//		//	setNormal(mesh->normal(i));
//		//	glDrawElements(GL_TRIANGLES , 3 , GL_UNSIGNED_INT , (const void*)(12 * i));//最后一个参数是偏移量
//		//}
//	}
//	void renderMesh(const StaticObject& o) {
//		bind(false);
//		setCoordType(o.mTexCoordType);
//		setInt("light_num", lts.size());
//		if (!force_render)setState(RENDER_MESH);
//		setColor(o.mColor);
//		setModelM(o.mModelTransform);
//		setTransformM(block.mPVTransform * (o.mModelTransform));
//		setViewPos(block.mCameraPosition);
//		useAnimation(0);
//		//glDrawElements(GL_TRIANGLES , mesh->getFaceNum()*3 , GL_UNSIGNED_INT , mesh->getIndices());//当没有绑定IBO时可以直接放indices
//		//for (int i = 0; i < mesh->getFaceNum(); i++) {
//		//	setNormal(mesh->normal(i));
//		//	glDrawElements(GL_TRIANGLES , 3 , GL_UNSIGNED_INT , (const void*)(12 * i));//最后一个参数是偏移量
//		//}
//	}
//};
//
//class PhongRender :public BaseLightRender {
//public:
//	PhongRender() :BaseLightRender(PhongShading) {}
//
//	void renderMesh(SkeletonObject& o) {
//		bind(false);
//		setCoordType(o.mTexCoordType);
//		setInt("light_num", lts.size());
//		if (!force_render)setState(RENDER_MESH);
//		setColor(o.mColor);
//		setModelM(o.mModelTransform);
//		setTransformM(block.mPVTransform * (o.mModelTransform));
//		setViewPos(block.mCameraPosition);
//		useTexture(o.hasTexture());
//		useAnimation(o.mNumBones > 0 && o.mIsPlaying);
//		o.draw(id);
//	}
//
//	void renderMesh(StaticObject& o) {
//		bind(false);
//		setCoordType(o.mTexCoordType);
//		setInt("light_num", lts.size());
//		if (!force_render)setState(RENDER_MESH);
//		setColor(o.mColor);
//		setModelM(o.mModelTransform);
//		setTransformM(block.mPVTransform * (o.mModelTransform));
//		setViewPos(block.mCameraPosition);
//		useTexture(o.hasTexture());
//		useAnimation(0);
//		o.draw(id);
//	}
//};
//
//class GouraudRender :public BaseLightRender {
//public:
//	GouraudRender() :BaseLightRender(GouraudShading) {}
//	void renderMesh(SkeletonObject& o) {
//		bind(false);
//		setCoordType(o.mTexCoordType);
//		setInt("light_num", lts.size());
//		if (!force_render)setState(RENDER_MESH);
//		setColor(o.mColor);
//		setModelM(o.mModelTransform);
//		setTransformM(block.mPVTransform * (o.mModelTransform));
//		setViewPos(block.mCameraPosition);
//		useTexture(o.hasTexture());
//		useAnimation(o.mNumBones > 0 && o.mIsPlaying);
//		o.draw(id);
//	}
//	void renderMesh(StaticObject& o) {
//		bind(false);
//		setCoordType(o.mTexCoordType);
//		setInt("light_num", lts.size());
//		if (!force_render)setState(RENDER_MESH);
//		setColor(o.mColor);
//		setModelM(o.mModelTransform);
//		setTransformM(block.mPVTransform * (o.mModelTransform));
//		setViewPos(block.mCameraPosition);
//		useTexture(o.hasTexture());
//		useAnimation(0);
//		o.draw(id);
//	}
//};