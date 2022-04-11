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
		FORCEINLINE const Array<Asset*>& get_assets_fast() const;

		/// <summary>
		/// Returns a copy of the asset list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Asset*> get_assets_slow() const;

		/// <summary>
		/// Returns the owning pool of this package
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AssetPackagePool* get_owner_pool() const;

		/// <summary>
		/// Returns name of the package
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_name() const;

		/// <summary>
		/// Returns id of the package
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Guid get_id() const;

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
		/// Returns the allocated cpu memory size(only functional memory)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_cpu_allocated_functional_memory_size() const;

		/// <summary>
		/// Returns the allocated gpu memory size
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_gpu_allocated_functional_memory_size() const;

		/// <summary>
		/// Returns the cpu cached memory size
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_cpu_cached_memory_size() const;

		/// <summary>
		/// Returns the total allocated cpu memory size(functional + cached)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long get_cpu_allocated_total_memory_size() const;

		/// <summary>
		/// Creates a packed asset
		/// </summary>
		/// <param name="sourceFileAbsolutePath"></param>
		/// <param name="headerFileAbsolutePath"></param>
		/// <returns></returns>
		FORCEINLINE Asset* create_packed_asset(const String& sourceFileAbsolutePath,const String& headerFileAbsolutePath);

		/// <summary>
		/// Creates a raw asset
		/// </summary>
		/// <param name="rawFileAbsolutePath"></param>
		/// <returns></returns>
		FORCEINLINE Asset* create_raw_asset(const String& rawFileAbsolutePath,const AssetType fileAssetType);

		/// <summary>
		/// Creates a virtual asset
		/// </summary>
		/// <param name="object"></param>
		/// <returns></returns>
		FORCEINLINE Asset* create_virtual_asset(AssetObject* object);

		/// <summary>
		/// Internal method for incrementing compressed physical file size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _add_compressed_physical_file_size(unsigned long size);

		/// <summary>
		/// Internal method for decrementing compressed physical file size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _remove_compressed_physical_file_size(unsigned long size);

		/// <summary>
		/// Internal method for incrementing uncompressed physical file size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _add_uncompressed_physical_file_size(unsigned long size);

		/// <summary>
		/// Internal method for decrementing uncompressed physical file size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _remove_uncompressed_physical_file_size(unsigned long size);

		/// <summary>
		/// Internal method for incrementing cpu allocated functional memory size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _add_cpu_functional_memory_size(unsigned long size);

		/// <summary>
		/// Internal method for decrementing cpu allocated functional memory size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _remove_cpu_functional_memory_size(unsigned long size);

		/// <summary>
		/// Internal method for incrementing gpu allocated functional memory size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _add_gpu_functional_memory_size(unsigned long size);

		/// <summary>
		/// Internal method for decrementing gpu allocated functional memory size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _remove_gpu_functional_memory_size(unsigned long size);

		/// <summary>
		/// Internal method for incrementing cpu cached memory size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _add_cached_cpu_memory_size(unsigned long size);

		/// <summary>
		/// Internal method for decrementing cpu cached memory size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _remove_cached_cpu_memory_size(unsigned long size);
		
	private:
		AssetPackage(const String& packageName,AssetPackagePool* ownerPool);
		~AssetPackage() = default;

		FORCEINLINE void register_asset(Asset * asset);
	private:
		Array<Asset*> Assets;
		AssetPackagePool* OwnerPool;
		String Name;
		Guid ID;
		unsigned long CompressedPhysicalFileSize;
		unsigned long UncompressedPhysicalFileSize;
		unsigned long CpuAllocatedFunctionalMemorySize;
		unsigned long GpuAllocatedFunctionalMemorySize;
		unsigned long CpuCachedMemorySize;
		unsigned long CpuAllocatedTotalMemorySize;
	};
}