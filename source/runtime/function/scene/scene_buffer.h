#pragma once
#include"scene_memory.h"
#include"../base/render_base.h"
#include"../base/camera.h"

class SceneBuffer {
public:
	static VertexBufferHandle genVertexBuffer(const vector<vertex>& vertices) {
		auto mem = alloc<VertexMemory>(vertices.size() * sizeof(vertex));
		memcpy(mem->mData, vertices.data(), mem->mSize);
		mem->format = Vertex_PNTTB;
		mem->setup();
		return VertexBufferHandle{ mem };
	}
	static IndexBufferHandle genIndexBuffer(const vector<uint>& vertices) {
		auto mem = alloc<IndexMemory>(vertices.size() * sizeof(uint));
		memcpy(mem->mData, vertices.data(), mem->mSize);
		mem->setup();
		return IndexBufferHandle{ mem };
	}

	static TextureHandle genTextureBuffer(const Image& img) {
		auto mem = alloc<TextureMemory>(img.w * img.h * img.mNumChannels);
		memcpy(mem->mData, img.data(), mem->mSize);
		mem->mTarget = GL_TEXTURE_2D;
		mem->setupFromImage(img);
		return TextureHandle{ mem };
	}


	template<class T>
	static T* alloc(size_t size) {
		static_assert(is_base_of<SceneMemory, T>::value);
		return new T{ size,new char[size] };
	}

	static void destory(ResourceHandle hand) {
		SceneMemory* mem = (SceneMemory*)hand.mHandle;
		delete[] mem->mData; mem->mData = nullptr; mem->mSize = 0;
		delete mem;
	}
	static const SceneMemory* memory(ResourceHandle hand) {
		return (SceneMemory*)hand.mHandle;
	}
	static bool isValid(ResourceHandle hand) {
		return hand.mHandle != INVAILID_HANDLE;
	}

};