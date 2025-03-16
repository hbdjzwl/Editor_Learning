// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestEdGraph.h"
#include "TestEdGraphStyle.h"
#include "TestEdGraphCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "MyGraph/MyGraphWindow.h"
#include "MyGraph/MyGraphNodeFactory.h"


static const FName TestEdGraphTabName("TestEdGraph");

#define LOCTEXT_NAMESPACE "FTestEdGraphModule"

void FTestEdGraphModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTestEdGraphStyle::Initialize();
	FTestEdGraphStyle::ReloadTextures();
	FTestEdGraphCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FTestEdGraphCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTestEdGraphModule::PluginButtonClicked),
		FCanExecuteAction());
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTestEdGraphModule::RegisterMenus));
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TestEdGraphTabName, FOnSpawnTab::CreateRaw(this, &FTestEdGraphModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTestEdGraphTabTitle", "TestEdGraph"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);





	//图表的命令A
	PluginCommands->MapAction(
		FTestEdGraphCommands::Get().CommandPin,
		FExecuteAction::CreateLambda([]()
			{
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Command Pin Message"));
			}),
		FCanExecuteAction());

	//图表的命令B
	PluginCommands->MapAction(
		FTestEdGraphCommands::Get().CommandNode,
		FExecuteAction::CreateLambda([]()
			{
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Command Node Message"));
			}),
		FCanExecuteAction());



	//注册图表节点工厂
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShareable(new FMyGraphNodeFactory()));





}

void FTestEdGraphModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTestEdGraphStyle::Shutdown();

	FTestEdGraphCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestEdGraphTabName);
}

TSharedRef<SDockTab> FTestEdGraphModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTestEdGraphModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TestEdGraph.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			//添加自己写的图表窗口
			SNew(SMyGraphWindow)

			//将文件中的新增的FUICommandList的Commands命令添加到GraphWindow中。
			.TestEdGraphCommands(PluginCommands)
		];
}

void FTestEdGraphModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TestEdGraphTabName);
}

void FTestEdGraphModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTestEdGraphCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTestEdGraphCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestEdGraphModule, TestEdGraph)