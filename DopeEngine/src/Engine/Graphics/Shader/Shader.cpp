#include "Shader.h"

namespace DopeEngine
{
	Shader::Shader(const ShaderDescription& description)
	{
		Source = description.Source;
		Type = description.Type;
	}
	String Shader::get_source() const
	{
		return Source;
	}
	ShaderType Shader::get_type() const
	{
		return Type;
	}
}