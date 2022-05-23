#include "DX11ShaderUtils.h"
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	String DX11ShaderUtils::get_shader_target_string(ShaderStage type, const unsigned int majorVersion, const unsigned int minorVersion)
	{
		String text;

		switch (type)
		{
			case DopeEngine::ShaderStage::Vertex:
				text = "vs_";
				break;
			case DopeEngine::ShaderStage::Fragment:
				text = "ps_";
				break;
			case DopeEngine::ShaderStage::Geometry:
				break;
			case DopeEngine::ShaderStage::TesellationEval:
				break;
			case DopeEngine::ShaderStage::TesellationControl:
				break;
			case DopeEngine::ShaderStage::Compute:
				break;
			default:
				break;
		}

		text += String::get_from_integer(majorVersion) + "_" + String::get_from_integer(minorVersion);

		return text;
	}
}