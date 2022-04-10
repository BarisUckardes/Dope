#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Guid.h>
#include <Engine/Asset/AssetType.h>
#include <Engine/Asset/AssetImportType.h>
#
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
		/// <summary>
		/// Returns the owner package of this asset
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AssetPackage* get_owner_package() const;

		/// <summary>
		/// Returns the child object of this asset
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AssetObject* get_child_object() const;

		/// <summary>
		/// Returns the source file absolute path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_source_file_absolute_path() const;

		/// <summary>
		/// Returns the header file absolute path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_header_file_absolute_path() const;

		/// <summary>
		/// Returns the name of the asset
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_name() const;

		/// <summary>
		/// Returns the unique id of this asset
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Guid get_id() const;

		/// <summary>
		/// Returns the asset type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AssetType get_type() const;

		/// <summary>
		/// Returns the asset import type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AssetImportType get_import_type() const;

		/// <summary>
		/// Returns the compressed physical file size
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_compressed_physical_file_size() const;

		/// <summary>
		/// Returns the uncompressed physical file size
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_uncompressed_physical_file_size() const;

		/// <summary>
		/// Returns the size of the functional memory allocated on the cpu
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_cpu_allocated_functional_memory_size() const;

		/// <summary>
		/// Returns the size of the functional memory allocated on the gpu
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_gpu_allocated_functional_memory_size() const;

		/// <summary>
		/// Returns the size of the cached memory on the cpu
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_cpu_cached_memory_size() const;

		/// <summary>
		/// Returns the total allocated cpu memory size(Cpu + cache)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_cpu_total_allocated_memory_size() const;

		/// <summary>
		/// Returns whether this asset has a cached memory on the cpu
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_cached_memory() const;

		/// <summary>
		/// Loads the asset sync
		/// <para>Packed Asset	->	Loads the data from the packed file path</para>
		/// <para>Raw Asset		->	Loads the data from the raw file path</para>
		/// <para>Virtual Asset ->	Cannot load it because virtual is independent</para>
		/// </summary>
		void load_sync();

		/// <summary>
		/// Unloads the asset sync
		/// <para>Packed asset	->	Unloads the asset</para>
		/// <para>Raw asset		->	Unloads the asset</para>
		/// <para>Virtual asset ->	Unloads the asset</para>
		/// </summary>
		void unload_sync();

		/// <summary>
		/// An internal allocated cpu memory setter
		/// </summary>
		/// <param name="size"></param>
		void _set_allocated_cpu_memory_size(unsigned long size);

		/// <summary>
		/// An internal allocated gpu memory setter
		/// </summary>
		/// <param name="size"></param>
		void _set_allocated_gpu_memory_size(unsigned long size);
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

		/// <summary>
		/// Initializes the member variables for this asset
		/// </summary>
		void initialize(const String& sourceFileAbsolutePath, const String& headerFileAbsolutePath,const String& rawFileAbsolutePath, const AssetType type, const AssetImportType importType, AssetPackage* ownerPackage);

		/// <summary>
		/// Loads the packed asset sync
		/// </summary>
		void load_packed_asset_sync();

		/// <summary>
		/// Loads the raw asset sync
		/// </summary>
		void load_raw_asset_sync();

		/// <summary>
		/// Unloads the packed asset sync
		/// </summary>
		void unload_packed_asset_sync();

		/// <summary>
		/// Unloads the raw asset sync
		/// </summary>
		void unload_raw_asset_sync();

		/// <summary>
		/// Unloads the virtual asset sync
		/// </summary>
		void unload_virtual_asset_sync();

		/// <summary>
		/// Retrives the required information from the packed asset
		/// </summary>
		void gather_packed_asset_information();

		/// <summary>
		/// Retrives the required information from the raw asset
		/// </summary>
		void gather_raw_file_information();

		/// <summary>
		/// Bind this asset with the target child object
		/// </summary>
		/// <param name="childObject"></param>
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
		unsigned long UncompressedPhysicalFileSize;
		unsigned long CompressedPhysicalFileSize;
		unsigned long CpuAllocatedFunctionalMemorySize;
		unsigned long GpuAllocatedFunctionalMemorySize;
		unsigned long CpuCachedMemorySize;
		unsigned long CpuAllocatedTotalMemorySize;
	};


}