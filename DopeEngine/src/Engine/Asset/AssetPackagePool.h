#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	class AssetPackage;
	class Guid;
	class String;
	class DOPE_ENGINE_API AssetPackagePool final
	{
		friend class GameSession;
	public:
		FORCEINLINE const Array<AssetPackage*>& get_packages_fast() const;
		FORCEINLINE Array<AssetPackage*> get_packages_slow() const;
		FORCEINLINE AssetPackage* get_package_by_id(const Guid& id) const;
		FORCEINLINE AssetPackage* get_package_by_name(const String& name) const;

		AssetPackage* create_package(const String& name);
	private:
		AssetPackagePool();
		~AssetPackagePool() = default;
	private:
		Array<AssetPackage*> Packages;
	};
}