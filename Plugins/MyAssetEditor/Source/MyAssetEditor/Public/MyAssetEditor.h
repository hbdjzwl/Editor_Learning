// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <IAssetTypeActions.h>

class FMyAssetEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

};
