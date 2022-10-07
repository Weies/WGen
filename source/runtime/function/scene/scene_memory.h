#pragma once
#include"core/core.h"
#include"function/base/image.h"
#include"resource/resource_handle.h"
#include"resource/res_type.h"

class SceneMemory {
public:
	SceneMemory() :mSize(0), mData(0) {}
	SceneMemory(size_t size, void* data) :mSize(size), mData(data) {}
	size_t		mSize;
	void* mData;
	virtual void sync()const = 0;
	virtual void bind()const = 0;
	virtual void setup() = 0;
	virtual ~SceneMemory() {
		delete[] mData; mData = 0; mSize = 0;
	}
};
#define Constructor(name) name(){} name(size_t size, void* data):SceneMemory(size,data){}
class VertexMemory :public SceneMemory {
public:
	Constructor(VertexMemory);
	uint mVAO;
	uint mVBO;
	VertexFormat format{ Vertex_Invalid };
	void sync()const {
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		if (mSize > 0)
			glBufferData(GL_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
	}
	void bind()const {
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	}
	void setup() {
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		if (mSize > 0)
			glBufferData(GL_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
		switch (format)
		{
		case Vertex_PNTTB:
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mNormal));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mTexCoord));

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mTangent));

			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mBitangent));

			//注意整形要用IPointer
			glEnableVertexAttribArray(5);
			glVertexAttribIPointer(5, 4, GL_UNSIGNED_INT, sizeof(vertex), (void*)offsetof(vertex, mBoneIds));

			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mBoneWeights));
			break;
		case Vertex_Invalid:
		default:
			excep(WERROR_ARGUMENT, "Vertex format is not valid");
			break;
		}
	}
	~VertexMemory() {
		glDeleteBuffers(2, &mVAO);
	}
};
class IndexMemory :public SceneMemory {
public:
	Constructor(IndexMemory);

	uint mIBO;
	void sync() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
		if (mSize > 0)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
	}
	void bind()const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	}
	void setup() {
		glGenBuffers(1, &mIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
		if (mSize > 0)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
	}
	~IndexMemory() {
		glDeleteBuffers(1, &mIBO);
	}
};
class TextureMemory :public SceneMemory {
public:
	Constructor(TextureMemory);
	uint mTID; uint mTarget; int mNumChannels;
	int w; int h;
	void sync() const {
		glBindTexture(mTarget, mTID);
		if (mNumChannels == 1)
			glTexImage2D(mTarget, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, mData);
		else if (mNumChannels == 3)
			glTexImage2D(mTarget, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
		else if (mNumChannels == 4)
			glTexImage2D(mTarget, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData);
	}
	void bind()const {
		glBindTexture(mTarget, mTID);
	}
	void setupFromImage(const Image& img) {
		glGenTextures(1, &mTID);
		glBindTexture(mTarget, mTID);
		if (img.mNumChannels == 1)
			glTexImage2D(mTarget, 0, GL_RED, img.w, img.h, 0, GL_RED, GL_UNSIGNED_BYTE, img.data());
		else if (img.mNumChannels == 3)
			glTexImage2D(mTarget, 0, GL_RGB, img.w, img.h, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data());
		else if (img.mNumChannels == 4)
			glTexImage2D(mTarget, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data());
		w = img.w; h = img.h; mNumChannels = img.mNumChannels;
		if (img.w == img.h)glGenerateMipmap(mTarget);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (w == h) {
			glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else {
			glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		mData = img.data();
	}
	void setup() {
		glGenTextures(1, &mTID);
		glBindTexture(mTarget, mTID);
		if (mNumChannels == 1)
			glTexImage2D(mTarget, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, mData);
		else if (mNumChannels == 3)
			glTexImage2D(mTarget, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
		else if (mNumChannels == 4)
			glTexImage2D(mTarget, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData);
		if (w == h)glGenerateMipmap(mTarget);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (w == h) {
			glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else {
			glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
};
#undef Constructor

