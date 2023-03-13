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
	//��õ�ǰѡ�����Դ
	TArray<FAssetData> SelectedAssets;
	TArray<FString> SelectedPaths;
	if (GetSelectionDelegate.IsBound())
		GetSelectionDelegate.Execute(SelectedAssets, SelectedPaths);

	//Ҫ��ʾ����Ϣ��
	FString Message = "Execute CommandB:";
	for (auto ad : SelectedAssets)
		Message += ad.GetAsset()->GetName() + " ";
	//��ʾ�Ի���
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
}


void FMyUICommandModule::StartupModule()
{
	//Register��TCommands�Ľӿڡ�����ע�����ͨ����ģ������������е��á��۲�����ʵ�ֿɿ����ڲ�������RegisterCommands������
	FMyCustomCommands::Register();

	//����UICommandList
	PluginCommandList = MakeShareable(new FUICommandList);
	//Ϊ����ӳ�����
	PluginCommandList->MapAction(
		FMyCustomCommands::Get().CommandA,
		FExecuteAction::CreateRaw(this,&FMyUICommandModule::CommandAAction),
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
	//Menu �˵�
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
	//������
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

	//������������ģ��
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
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

}

void FMyUICommandModule::ShutdownModule()
{
	//Unregister��TCommands�Ľӿڡ������������к�����������ص���Դ��ͨ����ģ��Ĺرպ����б����á�
	FMyCustomCommands::Unregister();

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyUICommandModule, MyUICommand)