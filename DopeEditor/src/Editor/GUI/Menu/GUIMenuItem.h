#pragma once
#include <Editor/Core/Symbols.h>
#include <Engine/Structures/String.h>

namespace DopeEditor
{
	class DOPE_EDITOR_API GUIMenuItem
	{
	public:
		GUIMenuItem() = default;
		~GUIMenuItem() = default;

		FORCEINLINE virtual DopeEngine::String get_name() const = 0;
		FORCEINLINE virtual void execute() const = 0;
	};

#define GENERATE_MENU_ITEM(name) final virtual DopeEngine::String get_name() const override { return #name;} \
								 final virtual void execute() const override;
#define GENERATE_MENU_ITEM_EXÊCUTE(name) name::execute()
}