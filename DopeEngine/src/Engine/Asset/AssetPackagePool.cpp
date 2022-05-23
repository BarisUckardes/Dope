#include "AssetPackagePool.h"
#include <Engine/Asset/AssetPackage.h>
namespace DopeEngine
{
    const Array<AssetPackage*>& AssetPackagePool::get_packages() const
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
        AssetPackage* package = new AssetPackage(name,this);
        Packages.add(package);

        return package;
    }
    AssetPackage* AssetPackagePool::create_package()
    {
        AssetPackage* package = new AssetPackage(this);
        Packages.add(package);

        return package;
    }
}