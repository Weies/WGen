#pragma once

#include"resource/res_type/data/mesh_data.h"


#define JoinIdenticalVertices		2ll
#define Triangulate					8ll
#define GenNormals					32ll
#define GenSmoothNormals			64ll
#define LimitBoneWeights			512ll
#define OptimizeMeshes				2097152ll
#define FlipUV						8388608ll
#define LoadTextures				(1ll << 33)
#define LoadMeshes					(1ll << 34)
#define LoadAnimations				(1ll << 35)

#define Import_Mask  (Triangulate | GenNormals | LoadTextures| LoadMeshes| LoadAnimations)
#define Export_Mask 0

class Importer {
public:
	Importer();
	// 导入时Windows默认使用GBK编码，所以会自动将文件导入为GBK
	bool Import(MeshData& m, const string& filePath, llong mask = Import_Mask);
	bool Import(const string& filePath, MeshData& m, bool load_texture = true,
		bool load_meshes = true, bool load_anims = true, bool flip_uv = false) {
		llong mask = (Triangulate | GenNormals);
		if (load_texture)mask |= LoadTextures;
		if (flip_uv)mask |= FlipUV;
		if (load_meshes)mask |= LoadMeshes;
		if (load_anims)mask |= LoadAnimations;
		return Import(m, filePath, mask);
	}
	

	// 导出时为了满足软件的读取需求，可以单独指定编码格式
	bool Export(const string& filePath, llong mask = Export_Mask, CodeType tp = gb2312);
	//导出一个MeshModel对象
	static bool Export(const MeshData& m, const string& filePath, llong mask = Export_Mask, CodeType tp = gb2312);
	~Importer();
	void* imp;
	void* hand;
};