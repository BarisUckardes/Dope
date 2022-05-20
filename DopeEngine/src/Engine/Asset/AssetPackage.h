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
		/// <summary>
		/// Returns a reference to the asset list
		/// </summary>
		/// <returns></returns>
		const Array<Asset*>& get_assets_fast() const;

		/// <summary>
		/// Returns a copy of the asset list
		/// </summary>
		/// <returns></returns>
		Array<Asset*> get_assets_slow() const;

		/// <summary>
		/// Returns the owning pool of this package
		/// </summary>
		/// <returns></returns>
		AssetPackagePool* get_owner_pool() const;

		/// <summary>
		/// Returns name of the package
		/// </summary>
		/// <returns></returns>
		String get_name() const;

		/// <summary>
		/// Returns id of the package
		/// </summary>
		/// <returns></returns>
		Guid get_id() const;

		/// <summary>
		/// Returns if this package is an virtual package
		/// </summary>
		/// <returns></returns>
		bool is_virtual_package() const;

		/// <summary>
		/// Creates a packed asset
		/// </summary>
		/// <param name="sourceFileAbsolutePath"></param>
		/// <param name="headerFileAbsolutePath"></param>
		/// <returns></returns>
		Asset* create_packed_asset(const String& sourceFileAbsolutePath,const String& headerFileAbsolutePath);

		/// <summary>
		/// Creates a raw asset
		/// </summary>
		/// <param name="rawFileAbsolutePath"></param>
		/// <returns></returns>
		Asset* create_raw_asset(const String& rawFileAbsolutePath,const AssetType fileAssetType);

		/// <summary>
		/// Creates a virtual asset
		/// </summary>
		/// <param name="object"></param>
		/// <returns></returns>
		Asset* create_virtual_asset(AssetObject* object);
	private:
		AssetPackage(const String& packageName,AssetPackagePool* ownerPool);
		AssetPackage(AssetPackagePool* ownerPool);
		~AssetPackage() = default;

		void register_asset(Asset * asset);
	private:
		Array<Asset*> Assets;
		AssetPackagePool* OwnerPool;
		String Name;
		Guid ID;
		bool Virtual;
	};
}