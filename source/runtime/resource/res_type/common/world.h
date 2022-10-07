#pragma once

#include"resource/basis.h"

//Save as .world file
class WorldRes
{
public:
	string mPath;

	string mDefaultLevelUrl;

	vector<string> mLevelUrls;
};

inline Archive& operator<<(Archive& ar, WorldRes& res)
{
	return ar << res.mPath << res.mDefaultLevelUrl << res.mLevelUrls;
}