#include "stbi/stb_image.h"
#include "stbi/stb_image_resize.h"
#include "../ui/font.h"
#include "scene_builder.h"
#include "assimp/Importer.hpp"        //assimp库头文件
#include "assimp/Exporter.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "model_importer.h"
#include "resource/resource_handle.h"

//void tralMesh(aiMesh* mesh, const aiScene* scene) {
//	debug << "Mesh at 0x" << mesh << " has: " << endl
//		<< mesh->mNumVertices << " vertices;" << endl
//		<< mesh->mNumBones << " bones: " << endl;
//	for (int i = 0; i < mesh->mNumBones; ++i) {
//		debug << "Bone " << i << " name: " << mesh->mBones[i]->mName.C_Str() << endl;
//		debug << "Weights: " << mesh->mBones[i]->mNumWeights << endl;
//		debug << "Offset Matrix:\n" << *(mat4*)&mesh->mBones[i]->mOffsetMatrix << endl;
//	}
//	debug << endl;
//}
//
//void traverseScene(aiNode* node, const aiScene* scene, int lv, int its) {
//	debug << "________________________________________________________\n";
//	debug << "Node " << node->mName.C_Str() << " at layer: " << lv
//		<< ", " << "items: " << its << ", has " << node->mNumChildren << " children" << endl;
//	if (node->mMetaData) {
//		debug << endl << "Node has " << node->mMetaData->mNumProperties << " meta data :" << endl;
//		for (int i = 0; i < node->mMetaData->mNumProperties; ++i) {
//			debug << "Key: " << node->mMetaData->mKeys[i].C_Str() << ",      Values: " << (const char*)node->mMetaData->mValues[i].mData << endl;
//		}
//		debug << endl;
//	}
//	else debug << endl << "Node has no meta data" << endl;
//
//	debug << "Node has " << node->mNumMeshes << " meshes :" << endl;
//	for (unsigned int i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		tralMesh(mesh, scene);
//	}
//	debug << endl;
//
//	debug << "________________________________________________________\n|\n|\n|\n|\n|";
//	for (unsigned int i = 0; i < node->mNumChildren; i++)
//	{
//		traverseScene(node->mChildren[i], scene, lv + 1, i);
//	}
//}
//


void getTextureFile(string& name, aiMaterial* mat, TextureType tex_type) {
	int end = mat->GetTextureCount(cast(aiTextureType, tex_type));
	assert(end == 1);
	aiString str;
	mat->GetTexture(cast(aiTextureType, tex_type), 0, &str);
	name = str.C_Str();
}


void processMesh(ModelHandle& m, aiMesh* mesh, const aiScene* scene, map<string, int>& bone_id, ll mask)
{
	vector<vertex> vertices; vector<uint> indices; vector<Texture*> textures;


	//导入网格
	if (mask & LoadMeshes) {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex vertex;
			auto& v = mesh->mVertices[i];
			vertex.mPosition = vec3(v.x, v.y, v.z);
			if (mesh->HasNormals()) {
				v = mesh->mNormals[i];
				vertex.mNormal = { v.x,v.y,v.z };
			}
			if (mesh->mTextureCoords[0]) {
				vertex.mTexCoord = vec2(mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y);
				if (mesh->HasTangentsAndBitangents()) {
					vertex.mTangent = vec3(mesh->mTangents[i].x,
						mesh->mTangents[i].y,
						mesh->mTangents[i].z);
					vertex.mBitangent = vec3(mesh->mBitangents[i].x,
						mesh->mBitangents[i].y,
						mesh->mBitangents[i].z);
				}
			}
			vertices.push_back(vertex);
		}
		if (mesh->HasBones()) {
			for (int j = 0; j < mesh->mNumBones; ++j) {
				auto& bone = mesh->mBones[j];
				string name = string(bone->mName.C_Str(), bone->mName.length);
				name = Encoder::getGBK(name);;
				if (bone_id.find(name) != bone_id.end()) {
					int b_id = bone_id[name];

					//m.mSkeleton[b_id].mOffsetTransform = (*(mat4*)&bone->mOffsetMatrix).t();

					for (int i = 0; i < mesh->mBones[j]->mNumWeights; ++i) {
						int id = mesh->mBones[j]->mWeights[i].mVertexId;
						for (int l = 0; l < 4; ++l) {
							if (vertices[id].mBoneWeights[l] == 0.0f) {
								vertices[id].mBoneWeights[l] = mesh->mBones[j]->mWeights[i].mWeight;
								vertices[id].mBoneIds[l] = b_id;
								break;
							}
							//ASSERT(l != 3);
						}
					}
					//ASSERT(bone_id.find(name) != bone_id.end());
				}
				//else __debugbreak();
			}
			for (int i = 0; i < vertices.size(); ++i) {
				vertices[i].mBoneWeights = vertices[i].mBoneWeights.weightlize();
			}
		}
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
			ASSERT(face.mNumIndices == 3);
		}
	}
	MaterialDesc desc;
	map<string, TextureHandle> ma;

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	bool load_from_file = mask & LoadTextures;

	aiString str;

	material->GetTexture(cast(aiTextureType, texture_diffuse), 0, &str);
	desc.mDiffuseMapFile = Encoder::getGBK(str.C_Str());
	material->GetTexture(cast(aiTextureType, texture_specular), 0, &str);
	desc.mSpecularMapFile = Encoder::getGBK(str.C_Str());
	material->GetTexture(cast(aiTextureType, texture_normal), 0, &str);

	desc.mNormalMapFile = Encoder::getGBK(str.C_Str());
	material->GetTexture(cast(aiTextureType, texture_metalness), 0, &str);
	desc.mMetallicMapFile = Encoder::getGBK(str.C_Str());
	material->GetTexture(cast(aiTextureType, texture_diffuse_roughness), 0, &str);
	desc.mRoughnessMapFile = Encoder::getGBK(str.C_Str());
	material->GetTexture(cast(aiTextureType, texture_base_color), 0, &str);
	desc.mBaseColorFile = Encoder::getGBK(str.C_Str());
	material->GetTexture(cast(aiTextureType, texture_base_color), 0, &str);
	desc.mBaseColorFile = Encoder::getGBK(str.C_Str());

	m.mMeshHandles.push_back(SceneBuilder::buildMesh(vertices, indices));
	m.mMeshHandles.back().mMTH = SceneBuilder::loadMaterial(desc);
}

void processNode(ModelHandle& m, aiNode* node, const aiScene* scene, map<string, int>& bone_id, ll mask)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(m, mesh, scene, bone_id, mask);
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(m, node->mChildren[i], scene, bone_id, mask);
	}
}
//
//bool hasBone(const aiScene* scene, aiNode* no) {
//	if (!scene->HasMeshes())return true;
//	for (int i = 0; i < no->mNumMeshes; ++i) {
//		if (scene->mMeshes[no->mMeshes[i]]->HasBones())return true;
//	}
//	for (int i = 0; i < no->mNumChildren; ++i) {
//		if (hasBone(scene, no->mChildren[i]))return true;
//	}
//	return false;
//}
//
//void processJoint(SkeletonObject& m, aiNode* node, const aiScene* scene, map<string, int>& bone_id)
//{
//	queue<aiNode*> q; q.push(node);
//	queue<int> father; father.push(-1);
//	int idx = 0;
//	Joint* jos = new Joint[500]; bool first = true;
//	for (int i = 0; i < 500; ++i) {
//		jos[i].mCurTransform = mat4(1.0);
//	}
//	aiNode* no;
//	while (!q.empty()) {
//		no = q.front(); q.pop();
//		auto& jo = jos[idx];
//		string name = string(no->mName.C_Str(), no->mName.length);
//		while (name[0] == '<' || name.find('$') < 1000) {
//			jo.mCurTransform = jo.mCurTransform * (*(mat4*)&no->mTransformation).t();
//			no = no->mChildren[0]; name = no->mName.C_Str();
//		}
//		name = Encoder::getGBK(name);
//		//if (bone_id.find(name) != bone_id.end()) __debugbreak();//debug("failed");//
//		bone_id.insert({ name,bone_id.size() });
//		jo.mName = name;
//		jo.mParentId = father.front(); father.pop();
//		/*if (jo.mParentId != -1)
//			jo.transform = jos[jo.mParentId].transform * jo.cur * (*(mat4*)&no->mTransformation).t();
//		else jo.transform = jo.cur * (*(mat4*)&no->mTransformation).t();*/
//
//		for (int i = 0; i < no->mNumChildren; ++i) {
//			q.push(no->mChildren[i]); father.push(idx);
//		}
//		++idx;
//	}
//	m.mSkeleton = Skeleton(jos, idx);
//	m.mNumBones = idx;
//	m.mPose = Pose(OffsetPose, idx);
//	delete[] jos;
//}
//

Importer::Importer() :hand(0), imp(new Assimp::Importer) {}

bool Importer::Import(ModelHandle& m, const string& path, ll mask) {
	if (hand)delete (aiScene*)hand;
	//if (imp)((Assimp::Importer*)imp)->FreeScene();
	//m.clear();
	Assimp::Importer* importer = (Assimp::Importer*)imp;
	const aiScene* scene = importer->ReadFile(path, mask);
	hand = (void*)scene;
	if (!scene || !scene->mRootNode) {
		debug << "ERROR::ASSIMP:: " << importer->GetErrorString() << endl;
		return false;
	}
	map<string, int> mBoneIdMap;
	//m.mDirectory = path.substr(0, path.find_last_of('/'));
	//m.mName = path.substr(path.find_last_of('/') + 1);
	//m.mName = Encoder::getGBK(m.mName);
	//if (::hasBone(scene, scene->mRootNode) && (mask & LoadAnimations)) {
	//	//最后一个节点是骨骼
	//	processJoint(m, scene->mRootNode->mChildren[scene->mRootNode->mNumChildren - 1], scene, m.mBoneIdMap);
	//}
	//else m.mSkeleton = Skeleton(0), m.mNumBones = 0;

	processNode(m, scene->mRootNode, scene, mBoneIdMap, mask);
	//if (scene->HasAnimations() && (mask & LoadAnimations)) {
	//	for (int i = 0; i < scene->mNumAnimations; ++i) {
	//		Animation anim;
	//		auto& an = scene->mAnimations[i];
	//		anim.mNumFrames = an->mChannels[0]->mNumPositionKeys;
	//		anim.mFps = an->mTicksPerSecond;
	//		anim.mDuring = an->mDuration;
	//		anim.mName = an->mName.C_Str();
	//		anim.mChannels.resize(an->mNumChannels);
	//		int k = 0;
	//		for (int l = 0; l < an->mNumChannels; ++l) {
	//			auto& n = an->mChannels[l]->mNodeName;
	//			string s(n.C_Str(), n.C_Str() + n.length);
	//			size_t i = s.find('$');
	//			if (i < s.length()) {
	//				i = s.find_first_of('$') - 1;
	//				s = s.substr(0, i);
	//			}
	//			if (m.mBoneIdMap.size() >= 5)
	//				k = m.mBoneIdMap[s];
	//			anim.mChannels[l].mName = s;
	//			anim.mChannels[l].mBoneId = k;
	//			int num = an->mChannels[l]->mNumPositionKeys;
	//			for (int j = 0; j < num; ++j) {
	//				auto& key = an->mChannels[l]->mPositionKeys[j];
	//				anim.mChannels[l].mPositions.push_back({ *(vec3*)&key.mValue, (float)key.mTime });
	//			}
	//			num = an->mChannels[l]->mNumRotationKeys;
	//			for (int j = 0; j < num; ++j) {
	//				auto& key = an->mChannels[l]->mRotationKeys[j];
	//				auto& q = key.mValue;
	//				anim.mChannels[l].mQuaternions.push_back({ {q.x,q.y,q.z,q.w},(float)key.mTime });
	//			}
	//			num = an->mChannels[l]->mNumScalingKeys;
	//			for (int j = 0; j < num; ++j) {
	//				auto& key = an->mChannels[l]->mScalingKeys[j];
	//				anim.mChannels[l].mScales.push_back({ (key.mValue.x + key.mValue.y + key.mValue.z) / 3,(float)key.mTime });
	//			}
	//			if (m.mBoneIdMap.size() < 5)
	//				++k;
	//		}
	//		anim.mNumBones = m.mNumBones;
	//		anim.genID();
	//		m.pushAnims(anim);
	//	}
	//}
	//if (m.mNumBones > 0) {
	//	auto& jos = m.mSkeleton;
	//	for (int i = 0; i < m.mNumBones; ++i) {
	//		auto& jo = jos[i];
	//		if (i > 0) {
	//			if (jo.mName.find("4") != string::npos || jo.mName.find("End") != string::npos) {
	//				jos[i].mLocalTransform = jos[jos[i].mParentId].mLocalTransform; jos[i].mIsGood = false;
	//			}
	//			else jos[i].mLocalTransform = jos[jos[i].mParentId].mOffsetTransform * jos[i].mOffsetTransform.inv();
	//		}
	//		else jos[i].mLocalTransform = jos[i].mOffsetTransform.inv();
	//	}
	//}
	return true;
}
//bool Importer::Export(const string& filePath, ll mask, CodeType type) {
//	Assimp::Exporter exp;
//	return !exp.Export((aiScene*)hand, filePath.substr(filePath.find_last_of('.') + 1), filePath, mask);
//}
//
//aiMesh* makeMesh(const SkeletonObject& m, const int meshIdx, bool tran, CodeType type) {
//	aiMesh* pMesh = new aiMesh;
//	auto& vv = m.mMeshes[meshIdx].mVertices; auto& id = m.mMeshes[meshIdx].mIndices;
//	pMesh->mNumVertices = vv.size();
//	pMesh->mNumFaces = id.size() / 3;
//	pMesh->mFaces = new aiFace[pMesh->mNumFaces];
//	pMesh->mVertices = new aiVector3D[pMesh->mNumVertices];
//	pMesh->mNormals = new aiVector3D[pMesh->mNumVertices];
//	pMesh->mTextureCoords[0] = new aiVector3D[pMesh->mNumVertices];
//	pMesh->mNumUVComponents[0] = 2;
//
//	const int numIndices = 3; // triangular face
//	for (unsigned int index = 0; index < id.size(); index += 3) {
//		unsigned int* indices = new unsigned int[numIndices];
//		indices[0] = id[index]; indices[1] = id[index + 1]; indices[2] = id[index + 2];
//		pMesh->mFaces[index / 3].mNumIndices = numIndices;
//		pMesh->mFaces[index / 3].mIndices = indices;
//	}
//
//	for (int index = 0; index < vv.size(); index++) {
//		auto& v = vv[index];
//		pMesh->mVertices[index].Set(v.mPosition[0], v.mPosition[1], v.mPosition[2]);
//		pMesh->mNormals[index].Set(v.mNormal[0], v.mNormal[1], v.mNormal[2]);
//		pMesh->mTextureCoords[0][index].x = v.mTexCoord[0];
//		pMesh->mTextureCoords[0][index].y = v.mTexCoord[1];
//	}
//
//	if (m.hasBone()) {
//		map<int, vector<aiVertexWeight>> bone_vertex_map;
//		auto& bm = bone_vertex_map;
//		for (int index = 0; index < vv.size(); index++) {
//			auto& v = vv[index];
//			if (v.mBoneWeights[0] > 0.0000001f)bm[v.mBoneIds[0]].push_back({ (uint)index,v.mBoneWeights[0] });
//			if (v.mBoneWeights[1] > 0.0000001f)bm[v.mBoneIds[1]].push_back({ (uint)index,v.mBoneWeights[1] });
//			if (v.mBoneWeights[2] > 0.0000001f)bm[v.mBoneIds[2]].push_back({ (uint)index,v.mBoneWeights[2] });
//			if (v.mBoneWeights[3] > 0.0000001f)bm[v.mBoneIds[3]].push_back({ (uint)index,v.mBoneWeights[3] });
//		}
//
//		auto bone_ptr_ptr = new aiBone * [m.mNumBones];
//		pMesh->mNumBones = m.mNumBones;
//		pMesh->mBones = bone_ptr_ptr;
//		string name;
//		for (auto ii = 0; ii < m.mNumBones; ++ii) {
//			auto pBone = new aiBone;
//			const auto& pmxBone = m.mSkeleton[ii];
//			name = pmxBone.mName;
//			if (tran)name = Encoder::convert(gb2312, type, name);
//			pBone->mName = name;
//			auto it = bone_vertex_map.find(ii);
//			if (it != bone_vertex_map.end()) {
//				pBone->mNumWeights = static_cast<unsigned int>(it->second.size());
//				pBone->mWeights = new aiVertexWeight[pBone->mNumWeights];
//				for (unsigned int j = 0; j < pBone->mNumWeights; j++) {
//					pBone->mWeights[j] = it->second[j];
//				}
//			}
//			bone_ptr_ptr[ii] = pBone;
//		}
//	}
//	else pMesh->mNumBones = 0;
//
//	return pMesh;
//}
//
//aiMaterial* makeMaterial(const SkeletonObject& m, int texIdx, bool tran, CodeType tp) {
//	aiMaterial* mat = new aiMaterial();
//	auto& tex = m.mTextures[texIdx];
//	string name = tex.mName.substr(tex.mName.find_last_of('/') + 1);
//	if (tran)name = Encoder::convert(gb2312, tp, name);
//	aiString Tname(name);
//	mat->AddProperty(&Tname, AI_MATKEY_NAME);
//
//	name = tex.mName; if (tran)name = Encoder::convert(gb2312, tp, name);
//	aiString texture_path(name);
//	mat->AddProperty(&texture_path, AI_MATKEY_TEXTURE(tex.mType, 0));
//
//	//aiColor3D diffuse(0.8, 0.8, 0.8);
//	//mat->AddProperty(&diffuse, 1, AI_MATKEY_COLOR_DIFFUSE);
//	//aiColor3D specular(0.8, 0.8, 0.8);
//	//mat->AddProperty(&specular, 1, AI_MATKEY_COLOR_SPECULAR);
//	//aiColor3D ambient(0.2, 0.2, 0.2);
//	//mat->AddProperty(&ambient, 1, AI_MATKEY_COLOR_AMBIENT);
//
//	//float opacity = 1.0;
//	//mat->AddProperty(&opacity, 1, AI_MATKEY_OPACITY);
//	//float shininess = 1.0;
//	//mat->AddProperty(&shininess, 1, AI_MATKEY_SHININESS_STRENGTH);
//
//	int mapping_uvwsrc = 0;
//	mat->AddProperty(&mapping_uvwsrc, 1, AI_MATKEY_UVWSRC(aiTextureType_DIFFUSE, 0));
//
//	return mat;
//}
//
//bool Importer::Export(const SkeletonObject& m, const string& filePath, ll mask, CodeType type) {
//	aiScene* sn = new aiScene;
//	string name = m.mDirectory + '/' + m.mName; bool tran = (type != gb2312);
//	if (tran)name = Encoder::convert(gb2312, type, name);
//	sn->mName = name; sn->mNumCameras = 0; sn->mNumLights = 0; sn->mNumTextures = 0;
//	sn->mNumMeshes = m.mMeshes.size(); sn->mNumAnimations = m.mAnims.size();
//
//	name = m.mName;
//	if (tran)name = Encoder::convert(gb2312, type, name);
//	aiNode* nd = new aiNode; nd->mName.Set(name);
//	sn->mRootNode = nd;
//
//	nd = new aiNode;
//	sn->mRootNode->addChildren(1, &nd);
//	nd->mNumMeshes = m.mMeshes.size();
//	nd->mMeshes = new uint[nd->mNumMeshes];
//	sn->mMeshes = new aiMesh * [sn->mNumMeshes];
//
//	for (uint i = 0; i < nd->mNumMeshes; ++i) { nd->mMeshes[i] = i; }
//	for (uint i = 0; i < sn->mNumMeshes; i++) {
//		auto& mes = m.mMeshes[i];
//		sn->mMeshes[i] = makeMesh(m, i, tran, type);
//
//		name = mes.mName;
//		if (tran)name = Encoder::convert(gb2312, type, name);
//		sn->mMeshes[i]->mName = name;
//
//		if (mes.mTextures.size() > 0) {
//			sn->mMeshes[i]->mMaterialIndex = mes.mTextures[0] - &m.mTextures[0];
//		}
//		else sn->mMeshes[i]->mMaterialIndex = 0;
//	}
//
//	sn->mNumMaterials = m.mTextures.size();
//	sn->mMaterials = new aiMaterial * [sn->mNumMaterials];
//	for (unsigned int i = 0; i < sn->mNumMaterials; i++) {
//		sn->mMaterials[i] = makeMaterial(m, i, tran, type);
//	}
//
//	if (m.hasBone()) {
//		std::unique_ptr<aiNode* []> ppNode(new aiNode * [m.mNumBones]);
//		for (int i = 0; i < m.mNumBones; i++) {
//			ppNode[i] = new aiNode(m.mSkeleton[i].mName);
//			ppNode[i]->mTransformation = *(aiMatrix4x4*)&(m.mSkeleton[i].mTransform);
//		}
//		for (int i = 0; i < m.mNumBones; i++) {
//			const Joint& bone = m.mSkeleton[i];
//			if (bone.mParentId < 0) sn->mRootNode->addChildren(1, ppNode.get() + i);
//			else ppNode[bone.mParentId]->addChildren(1, ppNode.get() + i);
//		}
//	}
//
//	Assimp::Exporter exp;
//	bool ret = true;
//	if (exp.Export(sn, filePath.substr(filePath.find_last_of('.') + 1), filePath, mask)) {
//		debug(exp.GetErrorString());
//		ret = false;
//	}
//	delete sn;
//	return ret;
//}
//Importer::~Importer() {
//	if (imp)delete (Assimp::Importer*)imp, imp = 0;
//}