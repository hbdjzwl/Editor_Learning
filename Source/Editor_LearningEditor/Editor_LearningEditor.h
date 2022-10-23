#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "AssetTypeCategories.h"


class FEditor_LearningEditorModule : public IModuleInterface
{
public:
	static inline FEditor_LearningEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FEditor_LearningEditorModule>("Editor_LearningEditor");
	}
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

// 	TSharedPtr<FMyConfig> ScannerConfig;
// 	TSharedPtr<IStructureDetailsView> SettingsView;
};