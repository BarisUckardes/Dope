#include "AssetPackage.h"
#include <Engine/Asset/Asset.h>
namespace DopeEngine
{
	const Array<Asset*>& AssetPackage::get_assets_fast() const
	{
		return Assets;
	}
	AssetPackagePool* AssetPackage::get_owner_pool() const
	{
		return OwnerPool;
	}
	String AssetPackage::get_name() const
	{
		return Name;
	}
	Guid AssetPackage::get_id() const
	{
		return ID;
	}

	bool AssetPackage::is_virtual_package() const
	{
		return Virtual;
	}

	Asset* AssetPackage::create_packed_asset(const String& sourceFileAbsolutePath, const String& headerFileAbsolutePath)
	{
		Asset* asset = new Asset(sourceFileAbsolutePath, headerFileAbsolutePath,this);
		register_asset(asset);

		return asset;
	}
	Asset* AssetPackage::create_raw_asset(const String& rawFileAbsolutePath,const AssetType fileType)
	{
		Asset* asset = new Asset(rawFileAbsolutePath, fileType, this);
		register_asset(asset);

		return asset;
	}
	Asset* AssetPackage::create_virtual_asset(AssetObject* object)
	{
		Asset* asset = new Asset(object,this);
		register_asset(asset);

		return asset;
	}
	
	AssetPackage::AssetPackage(const String& packageAbsolutePath, AssetPackagePool* ownerPool)
	{
		OwnerPool = ownerPool;
		AbsolutePath = packageAbsolutePath;
		ID = Guid();
		Virtual = false;
	}

	AssetPackage::AssetPackage(AssetPackagePool* ownerPool)
	{
		OwnerPool = ownerPool;
		Virtual = true;
	}
	
	void AssetPackage::register_asset(Asset* asset)
	{
		Assets.add(asset);
	}
}