#pragma once
#include <Engine/Application/ApplicationModule.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API WorldResolverModule : public ApplicationModule
	{
		GENERATE_MODULE(WorldResolverModule);
	public:
		WorldResolverModule() = default;
		~WorldResolverModule() = default;

		// Inherited via ApplicationModule
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
		virtual void on_receive_application_event(ApplicationEvent* event) override;
	};


}