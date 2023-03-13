#include "MyCustomCommands.h"
#define LOCTEXT_NAMESPACE "FTestYaksueModule"

FMyCustomCommands::FMyCustomCommands() 
	: TCommands<FMyCustomCommands>(
		"MyCustomCommands",
		NSLOCTEXT("Contexts", "MyCustomCommands", "MyCustomCommands Plugin"),
		NAME_None,
		FName(*FString("todo")
		)
	)
{
}

void FMyCustomCommands::RegisterCommands()
{
	UI_COMMAND(CommandA, "MyCustomCommandA", "Execute MyCustom CommandA", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CommandB, "MyCustomCommandB", "Execute MyCustom CommandB", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift | EModifierKey::Alt, EKeys::X));

}

#undef LOCTEXT_NAMESPACE
