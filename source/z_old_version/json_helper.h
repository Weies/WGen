#pragma once

#include"core/core.h"
#include<fstream>
#include"basis.h"
using namespace gm;
class JsonHelper
{
public:
	static Json load(const string& json_path)
	{
		std::fstream f;
		f.open(json_path, std::ios::in);
		string json_str = string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
		f.close();

		string err_str;
		Json json = Json::parse(json_str, err_str);
		if (!err_str.empty())
		{
			debug << "Failed to load json object : " << err_str << endl;
			return Json();
		}
		return json;
	}

	static vec3 parseVector3(const Json& j)
	{
		vec3 v;
		v.x = j["x"].number_value();
		v.y = j["y"].number_value();
		v.z = j["z"].number_value();
		return v;
	}

	static vec4 parseVector4(const Json& j)
	{
		vec4 v;
		v.x = j["x"].number_value();
		v.y = j["y"].number_value();
		v.z = j["z"].number_value();
		v.w = j["w"].number_value();
		return v;
	}

	static Transform parseTransform(const Json& j)
	{
		Transform ret;
		Json translate = j["Translate"];
		ret.p = parseVector3(translate);

		Json scale = j["Scale"];
		ret.s = parseVector3(scale);

		Json rotation = j["Rotation"];
		vec3 Rot = parseVector3(rotation);
		ret.q = qua(vec3(1, 0, 0), Radian(Rot.x)) * qua(vec3(0, 1, 0), Radian(Rot.y)) * qua(vec3(0, 0, 1), Radian(Rot.z));

		return ret;
	}

	static MaterialDesc parseMaterial(const Json& j)
	{
		MaterialDesc desc;
		desc.mBaseColorFile = j["BaseColorFile"].string_value();
		desc.mDiffuseMapFile = j["DiffuseMapFile"].string_value();
		desc.mSpecularMapFile = j["SpecularMapFile"].string_value();
		desc.mMetallicMapFile = j["MetallicMapFile"].string_value();
		desc.mRoughnessMapFile = j["RoughnessMapFile"].string_value();
		desc.mOcculusionMapFile = j["OcculusionMapFile"].string_value();


		desc.mBaseColor = parseVector4(j["BaseColor"]);
		desc.mDiffuse = parseVector3(j["Diffuse"]);
		desc.mSpecular = parseVector3(j["Specular"]);

		desc.mMetallic = j["Metallic"].number_value();
		desc.mRoughness = j["Roughness"].number_value();
		desc.mOcculusion = j["Occulusion"].number_value();
		return desc;
	}

};