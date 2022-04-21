#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Structures/Guid.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	class AssetPackage;
	class DOPE_ENGINE_API AssetPackagePool final
	{
		friend class GameSession;
	public:
		 const Array<AssetPackage*>& get_packages_fast() const;
		 Array<AssetPackage*> get_packages_slow() const;
		 AssetPackage* get_package_by_id(const Guid& id) const;
		 AssetPackage* get_package_by_name(const String& name) const;

		AssetPackage* create_package(const String& name);
	private:
		AssetPackagePool();
		~AssetPackagePool() = default;
	private:
		Array<AssetPackage*> Packages;
	};
}