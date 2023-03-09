// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyAssetEditor.h"
#include "MyAssetTypeActions.h"
#define LOCTEXT_NAMESPACE "FMyAssetEditorModule"

void FMyAssetEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked< FAssetToolsModule >("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FMyAssetTypeActions()));
}

void FMyAssetEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyAssetEditorModule, MyAssetEditor)