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
	UI_COMMAND(LevelEditor_Menu_Command,"LevelEditor_Menu_Command", "Execute Custom LevelEditor Menu Command", EUserInterfaceActionType::Button, FInputChord())
	UI_COMMAND(LevelEditor_TooolBar_Command, "LevelEditor_TooolBar_Command", "Execute Custom LevelEditor Toolbar Command", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(ContentBrowser_SelectRightMouseMenu, "ContentBrowser_SelectRightMouseMenu", "Execute Custom Select Target ContentBrowser RightMouseMenu Command", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ContentBrowser_ShortcutKey, "ContentBrowser_ShortcutKey", "Execute Custom ContentBrowser ContentBrowser ShortcutKey Command", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift | EModifierKey::Alt, EKeys::X));


	UI_COMMAND(AssetEditor_Menu_Command, "AssetEditor_Menu_Command", "Execute Custom AssetEditor Menu Command", EUserInterfaceActionType::Button, FInputChord())
	UI_COMMAND(AssetEditor_TooolBar_Command, "AssetEditor_TooolBar_Command", "Execute Custom AssetEditor Toolbar Command", EUserInterfaceActionType::Button, FInputChord());

}

#undef LOCTEXT_NAMESPACE


