#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Shader/ShaderType.h>
#include <Engine/Graphics/Shader/ShaderDescription.h>

namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic shader abstraction class
	/// </summary>
	class DOPE_ENGINE_API Shader : public DeviceObject
	{
	public:
		Shader(const ShaderDescription& description);
		virtual ~Shader() = default;


		/// <summary>
		/// Returns the shader source
		/// </summary>
		/// <returns></returns>
		 String get_source() const;

		/// <summary>
		/// Returns the shader stage type of this shader
		/// </summary>
		/// <returns></returns>
		 ShaderType get_type() const;

		/// <summary>
		/// Compiles this shader
		/// </summary>
		virtual void compile() = 0;
	private:
		String Source;
		ShaderType Type;
	};


}