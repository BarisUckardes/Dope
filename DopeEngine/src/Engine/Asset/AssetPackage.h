#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Guid.h>
#include <Engine/Asset/AssetType.h>

namespace DopeEngine
{
	class Asset;
	class AssetObject;
	class AssetPackagePool;

	/// <summary>
	/// A package consist of assets
	/// </summary>
	class DOPE_ENGINE_API AssetPackage final
	{
		friend class AssetPackagePool;
	public:
		const Array<Asset*>& get_assets_fast() const;

		AssetPackagePool* get_owner_pool() const;
		String get_name() const;
		Guid get_id() const;
		bool is_virtual_package() const;
		Asset* create_packed_asset(const String& sourceFileAbsolutePath,const String& headerFileAbsolutePath);
		Asset* create_raw_asset(const String& rawFileAbsolutePath,const AssetType fileAssetType);
		Asset* create_virtual_asset(AssetObject* object);
	private:
		AssetPackage(const String& packageAbsolutePath,AssetPackagePool* ownerPool);
		AssetPackage(AssetPackagePool* ownerPool);
		~AssetPackage() = default;

		void register_asset(Asset * asset);
	private:
		Array<Asset*> Assets;
		AssetPackagePool* OwnerPool;
		String Name;
		Guid ID;
		bool Virtual;
		String AbsolutePath;
	};
}