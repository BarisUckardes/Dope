#include "AssetPackage.h"
#include <Engine/Asset/Asset.h>
namespace DopeEngine
{
	const Array<Asset*>& AssetPackage::get_assets_fast() const
	{
		return Assets;
	}
	Array<Asset*> AssetPackage::get_assets_slow() const
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
	unsigned long AssetPackage::get_compressed_physical_file_size() const
	{
		return CompressedPhysicalFileSize;
	}
	unsigned long AssetPackage::get_uncompressed_physical_file_size() const
	{
		return UncompressedPhysicalFileSize;
	}
	unsigned long AssetPackage::get_cpu_allocated_functional_memory_size() const
	{
		return CpuAllocatedFunctionalMemorySize;
	}
	unsigned long AssetPackage::get_gpu_allocated_functional_memory_size() const
	{
		return GpuAllocatedFunctionalMemorySize;
	}
	unsigned long AssetPackage::get_cpu_cached_memory_size() const
	{
		return CpuCachedMemorySize;
	}
	unsigned long AssetPackage::get_cpu_allocated_total_memory_size() const
	{
		return CpuAllocatedTotalMemorySize;
	}
	Asset* AssetPackage::create_packed_asset(const String& sourceFileAbsolutePath, const String& headerFileAbsolutePath)
	{
		/*
		* Create new packed asset
		*/
		Asset* asset = new Asset(sourceFileAbsolutePath, headerFileAbsolutePath,this);

		/*
		* Register asset
		*/
		register_asset(asset);

		return asset;
	}
	Asset* AssetPackage::create_raw_asset(const String& rawFileAbsolutePath,const AssetType fileType)
	{
		/*
		* Create new raw asset
		*/
		Asset* asset = new Asset(rawFileAbsolutePath, fileType, this);

		/*
		* Register rasset
		*/
		register_asset(asset);

		return asset;
	}
	Asset* AssetPackage::create_virtual_asset(AssetObject* object)
	{
		/*
		* Create new virtual assets
		*/
		Asset* asset = new Asset(object,this);

		/*
		* Register asset
		*/
		register_asset(asset);

		return asset;
	}
	void AssetPackage::_add_compressed_physical_file_size(unsigned long size)
	{
		CompressedPhysicalFileSize += size;
	}
	void AssetPackage::_remove_compressed_physical_file_size(unsigned long size)
	{
		CompressedPhysicalFileSize -= size;
	}
	void AssetPackage::_add_uncompressed_physical_file_size(unsigned long size)
	{
		UncompressedPhysicalFileSize += size;
	}
	void AssetPackage::_remove_uncompressed_physical_file_size(unsigned long size)
	{
		UncompressedPhysicalFileSize -= size;
	}
	void AssetPackage::_add_cpu_functional_memory_size(unsigned long size)
	{
		CpuAllocatedFunctionalMemorySize += size;
		CpuAllocatedTotalMemorySize += size;
	}
	void AssetPackage::_remove_cpu_functional_memory_size(unsigned long size)
	{
		CpuAllocatedFunctionalMemorySize -= size;
		CpuAllocatedTotalMemorySize -= size;
	}
	void AssetPackage::_add_gpu_functional_memory_size(unsigned long size)
	{
		GpuAllocatedFunctionalMemorySize += size;
	}
	void AssetPackage::_remove_gpu_functional_memory_size(unsigned long size)
	{
		GpuAllocatedFunctionalMemorySize -= size;
	}
	void AssetPackage::_add_cached_cpu_memory_size(unsigned long size)
	{
		CpuCachedMemorySize += size;
		CpuAllocatedTotalMemorySize += size;
	}
	void AssetPackage::_remove_cached_cpu_memory_size(unsigned long size)
	{
		CpuCachedMemorySize -= size;
		CpuAllocatedTotalMemorySize -= size;
	}
	AssetPackage::AssetPackage(const String& packageName, AssetPackagePool* ownerPool)
	{
		OwnerPool = ownerPool;
		Name = packageName;
		ID = Guid::create();
		CompressedPhysicalFileSize = 0;
		UncompressedPhysicalFileSize = 0;
		CpuAllocatedFunctionalMemorySize = 0;
		GpuAllocatedFunctionalMemorySize = 0;
		CpuCachedMemorySize = 0;
		CpuAllocatedTotalMemorySize = 0;
	}
	
	void AssetPackage::register_asset(Asset* asset)
	{
		Assets.add(asset);
	}
}