// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUICommand.h"
#include "MyCustomCommands.h"
#include <Misc/MessageDialog.h>
#include <LevelEditor.h>
#include "Framework/MultiBox/MultiBoxExtender.h"
#include <ContentBrowserModule.h>
//#include "MultiBox/MultiBoxExtender.h"
#define LOCTEXT_NAMESPACE "FMyUICommandModule"

void FMyUICommandModule::CommandAAction()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Execute CommandA"));
}



void FMyUICommandModule::CommandBAction(FOnContentBrowserGetSelection GetSelectionDelegate)
{
	//获得当前选择的资源
	TArray<FAssetData> SelectedAssets;
	TArray<FString> SelectedPaths;
	if (GetSelectionDelegate.IsBound())
		GetSelectionDelegate.Execute(SelectedAssets, SelectedPaths);

	//要显示的信息：
	FString Message = "Execute CommandB:";
	for (auto ad : SelectedAssets)
		Message += ad.GetAsset()->GetName() + " ";
	//显示对话框
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
}


void FMyUICommandModule::StartupModule()
{
	//Register是TCommands的接口。用来注册命令，通常在模块的启动函数中调用。观察它的实现可看到内部调用了RegisterCommands函数。
	FMyCustomCommands::Register();

	//创建UICommandList
	PluginCommandList = MakeShareable(new FUICommandList);
	//为命令映射操作
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().CommandA,
		FExecuteAction::CreateRaw(this,&FMyUICommandModule::CommandAAction),
		FCanExecuteAction());




	//获得关卡编辑器模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

#if 1
	//MenuBar 菜单栏
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension(
			"Help",
			EExtensionHook::After,
			PluginCommandList,
			FMenuBarExtensionDelegate::CreateLambda([](FMenuBarBuilder& Builder)
				{
					Builder.AddMenuEntry(FMyCustomCommands::Get().CommandA);
				}
			)
		);
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}
#endif

#if 1
	//Menu 菜单
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("LevelEditor"
			, EExtensionHook::First
			, PluginCommandList
			, FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder)
				{
					Builder.AddMenuEntry(FMyCustomCommands::Get().CommandA);
				}));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
#endif


#if 0
	//工具栏
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings"
			, EExtensionHook::After
			, PluginCommandList
			, FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder)
				{
					Builder.AddToolBarButton(FMyCustomCommands::Get().CommandA);
				}));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
#endif

	//获得内容浏览器模块
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	//加入内容浏览器的命令
	TArray<FContentBrowserCommandExtender>& CBCommandExtenderDelegates = ContentBrowserModule.GetAllContentBrowserCommandExtenders();
	CBCommandExtenderDelegates.Add(FContentBrowserCommandExtender::CreateLambda([this](TSharedRef<FUICommandList> CommandList, FOnContentBrowserGetSelection GetSelectionDelegate)
		{
			CommandList->MapAction(FMyCustomCommands::Get().CommandB,
				FExecuteAction::CreateLambda([this, GetSelectionDelegate]
					{
						CommandBAction(GetSelectionDelegate);
					})
			);
		}));


	//增加内容浏览器中Asset右键菜单
	TArray<FContentBrowserMenuExtender_SelectedAssets>& CBAssetMenuExtenderDelegates = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
	CBAssetMenuExtenderDelegates.Add(FContentBrowserMenuExtender_SelectedAssets::CreateLambda([](const TArray<FAssetData>& SelectedAssets)
		{
			TSharedRef<FExtender> Extender(new FExtender());

			Extender->AddMenuExtension(
				"AssetContextReferences",
				EExtensionHook::After,
				nullptr,
				FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
					{
						MenuBuilder.AddMenuEntry(FMyCustomCommands::Get().CommandB);
					}));

			return Extender;
		}));




	//增加Asset编辑器中的菜单
	TArray<FAssetEditorExtender>& AssetEditorMenuExtenderDelegates = FAssetEditorToolkit::GetSharedMenuExtensibilityManager()->GetExtenderDelegates();
	AssetEditorMenuExtenderDelegates.Add(FAssetEditorExtender::CreateLambda([this](const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects)
		{
			//映射操作
			CommandList->MapAction(
				FMyCustomCommands::Get().CommandA,
				FExecuteAction::CreateRaw(this, &FMyUICommandModule::CommandAAction),
				FCanExecuteAction());
			//添加菜单扩展
			TSharedRef<FExtender> Extender(new FExtender());
			Extender->AddMenuExtension(
				"FindInContentBrowser",
				EExtensionHook::After,
				CommandList,
				FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
					{
						MenuBuilder.AddMenuEntry(FMyCustomCommands::Get().CommandA);
					}));
			return Extender;
		}));

}

void FMyUICommandModule::ShutdownModule()
{
	//Unregister是TCommands的接口。负责清理所有和这组命令相关的资源，通常在模块的关闭函数中被调用。
	FMyCustomCommands::Unregister();

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyUICommandModule, MyUICommand)