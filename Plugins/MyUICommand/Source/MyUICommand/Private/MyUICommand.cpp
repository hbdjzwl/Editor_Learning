// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUICommand.h"
#include "MyCustomCommands.h"
#include <Misc/MessageDialog.h>
#include <LevelEditor.h>
#include "Framework/MultiBox/MultiBoxExtender.h"
#include <ContentBrowserModule.h>
#include <MyStyle.h>

#define LOCTEXT_NAMESPACE "FMyUICommandModule"

void FMyUICommandModule::CommandAAction()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Execute CommandA"));
}


void FMyUICommandModule::CommandBAction(FOnContentBrowserGetSelection GetSelectionDelegate)
{
	//��õ�ǰѡ�����Դ
	TArray<FAssetData> SelectedAssets;
	TArray<FString> SelectedPaths;
	if (GetSelectionDelegate.IsBound())
		GetSelectionDelegate.Execute(SelectedAssets, SelectedPaths);

	//Ҫ��ʾ����Ϣ��
	FString Message = "Execute CommandB:";
	for (auto ad : SelectedAssets)
	{
		Message += ad.GetAsset()->GetName() + " ";
	}
	//��ʾ�Ի���
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
}





void FMyUICommandModule::StartupModule()
{
	//��ʼ��ͼ����ʽ
	FMyStyle::Initialize();
	FMyStyle::ReloadTextures();


	//��������FMyCustomCommandע��ӿڣ��ڲ�������RegisterCommands������(ͨ����ģ������������е���)
	FMyCustomCommands::Register();

	//����UICommandList���������
	PluginCommandList = MakeShareable(new FUICommandList);



	//ע��˵���������
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().LevelEditor_MenuBar_Command,
		FExecuteAction::CreateLambda([]() {
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute LevelEditor MenuBar"));
			}),
		FCanExecuteAction());

	//ע��˵�������
 	PluginCommandList->MapAction(
		FMyCustomCommands::Get().LevelEditor_Menu_Command,
		FExecuteAction::CreateLambda([]() {
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute LevelEditor Menu"));
			}),
		FCanExecuteAction());

	//ע�Ṥ��������
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().LevelEditor_TooolBar_Command,
		FExecuteAction::CreateLambda([]() {
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Clicked Execute LevelEditor TooolBar"));
			}),
		FCanExecuteAction());



	//��ùؿ��༭��ģ��
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

#if 1
	//MenuBar �˵���
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
		);//�˴������GetMenu������GetMenuBar
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
#endif

#if 1
	//Menu �˵�
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
	//TooolBar ������
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

	//������������ģ��
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));


#if 0
	//�������������������
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

#endif

#if 0
	//���������������Asset�Ҽ��˵�
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
#endif


#if 0
	//����Asset�༭���еĲ˵�
	TArray<FAssetEditorExtender>& AssetEditorMenuExtenderDelegates = FAssetEditorToolkit::GetSharedMenuExtensibilityManager()->GetExtenderDelegates();
	AssetEditorMenuExtenderDelegates.Add(FAssetEditorExtender::CreateLambda([this](const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects)
		{
			//ӳ�����
			CommandList->MapAction(
				FMyCustomCommands::Get().CommandA,
				FExecuteAction::CreateRaw(this, &FMyUICommandModule::CommandAAction),
				FCanExecuteAction());
			//��Ӳ˵���չ
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
#endif

#if 0
	//����ToolBar�༭���еĲ˵�
	TArray<FAssetEditorExtender>& AssetEditorMenuExtenderDelegates1 = FAssetEditorToolkit::GetSharedToolBarExtensibilityManager()->GetExtenderDelegates();
	AssetEditorMenuExtenderDelegates1.Add(FAssetEditorExtender::CreateLambda([this](const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects)
		{
			//ӳ�����
			CommandList->MapAction(
				FMyCustomCommands::Get().CommandB,
				FExecuteAction::CreateRaw(this, &FMyUICommandModule::CommandAAction),
				FCanExecuteAction());

			//��Ӳ˵���չ
			TSharedRef<FExtender> Extender(new FExtender());
			Extender->AddToolBarExtension(
				"Asset",
				EExtensionHook::After,
				CommandList,
				FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder)
					{
						Builder.AddToolBarButton(FMyCustomCommands::Get().CommandB);
					}));
			return Extender;
		}));
#endif
}

void FMyUICommandModule::ShutdownModule()
{
	//Unregister��TCommands�Ľӿ�,�����������к�����������ص���Դ��(ͨ����ģ��Ĺرպ����б�����)
	FMyCustomCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyUICommandModule, MyUICommand)