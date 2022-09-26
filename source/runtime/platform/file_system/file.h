#pragma once
#include"core/core.h"

class FileHelper
{
public:
	static bool saveStringToFile(const string& text, const string& path)
	{
		std::fstream f;
		f.open(path, std::ios::out);
		if (!f.is_open())
		{
			debug("Failed to open file: {}", path);
			return false;
		}
		f.write(text.c_str(), text.size());
		f.close();
		return true;
	}

	static bool readFileToString(const string& path, string& text)
	{
		std::ifstream in(path);
		std::istreambuf_iterator<char> beg(in), end;
		text = string(beg, end);
		return true;
	}
};