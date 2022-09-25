//#include "triangleMesh.h"
//#include "../ui/font.h"
//#include "function/scene/model_importer.h"
//
//void MeshPatch::createFace(us a, us b, us c, vector<face>& f, vector<edge>& eg
//	, map<pa, us>& m, vector<vertex>& vt) {
//
//
//	face fa;
//	us sz = f.size();
//	fa.e = eg.size();
//	fa.mNormal = getNormal(vt[a].mPosition, vt[b].mPosition, vt[c].mPosition);
//	f.push_back(fa);
//
//	edge e(a, eg.size() + 1, sz);
//	auto it = m.find(pa(b, a));
//	if (it != m.end()) e.opp = it->second, eg[it->second].opp = eg.size();
//	m.insert({ pa(a , b) , eg.size() });
//	vt[a].out = eg.size();
//	eg.push_back(e);
//
//	e = edge(b, eg.size() + 1, sz);
//	it = m.find(pa(c, b));
//	if (it != m.end()) e.opp = it->second, eg[it->second].opp = eg.size();
//	m.insert({ pa(b , c) , eg.size() });
//	vt[b].out = eg.size();
//	eg.push_back(e);
//
//	e = edge(c, eg.size() - 2, sz);
//	it = m.find(pa(a, c));
//	if (it != m.end()) e.opp = it->second, eg[it->second].opp = eg.size();
//	m.insert({ pa(c , a) , eg.size() });
//	vt[c].out = eg.size();
//	eg.push_back(e);
//}
//
//void MeshPatch::draw(uint shader_id, int primitive) const
//{
//	int text_num[20] = {};
//	for (unsigned int i = 0; i < mTextures.size(); i++)
//	{
//		++text_num[mTextures[i]->mType];
//		string tp = mTextures[i]->mTypeStr();
//		mTextures[i]->bindToShader(shader_id, tp + itos(text_num[mTextures[i]->mType]), i + 1);
//	}
//	glUniform1iv(glGetUniformLocation(shader_id, "text_num"), 20, text_num);
//
//	glBindVertexArray(mVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
//
//	glDrawElements(primitive, mIndices.size(), GL_UNSIGNED_INT, 0);
//}
//void MeshPatch::resetData() {
//	glBindVertexArray(mVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(vertex), &mVertices[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
//
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mNormal));
//
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mTexCoord));
//
//	glEnableVertexAttribArray(3);
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mTangent));
//
//	glEnableVertexAttribArray(4);
//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mBitangent));
//
//	glEnableVertexAttribArray(5);
//	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mBoneIds));
//
//	glEnableVertexAttribArray(6);
//	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mBoneWeights));
//}
//
//void MeshPatch::setup()
//{
//	mVAO = mVBO = mEBO = 0;
//	glGenVertexArrays(1, &mVAO);
//	glGenBuffers(1, &mVBO);
//	glGenBuffers(1, &mEBO);
//	glBindVertexArray(mVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//
//	if (mVertices.size() > 0)
//		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(vertex), &mVertices[0], GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
//	if (mIndices.size() > 0)
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint), &mIndices[0], GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
//
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mNormal));
//
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mTexCoord));
//
//	glEnableVertexAttribArray(3);
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mTangent));
//
//	glEnableVertexAttribArray(4);
//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mBitangent));
//
//	//注意整形要用IPointer
//	glEnableVertexAttribArray(5);
//	glVertexAttribIPointer(5, 4, GL_UNSIGNED_INT, sizeof(vertex), (void*)offsetof(vertex, mBoneIds));
//
//	glEnableVertexAttribArray(6);
//	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mBoneWeights));
//
//	glBindVertexArray(0);
//}
//
//void MeshPatch::deg3Clean() {
//	auto& vt = mVertices;
//	vector<us> deg(vt.size()); queue<us> c;
//	for (int i = 0; i < vt.size(); ++i) {
//		us e = vt[i].out; us v = mEdges[mEdges[e].next].vert; us pv = v;
//		e = mEdges[mEdges[e].opp].next; v = mEdges[mEdges[e].next].vert;
//		int d = 1;
//		while (v != pv) {
//			e = mEdges[mEdges[e].opp].next; v = mEdges[mEdges[e].next].vert; ++d;
//		}
//		deg[i] = d;
//		if (d == 3)c.push(i);
//	}
//	vector<us> vdel(vt.size(), false); vector<us> nf;
//	while (!c.empty())
//	{
//		us v = c.front(); c.pop(); us e = vt[v].out; deg[v] = 0;
//		vdel[v] = true;
//		v = mEdges[mEdges[e].next].vert; nf.push_back(v);
//		//if (--deg[v] == 3 && !vdel[v])c.push(v);
//
//		e = mEdges[mEdges[e].opp].next;
//		v = mEdges[mEdges[e].next].vert; nf.push_back(v);
//		//if (--deg[v] == 3 && !vdel[v])c.push(v);
//
//		e = mEdges[mEdges[e].opp].next;
//		v = mEdges[mEdges[e].next].vert; nf.push_back(v);
//		//if (--deg[v] == 3 && !vdel[v])c.push(v);
//	}
//
//	map<us, us>nv; vector<vertex> ve;//顶点表
//	for (int i = 0; i < vt.size(); ++i) {
//		if (!vdel[i]) {
//			nv.insert({ i,ve.size() });
//			ve.push_back(vt[i]);
//		}
//	}
//
//	vector<edge> eg;//边表
//	vector<face> fa;//面表
//	map<pa, us> m;
//	for (int i = 0; i < mFaces.size(); ++i) {
//		us e1 = mFaces[i].e; us e2 = mEdges[e1].next; us e3 = mEdges[e2].next;
//		us v1 = mEdges[e1].vert; us v2 = mEdges[e2].vert; us v3 = mEdges[e3].vert;
//		if (!vdel[v1] && !vdel[v2] && !vdel[v3]) {
//			createFace(nv[v1], nv[v2], nv[v3], fa, eg, m, ve);
//		}
//	}
//	for (int i = 0; i < nf.size(); i += 3) {
//		if (!vdel[nf[i + 2]] && !vdel[nf[i + 1]] && !vdel[nf[i]])
//			createFace(nv[nf[i + 2]], nv[nf[i + 1]], nv[nf[i]], fa, eg, m, ve);
//	}
//	mFaces.swap(fa);
//	mEdges.swap(eg);
//	mVertexEdgeMap.swap(m);
//	vt.swap(ve);
//}
//
//void MeshPatch::makeIndices() {
//	mIndices.resize(mFaces.size() * 3); int idx = -1;
//	for (int i = 0; i < mFaces.size(); ++i) {
//		us e = mFaces[i].e;
//		mIndices[++idx] = mEdges[e].vert;
//		e = mEdges[e].next;
//		mIndices[++idx] = mEdges[e].vert;
//		e = mEdges[e].next;
//		mIndices[++idx] = mEdges[e].vert;
//	}
//}
//
//void MeshPatch::calcuNormal(bool flip_mNormal, bool sync) {
//	auto& id = mIndices; auto& vt = mVertices;
//	for (int i = 0; i < mVertices.size(); ++i) {
//		vt[i].mNormal = vec3(0.0f);
//	}
//	for (int i = 0; i < mIndices.size(); i += 3) {
//		vec3 norm = getNormal(vt[id[i]].mPosition, vt[id[i + 1]].mPosition, vt[id[i + 2]].mPosition);
//		vt[id[i]].mNormal += norm;
//		vt[id[i + 1]].mNormal += norm;
//		vt[id[i + 2]].mNormal += norm;
//	}
//	for (int i = 0; i < mVertices.size(); ++i) {
//		vt[i].mNormal = normalize(vt[i].mNormal);
//		if (flip_mNormal)vt[i].mNormal *= -1;
//	}
//	if (sync)syncData();
//}
//
//void MeshPatch::simplify() {//简化
//	auto& vt = mVertices;
//	if (vt.size() <= 10)return;
//	map<us, vertex> mv; map<us, face>mf; map<us, edge> mee;
//
//	for (int i = 0; i < vt.size(); ++i) {
//		mv.insert({ i,vt[i] });
//	}
//	for (int i = 0; i < mFaces.size(); ++i) {
//		mf.insert({ i,mFaces[i] });
//	}
//	for (int i = 0; i < mEdges.size(); ++i) {
//		mee.insert({ i,mEdges[i] });
//	}
//
//	vector<us> delf;
//	bool* del = new bool[vt.size()]();//顶点是否被删除
//	auto& ma = mVertexEdgeMap;
//	for (int i = 0; i < mFaces.size(); ++i) {
//		us e1 = mFaces[i].e; us e2 = mEdges[e1].next; us e3 = mEdges[e2].next;
//		us v1 = mEdges[e1].vert; us v2 = mEdges[e2].vert; us v3 = mEdges[e3].vert;
//		if (!del[v1] && !del[v2] && !del[v3]) {
//			vector<us> adv;
//			delf.push_back(i);
//			us ce = mEdges[mEdges[e1].opp].next;
//			us cv = mEdges[mEdges[ce].next].vert;
//			del[v1] = true; del[v2] = true; del[v3] = true;
//			mVertexEdgeMap.erase({ v1,v2 }); mVertexEdgeMap.erase({ v2 , v3 }); mVertexEdgeMap.erase({ v3 , v1 });
//			us vlast = v2;
//			{//查询邻接点
//				while (cv != v3) {
//					del[cv] = true;
//					adv.push_back(cv);
//					ma.erase({ v1,cv }); ma.erase({ cv,vlast }); ma.erase({ vlast,v1 });
//					vlast = cv;
//					delf.push_back(mEdges[ce].face);
//					ce = mEdges[mEdges[ce].opp].next;
//					cv = mEdges[mEdges[ce].next].vert;
//				}
//				delf.push_back(mEdges[ce].face);
//				ma.erase({ v1,cv }); ma.erase({ cv,vlast }); ma.erase({ vlast,v1 });
//
//				ce = mEdges[mEdges[mEdges[ce].next].opp].next;
//				cv = mEdges[mEdges[ce].next].vert;
//				while (cv != v2) {
//					del[cv] = true;
//					adv.push_back(cv);
//					ma.erase({ v3,cv }); ma.erase({ cv,vlast }); ma.erase({ vlast,v3 });
//					vlast = cv;
//					delf.push_back(mEdges[ce].face);
//					ce = mEdges[mEdges[ce].opp].next;
//					cv = mEdges[mEdges[ce].next].vert;
//				}
//				delf.push_back(mEdges[ce].face);
//				ma.erase({ v3,cv }); ma.erase({ cv,vlast }); ma.erase({ vlast,v3 });
//
//				ce = mEdges[mEdges[mEdges[ce].next].opp].next;
//				cv = mEdges[mEdges[ce].next].vert;
//				while (cv != v1) {
//					del[cv] = true;
//					adv.push_back(cv);
//					ma.erase({ v2,cv }); ma.erase({ cv,vlast }); ma.erase({ vlast,v2 });
//					vlast = cv;
//					delf.push_back(mEdges[ce].face);
//					ce = mEdges[mEdges[ce].opp].next;
//					cv = mEdges[mEdges[ce].next].vert;
//				}
//				adv.pop_back();
//			}
//
//			pt p = (vt[v1].mPosition + vt[v2].mPosition + vt[v3].mPosition) * 0.333333;
//			us sz = mv.size();
//			mv.insert({ sz,vertex(p) });
//
//			//make face
//			for (int j = 1; j < adv.size(); ++j) {
//				SPFMakeFace(adv[j], adv[j - 1], sz, mv, mf, mee, mf.size());
//			}
//			SPFMakeFace(adv.front(), adv.back(), sz, mv, mf, mee, mf.size());
//		}
//	}
//	for (int i = 0; i < delf.size(); ++i) {
//		mf.erase(delf[i]);
//	}
//
//	map<us, us> nv; map<us, us> ne; map<us, us> nf;
//	mFaces.resize(0); mEdges.resize(0); vt.resize(0);
//
//	for (auto& y : mf) {
//		face f = y.second;
//		nf.insert({ y.first , nf.size() });
//		mFaces.push_back(f);
//
//		us e1 = f.e; us e2 = mee[e1].next; us e3 = mee[e2].next;
//		us v1 = mee[e1].vert; us v2 = mee[e2].vert; us v3 = mee[e3].vert;
//		if (nv.find(v1) == nv.end()) {
//			nv.insert({ v1,vt.size() });
//			vt.push_back(mv[v1]);
//		}
//		if (nv.find(v2) == nv.end()) {
//			nv.insert({ v2,vt.size() });
//			vt.push_back(mv[v2]);
//		}
//		if (nv.find(v3) == nv.end()) {
//			nv.insert({ v3,vt.size() });
//			vt.push_back(mv[v3]);
//		}
//		if (ne.find(e1) == ne.end()) {
//			ne.insert({ e1,mEdges.size() });
//			mEdges.push_back(mee[e1]);
//		}
//		if (ne.find(e2) == ne.end()) {
//			ne.insert({ e2,mEdges.size() });
//			mEdges.push_back(mee[e2]);
//		}
//		if (ne.find(e3) == ne.end()) {
//			ne.insert({ e3,mEdges.size() });
//			mEdges.push_back(mee[e3]);
//		}
//	}
//
//	for (int i = 0; i < mFaces.size(); ++i) {
//		mFaces[i].e = ne[mFaces[i].e];
//	}
//	for (int i = 0; i < vt.size(); ++i) {
//		vt[i].out = ne[vt[i].out];
//	}
//	for (int i = 0; i < mEdges.size(); ++i) {
//		mEdges[i].vert = nv[mEdges[i].vert];
//		mEdges[i].next = ne[mEdges[i].next];
//		mEdges[i].opp = ne[mEdges[i].opp];
//		mEdges[i].face = nf[mEdges[i].face];
//	}
//	deg3Clean();
//	makeIndices();
//	calcuNormal();//计算顶点的法向量并生成顶点数据
//	delete[] del;
//};
//
//void MeshPatch::tessellate() {
//	vector<vertex> nvt = mVertices;
//	auto& vt = mVertices;
//	vector<face> nface;
//	vector<edge> nedge;
//	map<pa, us> m;
//	map<ll, us> s;
//	mIndices.resize(mFaces.size() * 12); int idx = -1;
//	float stick = 5.0 / 8.0; float change = 3.0 / 8.0;
//	vector<vector<us>> adv; vector<us> lret;
//	for (int i = 0; i < vt.size(); ++i) {
//		qav(i, lret); adv.push_back(lret); lret.resize(0);
//	}
//
//	for (int i = 0; i < mFaces.size(); ++i)
//	{
//		us e1 = mFaces[i].e; us v1 = mEdges[e1].vert;
//		us e2 = mEdges[e1].next; us v2 = mEdges[e2].vert;
//		us e3 = mEdges[e2].next; us v3 = mEdges[e3].vert;
//		us nv1; us nv2; us nv3;
//
//		pt np;
//		auto it = s.find(hash(v2, v1));
//		if (it == s.end()) {
//			np = (vt[v1].mPosition + vt[v2].mPosition) * (3.50f / 8) + (vt[v3].mPosition + vt[qov(e1)].mPosition) * (0.5f / 8);
//			nv1 = nvt.size();
//			nvt.push_back(vertex(np));
//		}
//		else nv1 = it->second;
//		s.insert({ hash(v1,v2), nvt.size() - 1 });
//
//		it = s.find(hash(v3, v2));
//		if (it == s.end()) {
//			np = (vt[v2].mPosition + vt[v3].mPosition) * (3.5f / 8) + (vt[v1].mPosition + vt[qov(e2)].mPosition) * (0.5f / 8);
//			nv2 = nvt.size();
//			nvt.push_back(vertex(np));
//		}
//		else nv2 = it->second;
//		s.insert({ hash(v2,v3), nvt.size() - 1 });
//
//		it = s.find(hash(v3, v1));
//		if (it == s.end()) {
//			np = (vt[v1].mPosition + vt[v3].mPosition) * (3.5f / 8) + (vt[v2].mPosition + vt[qov(e3)].mPosition) * (0.5f / 8);
//			nv3 = nvt.size();
//			nvt.push_back(vertex(np));
//		}
//		else nv3 = s[hash(v3, v1)];
//		s.insert({ hash(v1,v3), nvt.size() - 1 });
//
//		float u = change / adv[v1].size();
//		pt op;
//		for (int ii = 0; ii < adv[v1].size(); ii++)
//			op += vt[adv[v1][ii]].mPosition;
//		op = op * u + vt[v1].mPosition * (stick);
//		nvt[v1].mPosition = op; op = {};
//
//		u = change / adv[v2].size();
//		for (int ii = 0; ii < adv[v2].size(); ii++)
//			op += vt[adv[v2][ii]].mPosition;
//		op = op * u + vt[v2].mPosition * (stick);
//		nvt[v2].mPosition = op; op = {};
//
//		u = change / adv[v3].size();
//		for (int ii = 0; ii < adv[v3].size(); ii++)
//			op += vt[adv[v3][ii]].mPosition;
//		op = op * u + vt[v3].mPosition * (stick);
//		nvt[v3].mPosition = op;
//
//		createFace(v1, nv1, nv3, nface, nedge, m, nvt);
//		mIndices[++idx] = v1; mIndices[++idx] = nv1; mIndices[++idx] = nv3;
//
//		createFace(v2, nv2, nv1, nface, nedge, m, nvt);
//		mIndices[++idx] = v2; mIndices[++idx] = nv2; mIndices[++idx] = nv1;
//
//		createFace(v3, nv3, nv2, nface, nedge, m, nvt);
//		mIndices[++idx] = v3; mIndices[++idx] = nv3; mIndices[++idx] = nv2;
//
//		createFace(nv1, nv2, nv3, nface, nedge, m, nvt);
//		mIndices[++idx] = nv1; mIndices[++idx] = nv2; mIndices[++idx] = nv3;
//	}
//	mVertices.swap(nvt);
//	mVertexEdgeMap.swap(m);
//	mEdges.swap(nedge);
//	mFaces.swap(nface);
//	calcuNormal();
//}
//
//void MeshPatch::SPFMakeFace(us a, us b, us c, map<us, vertex>& mv, map<us, face>& mf, map<us, edge>& mee, us szz) {
//	face fa;
//	fa.e = mee.size();
//	fa.mNormal = getNormal(mv[a].mPosition, mv[b].mPosition, mv[c].mPosition);
//	mf.insert({ szz , fa });
//
//	edge e(a, mee.size() + 1, szz);
//	auto& ma = mVertexEdgeMap;
//	auto it = ma.find(pa(b, a));
//	if (it == ma.end())
//		ma.insert({ pa(a , b) , mee.size() });
//	else {
//		ma.insert({ pa(a , b) , mee.size() });
//		e.opp = it->second, mee[it->second].opp = mee.size();
//	}
//	mv[a].out = mee.size();
//	mee.insert({ mee.size() , e });
//
//	e = edge(b, mee.size() + 1, szz);
//	it = ma.find(pa(c, b));
//	if (it == ma.end())
//		ma.insert({ pa(b , c) , mee.size() });
//	else {
//		ma.insert({ pa(b , c) , mee.size() });
//		e.opp = it->second, mee[it->second].opp = mee.size();
//	}
//	mv[b].out = mee.size();
//	mee.insert({ mee.size() , e });
//
//	e = edge(c, mee.size() - 2, szz);
//	it = ma.find(pa(a, c));
//	if (it == ma.end())
//		ma.insert({ pa(c , a) , mee.size() });
//	else {
//		ma.insert({ pa(c , a) , mee.size() });
//		e.opp = it->second, mee[it->second].opp = mee.size();
//	}
//	mv[c].out = mee.size();
//	mee.insert({ mee.size() , e });
//}
//
//void Mesh::addTexture(const string& name, TextureType tp, int to_whom) {
//	Texture tex(GL_TEXTURE_2D);
//	tex.load(name, mDirectory);
//	tex.mType = tp;
//	mTextures.push_back(tex);
//	if (to_whom == -1) {
//		for (int i = 0; i < mMeshes.size(); ++i)
//			mMeshes[i].addTexture(mTextures.back());
//	}
//	else if (to_whom >= mMeshes.size())mMeshes.back().addTexture(mTextures.back());
//	else mMeshes[to_whom].addTexture(mTextures.back());
//}
//
//void Mesh::addTexture(const Texture& tex, int to_whom) {
//	mTextures.push_back(tex);
//	if (to_whom == -1) {
//		for (int i = 0; i < mMeshes.size(); ++i)
//			mMeshes[i].addTexture(mTextures.back());
//	}
//	else if (to_whom >= mMeshes.size())mMeshes.back().addTexture(mTextures.back());
//	else mMeshes[to_whom].addTexture(mTextures.back());
//}
//
////mat4 Mesh::curPose[500];
//
//
//
//
//
//
//
//
//
