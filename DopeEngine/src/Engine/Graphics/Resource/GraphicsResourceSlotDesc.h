#pragma once
#include <Engine/Graphics/Resource/GraphicsResourceType.h>
#include <Engine/Graphics/Shader/ShaderType.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Description for a graphics resource
	/// </summary>
	struct DOPE_ENGINE_API GraphicsResourceSlotDesc
	{
		GraphicsResourceSlotDesc(const String& name,const GraphicsResourceType type,const ShaderType shaderStage) : Name(name),Type(type),ShaderStage(shaderStage) {}
		GraphicsResourceSlotDesc() : ShaderStage(ShaderType::Undefined),Type(GraphicsResourceType::Undefined) {}
		~GraphicsResourceSlotDesc() = default;

		/// <summary>
		/// The name of the resource
		/// </summary>
		String Name;

		/// <summary>
		/// Resource type
		/// </summary>
		GraphicsResourceType Type;

		/// <summary>
		/// Shader stage type
		/// </summary>
		ShaderType ShaderStage;

	};
}