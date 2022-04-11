#include "Shader.h"

namespace DopeEngine
{
	Shader::Shader(const String& source, const ShaderType type)
	{
		Source = source;
		Type = type;
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