#pragma once
#include"mesh.h"
#include"../base/encoder.h"

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
	// ����ʱWindowsĬ��ʹ��GBK���룬���Ի��Զ����ļ�����ΪGBK
	bool Import(SkeletalMesh& m, const string& filePath, ll mask = Import_Mask);
	bool Import(const string& filePath, SkeletalMesh& m, bool load_texture = true,
		bool load_meshes = true, bool load_anims = true, bool flip_uv = false) {
		ll mask = (Triangulate | GenNormals);
		if (load_texture)mask |= LoadTextures;
		if (flip_uv)mask |= FlipUV;
		if (load_meshes)mask |= LoadMeshes;
		if (load_anims)mask |= LoadAnimations;
		return Import(m, filePath, mask);
	}
	


	// ����ʱΪ����������Ķ�ȡ���󣬿��Ե���ָ�������ʽ
	bool Export(const string& filePath, ll mask = Export_Mask, CodeType tp = gb2312);
	//����һ��MeshModel����
	static bool Export(const SkeletalMesh& m, const string& filePath, ll mask = Export_Mask, CodeType tp = gb2312);
	~Importer();
	void* imp;
	void* hand;
};