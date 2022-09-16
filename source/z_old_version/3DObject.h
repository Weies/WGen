#pragma once
#include"render_mesh.h"


class Cube :public StaticObject {
public:
	Cube() {
		float data[] = {
			// positions          // normals           //texCoords
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0, 1.0,//back
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0, 0.0,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0, 0.0,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0, 1.0,

			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0, 1.0,//left
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0, 0.0,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0, 0.0,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0, 1.0,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   0.0, 1.0,//right
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   0.0, 0.0,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   1.0, 0.0,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   1.0, 1.0,

			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   0.0, 1.0,//front
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   0.0, 0.0,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0, 0.0,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0, 1.0,

			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   0.0, 1.0,//top
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0, 0.0,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   1.0, 0.0,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   1.0, 1.0,

			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0, 1.0,//bottom
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   0.0, 0.0,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   1.0, 0.0,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   1.0, 1.0,
		};

		uint ids[] = {
			0,2,3,    1,2,0
		};

		float* p = data;
		MeshPatch m;
		for (int i = 0; i < 6; ++i, p += 32) {
			m.parseData(p, 4, ids, 6);
			pushMesh(m);
		}
		mTexCoordType = TEXTURE_COORD;
		initBody();
	}
private:
	void initBody() {
		mColliBody.initBody(Colli_Cube);
		mColliBody.body<cube>() = cube(vec3(-0.5, 0.5, -0.5), vec3(0.5, 0.5, -0.5), vec3(-0.5, 0.5, 0.5), vec3(-0.5, -0.5, -0.5));
	}
};

class Tetrahedron :public StaticObject {
public:
	Tetrahedron() {
		float sqrt3 = sqrt(3); float sqrt6 = sqrt(6); float sqrt2 = sqrt(2);
		float data[] = {
			0			,		 	 0,		 sqrt3 / 2,		0			,		 	 0,		 sqrt3 / 2,		0.5 ,0.5,
			sqrt6 / 6	,	-sqrt2 / 2,		-sqrt3 / 6,		sqrt6 / 6	,	-sqrt2 / 2,		-sqrt3 / 6,		0   ,0,
		   -sqrt6 / 3	,			 0,		-sqrt3 / 6,		sqrt6 / 3	,			 0,		-sqrt3 / 6,		0   ,1,

			0			,		 	 0,		 sqrt3 / 2,		0			,		 	 0,		 sqrt3 / 2,		0.5 ,0.5,
			sqrt6 / 6 	,	 sqrt2 / 2,		-sqrt3 / 6,		sqrt6 / 6	,	 sqrt2 / 2,		-sqrt3 / 6,		0   ,0,
		   -sqrt6 / 3 	,			 0,		-sqrt3 / 6,		sqrt6 / 3	,			 0,		-sqrt3 / 6,		0   ,1,

			0			,		 	 0,		 sqrt3 / 2,		0			,		 	 0,		 sqrt3 / 2,		0.5 ,0.5,
		   -sqrt6 / 3	,			 0,		-sqrt3 / 6,		sqrt6 / 3	,			 0,		-sqrt3 / 6,		0   ,0,
			sqrt6 / 6	,	-sqrt2 / 2,		-sqrt3 / 6,		sqrt6 / 6	,	-sqrt2 / 2,		-sqrt3 / 6,		0   ,1,

			sqrt6 / 6	,	-sqrt2 / 2,		-sqrt3 / 6,		sqrt6 / 6	,	-sqrt2 / 2,		-sqrt3 / 6,		0.5 ,0.5,
		   -sqrt6 / 3	,			 0,		-sqrt3 / 6,		sqrt6 / 3	,			 0,		-sqrt3 / 6,		0   ,0,
			sqrt6 / 6	,	 sqrt2 / 2,		-sqrt3 / 6,		sqrt6 / 6	,	 sqrt2 / 2,		-sqrt3 / 6,		0   ,1,
		};

		uint ids[] = {
			0,1,2
		};
		float* p = data;
		MeshPatch m;
		for (int i = 0; i < 4; ++i, p += 24) {
			m.parseData(p, 4, ids, 6);
			pushMesh(m);
		}
	}
};

class Sphere : public StaticObject {
public:
	Sphere(int seg = 36, bool flip_normal = false) {
		MeshPatch m;
		float a = 0; float x = 0;
		const float ax = 1.0f / seg; const float ay = 2.0f / seg;
		const float aa = 2 * PI / seg;
		for (int i = 0; i <= seg; ++i) {
			float b = -PI * 0.5; float y = 0;
			for (int j = 0; j <= seg / 2; ++j) {
				vertex v(vec3(cos(b) * sin(a), sin(b), cos(b) * cos(a)));
				v.mTexCoord = { x,y };
				v.mNormal = v.mPosition;
				m.mVertices.push_back(v);
				b += aa; y += ay;
			}
			a += aa; x += ax;
		}
		auto& id = m.mIndices; int segg = seg / 2 + 1;
		for (int i = 1; i <= seg; ++i) {
			for (int j = 1; j <= seg / 2; ++j) {
				id.push_back((i - 1) * segg + j - 1);
				id.push_back(i * segg + j - 1);
				id.push_back(i * segg + j);

				id.push_back((i - 1) * segg + j - 1);
				id.push_back(i * segg + j);
				id.push_back((i - 1) * segg + j);
			}
		}
		m.setup();
		pushMesh(m);
		mTexCoordType = TEXTURE_COORD;
		initBody();
	}
	void setRadius(float r) {

	}
private:
	void initBody() {
		mColliBody.initBody(Colli_Ball);
		mColliBody.body<ball>() = ball(vec3(0.0f), 1);
	}
};

class SkyBox :public StaticObject {
public:
	SkyBox(const string str[6], const string directory = "asset/skybox") {
		float arr[] = {
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};
		MeshPatch m;
		m.parseArray(arr, 36);
		Texture tex(GL_TEXTURE_CUBE_MAP);
		tex.loadCubeMap(str, directory + '/');
		addTexture(tex, -1);
		m.addTexture(mTextures.back());	text = tex;
		pushMesh(m);
		scale(1000);
		this->mDirectory = directory; this->mName = str[0];
	}
	SkyBox() :SkyBox(texts) {}
	Texture text;
	string texts[6] = {
			"right.jpg" , "left.jpg",
			"top.jpg"   , "bottom.jpg",
			"front.jpg" , "back.jpg"
	};
};

class SkySphere :public StaticObject {
public:
	SkySphere(int seg = 36, bool flip_normal = false) {
		int sq = 2 + seg * (seg / 2 - 1);
		MeshPatch m;
		m.mVertices.push_back(vertex(vec3(0, 0, 1)));
		for (float a = PI / (seg / 2); a < PI - 0.001; a += PI / (seg / 2))
		{
			for (float b = 0; b < 2 * PI - 0.001; b += PI / (seg / 2))
			{
				m.mVertices.push_back(vertex(vec3(sin(a) * cos(b), sin(a) * sin(b), cos(a))));
			}
		}
		m.mVertices.push_back(vertex(vec3(0, 0, -1)));

		int last = m.mVertices.size() * 2 - 1;
		m.mIndices.resize(3 * seg * seg);
		int idx = -1;
		for (int i = 0; i < seg; i++) {
			m.createFace(0, i + 1, 1 + (i + 1) % seg, m.mFaces, m.mEdges, m.mVertexEdgeMap, m.mVertices);
			m.mIndices[++idx] = 0;
			m.mIndices[++idx] = i + 1;
			m.mIndices[++idx] = 1 + (i + 1) % seg;
			m.createFace(sq - 1, sq - seg + (i + 1) % seg - 1, sq - seg + i - 1, m.mFaces, m.mEdges, m.mVertexEdgeMap, m.mVertices);
			m.mIndices[++idx] = sq - 1;
			m.mIndices[++idx] = sq - seg + (i + 1) % seg - 1;
			m.mIndices[++idx] = sq - seg + i - 1;
		}

		for (int i = 0; i < seg / 2 - 2; i++) {
			for (int j = 1; j <= seg; j++) {
				int o, p, q;
				o = i * seg + j;
				p = i * seg + seg + j;
				q = (i * seg + seg) + 1 + (j) % seg;
				m.mIndices[++idx] = o;
				m.mIndices[++idx] = p;
				m.mIndices[++idx] = q;
				m.createFace(o, p, q, m.mFaces, m.mEdges, m.mVertexEdgeMap, m.mVertices);

				o = i * seg + j;
				p = (i * seg + seg) + 1 + (j) % seg;
				q = i * seg + 1 + j % seg;
				m.mIndices[++idx] = o;
				m.mIndices[++idx] = p;
				m.mIndices[++idx] = q;
				m.createFace(o, p, q, m.mFaces, m.mEdges, m.mVertexEdgeMap, m.mVertices);
			}
		}
		m.calcuNormal(flip_normal);
		scale(6000);
	}

};

//inline void markMesh(const Basic3DObject& m , const CameraBlock& b , bool f , bool v , bool se) {
//	font.setColor(WHITE);
//
//	if (v) {
//		for (int i = 0; i < m..mVertices.size(); ++i) {
//			pt p = m..mVertices[i].p;
//			vec4 v = b.mPVTransform * m.mModelTransform * vec4(p.x , p.y , p.z , 1.0f);
//
//			if (gm::dot(b.mCameraPosition - vec3(m.mModelTransform * vec4(p.x , p.y , p.z , 1.0)) , m..mVertices[i].normal) > 0 && v.z > 0) {
//				v.x /= v.w; v.y /= v.w;
//				font.pushString((1 + v.x) * win_w / 2 , (1 + v.y) / 2 * win_h , "v:" + toString(i));
//			}
//		}
//	}
//	if (f || se) {
//		for (int i = 0; i < m.mFaces.size(); ++i) {
//			us e = m.mFaces[i].e;
//			pt p1 = m..mVertices[m.mEdges[e].vert].p;
//			e = m.mEdges[e].next;
//			pt p2 = m..mVertices[m.mEdges[e].vert].p;
//			e = m.mEdges[e].next;
//			pt p3 = m..mVertices[m.mEdges[e].vert].p;
//			pt p = (p1 + p2 + p3) * 0.333333;
//			vec4 v = b.mPVTransform * m.mModelTransform * vec4(p.x , p.y , p.z , 1.0f);
//			if (gm::dot(b.mCameraPosition - vec3(m.mModelTransform * vec4(p.x , p.y , p.z , 1.0)) , m.mFaces[i].normal) > 0 && v.z > 0) {
//				v.x /= v.w; v.y /= v.w;
//				if (f) {
//					font.setColor(SKYBLUE);
//					font.pushString((1 + v.x) * win_w / 2 , (1 + v.y) / 2 * win_h , "f:" + toString(i));
//				}
//
//				if (se) {
//					font.setColor(PINK);
//					pt center = p;
//					p = (p1 + p2) * 0.5;
//					p += (center - p) * 0.3f;
//					vec4 ve = b.mPVTransform * m.mModelTransform * vec4(p.x , p.y , p.z , 1.0f);
//					ve.x /= ve.w; ve.y /= ve.w;
//					e = m.mFaces[i].e;
//					font.pushString((1 + ve.x) * win_w / 2 , (1 + ve.y) / 2 * win_h , toString(e) + "," + toString(m.mEdges[e].opp) + "," + toString(m.mEdges[e].next));
//					p = (p3 + p2) * 0.5;
//					p += (center - p) * 0.3f;
//					ve = b.mPVTransform * m.mModelTransform * vec4(p.x , p.y , p.z , 1.0f);
//					ve.x /= ve.w; ve.y /= ve.w;
//					e = m.mEdges[e].next;
//					font.pushString((1 + ve.x) * win_w / 2 , (1 + ve.y) / 2 * win_h , toString(e) + "," + toString(m.mEdges[e].opp) + "," + toString(m.mEdges[e].next));
//					p = (p1 + p3) * 0.5;
//					p += (center - p) * 0.3f;
//					ve = b.mPVTransform * m.mModelTransform * vec4(p.x , p.y , p.z , 1.0f);
//					ve.x /= ve.w; ve.y /= ve.w;
//					e = m.mEdges[e].next;
//					font.pushString((1 + ve.x) * win_w / 2 , (1 + ve.y) / 2 * win_h , toString(e) + "," + toString(m.mEdges[e].opp) + "," + toString(m.mEdges[e].next));
//				}
//			}
//		}
//	}
//}