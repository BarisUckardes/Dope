#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/Window.h>

namespace DopeEngine
{
	/// <summary>
	/// Graphics device abstraction class
	/// </summary>
	class DOPE_ENGINE_API GraphicsDevice
	{
	public:
		/// <summary>
		/// Creates new graphics device with the specified api type
		/// </summary>
		/// <param name="api"></param>
		/// <param name="ownerWindow"></param>
		/// <returns></returns>
		static GraphicsDevice* create(GraphicsAPIType api,Window* ownerWindow);

		/// <summary>
		/// Returns whether this device is the current device
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_current() const;

		/// <summary>
		/// Returns the owner window of this device (if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Window* get_owner_window() const;

		/// <summary>
		/// Makes this device current for this process
		/// </summary>
		FORCEINLINE void make_current();

		/// <summary>
		/// Returns the graphics api type
		/// </summary>
		/// <returns></returns>
		virtual GraphicsAPIType get_api_type() const = 0;

		/// <summary>
		/// Returns the graphics api version string
		/// </summary>
		/// <returns></returns>
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