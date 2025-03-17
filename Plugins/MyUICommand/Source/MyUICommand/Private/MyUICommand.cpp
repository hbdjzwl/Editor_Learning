// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUICommand.h"
#include "MyCustomCommands.h"
#include <Misc/MessageDialog.h>
#include <LevelEditor.h>
#include "Framework/MultiBox/MultiBoxExtender.h"
#include <ContentBrowserModule.h>
#include <MyStyle.h>

#define LOCTEXT_NAMESPACE "FMyUICommandModule"


void FMyUICommandModule::StartupModule()
{
	//初始化图标样式
	FMyStyle::Initialize();
	FMyStyle::ReloadTextures();


	//用来调用FMyCustomCommand注册接口，内部调用了RegisterCommands函数。(通常在模块的启动函数中调用)
	FMyCustomCommands::Register();

	//创建UICommandList，用于祖册
	PluginCommandList = MakeShareable(new FUICommandList);

	//注册用于关卡编辑器Widget命令
	RegisterAllCommand();

	//创建关卡编辑器Widget
	CreateLevelEditorWidget();

	//创建内容编辑器Widget
	CreateContentBrowserWidget();

	//创建资产编辑器Widget及注册映射命令。
	CreateAssetWidgetAndRegisterAssetCommand();



}

void FMyUICommandModule::ShutdownModule()
{
	//Unregister是TCommands的接口,负责清理所有和这组命令相关的资源。(通常在模块的关闭函数中被调用)
	FMyCustomCommands::Unregister();

	FMyStyle::Shutdown();
}

//辅助函数
void FMyUICommandModule::GetSelectAllAssets(FOnContentBrowserGetSelection GetSelectionDelegate)
{
	//获得当前选择的资源
	TArray<FAssetData> SelectedAssets;
	TArray<FString> SelectedPaths;
	if (GetSelectionDelegate.IsBound())
	{
		GetSelectionDelegate.Execute(SelectedAssets, SelectedPaths);
	}

	//要显示的信息：
	FString Message = "Execute ContentBrowser ShortcutKey :[";
	for (auto ad : SelectedAssets)
	{
		Message += ad.GetAsset()->GetName() + "-";
	}
	Message += "]";

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
}

//注册所有命令
void FMyUICommandModule::RegisterAllCommand()
{
	//注册菜单栏的命令
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().LevelEditor_MenuBar_Command,
		FExecuteAction::CreateLambda([]() {
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute LevelEditor MenuBar"));
			}),
		FCanExecuteAction());

	//注册菜单的命令
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().LevelEditor_Menu_Command,
		FExecuteAction::CreateLambda([]() {
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute LevelEditor Menu"));
			}),
		FCanExecuteAction());

	//注册工具栏命令
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().LevelEditor_TooolBar_Command,
		FExecuteAction::CreateLambda([]() {
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute LevelEditor TooolBar"));
			}),
		FCanExecuteAction());


	//内容浏览器选择目标命令
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().ContentBrowser_SelectRightMouseMenu,
		FExecuteAction::CreateLambda([]() {
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute Content Browser Menu Select Right Mouse"));
			}),
		FCanExecuteAction());
}

//创建关卡编辑器的UI
void FMyUICommandModule::CreateLevelEditorWidget()
{
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
			FMenuBarExtensionDelegate::CreateLambda([](FMenuBarBuilder& MenuBarBuilder)
				{
					MenuBarBuilder.AddMenuEntry(FMyCustomCommands::Get().LevelEditor_MenuBar_Command);
				}
			)
		);//此处很奇怪GetMenu并不是GetMenuBar
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
#endif

#if 1
	//Menu 菜单
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension(
			"LevelEditor",
			EExtensionHook::First,
			PluginCommandList,
			FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder)
				{
					Builder.AddMenuEntry(FMyCustomCommands::Get().LevelEditor_Menu_Command);
				}));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
#endif


#if 1
	//TooolBar 工具栏
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings"
			, EExtensionHook::After
			, PluginCommandList
			, FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder)
				{
					Builder.AddToolBarButton(FMyCustomCommands::Get().LevelEditor_TooolBar_Command);
				}));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
#endif

}

//创建内容浏览器的UI、及快捷命令
void FMyUICommandModule::CreateContentBrowserWidget()
{

	//获得内容浏览器模块
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));


#if 1
	//内容浏览器快捷键
	TArray<FContentBrowserCommandExtender>& CBCommandExtenderDelegates = ContentBrowserModule.GetAllContentBrowserCommandExtenders();
	CBCommandExtenderDelegates.Add(FContentBrowserCommandExtender::CreateLambda([this](TSharedRef<FUICommandList> CommandList, FOnContentBrowserGetSelection GetSelectionDelegate)
		{
			CommandList->MapAction(FMyCustomCommands::Get().ContentBrowser_ShortcutKey,
				FExecuteAction::CreateLambda([this, GetSelectionDelegate]
					{
						GetSelectAllAssets(GetSelectionDelegate);
					})
			);
		}));

#endif

#if 1
	//内容浏览器:选择右键菜单
	TArray<FContentBrowserMenuExtender_SelectedAssets>& CBAssetMenuExtenderDelegates = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
	CBAssetMenuExtenderDelegates.Add(FContentBrowserMenuExtender_SelectedAssets::CreateLambda([this](const TArray<FAssetData>& SelectedAssets)
		{
			TSharedRef<FExtender> Extender(new FExtender());

			Extender->AddMenuExtension(
				"AssetContextReferences",
				EExtensionHook::After,
				PluginCommandList,
				FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
					{
						MenuBuilder.AddMenuEntry(FMyCustomCommands::Get().ContentBrowser_SelectRightMouseMenu);
					}));

			return Extender;
		}));
#endif
}


//创建资产UI、及注册映射命令
void FMyUICommandModule::CreateAssetWidgetAndRegisterAssetCommand()
{
#if 1
	//增加Asset编辑器中的菜单
	TArray<FAssetEditorExtender>& AssetEditorMenuExtenderDelegates = FAssetEditorToolkit::GetSharedMenuExtensibilityManager()->GetExtenderDelegates();
	AssetEditorMenuExtenderDelegates.Add(FAssetEditorExtender::CreateLambda([this](const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects)
		{
			//映射操作
			CommandList->MapAction(
				FMyCustomCommands::Get().AssetEditor_Menu_Command,
				FExecuteAction::CreateLambda([](){
						FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute AssetEditor Menu"));
					}
				),
				FCanExecuteAction()
			);


			//添加菜单扩展
			TSharedRef<FExtender> Extender(new FExtender());
			Extender->AddMenuExtension(
				"FindInContentBrowser",
				EExtensionHook::After,
				CommandList,
				FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
					{
						MenuBuilder.AddMenuEntry(FMyCustomCommands::Get().AssetEditor_Menu_Command);
					}));
			return Extender;
		}));
#endif

#if 0
	//所有资产里，增加ToolBar编辑器中的菜单，如果要针对某个资产扩展ToolBar，参考FSMAssetEditor.cpp里
	TArray<FAssetEditorExtender>& AssetEditorMenuExtenderDelegates1 = FAssetEditorToolkit::GetSharedToolBarExtensibilityManager()->GetExtenderDelegates();
	AssetEditorMenuExtenderDelegates1.Add(FAssetEditorExtender::CreateLambda([this](const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects)
		{
			//映射操作
			CommandList->MapAction(
				FMyCustomCommands::Get().AssetEditor_TooolBar_Command,
				FExecuteAction::CreateLambda([]() {
					FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute AssetEditor ToolBar"));
					}
				),
				FCanExecuteAction()
			);

			//添加菜单扩展
			TSharedRef<FExtender> Extender(new FExtender());
			Extender->AddToolBarExtension(
				"Asset",
				EExtensionHook::After,
				CommandList,
				FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder)
					{
						Builder.AddToolBarButton(FMyCustomCommands::Get().AssetEditor_TooolBar_Command);
					}));
			return Extender;
		}));
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyUICommandModule, MyUICommand)