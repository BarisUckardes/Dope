#include "Asset.h"
#include <Engine/Asset/AssetObject.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	AssetPackage* Asset::get_owner_package() const
	{
		return OwnerPackage;
	}
	AssetObject* Asset::get_child_object() const
	{
		return ChildObject;
	}
	String Asset::get_source_file_absolute_path() const
	{
		return SourceFileAbsolutePath;
	}
	String Asset::get_header_file_absolute_path() const
	{
		return HeaderFileAbsolutePath;
	}
	String Asset::get_name() const
	{
		return Name;
	}
	Guid Asset::get_id() const
	{
		return ID;
	}
	AssetType Asset::get_type() const
	{
		return Type;
	}
	AssetImportType Asset::get_import_type() const
	{
		return ImportType;
	}
	unsigned long Asset::get_compressed_physical_file_size() const
	{
		return CompressedPhysicalFileSize;
	}
	unsigned long Asset::get_uncompressed_physical_file_size() const
	{
		return UncompressedPhysicalFileSize;
	}
	unsigned long Asset::get_cpu_allocated_functional_memory_size() const
	{
		return CpuAllocatedFunctionalMemorySize;
	}
	unsigned long Asset::get_gpu_allocated_functional_memory_size() const
	{
		return GpuAllocatedFunctionalMemorySize;
	}
	unsigned long Asset::get_cpu_cached_memory_size() const
	{
		return CpuCachedMemorySize;
	}
	unsigned long Asset::get_cpu_total_allocated_memory_size() const
	{
		return CpuAllocatedTotalMemorySize;
	}
	bool Asset::has_cached_memory() const
	{
		return false;
	}
	void Asset::load_sync()
	{
		switch (ImportType)
		{
			case DopeEngine::AssetImportType::Undefined:
				ASSERT(false, "Asset", "Cannot load an asset which has a import type marked as Undefined!");
				break;
			case DopeEngine::AssetImportType::Virtual:
				//Virtual assets cannot be loaded because they dont have physical body in the harddrive
				break;
			case DopeEngine::AssetImportType::Raw:
				load_raw_asset_sync();
				break;
			case DopeEngine::AssetImportType::Packed:
				load_packed_asset_sync();
				break;
			default:
				break;
		}
	}
	void Asset::unload_sync()
	{
		switch (ImportType)
		{
			case DopeEngine::AssetImportType::Undefined:
				ASSERT(false, "Asset", "Cannot unload an asset which has a import type marked as Undefined!");
				break;
			case DopeEngine::AssetImportType::Virtual:
				unload_virtual_asset_sync();
				break;
			case DopeEngine::AssetImportType::Raw:
				unload_raw_asset_sync();
				break;
			case DopeEngine::AssetImportType::Packed:
				unload_packed_asset_sync();
				break;
			default:
				break;
		}
	}
	void Asset::_set_allocated_cpu_memory_size(unsigned long size)
	{
		CpuAllocatedFunctionalMemorySize = size;
		CpuAllocatedTotalMemorySize = size + CpuCachedMemorySize;
	}
	void Asset::_set_allocated_gpu_memory_size(unsigned long size)
	{
		GpuAllocatedFunctionalMemorySize = size;
	}
	Asset::Asset(const String& sourceFileAbsolutePath, const String& headerFileAbsolutePath, AssetPackage* ownerPackage)
	{
		/*
		* Initialize
		*/
		initialize(sourceFileAbsolutePath, headerFileAbsolutePath, "Not Raw Asset", AssetType::Undefined, AssetImportType::Packed, ownerPackage);

		/*
		* Gather packed information
		*/
		gather_packed_asset_information();
	}
	Asset::Asset(const String& rawFileAbsolutePath, const AssetType targetFileType, AssetPackage* ownerPackage)
	{
		/*
		* Initialize
		*/
		initialize("Not Packed Asset", "Not Packed Asset", rawFileAbsolutePath, targetFileType, AssetImportType::Raw, ownerPackage);

		/*
		* Gather raw information
		*/
		gather_raw_file_information();
	}
	Asset::Asset(AssetObject* childObject, AssetPackage* ownerPackage)
	{
		/*
		* Initialize
		*/
		initialize("Not Packed Asset", "Not Packed Asset", "Not Raw Asset", childObject->get_asset_type(), AssetImportType::Virtual, ownerPackage);

		/*
		* Bind child object
		*/
		bind_child_object(childObject);
	}
	void Asset::initialize(const String& sourceFileAbsolutePath, const String& headerFileAbsolutePath,const String& rawFileAbsolutePath, const AssetType type, const AssetImportType importType, AssetPackage* ownerPackage)
	{
		SourceFileAbsolutePath = sourceFileAbsolutePath;
		HeaderFileAbsolutePath = headerFileAbsolutePath;
		RawFileAbsolutePath = rawFileAbsolutePath;
		Type = type;
		ImportType = importType;
		OwnerPackage = ownerPackage;
	}

	void Asset::load_packed_asset_sync()
	{

	}

	void Asset::load_raw_asset_sync()
	{

	}

	void Asset::unload_packed_asset_sync()
	{

	}

	void Asset::unload_raw_asset_sync()
	{

	}

	void Asset::unload_virtual_asset_sync()
	{

	}

	void Asset::gather_packed_asset_information()
	{

	}

	void Asset::gather_raw_file_information()
	{

	}
	void Asset::bind_child_object(AssetObject* childObject)
	{
		ChildObject = childObject;
		ChildObject->_set_owner_asset(this);
	}
}