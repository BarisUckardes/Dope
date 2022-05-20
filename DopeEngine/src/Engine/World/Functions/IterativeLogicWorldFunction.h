#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/World/WorldFunction.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API IterativeLogicWorldFunction final : public WorldFunction
	{
		GENERATE_WORLD_FUNCTION(IterativeLogicResolver);
	public:
		IterativeLogicWorldFunction() = default;
		~IterativeLogicWorldFunction() = default;


		virtual void register_component(Component* component) override final;
		virtual void remove_component(Component* component) override final;
		virtual void initialize() override final;
		virtual void execute() override final;
		virtual void finalize() override final;
	private:
		Array<Component*> LogicInflictedComponents;
	};


}