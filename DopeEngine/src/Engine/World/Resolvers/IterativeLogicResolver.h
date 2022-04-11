#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/World/WorldResolver.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API IterativeLogicResolver final : public WorldResolver
	{
		GENERATE_RESOLVER(IterativeLogicResolver);
	public:
		IterativeLogicResolver() = default;
		~IterativeLogicResolver() = default;


		virtual void register_component(Component* component) override final;
		virtual void remove_component(Component* component) override final;
		virtual void initialize() override final;
		virtual void resolve() override final;
		virtual void finalize() override final;
	private:
		Array<Component*> LogicInflictedComponents;
	};


}