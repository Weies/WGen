#pragma once
#include"math/math_include.h"
#include"meta/serializer.h"
#include"log/debuger.h"
#include"log/exception.h"
#include"base/singleton.h"
#include"meta/json.h"


#include<fstream>
using Transform = SQT;

class JsonHelper
{
public:
	static Json load(const string& json_path)
	{
		fstream f;
		f.open(json_path, ios::in);
		string config_str = string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
		f.close();

		string err_str;
		Json json = Json::parse(config_str, err_str);
		if (!err_str.empty())
		{
			debug << "Failed to load json object : " << err_str << endl;
			return Json();
		}
		return json;
	}

	static Transform parseTransform(const Json& j)
	{
		Transform ret;
		Json translate = j["Translate"];
		ret.p.x = translate["x"].number_value();
		ret.p.y = translate["y"].number_value();
		ret.p.z = translate["z"].number_value();

		Json scale = j["Scale"];
		ret.s.x = scale["x"].number_value();
		ret.s.y = scale["y"].number_value();
		ret.s.z = scale["z"].number_value();

		vec3 Rot;
		Json rot = j["Rotation"];
		Rot.x = rot["x"].number_value();
		Rot.y = rot["y"].number_value();
		Rot.z = rot["z"].number_value();
		JsonHelper;
		ret.q = qua(vec3(1, 0, 0), Radian(Rot.x)) * qua(vec3(0, 1, 0), Radian(Rot.y)) * qua(vec3(0, 0, 1), Radian(Rot.z));
		return ret;
	}

};
