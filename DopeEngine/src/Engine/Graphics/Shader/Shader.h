#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Graphics/Shader/ShaderStage.h>
#include <Engine/Graphics/Shader/ShaderDescription.h>

namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic shader abstraction class
	/// </summary>
	class DOPE_ENGINE_API Shader : public GraphicsDeviceObject
	{
	public:
		Shader(const ShaderDescription& description);
		virtual ~Shader() = default;

		String get_source() const;
		ShaderStage get_type() const;
		virtual void compile() = 0;
	private:
		String Source;
		ShaderStage Type;
	};


}