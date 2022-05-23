#pragma once
#include <Engine/Graphics/Resource/GraphicsResourceType.h>
#include <Engine/Graphics/Shader/ShaderStage.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Description for a graphics resource
	/// </summary>
	struct DOPE_ENGINE_API GraphicsResourceSlotDesc
	{
		GraphicsResourceSlotDesc(const String& name,const GraphicsResourceType type,const ShaderStage shaderStage) : Name(name),Type(type),ShaderStage(shaderStage) {}
		GraphicsResourceSlotDesc() : ShaderStage(ShaderStage::Undefined),Type(GraphicsResourceType::Undefined) {}
		~GraphicsResourceSlotDesc() = default;

		String Name;
		GraphicsResourceType Type;
		ShaderStage ShaderStage;

	};
}