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
		virtual bool should_tick() const override final;
		virtual void initialize() override final;
		virtual void update() override final;
		virtual void finalize() override final;
	private:
		String Message;
	};


}