#pragma once

#include "../base/render_base.h"
#include "../base/image.h"
#include "stbi/stb_image.h"
#include "stbi/stb_image_resize.h"

enum TextureType {
	texture_none = 0,
	texture_diffuse = 1,
	texture_specular = 2,
	texture_ambient = 3,
	texture_emmisive = 4,
	texture_height = 5,
	texture_normal = 6,
	texture_shiness = 7,
	texture_opacity = 8,
	texture_displaces = 9,
	texture_lightmap = 10,
	texture_reflect = 11,
	texture_base_color = 12,
	texture_normal_camera = 13,
	texture_emission_color = 14,
	texture_metalness = 15,
	texture_diffuse_roughness = 16,
	texture_abient_occlusion = 17,
	texture_unknown = 18,
	texture_cubemap = 10,
	texture_buffer = 19,
};

class Texture {
public:

	string mName; TextureType mType = texture_none;
	uint mId; int mTarget = -1;
	void* mData = 0;
	union { int mWidth; int w; };
	union { int mHeight; int h; };
	int mNumChannels;

	Texture(int texture_mTarget = -1) {
		if (texture_mTarget != -1)
			gen(texture_mTarget);
	}

	Texture(Texture&& tex)
	{
		swap(tex);
	}

	Texture& operator=(const Texture& tex) = default;

	Texture& operator=(Texture&& tex)
	{
		swap(tex);
		return *this;
	}

	void swap(Texture& tex)
	{
		mName.swap(tex.mName);

		std::swap(mType, tex.mType);
		std::swap(mId, tex.mId);
		std::swap(mTarget, tex.mTarget);
		std::swap(mData, tex.mData);
		std::swap(mWidth, tex.mWidth);
		std::swap(mHeight, tex.mHeight);
		std::swap(mNumChannels, tex.mNumChannels);
	}

	void gen(int texture_mTarget = GL_TEXTURE_2D)
	{
		if (mTarget != -1)glDeleteTextures(1, &mId);
		mTarget = texture_mTarget;
		glGenTextures(1, &mId);
		glBindTexture(mTarget, mId);
	}


	void bind()const
	{
		glBindTexture(mTarget, mId);
	}

	// to_which is texture unit
	void bindToShader(uint shader_id, const string& textureName, int to_which = 1)const
	{
		//ASSERT(complete());
		glActiveTexture(GL_TEXTURE0 + to_which);
		glBindTexture(mTarget, mId);
		glUniform1i(glGetUniformLocation(shader_id, textureName.c_str()), to_which);
	}

	void load(const string& mName, const string& directory = "") {
		string truedir;
		if (directory == "")truedir = mName;
		else truedir = directory + '/' + mName;
		Image img(truedir);
		setData(img);
		this->mName = mName;
	}
	void load(const string& filePath) {
		Image img(filePath);
		setData(img);
		this->mName = filePath;
		//this->mName = filePath.substr(filePath.find_last_of('/') + 1);
	}

	void loadCubeMap(const string path[6], const string& directory = "") {
		ASSERT(mTarget == GL_TEXTURE_CUBE_MAP);
		glBindTexture(mTarget, mId); mType = texture_cubemap;
		Image img; this->mName = path[0];
		for (unsigned int i = 0; i < 6; i++)
		{
			img.load(directory + path[i], false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
				img.w, img.h, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data());
		}
		mData = img.data();
		//glGenerateMipmap(mTarget);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	//what:what's the inner format,eg:GL_DEPTH_ATTACHMENT
	void setVoid(int what, int w, int h, int  mData_mType) {
		glBindTexture(mTarget, mId);
		glTexImage2D(mTarget, 0, what, w, h, 0, what, mData_mType, NULL);
		setParas(); mType = texture_buffer;
		mData = (void*)(-1);
	}

	void setParas(bool mipmap = false) {
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (mipmap) {

			glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else {
			glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	void setPara(int para, int val) {
		glTexParameteri(mTarget, para, val);
	}

	void setData(const Image& img)
	{
		glBindTexture(mTarget, mId);
		if (img.mNumChannels == 1)
			glTexImage2D(mTarget, 0, GL_RED, img.w, img.h, 0, GL_RED, GL_UNSIGNED_BYTE, img.data());
		else if (img.mNumChannels == 3)
			glTexImage2D(mTarget, 0, GL_RGB, img.w, img.h, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data());
		else if (img.mNumChannels == 4)
			glTexImage2D(mTarget, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data());
		w = img.w; h = img.h; mNumChannels = img.mNumChannels;
		if (img.w == img.h)glGenerateMipmap(mTarget);
		setParas(img.w == img.h);
		mData = img.data();
	}

	void setData(const Mat<uchar>& m) {
		glBindTexture(mTarget, mId);
		glTexImage2D(mTarget, 0, GL_RED, m.rows, m.cols, 0, GL_RED, GL_UNSIGNED_BYTE, m.v);
		if (m.cols == m.rows)glGenerateMipmap(mTarget);
		setParas(m.cols == m.rows); w = m.rows; h = m.cols;
		mData = m.v; mNumChannels = 1;
	}
	void setData(const Mat<cvec3>& m) {
		glBindTexture(mTarget, mId);
		glTexImage2D(mTarget, 0, GL_RGB, m.rows, m.cols, 0, GL_RGB, GL_UNSIGNED_BYTE, m.v);
		if (m.cols == m.rows)glGenerateMipmap(mTarget);
		setParas(m.cols == m.rows);
		mWidth = m.rows; mHeight = m.cols;
		mData = m.v; mNumChannels = 3;
	}
	void setData(const Mat<cvec4>& m) {
		glBindTexture(mTarget, mId);
		glTexImage2D(mTarget, 0, GL_RGBA, m.rows, m.cols, 0, GL_RGBA, GL_UNSIGNED_BYTE, m.v);
		if (m.cols == m.rows)glGenerateMipmap(mTarget);
		setParas(m.cols == m.rows);
		mData = m.v; w = m.rows; h = m.cols; mNumChannels = 4;
	}
	string mTypeStr() const {
		switch (mType) {
		case texture_none:				return "texture_none";
		case texture_diffuse:			return "texture_diffuse";
		case texture_specular:			return "texture_specular";
		case texture_ambient:			return "texture_ambient";
		case texture_emmisive:			return "texture_emmisive";
		case texture_height:			return "texture_height";
		case texture_normal:			return "texture_normal";
		case texture_shiness:			return "texture_shiness";
		case texture_opacity:			return "texture_opacity";
		case texture_displaces:			return "texture_displaces";
		case texture_cubemap:			return "texture_cubemap";
		case texture_reflect:			return "texture_reflect";
		case texture_base_color:		return "texture_base_color";
		case texture_normal_camera:		return "texture_normal_camera";
		case texture_emission_color:	return "texture_emission_color";
		case texture_metalness:			return "texture_metalness";
		case texture_diffuse_roughness:	return "texture_diffuse_roughness";
		case texture_abient_occlusion:	return "texture_abient_occlusion";
		case texture_unknown:			return "texture_unknown";
		case texture_buffer:			return "texture_buffer";
		default:
			debug << "No  texture mType was set" << endl;
			return "texture_unknown";
		}
	}
	bool complete() const {
		return mTarget != -1 && mData && mType != texture_none && mType != texture_unknown;
	}
	void genMipmap()const
	{
		glBindTexture(mTarget, mId);
		glGenerateMipmap(mTarget);
	}
	void useDefault()const {
		//glActiveTexture(mTarget);
	}

};

class FBOBuffer {
public:
	FBOBuffer() {
		glGenFramebuffers(1, &mId);
		glBindFramebuffer(GL_FRAMEBUFFER, mId);
	}
	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, mId);
	}

	//what:what buffer to be attach,eg:GL_DEPTH_ATTACHMENT
	void attach(int what, const Texture& t) {
		ASSERT(t.complete());
		glBindFramebuffer(GL_FRAMEBUFFER, mId);
		glFramebufferTexture2D(GL_FRAMEBUFFER, what, t.mTarget, t.mId, 0);
	}

	void attachRBO(const RBOBuffer& r) {
		glBindFramebuffer(GL_FRAMEBUFFER, mId);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, r.mId);
	}

	void noColorBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, mId);
		glDrawBuffer(GL_NONE); glReadBuffer(GL_NONE);
	}
	void zero() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	uint mId;
};