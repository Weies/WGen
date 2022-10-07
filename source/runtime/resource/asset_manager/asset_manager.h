#pragma once
#include"core/core.h"
#include"resource/res_type/data/asset_data.h"
#include"function/framework/object/GObject.h"

class AssetManager :public Singleton<AssetManager>
{
public:
	umap<string, Asset*> mNameAseetMap;

	template<class AssetType>
	AssetType* loadAsset(const string& asset_path)
	{
		Archive ar(new LinkerLoad);
		ar.load(asset_path);
		AssetType* asset = new AssetType;
		string type;
		ar << type;

		ar << *asset;
		mNameAseetMap.insert({ asset->mName,asset });

		return asset;
	}

	template<class AssetType>
	void saveAsset(const string& asset_path, AssetType& asset)
	{
		Archive ar(new LinkerSave);
		asset.mPath = asset_path;
		string type = asset.type();
		ar << type << asset;
		ar.save(asset_path);
	}

};