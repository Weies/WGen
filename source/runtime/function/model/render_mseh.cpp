#include"render_mesh.h"
#include "function/scene/model_importer.h"

void SkeletonObject::loadModel(string const& path, bool flip, bool load_texture)
{
	clear();
	::Importer imp;
	ll mask = (Triangulate | GenNormals | LoadMeshes | LoadAnimations);
	if (flip)mask |= FlipUV;
	if (load_texture) mask |= LoadTextures;
	//imp.Import(*this, path, mask);
}

void SkeletonObject::addBones(bool mNormalize) {
	/*has_bone = true;
	if (mNormalize)mNormalizeCharacter();
	setupJoints();
	for (int i = 0; i < mMeshes.size(); ++i) {
		auto& v = mMeshes[i].mVertices;
		glBindVertexArray(mMeshes[i].mVAO);
		glBindBuffer(GL_ARRAY_BUFFER , mMeshes[i].mVBO);
		for (int j = 0; j < v.size(); ++j) {
			if (v[j].mPosition.y < 0.9625) {
				if (v[j].mPosition.x > 0) {
					float l1 = 1 / (jos[15].mPositionos - v[j].mPosition).len();
					float l2 = 1 / (jos[16].mPositionos - v[j].mPosition).len();
					float l3 = 1 / (jos[17].mPositionos - v[j].mPosition).len();
					ivec3 tp;
					if (l1 > l2) {
						if (l1 > l3) {
							if (l2 > l3)
								tp = { 15,16,17 };
							else tp = { 15,17,16 };
						}
						else tp = { 17,15,16 };
					}
					else {
						if (l1 > l3) {
							tp = { 16,15,17 };
						}
						else {
							if (l2 > l3)
								tp = { 16,17,15 };
							else tp = { 17,16,15 };
						}
					}
					float sum = l1 + l2 + l3;
					v[j].mBoneIds[0] = tp.x; v[j].mBoneWeights[0] = 0;
					v[j].mBoneIds[1] = tp.x; v[j].mBoneWeights[1] = l1 / sum;
					v[j].mBoneIds[2] = tp.y; v[j].mBoneWeights[2] = l2 / sum;
					v[j].mBoneIds[3] = tp.z; v[j].mBoneWeights[3] = l3 / sum;
				}
				else {
					float l1 = 1 / (jos[12].mPositionos - v[j].mPosition).len();
					float l2 = 1 / (jos[13].mPositionos - v[j].mPosition).len();
					float l3 = 1 / (jos[14].mPositionos - v[j].mPosition).len();
					ivec3 tp;
					if (l1 > l2) {
						if (l1 > l3) {
							if (l2 > l3)
								tp = { 12,13,14 };
							else tp = { 12,14,13 };
						}
						else tp = { 14,12,13 };
					}
					else {
						if (l1 > l3) {
							tp = { 13,12,14 };
						}
						else {
							if (l2 > l3)
								tp = { 13,14,12 };
							else tp = { 14,13,12 };
						}
					}
					float sum = l1 + l2 + l3;
					v[j].mBoneIds[0] = tp.x; v[j].mBoneWeights[0] = 0;
					v[j].mBoneIds[1] = tp.x; v[j].mBoneWeights[1] = l1 / sum;
					v[j].mBoneIds[2] = tp.y; v[j].mBoneWeights[2] = l2 / sum;
					v[j].mBoneIds[3] = tp.z; v[j].mBoneWeights[3] = l3 / sum;
				}
			}
			else {
				priority_queue<pair<float , int> , vector<pair<float , int>> , greater<pair<float , int>>> pq;
				vec3 p = v[j].mPosition;
				float min = 10000;
				for (int k = 0; k < 18; ++k) {
					float l = (jos[k].mPositionos - p).len();
					pq.push({ l,k });
				}
				v[j].mBoneIds[0] = pq.top().second; v[j].mBoneWeights[0] = 1 / pq.top().first; pq.pop();
				v[j].mBoneIds[1] = pq.top().second; v[j].mBoneWeights[1] = 1 / pq.top().first; pq.pop();
				v[j].mBoneIds[2] = pq.top().second; v[j].mBoneWeights[2] = 1 / pq.top().first; pq.pop();
				v[j].mBoneIds[3] = pq.top().second; v[j].mBoneWeights[3] = 1 / pq.top().first;
				auto& w = v[j].mBoneWeights;
				w.x *= w.x; w.y *= w.y; w.z *= w.z; w.w *= w.w;
				w /= w.sum();
			}
		}
		glBufferData(GL_ARRAY_BUFFER , mMeshes[i].mVertices.size() * sizeof(vertex) , &mMeshes[i].mVertices[0] , GL_STATIC_DRAW);
	}*/
}

void SkeletonObject::setupJoints() {
	//	string name[18] = { "pelvis","low_spine","mid_spine","up_spine", "l_shoulder","l_elbow","l_hand" ,
	//	"r_shoulder","r_elbow","r_hand","neck","head","l_thigh","l_knee","l_ankle","r_thigh","r_knee","r_ankle" };
	//
	//#define r(d,x,y,z) rotate<float>(mat4(1.0),d,vec3(x,y,z).vec())
	//#define r(m,d) rotate<float>(m,d,vec3(1,0,0).vec())
	//#define t(m,x,y,z) translate<float>(m,vec3(x,y,z).vec())
	//#define t(x,y,z) translate<float>(mat4(1.0),vec3(x,y,z).vec())
	//	mat4 mats[18] = {
	//			t(0,0,0.9625),//0
	//			t(-0.02,0,0.1575),t(-0.02,0,0.16875),t(0.0,0.0,0.18),//1
	//			r(t(0,-0.12125,0),90),t(0,-0.03,0.2625),t(0,-0.012,0.2075),//4
	//			r(t(0,0.12125,0),-90),t(0,0.03,0.2625),t(0,0.012,0.2075),//7
	//			t(0.02,0.0,0.045),t(0.05,0.0,0.143),//10
	//			r(t(-0.045,-0.09975,0),90),r(t(0.04,-0.36,0),90),t(-0.03,0.02,0.43),//12
	//			r(t(-0.045,0.0995,0),-90),r(t(0.04,0.36,0),-90),t(-0.03,-0.02,0.43)//15
	//	};
	//	for (int i = 0; i < 18; ++i) {
	//		jos[i].cur = mats[i];
	//	}
}