#pragma once
#include <Engine/Graphics/Shader/ShaderStage.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Used for creating a shader
	/// </summary>
	struct DOPE_ENGINE_API ShaderDescription
	{
		ShaderDescription(const ShaderStage type, const String& source) : Type(type),Source(source) {}
		ShaderDescription() : Type(ShaderStage::Undefined) {}
		~ShaderDescription() = default;

		ShaderStage Type;
		String Source;
	};
}