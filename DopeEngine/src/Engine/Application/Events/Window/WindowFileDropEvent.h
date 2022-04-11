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

		/// <summary>
		/// Returns the drag and dropped files
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<String> get_drops() const;

		// Inherited via ApplicationEvent
		virtual ApplicationEventType get_type() const override final;
		virtual String get_as_string() const override final;

	private:
		Array<String> Drops;
	};


}