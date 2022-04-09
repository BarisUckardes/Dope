#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class Window;
	class DOPE_ENGINE_API GraphicsDevice
	{
	public:
		static GraphicsDevice* create(GraphicsAPIType api,Window* ownerWindow);


		FORCEINLINE bool is_current() const;
		FORCEINLINE const Window* get_owner_window() const;
		FORCEINLINE void make_current();

		virtual GraphicsAPIType get_api_type() const = 0;
		virtual String get_version() const = 0;
	protected:
		GraphicsDevice(Window* window);
		virtual ~GraphicsDevice() = default;

		virtual void make_current_impl() = 0;
	private:
		Window* OwnerWindow;
		bool Current;
	};


}