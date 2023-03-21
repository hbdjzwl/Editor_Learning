// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomPreviewViewport.h"
#include "CustomPreviewViewportStyle.h"
#include "CustomPreviewViewportCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include <CustomEditorViewport.h>

static const FName CustomPreviewViewportTabName("CustomPreviewViewport");

#define LOCTEXT_NAMESPACE "FCustomPreviewViewportModule"

void FCustomPreviewViewportModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomPreviewViewportStyle::Initialize();
	FCustomPreviewViewportStyle::ReloadTextures();

	FCustomPreviewViewportCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	//点击会创建 CustomPreviewViewportTabName 名称的编辑区
	PluginCommands->MapAction(
		FCustomPreviewViewportCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCustomPreviewViewportModule::PluginButtonClicked),
		FCanExecuteAction());


	//创建UI到工具栏里。并创建一个默认的编辑器区域
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCustomPreviewViewportModule::RegisterMenus));
	
	//全局的Tab注册，当时CustomPreviewViewportTabName 名称创建时，会调用OnSpawnPluginTab()函数。
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CustomPreviewViewportTabName, FOnSpawnTab::CreateRaw(this, &FCustomPreviewViewportModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("Custom Tab Name", "Custom Tab Name"))
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
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// 此区域是创建视图窗口的地图。
			SNew(SCustomEditorViewport)
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

	//关卡编辑器MainMenu菜单项下的Window菜单
	{
 		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
 		{
 			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
 			Section.AddMenuEntryWithCommandList(FCustomPreviewViewportCommands::Get().OpenPluginWindow, PluginCommands);
 		}
	}

	//关卡编辑器的工具栏
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