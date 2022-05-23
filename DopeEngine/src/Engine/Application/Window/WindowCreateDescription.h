#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Holds window creation details
	/// </summary>
	struct DOPE_ENGINE_API WindowCreateDescription final
	{
		WindowCreateDescription() : Title("Default Window Title"),Width(512),Height(512),PositionX(100),PositionY(100) {}
		WindowCreateDescription(const String& title,const unsigned int width,const unsigned int height,unsigned int positionX,unsigned int positionY) : 
			Title(title),
			Width(width),Height(height),
			PositionX(positionX),PositionY(positionY) {}

		String Title;
		unsigned int Width;
		unsigned int Height;
		unsigned int PositionX;
		unsigned int PositionY;
	};
}