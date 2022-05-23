#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Guid.h>
#include <Engine/Asset/AssetType.h>
#include <Engine/Asset/AssetImportType.h>

namespace DopeEngine
{
	class AssetPackage;
	class AssetObject;

	/// <summary>
	/// Represents an asset and its child object
	/// </summary>
	class DOPE_ENGINE_API Asset final
	{
		friend class AssetPackage;
	public:
		AssetPackage* get_owner_package() const;
		AssetObject* get_child_object() const;
		String get_source_file_absolute_path() const;
		String get_header_file_absolute_path() const;
		String get_name() const;
		Guid get_id() const;
		AssetType get_type() const;
		AssetImportType get_import_type() const;
		bool has_cached_memory() const;

		void load_sync();
		void unload_sync();
	private:
		/// <summary>
		/// Creates this asset as a packed asset
		/// </summary>
		/// <param name="sourceAbsolutePath"></param>
		/// <param name="headerAbsolutePath"></param>
		Asset(const String& sourceFileAbsolutePath,const String& headerFileAbsolutePath,AssetPackage* ownerPackage);

		/// <summary>
		/// Creates this asset a raw asset
		/// </summary>
		/// <param name="assetFileAbsolutePath"></param>
		/// <param name="targetFileType"></param>
		Asset(const String& rawFileAbsolutePath, const AssetType targetFileType,AssetPackage* ownerPackage);

		/// <summary>
		/// Creates this asset as a virtual asset
		/// </summary>
		/// <param name="childObject"></param>
		Asset(AssetObject* childObject,AssetPackage* ownerPackage);

		void initialize(const String& sourceFileAbsolutePath, const String& headerFileAbsolutePath,const String& rawFileAbsolutePath, const AssetType type, const AssetImportType importType, AssetPackage* ownerPackage);
		void load_packed_asset_sync();
		void load_raw_asset_sync();
		void unload_packed_asset_sync();
		void unload_raw_asset_sync();
		void unload_virtual_asset_sync();
		void gather_packed_asset_information();
		void gather_raw_file_information();
		void bind_child_object(AssetObject* childObject);
	private:
		AssetPackage* OwnerPackage;
		AssetObject* ChildObject;
		String SourceFileAbsolutePath;
		String HeaderFileAbsolutePath;
		String RawFileAbsolutePath;
		String Name;
		Guid ID;
		AssetType Type;
		AssetImportType ImportType;
	
	};


}