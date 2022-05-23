#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Asset/AssetType.h>
namespace DopeEngine
{
	class Asset;

	/// <summary>
	/// Asset object responsible for containing the relation between an object and the actual asset
	/// </summary>
	class DOPE_ENGINE_API AssetObject
	{
		friend class Asset;
	public:
		Asset* get_owner_asset() const;
		AssetType get_asset_type() const;

		void destroy_asset();

		virtual String get_asset_class_name() const = 0;
	protected:
		AssetObject(const AssetType type);
		~AssetObject() = default;

		virtual void destroy_asset_impl() = 0;
	private:
		void _set_owner_asset(Asset* ownerAsset);
	private:
		Asset* OwnerAsset;
		AssetType Type;
	};

#define GENERATE_ASSET_OBJECT(className) static String get_asset_class_name_static() { return #className;} virtual String get_asset_class_name() const override { return #className;}
}