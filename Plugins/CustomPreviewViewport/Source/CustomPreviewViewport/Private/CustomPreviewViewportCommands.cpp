// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomPreviewViewportCommands.h"

#define LOCTEXT_NAMESPACE "FCustomPreviewViewportModule"

void FCustomPreviewViewportCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CustomPreviewViewport", "Bring up CustomPreviewViewport window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
