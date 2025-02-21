#include "MyAssetEditorToolkit.h"
#include "MyAsset.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "MyTest"

const FName TestTabId(TEXT("YaksueTestAssetEditor_TestTab"));

FName FMyAssetEditorToolkit::GetToolkitFName() const
{
	return FName("MyAssetName");
}

FText FMyAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("MyAssetToolkitName", "MyAssetToolkitName");
}

FString FMyAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("MyAssetTabPrefix", "MyAssetTabPrefix").ToString();
}

FLinearColor FMyAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0.5f, 0.6f, 0.5f);
}


TSharedRef<SDockTab> FMyAssetEditorToolkit::SpawnTestTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()
			[
				SAssignNew(NumberText,STextBlock)
				.Text(FText::FromString(FString::FromInt(EditingAsset->TestData)))
			]
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("TestJoJo!"))
				.OnClicked_Lambda([this]() 
				{
					EditingAsset->TestData++; 
					NumberText->SetText(FText::FromString(FString::FromInt(EditingAsset->TestData)));
					return FReply::Handled();
				})
			]

		];
}

void FMyAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(FName("MyTabID"), FOnSpawnTab::CreateSP(this, &FMyAssetEditorToolkit::SpawnTestTab))
		.SetDisplayName(LOCTEXT("MyAssetTestTab", "MyAssetTestTab"));
}

void FMyAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(FName("MyTabID"));
}

void FMyAssetEditorToolkit::Initialize(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UMyAsset* Asset)
{
	EditingAsset = Asset;

	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("MyAssetEditorToolkit_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()//����һ��FArea
			->Split
			(
				FTabManager::NewStack()	////����һ��FStack�̳���FLayoutNode
				->SetSizeCoefficient(0.7f)
				->AddTab(FName("TestTab"), ETabState::OpenedTab)
			)
#if 0
	//�����������µģ�����Ч��������һ����
			FTabManager::NewPrimaryArea()	//����һ��FArea
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()		//����һ��FSplitter�̳���FLayoutNode
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()			//����һ��FStack�̳���FLayoutNode
					->SetSizeCoefficient(0.7f)
					->AddTab(FName("MyTabID"), ETabState::OpenedTab)
				)
			)
#endif
		);

	const bool bCreateDefaultStandaloneMenu = true;	// �����˵���
	const bool bCreateDefaultToolbar = true;	// ������ToolBar
	const FName AppIdentifier = TEXT("MyAssetEditor");
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, AppIdentifier, Layout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, Asset);
}

#undef LOCTEXT_NAMESPACE



