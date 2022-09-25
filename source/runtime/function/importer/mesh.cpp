#include "mesh.h"
#include "../ui/font.h"
#include "Importer.h"

void MeshPatch::calcuNormal(bool flip_mNormal, bool sync) {
	auto& id = mIndices; auto& vt = mVertices;
	for (int i = 0; i < mVertices.size(); ++i) {
		vt[i].mNormal = vec3(0.0f);
	}
	for (int i = 0; i < mIndices.size(); i += 3) {
		vec3 norm = getNormal(vt[id[i]].mPosition, vt[id[i + 1]].mPosition, vt[id[i + 2]].mPosition);
		vt[id[i]].mNormal += norm;
		vt[id[i + 1]].mNormal += norm;
		vt[id[i + 2]].mNormal += norm;
	}
	for (int i = 0; i < mVertices.size(); ++i) {
		vt[i].mNormal = normalize(vt[i].mNormal);
		if (flip_mNormal)vt[i].mNormal *= -1;
	}
}

void Mesh::addTexture(const string& name, TextureType tp, int to_whom) {
	Texture tex(GL_TEXTURE_2D);
	tex.load(name, mDirectory);
	tex.mType = tp;
	mTextures.push_back(tex);
	if (to_whom == -1) {
		for (int i = 0; i < mMeshes.size(); ++i)
			mMeshes[i].addTexture(mTextures.back());
	}
	else if (to_whom >= mMeshes.size())mMeshes.back().addTexture(mTextures.back());
	else mMeshes[to_whom].addTexture(mTextures.back());
}

void Mesh::addTexture(const Texture& tex, int to_whom) {
	mTextures.push_back(tex);
	if (to_whom == -1) {
		for (int i = 0; i < mMeshes.size(); ++i)
			mMeshes[i].addTexture(mTextures.back());
	}
	else if (to_whom >= mMeshes.size())mMeshes.back().addTexture(mTextures.back());
	else mMeshes[to_whom].addTexture(mTextures.back());
}

mat4 Mesh::curPose[500];
