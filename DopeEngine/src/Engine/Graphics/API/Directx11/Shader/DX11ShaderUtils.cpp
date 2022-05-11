#include "DX11ShaderUtils.h"
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	String DX11ShaderUtils::get_shader_target_string(ShaderType type, const unsigned int majorVersion, const unsigned int minorVersion)
	{
		String text;

		/*
		* Embed shader stage
		*/
		switch (type)
		{
			case DopeEngine::ShaderType::Vertex:
				text = "vs_";
				break;
			case DopeEngine::ShaderType::Fragment:
				text = "ps_";
				break;
			case DopeEngine::ShaderType::Geometry:
				break;
			case DopeEngine::ShaderType::TesellationEval:
				break;
			case DopeEngine::ShaderType::TesellationControl:
				break;
			case DopeEngine::ShaderType::Compute:
				break;
			default:
				break;
		}

		/*
		* Embed shader ver
		*/
		text += String::get_from_integer(majorVersion) + "_" + String::get_from_integer(minorVersion);
		return text;
	}
}