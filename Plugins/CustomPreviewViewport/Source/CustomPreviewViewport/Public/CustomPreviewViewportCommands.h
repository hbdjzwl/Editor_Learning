// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomPreviewViewportStyle.h"

class FCustomPreviewViewportCommands : public TCommands<FCustomPreviewViewportCommands>
{
public:

	FCustomPreviewViewportCommands()
		: TCommands<FCustomPreviewViewportCommands>(TEXT("CustomPreviewViewport"), NSLOCTEXT("Contexts", "CustomPreviewViewport", "CustomPreviewViewport Plugin"), NAME_None, FCustomPreviewViewportStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};