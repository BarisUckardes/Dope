#pragma once
#include <Engine/World/Component.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API TestComponent : public Component
	{
		GENERATE_COMPONENT(TestComponent);
	public:
		TestComponent(const String& debugMessage);
		~TestComponent() = default;

		// Inherited via Component
		virtual bool should_tick() const override;
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
	private:
		String Message;
	};


}