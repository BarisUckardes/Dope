#pragma once
#include <Engine/Application/Events/ApplicationEvent.h>
#include <Engine/Structures/Array.h>

namespace DopeEngine
{
	/// <summary>
	/// Window file drop event representation class
	/// </summary>
	class DOPE_ENGINE_API WindowFileDropEvent final : public ApplicationEvent
	{
	public:
		WindowFileDropEvent(const Array<String>& files);
		~WindowFileDropEvent() = default;


		Array<String> get_drop_paths() const;

		// Inherited via ApplicationEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;

	private:
		Array<String> Drops;
	};


}