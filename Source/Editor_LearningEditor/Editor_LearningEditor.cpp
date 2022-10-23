#include "Editor_LearningEditor.h"
#include "Customization/MyPropertyTypeCustomization.h"

#define LOCTEXT_NAMESPACE "FEditor_LearningModule"


void FEditor_LearningEditorModule::StartupModule()
{

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	PropertyEditorModule.RegisterCustomPropertyTypeLayout(TEXT("MyToDay"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyPropertyTypeCustomization::MakeInstance));

}
void FEditor_LearningEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditor_LearningEditorModule, Editor_LearningEditor)