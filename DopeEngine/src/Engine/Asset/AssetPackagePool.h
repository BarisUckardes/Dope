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
		/// <summary>
		/// Returns all the packages
		/// </summary>
		/// <returns></returns>
		const Array<AssetPackage*>& get_packages() const;

		/// <summary>
		/// Returns the package by the guid id
		/// </summary>
		/// <param name="id"></param>
		/// <returns></returns>
		AssetPackage* get_package_by_id(const Guid& id) const;

		/// <summary>
		/// Returns the package by the name of it
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		AssetPackage* get_package_by_name(const String& name) const;

		/// <summary>
		/// Creates a non-virtual package
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		AssetPackage* create_package(const String& absolutePath);

		/// <summary>
		/// Creates a virtual package
		/// </summary>
		/// <returns></returns>
		AssetPackage* create_package();
	private:
		AssetPackagePool();
		~AssetPackagePool() = default;
	private:
		Array<AssetPackage*> Packages;
	};
}