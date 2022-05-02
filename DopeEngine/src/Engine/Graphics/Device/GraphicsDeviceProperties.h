#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API GraphicsDeviceProperties
	{
	public:
		GraphicsDeviceProperties(const String& vendor,const String& model) :
			Vendor(vendor),Model(model)
		{}
		GraphicsDeviceProperties() = default;
		~GraphicsDeviceProperties() = default;


		FORCEINLINE String get_vendor() const;
		FORCEINLINE String get_model() const;
	private:
		String Vendor;
		String Model;
	};
}