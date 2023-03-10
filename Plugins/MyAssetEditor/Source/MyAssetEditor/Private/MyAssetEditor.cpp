// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyAssetEditor.h"
#include "MyAssetTypeActions.h"
#include <IAssetTypeActions.h>
#define LOCTEXT_NAMESPACE "FMyAssetEditorModule"


void FMyAssetEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked< FAssetToolsModule >("AssetTools").Get();
	TSharedRef<IAssetTypeActions> CustAssetAction = MakeShareable(new FMyAssetTypeActions());
	RegisteredAssetTypeActions.Add(CustAssetAction);

	AssetTools.RegisterAssetTypeActions(CustAssetAction);
}

void FMyAssetEditorModule::ShutdownModule()
{
	FAssetToolsModule* AssetToolsPtr = FModuleManager::GetModulePtr< FAssetToolsModule >("AssetTools");
	if (AssetToolsPtr)
	{
		IAssetTools& AssetTools = AssetToolsPtr->Get();
		for (auto& r : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(r);
		}
	}

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyAssetEditorModule, MyAssetEditor)