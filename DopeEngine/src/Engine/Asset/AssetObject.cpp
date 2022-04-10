#include "AssetObject.h"

namespace DopeEngine
{
	Asset* AssetObject::get_owner_asset() const
	{
		return OwnerAsset;
	}
	AssetType AssetObject::get_asset_type() const
	{
		return Type;
	}
	void AssetObject::destroy_asset()
	{

	}
	AssetObject::AssetObject(const AssetType type)
	{
		Type = type;
		OwnerAsset = nullptr;
	}
	void AssetObject::_set_owner_asset(Asset* ownerAsset)
	{
		OwnerAsset = ownerAsset;
	}
}