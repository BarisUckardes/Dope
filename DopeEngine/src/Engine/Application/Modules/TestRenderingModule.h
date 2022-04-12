#pragma once
#include <Engine/Application/ApplicationModule.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API TestRenderingModule : public ApplicationModule
	{
		GENERATE_MODULE(TestRenderingModule);
	public:
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
		virtual void on_receive_application_event(ApplicationEvent* event) override;

	};


}