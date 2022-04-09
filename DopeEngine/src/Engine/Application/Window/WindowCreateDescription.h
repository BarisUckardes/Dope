#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Holds window creation details
	/// </summary>
	struct DOPE_ENGINE_API WindowCreateDescription
	{
		WindowCreateDescription() : Title("Default Window Title"),Width(512),Height(512),PositionX(100),PositionY(100) {}
		WindowCreateDescription(const String& title,const unsigned int width,const unsigned int height,unsigned int positionX,unsigned int positionY) : 
			Title(title),
			Width(width),Height(height),
			PositionX(positionX),PositionY(positionY) {}


		/// <summary>
		/// The title of the window
		/// </summary>
		String Title;

		/// <summary>
		/// Window width in pixels
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// Window height in pixels
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// Window x-axis in pixels
		/// </summary>
		unsigned int PositionX;

		/// <summary>
		/// Window y-axis position in pixels
		/// </summary>
		unsigned int PositionY;
	};
}