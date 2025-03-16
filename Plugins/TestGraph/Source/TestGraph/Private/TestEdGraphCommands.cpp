// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestEdGraphCommands.h"

#define LOCTEXT_NAMESPACE "FTestEdGraphModule"

void FTestEdGraphCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TestEdGraph", "Bring up TestEdGraph window", EUserInterfaceActionType::Button, FInputGesture());

	UI_COMMAND(CommandPin, "Pin Command", "Execute Pin Command",	EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CommandNode, "Node Command", "Execute Node Command", EUserInterfaceActionType::Button, FInputChord());

}

#undef LOCTEXT_NAMESPACE
