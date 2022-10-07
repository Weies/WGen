#pragma once

#include"core/core.h"
//--------------------------------------------------
// Asset data is serializable, import : file -> asset,load: asset -> component
// Every subclass of Asset is able to save as a .asset file
//--------------------------------------------------

class Asset
{
public:
	virtual string type() const = 0;
	string mName;
	string mPath;
};

#define RegisterAsset(x) string type()const{static const string asset(#x);return asset;};