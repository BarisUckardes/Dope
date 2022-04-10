#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	class ApplicationEvent;
	class GameSession;

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
		/// Returns the class name of this module
		/// </summary>
		/// <returns></returns>
		virtual String get_module_class_name() const = 0;

		/// <summary>
		/// Called on application initialization
		/// </summary>
		virtual void initialize() = 0;

		/// <summary>
		/// Called each frame by the application
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// Called on application finalization
		/// </summary>
		virtual void finalize() = 0;

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
		FORCEINLINE GameSession* get_owner_session() const;
	private:
		void _set_owner_session(GameSession* session);
	private:
		GameSession* OwnerSession;
	};

#define GENERATE_MODULE(className) public: static String get_module_class_name_static() { return #className;} virtual String get_module_class_name() const override { return #className;}
}