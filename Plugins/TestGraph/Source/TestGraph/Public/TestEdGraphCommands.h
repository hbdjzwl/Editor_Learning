// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TestEdGraphStyle.h"

class FTestEdGraphCommands : public TCommands<FTestEdGraphCommands>
{
public:

	FTestEdGraphCommands()
		: TCommands<FTestEdGraphCommands>(TEXT("TestEdGraph"), NSLOCTEXT("Contexts", "TestEdGraph", "TestEdGraph Plugin"), NAME_None, FTestEdGraphStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;


	//√¸¡ÓA°¢√¸¡ÓB
	TSharedPtr< FUICommandInfo > CommandPin;
	TSharedPtr< FUICommandInfo > CommandNode;

};