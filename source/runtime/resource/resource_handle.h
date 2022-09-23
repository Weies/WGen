#pragma once
#include"basis.h"

//Handle -> Memory -> concrete data
struct ResourceHandle {
public:
	uid mHandle{ 0 };

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

struct MaterialHandle
{
	vec4				mBaseColor{ 1.0,1.0,1.0,1.0 };
	vec3				mDiffuse{ 1.0,1.0,1.0 };
	vec3				mSpecular{ 1.0,1.0,1.0 };
	float				mMetallic{ 0.5f };
	float				mRoughness{ 0.5f };
	float				mOcculusion{ 1.0f };

	TextureHandle		mBaseColorHandle{ nullptr };
	TextureHandle		mDiffuseMapHandle{ nullptr };
	TextureHandle		mSpecularMapHandle{ nullptr };
	TextureHandle		mNormalMapHandle;
	TextureHandle		mMetallicMapHandle{ nullptr };
	TextureHandle		mRoughnessMapHandle{ nullptr };
	TextureHandle		mOcculusionMapHandle{ nullptr };

	bool operator==(const MaterialHandle& otr)const {
		return otr.mBaseColorHandle == mBaseColorHandle;
	}
	uid hash() const { return mBaseColorHandle.hash(); }
};

struct MeshHandle {
	VertexBufferHandle		mVBH;
	IndexBufferHandle		mIBH;
	MaterialHandle			mMTH;
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

template<>
struct std::hash<MaterialHandle> {
	size_t operator()(const MaterialHandle& hd) {
		return hd.hash();
	}
};


struct ModelHandle;



// one mesh handle must have one material handle
struct ModelHandle
{
	vector<MeshHandle>		mMeshHandles;

	ModelHandle() = default;

	bool operator==(const ModelHandle& otr)const {
		return otr.mMeshHandles == mMeshHandles;
	}
	uid hash() const { return mMeshHandles[0].mVBH.hash(); }
};

template<>
struct std::hash<ModelHandle> {
	size_t operator()(const ModelHandle& hd) {
		return hd.hash();
	}
};
