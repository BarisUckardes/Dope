#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Structures/Guid.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	class AssetPackage;

	/// <summary>
	/// Represents a hub for asset packages
	/// </summary>
	class DOPE_ENGINE_API AssetPackagePool final
	{
		friend class GameSession;
	public:
		const Array<AssetPackage*>& get_packages() const;
		AssetPackage* get_package_by_id(const Guid& id) const;
		AssetPackage* get_package_by_name(const String& name) const;
		AssetPackage* create_package(const String& absolutePath);
		AssetPackage* create_package();
	private:
		AssetPackagePool();
		~AssetPackagePool() = default;
	private:
		Array<AssetPackage*> Packages;
	};
}