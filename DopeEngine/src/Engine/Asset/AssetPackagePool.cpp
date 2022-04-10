#include "AssetPackagePool.h"
#include <Engine/Asset/AssetPackage.h>
namespace DopeEngine
{
    const Array<AssetPackage*>& AssetPackagePool::get_packages_fast() const
    {
        return Packages;
    }
    Array<AssetPackage*> AssetPackagePool::get_packages_slow() const
    {
        return Packages;
    }
    AssetPackage* AssetPackagePool::get_package_by_id(const Guid& id) const
    {
        return nullptr;
    }
    AssetPackage* AssetPackagePool::get_package_by_name(const String& name) const
    {
        return nullptr;
    }
    AssetPackage* AssetPackagePool::create_package(const String& name)
    {
        /*
        * Create new package
        */
        AssetPackage* package = new AssetPackage(name,this);

        /*
        * Register package
        */
        Packages.add(package);

        return package;
    }
}