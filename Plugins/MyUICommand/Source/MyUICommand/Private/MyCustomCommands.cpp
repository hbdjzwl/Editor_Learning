#include "MyCustomCommands.h"
#include "MyStyle.h"
#define LOCTEXT_NAMESPACE "FTestYaksueModule"

FMyCustomCommands::FMyCustomCommands() 
	: TCommands<FMyCustomCommands>(
		"MyCustomCommands",
		NSLOCTEXT("Contexts", "MyCustomCommands", "MyCustomCommands Plugin"),
		NAME_None,
		FMyStyle::GetStyleSetName()
		)
{
}

void FMyCustomCommands::RegisterCommands()
{
	UI_COMMAND(LevelEditor_MenuBar_Command, "LevelEditor_MenuBar_Command", "Execute Custom LevelEditor MenuBar  Command", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(LevelEditor_Menu_Command,"LevelEditor_Menu_Command", "Execute Custom LevelEditor Menu Command", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(LevelEditor_Toolbar_Command, "LevelEditor_Toolbar_Command", "Execute Custom LevelEditor Toolbar Command", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(CommandA, "MyCustomCommandA", "Execute MyCustom CommandA", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CommandB, "MyCustomCommandB", "Execute MyCustom CommandB", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift | EModifierKey::Alt, EKeys::X));

}

#undef LOCTEXT_NAMESPACE
