#pragma once
#include"core/log/debuger.h"
#include"resource/resource_handle.h"
enum class RenderStrategy {
	Undefined = 0,
	NonPBR_PhongShading,
	NonPBR_FlatShading,
	NonPBR_GrouraudShading,
	PBR_MetallicRoughness,
	PBR_SpecularGlossiness,
	RayTracing_PathTracing
};




#define MAX_JOINT_COUNT 64

class RenderMesh {
public:
	uid						mGUID;
	uid						mInstanceID;
	SkeletonBindingHandle	mSBH;
	VertexBufferHandle		mVBH;
	IndexBufferHandle		mIBH;
	RenderMaterial			mMaterial;
};

class RenderModel {
public:
	RenderStrategy desired{ RenderStrategy::Undefined };
	mat4 mModelTransform;
	vector<RenderMesh> mMeshes;
	uint mNumJoints;
	mat4 mJointMat[MAX_JOINT_COUNT];
};

class VAOBuffer {
public:
	VAOBuffer() {
		glGenVertexArrays(1 , &mId);
		bind();
	}
	void bind()
	{
		glBindVertexArray(mId);
	}
	uint mId;
};

class VBOBuffer {
public:
	VBOBuffer() {
		glGenBuffers(1 , &mId);
		bind();
	}
	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER , mId);
	}
	void setData(unsigned int bytes , const void* data , GLenum usage = GL_STATIC_DRAW)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER , bytes , data , usage);
	}
	void setSubData(unsigned int bytes , unsigned int offset , const void* data)
	{
		bind();
		glBufferSubData(GL_ARRAY_BUFFER , offset , bytes , data);
	}
	void setAttribPointer(uint index = 0 , int components = 3 , GLsizei stride_bytes = 12 , const void* offset_bytes = (void*)12 , GLenum data_type = GL_FLOAT , GLboolean normalize = GL_FALSE)
	{
		bind();
		glVertexAttribPointer(index , components , data_type , normalize , stride_bytes , offset_bytes);
		glEnableVertexAttribArray(index);
	}
	void setAttribPointer(uint index = 0 , int components = 3 , GLsizei stride_bytes = 12 , int offset_bytes = 12 , GLenum data_type = GL_FLOAT , GLboolean normalize = GL_FALSE)
	{
		bind();
		glVertexAttribPointer(index , components , data_type , normalize , stride_bytes , (void*)offset_bytes);
		glEnableVertexAttribArray(index);
	}
	uint mId;
};

class IBOBuffer {
public:
	IBOBuffer() {
		glGenBuffers(1 , &mId);
		bind();
	}
	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , mId);
	}
	void setData(unsigned int len , const void* data , GLenum usage = GL_STATIC_DRAW)
	{
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER , len , data , usage);
	}
	uint mId;
};

class RBOBuffer {
public:
	RBOBuffer() {
		glGenRenderbuffers(1 , &mId);
	}
	void bind() {
		glBindRenderbuffer(GL_RENDERBUFFER , mId);
	}

	void setData(int w , int h) {
		glBindRenderbuffer(GL_RENDERBUFFER , mId);
		glRenderbufferStorage(GL_RENDERBUFFER , GL_DEPTH24_STENCIL8 , w , h);
	}
	uint mId;
};

