#pragma once
#include <Engine/Graphics/Shader/ShaderType.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Used for creating a shader
	/// </summary>
	struct DOPE_ENGINE_API ShaderDescription
	{
		ShaderDescription(const ShaderType type, const String& source) : Type(type),Source(source) {}
		ShaderDescription() : Type(ShaderType::Undefined) {}
		~ShaderDescription() = default;

		/// <summary>
		/// The type of the shader
		/// </summary>
		ShaderType Type;

		/// <summary>
		/// Source text of the shader
		/// </summary>
		String Source;
	};
}