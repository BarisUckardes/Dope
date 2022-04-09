#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	class ApplicationEvent;
	class ApplicationSession;

	/// <summary>
	/// Base class for application modules
	/// </summary>
	class DOPE_ENGINE_API ApplicationModule
	{
		friend class Application;
	public:
		ApplicationModule() = default;
		~ApplicationModule() = default;

		/// <summary>
		/// Called on application initialization
		/// </summary>
		virtual void on_attach() = 0;

		/// <summary>
		/// Called each frame by the application
		/// </summary>
		virtual void on_update() = 0;

		/// <summary>
		/// Called on application finalization
		/// </summary>
		virtual void on_detach() = 0;

		/// <summary>
		/// Called when each application event broadcasted by the application
		/// </summary>
		/// <param name="event"></param>
		virtual void on_receive_application_event(ApplicationEvent* event) = 0;
	protected:

		/// <summary>
		/// Returns the owner application session
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ApplicationSession* get_owner_session() const;
	private:
		void _set_owner_session(ApplicationSession* session);
	private:
		ApplicationSession* OwnerSession;
	};


}