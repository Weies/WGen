#pragma once

//static Json jsonlize(const vec3& v)
//{
//	Json::object obj;
//	obj.insert({ "x",v.x });
//	obj.insert({ "y",v.y });
//	obj.insert({ "z",v.z });
//	return obj;
//}
//static Json jsonlize(const vec2& v)
//{
//	Json::object obj;
//	obj.insert({ "x",v.x });
//	obj.insert({ "y",v.y });
//	return obj;
//}

//static Json jsonlize(const vec4& v)
//{
//	Json::object obj;
//	obj.insert({ "x",v.x });
//	obj.insert({ "y",v.y });
//	obj.insert({ "z",v.z });
//	obj.insert({ "w",v.w });
//	return obj;
//}

//static Json jsonlize(const ivec4& v)
//{
//	Json::object obj;
//	obj.insert({ "x",v.x });
//	obj.insert({ "y",v.y });
//	obj.insert({ "z",v.z });
//	obj.insert({ "w",v.w });
//	return obj;
//}

//static Json jsonlize(const Transform& t)
//{
//	Json::object obj;
//	obj.insert({ "Translate"	,jsonlize(t.t) });
//	obj.insert({ "Scale"		,jsonlize(t.s) });
//	obj.insert({ "Rotation"		,jsonlize(t.q.vec4()) });
//	return obj;
//}

//static Json jsonlize(const vertex& v)
//{
//	Json::object obj;
//	obj.insert({ "Position",jsonlize(v.mPosition) });
//	obj.insert({ "Normal",jsonlize(v.mNormal) });
//	obj.insert({ "TexCoord",jsonlize(v.mTexCoord) });
//	obj.insert({ "Tangent",jsonlize(v.mTangent) });
//	obj.insert({ "Bitangent",jsonlize(v.mBitangent) });
//	obj.insert({ "BoneIds",jsonlize(v.mBoneIds) });
//	obj.insert({ "BoneWeights",jsonlize(v.mBoneWeights) });
//	return obj;
//}

//static Json jsonlize(const ImportTexHead& h)
//{
//	Json::object obj;
//	obj.insert({ "Path",h.mPath });
//	obj.insert({ "Type",int(h.mType) });
//	return obj;
//}

//static Json jsonlize(const MeshPatch& m)
//{
//	Json::object obj;

//	obj.insert({ "Name",m.mName });
//	obj.insert({ "Transform",jsonlize(m.mTransform) });

//	{
//		Json::array vt;
//		for (int i = 0; i < m.mVertices.size(); ++i)
//		{
//			vt.push_back(jsonlize(m.mVertices[i]));
//		}
//		obj.insert({ "Vertices",vt });
//	}

//	{
//		Json::array id;
//		for (int i = 0; i < m.mIndices.size(); ++i)
//		{
//			id.push_back({ int(m.mIndices[i]) });
//		}
//		obj.insert({ "Indices",id });
//	}


//	{
//		Json::array tx;
//		for (int i = 0; i < m.mTextures.size(); ++i)
//		{
//			tx.push_back(jsonlize(m.mTextures[i]));
//		}
//		obj.insert({ "Textures",tx });
//	}
//	return obj;
//}

//Json jsonlize(const SkeletalMesh& m)
//{
//	Json::object obj;
//	obj.insert({ "Id"			,0 });
//	obj.insert({ "Name"			,m.mName });
//	obj.insert({ "Directory"	,m.mDirectory });
//	obj.insert({ "DefinitionUrl","" });
//	obj.insert({ "IsGammaCorection",m.mIsGammaCorection });

//	Json::array comps;

//	//mesh component
//	{
//		Json::object mesh;
//		mesh.insert({ "Type","Mesh" });

//		Json::array meshes;
//		for (int i = 0; i < m.mMeshes.size(); ++i)
//		{
//			meshes.push_back(jsonlize(m.mMeshes[i]));
//		}
//		mesh.insert({ "Meshes",meshes });

//		comps.push_back(mesh);
//	}

//	//transform component
//	{
//		Json::object trans;
//		trans.insert({ "Type","Transform" });
//		trans.insert({ "Transform",jsonlize(m.mTransform) });
//		comps.push_back(trans);
//	}

//	obj.insert({ "Components",comps });
//	return obj;
//}