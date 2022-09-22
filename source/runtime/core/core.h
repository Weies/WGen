#pragma once
#include"math/math_include.h"
#include"meta/serializer.h"
#include"log/debuger.h"
#include"log/exception.h"
#include"base/singleton.h"
#include"meta/json.h"


#include<fstream>

class JsonHelpher
{
public:
	static Json&& load(const string& json_path)
	{
		Json json;
		fstream f;
		f.open(json_path, ios::in);
		string config_str = string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
		f.close();

		string err_str;
		json.parse(config_str, err_str);
		if (!err_str.empty())
		{
			debug << "Failed to load json object : " << err_str << endl;
			return Json();
		}
		return std::move(json);
	}
};
