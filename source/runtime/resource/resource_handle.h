#pragma once
#include"basis.h"

//Handle -> Memory -> concrete data
struct ResourceHandle {
public:
	uid mHandle;

	ResourceHandle() :mHandle(INVAILID_HANDLE) {}
	ResourceHandle(uid handle) :mHandle(handle) {}
	ResourceHandle(const void* handle) :mHandle((uid)handle) {}

	bool operator==(const ResourceHandle& otr)const {
		return otr.mHandle == mHandle;
	}

	uid hash()const { return mHandle; }

	template<class T>
	operator T() const {
		static_assert(std::is_base_of<ResourceHandle, T>::value);
		return *(T*)this;
	}

	operator bool()const {
		return mHandle != 0;
	}
};
template<>
struct std::hash<ResourceHandle> {
	size_t operator()(const ResourceHandle& hd) {
		return hd.mHandle;
	}
};

struct VertexBufferHandle :public ResourceHandle {
	bool operator==(const ResourceHandle& otr)const {
		return otr.mHandle == mHandle;
	}
};
struct IndexBufferHandle :public ResourceHandle {
	bool operator==(const ResourceHandle& otr)const {
		return otr.mHandle == mHandle;
	}
};
struct TextureHandle :public ResourceHandle {
	bool operator==(const ResourceHandle& otr)const {
		return otr.mHandle == mHandle;
	}
};
struct SkeletonBindingHandle :public ResourceHandle {
	bool operator==(const ResourceHandle& otr)const {
		return otr.mHandle == mHandle;
	}
};


struct MeshHandle {
	VertexBufferHandle		mVBH;
	IndexBufferHandle		mIBH;
	SkeletonBindingHandle	mSBH;
	bool operator==(const MeshHandle& otr)const {
		return otr.mVBH == mVBH;
	}
	uid hash() const { return mVBH.hash(); }
};
template<>
struct std::hash<MeshHandle> {
	size_t operator()(const MeshHandle& hd) {
		return hd.hash();
	}
};

struct MaterialHandle {
	TextureHandle		mBaseColorHandle;
	TextureHandle		mDiffuseMapHandle;
	TextureHandle		mSpecularMapHandle;
	TextureHandle		mNormalMapHandle;
	TextureHandle		mMetallicMapHandle;
	TextureHandle		mRoughnessMapHandle;
	TextureHandle		mOcculusionMapHandle;
	bool operator==(const MaterialHandle& otr)const {
		return otr.mBaseColorHandle == mBaseColorHandle;
	}
	uid hash() const { return mBaseColorHandle.hash(); }
};

template<>
struct std::hash<MaterialHandle> {
	size_t operator()(const MaterialHandle& hd) {
		return hd.hash();
	}
};

class RenderMaterial {
public:
	vec4				mBaseColor{ 1.0,1.0,1.0,1.0 };
	vec3				mDiffuse{ 1.0,1.0,1.0 };
	vec3				mSpecular{ 1.0,1.0,1.0 };
	float				mMetallic{ 0.5f };
	float				mRoughness{ 0.5f };
	float				mOcculusion{ 1.0f };
	bool operator==(const RenderMaterial& otr)const {
		return otr.mBaseColorHandle == mBaseColorHandle;
	}
	//base color will be treat as albedo
	TextureHandle		mBaseColorHandle;

	TextureHandle		mDiffuseMapHandle;

	TextureHandle		mSpecularMapHandle;

	TextureHandle		mNormalMapHandle;

	TextureHandle		mMetallicMapHandle;

	TextureHandle		mRoughnessMapHandle;

	TextureHandle		mOcculusionMapHandle;
};

struct ModelHandle;

struct ModelDesc {
	vector<MeshHandle>		mHandles;
	vector<MaterialDesc>	mMaterials;
	bool operator==(const ModelHandle& otr)const;
	uid hash() const { return mHandles[0].mVBH.hash(); }
};

// one mesh handle must have one material handle
struct ModelHandle {
	ModelHandle() = default;
	ModelHandle(ModelDesc&& desc) :mHandles(move(desc.mHandles)) {}
	vector<MeshHandle>		mHandles;
	vector<MaterialHandle>	mMaterials;
	bool operator==(const ModelHandle& otr)const {
		return otr.mHandles == mHandles;
	}

	uid hash() const { return mHandles[0].mVBH.hash(); }
};
inline bool ModelDesc::operator==(const ModelHandle& otr)const {
	return otr.mHandles == mHandles;
}

template<>
struct std::hash<ModelHandle> {
	size_t operator()(const ModelHandle& hd) {
		return hd.hash();
	}
};