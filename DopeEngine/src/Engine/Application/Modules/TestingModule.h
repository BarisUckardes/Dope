#pragma once
#include <Engine/Application/ApplicationModule.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API TestingModule : public ApplicationModule
	{
		GENERATE_MODULE(TestingModule);
	public:
		TestingModule() = default;
		~TestingModule() = default;


		// Inherited via ApplicationModule
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
		virtual void on_receive_application_event(ApplicationEvent* event) override;

	private:
		

	};


}