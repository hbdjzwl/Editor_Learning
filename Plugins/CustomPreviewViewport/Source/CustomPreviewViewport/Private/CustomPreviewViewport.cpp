// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomPreviewViewport.h"
#include "CustomPreviewViewportStyle.h"
#include "CustomPreviewViewportCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName CustomPreviewViewportTabName("CustomPreviewViewport");

#define LOCTEXT_NAMESPACE "FCustomPreviewViewportModule"

void FCustomPreviewViewportModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomPreviewViewportStyle::Initialize();
	FCustomPreviewViewportStyle::ReloadTextures();

	FCustomPreviewViewportCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomPreviewViewportCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCustomPreviewViewportModule::PluginButtonClicked),
		FCanExecuteAction());


	//����UI���������
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCustomPreviewViewportModule::RegisterMenus));
	
	//�о�����ע�����Tab����CustomPreviewViewportTabName����ʱ�Ļص������������������ơ�
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CustomPreviewViewportTabName, FOnSpawnTab::CreateRaw(this, &FCustomPreviewViewportModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("BBB", "BBB"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);


}

void FCustomPreviewViewportModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCustomPreviewViewportStyle::Shutdown();

	FCustomPreviewViewportCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CustomPreviewViewportTabName);
}

TSharedRef<SDockTab> FCustomPreviewViewportModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCustomPreviewViewportModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CustomPreviewViewport.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FCustomPreviewViewportModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CustomPreviewViewportTabName);
}

void FCustomPreviewViewportModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	//�ؿ��༭��MainMenu�˵����µ�Window�˵�
	{
 		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
 		{
 			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
 			Section.AddMenuEntryWithCommandList(FCustomPreviewViewportCommands::Get().OpenPluginWindow, PluginCommands);
 		}
	}

	//�ؿ��༭���Ĺ�����
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCustomPreviewViewportCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomPreviewViewportModule, CustomPreviewViewport)