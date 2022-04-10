#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/World/WorldResolver.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API IterativeLogicResolver : public WorldResolver
	{
		GENERATE_RESOLVER(IterativeLogicResolver);
	public:
		IterativeLogicResolver() = default;
		~IterativeLogicResolver() = default;


		virtual void register_component(Component* component) override;
		virtual void remove_component(Component* component) override;
		virtual void initialize() override;
		virtual void resolve() override;
		virtual void finalize() override;
	private:
		Array<Component*> LogicInflictedComponents;
	};


}