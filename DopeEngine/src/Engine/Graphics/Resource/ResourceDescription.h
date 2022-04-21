#pragma once
#include <Engine/Graphics/Resource/ResourceType.h>
#include <Engine/Graphics/Shader/ShaderType.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Description for a graphics resource
	/// </summary>
	struct DOPE_ENGINE_API ResourceDescription
	{
		ResourceDescription(const String& name,const ResourceType type,const ShaderType shaderStage) : Name(name),Type(type),ShaderStage(shaderStage) {}
		ResourceDescription() : ShaderStage(ShaderType::Undefined),Type(ResourceType::Undefined) {}
		~ResourceDescription() = default;

		/// <summary>
		/// The name of the resource
		/// </summary>
		String Name;

		/// <summary>
		/// Resource type
		/// </summary>
		ResourceType Type;

		/// <summary>
		/// Shader stage type
		/// </summary>
		ShaderType ShaderStage;

	};
}