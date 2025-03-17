// Fill out your copyright notice in the Description page of Project Settings.

#include "FSMAssetEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "GraphEditor.h"
#include "EditorStyle.h"
#include "GraphEditor/FSMActionMenu.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "FSM.h"
#include "GraphEditor/FSMGraph.h"
#include "GraphEditor/FSMGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ScopedTransaction.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "EdGraphUtilities.h"
#include "HAL/PlatformApplicationMisc.h"
#include "SNodePanel.h"
#include "GraphEditor/SchemaActions/FSMSchemaAction_NewComment.h"
#include "Kismet2/Kismet2NameValidators.h"
#include "Logging/TokenizedMessage.h"
#include "Toolkits/AssetEditorManager.h"
#include "CustomUICommands/SuperManagerUICommands.h"

#define LOCTEXT_NAMESPACE "FSMAssetEditorNativeNames"

FFSMAssetEditor::FFSMAssetEditor()
{
}

FFSMAssetEditor::~FFSMAssetEditor()
{
}

const FName FFSMAssetEditor::TabID_EditorGraphCanvas(TEXT("EditorGraphCanvas"));//FFSMAssetEditor::SpawnTab_GraphCanvas创建的

void FFSMAssetEditor::InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UFSM * ObjectToEdit)
{
	// 一个资源同时只允许一个编辑器编辑，尽管在这里只有这一种AssetEditor会编辑UFSM，但还是最好在初始化函数的一开始加上一句
	FAssetEditorManager::Get().CloseOtherEditors(ObjectToEdit, this);
	//UAssetEditorSubsystem.CloseOtherEditors();

	TargetFSM = ObjectToEdit;

	//创建 UEdGraph和SGraphEditor，并且返回SGraphEditor
	GraphEditorView = CreateGraphEditorWidget();
#if 0
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("FSMAssetEditor_Layout")
		->AddArea
		(//PrimaryArea Begin
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(//Toolbar Begin
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)//Toolbar End
			->Split
			(//Editor Begin
				FTabManager::NewStack()
				->SetSizeCoefficient(0.9f)
				->SetHideTabWell(true)
				->AddTab(TabID_EditorGraphCanvas, ETabState::OpenedTab)
			)//Editor End
		);//PrimaryArea End
#else
	// 借鉴的Edtor_Learning资产,发现和上面没啥区别。
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("FSMAssetEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()	
// 				->SetSizeCoefficient(0.9f)
// 				->SetHideTabWell(true)
				->AddTab(TabID_EditorGraphCanvas, ETabState::OpenedTab)
			)
		);
#endif

	//Extent toolbar here
	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		/*AppIdentifier=*/FName(TEXT("FSMAssetEditor")),
		Layout,
		/*bCreateDefaultStandaloneMenu=*/true,
		/*bCreateDefaultToolbar=*/true,
		ObjectToEdit);


//测试Toolbar
	if (FSMToolbarExtender.IsValid())
	{
		RemoveToolbarExtender(FSMToolbarExtender);
		FSMToolbarExtender.Reset();
	}
	FSMToolbarExtender = MakeShareable(new FExtender);
	FSMToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& InToolbarBuilder)
		{
 			InToolbarBuilder.BeginSection("Toolbar");
			{
				//扩展一个按钮
				InToolbarBuilder.AddToolBarButton(FSuperManagerUICommands::Get().UnlockActorSelection);
				//扩展一个SWidget
				InToolbarBuilder.AddWidget(CreateDebugWidget());

 			}
 			InToolbarBuilder.EndSection();
		
		})
	);


	//FAssetEditorToolkit父类的函数
	AddToolbarExtender(FSMToolbarExtender);
	//不调用RegenerateMenusAndToolbars函数则不会刷新ToolBar界面，也就不显示。
	RegenerateMenusAndToolbars();
}



void FFSMAssetEditor::OnNodeTitleCommitted(const FText & NewText, ETextCommit::Type CommitInfo, UEdGraphNode * NodeBeingChanged)
{
	if (NodeBeingChanged)
	{
		const FScopedTransaction Transaction(LOCTEXT("RenameNode", "Rename Node"));
		NodeBeingChanged->Modify();
		NodeBeingChanged->OnRenameNode(NewText.ToString());
	}
}

bool FFSMAssetEditor::OnNodeVerifyTitleCommit(const FText & NewText, UEdGraphNode * NodeBeingChanged, FText & OutErrorMessage)
{
	//Reference: FBlueprintEditor::OnNodeVerifyTitleCommit
	bool bValid(false);
	TSharedPtr<INameValidatorInterface> NameEntryValidator = nullptr;

	if (NodeBeingChanged && NodeBeingChanged->bCanRenameNode)
	{
		// Clear off any existing error message 
		NodeBeingChanged->ErrorMsg.Empty();
		NodeBeingChanged->bHasCompilerMessage = false;

		if (!NameEntryValidator.IsValid())
		{
			NameEntryValidator = FNameValidatorFactory::MakeValidator(NodeBeingChanged);
		}

		EValidatorResult VResult = NameEntryValidator->IsValid(NewText.ToString(), true);
		if (VResult == EValidatorResult::Ok)
		{
			bValid = true;
		}
		else if (GraphEditorView.IsValid())
		{
			EValidatorResult Valid = NameEntryValidator->IsValid(NewText.ToString(), false);

			NodeBeingChanged->bHasCompilerMessage = true;
			NodeBeingChanged->ErrorMsg = NameEntryValidator->GetErrorString(NewText.ToString(), Valid);
			NodeBeingChanged->ErrorType = EMessageSeverity::Error;
		}
	}
	NameEntryValidator.Reset();

	return bValid;
}

bool FFSMAssetEditor::GetBound(FSlateRect & Rect, float Padding)
{
	return GraphEditorView->GetBoundsForSelectedNodes(Rect, Padding);
}

void FFSMAssetEditor::OnRenameNode()
{
	auto bVisible = GraphEditorView->IsNodeTitleVisible(GetFirstSelectedNode(), /*bRequestRename = */true);
}

bool FFSMAssetEditor::CanRenameNodes() const
{
	auto SelectedNodes = GetSelectedNodes();
	if (SelectedNodes.Num() > 1) {
		return false;
	}
	return GetFirstSelectedNode()->bCanRenameNode;
}

void FFSMAssetEditor::SelectAllNodes()
{
	GraphEditorView->SelectAllNodes();
}

bool FFSMAssetEditor::CanSelectAllNodes() const
{
	return true;
}

void FFSMAssetEditor::DeleteSelectedNodes()
{
	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	GraphEditorView->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*NodeIt))
		{
			if (Node->CanUserDeleteNode())
			{
				FBlueprintEditorUtils::RemoveNode(nullptr, Node, true);
			}
		}
	}
}

bool FFSMAssetEditor::CanDeleteNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	bool bCanUserDeleteNode = false;

	if (SelectedNodes.Num() > 0)
	{
		for (UObject* NodeObject : SelectedNodes)
		{
			// If any nodes allow deleting, then do not disable the delete option
			UEdGraphNode* Node = Cast<UEdGraphNode>(NodeObject);
			if (Node->CanUserDeleteNode())
			{
				bCanUserDeleteNode = true;
				break;
			}
		}
	}

	return bCanUserDeleteNode;
}

void FFSMAssetEditor::OnCreateComment()
{
	if (GraphEditorView.IsValid())
	{
		if (UEdGraph* Graph = GraphEditorView->GetCurrentGraph())
		{
			if (const UEdGraphSchema* Schema = Graph->GetSchema())
			{
				if (Schema->IsA(UEdGraphSchema_K2::StaticClass()))
				{
					FFSMSchemaAction_NewComment CommentAction;
					CommentAction.PerformAction(Graph, NULL, GraphEditorView->GetPasteLocation());
				}
			}
		}
	}
}

TSharedRef<SDockTab> FFSMAssetEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs & Args) const
{
	check(Args.GetTabId() == TabID_EditorGraphCanvas);

	return SNew(SDockTab)
		.Label(LOCTEXT("EditorGraphCanvas", "Viewport"))
		[
			GraphEditorView.ToSharedRef()
		]; 
}

TSharedRef<class SGraphEditor> FFSMAssetEditor::CreateGraphEditorWidget()
{
	//Reference: FBlueprintEditor

	UEdGraph* Graph = TargetFSM->GraphView;

	if (!Graph) 
	{
		//此处将FSM资产对象传递为图表的Outer，便于后续通过GetOuter()对应的 UFSMGraph::GetFSM()去获取状态机。
		Graph = FBlueprintEditorUtils::CreateNewGraph(TargetFSM, NAME_None, UFSMGraph::StaticClass(), UFSMGraphSchema::StaticClass());
		Graph->GetSchema()->CreateDefaultNodesForGraph(*Graph);
		Graph->bAllowDeletion = false;
		TargetFSM->GraphView = Graph;
	}

	// 自定义图形的外观
	FGraphAppearanceInfo AppearanceInfo;
	// 显示在图形视图右下角的文本。
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_FSM", "FSM");
	AppearanceInfo.InstructionText = LOCTEXT("AppearanceInstructionText_FSM", "Right Click to add new nodes.");

	// 从编辑器绑定图形事件操作
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnVerifyTextCommit = FOnNodeVerifyTextCommit::CreateSP(this, &FFSMAssetEditor::OnNodeVerifyTitleCommit);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FFSMAssetEditor::OnNodeTitleCommitted);
	//InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FFSMAssetEditor::OnSelectedNodesChanged);

	// 如果SGraphEditor::FOnCreateActionMenu代理没有绑定则默认创建SGraphEditorActionMenu。反之如果被绑定，则只指向绑定的函数。
	InEvents.OnCreateActionMenu = SGraphEditor::FOnCreateActionMenu::CreateSP(this, &FFSMAssetEditor::OnCreateGraphActionMenu);
	/*
		SFSMActionMenu（继承自SBorder）抑或是直接用SGraphEditorMenu都可以，
		我这里自定义了一个SFSMActionMenu封装了一下，和SGraphEditorMenu并没有什么区别
	*/

#pragma region GraphEditorCommands
	// 不需要重新生成命令。
	if (!GraphEditorCommands.IsValid())
	{
		GraphEditorCommands = MakeShareable(new FUICommandList);
		{

			GraphEditorCommands->MapAction(FGenericCommands::Get().Rename,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::OnRenameNode),
				FCanExecuteAction::CreateSP(this, &FFSMAssetEditor::CanRenameNodes)
			);

			// Editing commands
			GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::SelectAllNodes),
				FCanExecuteAction::CreateSP(this, &FFSMAssetEditor::CanSelectAllNodes)
			);

			GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::DeleteSelectedNodes),
				FCanExecuteAction::CreateSP(this, &FFSMAssetEditor::CanDeleteNodes)
			);

			//I don't think it's allowed to cut/copy/paste
			/*GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::CopySelectedNodes),
				FCanExecuteAction::CreateSP(this, &FFSMAssetEditor::CanCopyNodes)
			);

			GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::CutSelectedNodes),
				FCanExecuteAction::CreateSP(this, &FFSMAssetEditor::CanCutNodes)
			);

			GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::PasteNodes),
				FCanExecuteAction::CreateSP(this, &FFSMAssetEditor::CanPasteNodes)
			);

			GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::DuplicateNodes),
				FCanExecuteAction::CreateSP(this, &FFSMAssetEditor::CanDuplicateNodes)
			);*/

			GraphEditorCommands->MapAction(FGraphEditorCommands::Get().CreateComment,
				FExecuteAction::CreateSP(this, &FFSMAssetEditor::OnCreateComment)
			);

			//override for append command
			//OnCreateGraphEditorCommands(GraphEditorCommands);
		}
	}

	// Append play world commands
	//GraphEditorCommands->Append(FPlayWorldCommands::GlobalPlayWorldActions.ToSharedRef());
#pragma endregion 
	/*TSharedRef<SGraphEditor> Editor = SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(this, &FBlueprintEditor::IsEditable, InGraph)
		.DisplayAsReadOnly(this, &FBlueprintEditor::IsGraphReadOnly, InGraph)
		.TitleBar(TitleBarWidget)
		.Appearance(this, &FBlueprintEditor::GetGraphAppearance, InGraph)
		.GraphToEdit(InGraph)
		.GraphEvents(InEvents)
		.OnNavigateHistoryBack(FSimpleDelegate::CreateSP(this, &FBlueprintEditor::NavigateTab, FDocumentTracker::NavigateBackwards))
		.OnNavigateHistoryForward(FSimpleDelegate::CreateSP(this, &FBlueprintEditor::NavigateTab, FDocumentTracker::NavigateForwards));*/
	
	//创建SGraphEditor
	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(Graph)
		.GraphEvents(InEvents)
		.ShowGraphStateOverlay(false);
}

FActionMenuContent FFSMAssetEditor::OnCreateGraphActionMenu(UEdGraph* Graph, const FVector2D& NodePosition,
	const TArray<UEdGraphPin*>& DraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed OnMenuClosed)
{
	const TSharedRef<SFSMActionMenu> ActionMenu = SNew(SFSMActionMenu)
		.Graph(Graph)
		.NewNodePosition(NodePosition)
		.DraggedFromPins(DraggedPins)
		.AutoExpandActionMenu(bAutoExpand)
		.OnClosedCallback(OnMenuClosed)
		.OnCloseReason(this, &FFSMAssetEditor::OnGraphActionMenuClosed);

	return FActionMenuContent(ActionMenu, ActionMenu->GetFilterTextBox());
}

void FFSMAssetEditor::OnGraphActionMenuClosed(bool bActionExecuted, bool bGraphPinContext)
{
}

FGraphPanelSelectionSet FFSMAssetEditor::GetSelectedNodes() const
{
	return GraphEditorView->GetSelectedNodes();
}

UEdGraphNode * FFSMAssetEditor::GetFirstSelectedNode() const
{
	auto SelectedNodes = GetSelectedNodes();
	if (SelectedNodes.Num() == 0) {
		return nullptr;
	}
	return Cast<UEdGraphNode>(SelectedNodes[FSetElementId::FromInteger(0)]);
}

TSharedRef<SWidget> FFSMAssetEditor::CreateDebugWidget()
{
	{
		DebugObjectsComboBox = SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&DebugComboBoxSourceItems)
		.OnComboBoxOpening(this,&FFSMAssetEditor::DebugOnComboBoxOpening)	//每次打开这个ComboBox时触发。在OnGenerateWidget之前。
		.OnGenerateWidget(this, &FFSMAssetEditor::GenerateContentInDebugComboBox)	//遍历OptionsSource的数据源，对应生成每一行S，但是每一行的具体Slate形式还是自己去创建
		.OnSelectionChanged(this,&FFSMAssetEditor::DebugOnComboSelectionChanged)
		[
			SAssignNew(DebugDiplayText, STextBlock)
			.Text(FText::FromString(TEXT("No debug object selected")))	//将默认未选择的提示语跟DebugComboBoxSourceItems[0]设一样，因为SetSelectedItem(0)我们是放在OnComboBoxOpening里调用的，慢了一拍
		];
	}


	TSharedRef<SWidget> DebugObjectSelectionWidget =
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			DebugObjectsComboBox.ToSharedRef()
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(2.0f);


	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Bottom)
		[
			DebugObjectSelectionWidget
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		.Padding(2.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("DebugSelectTitle", "Debug Filter"))
		];
	
}

void FFSMAssetEditor::DebugOnComboBoxOpening()
{
	// 判断上一次的选择是有效的，
	if (LastSelectDebugItem.IsValid() && DebugComboBoxSourceItems.Contains(LastSelectDebugItem))
	{
		DebugObjectsComboBox->SetSelectedItem(LastSelectDebugItem.Pin());
	}
	else
	{
		DebugComboBoxSourceItems.Empty();
		DebugComboBoxSourceItems.Add(MakeShared<FString>("No debug object selected"));
		DebugComboBoxSourceItems.Add(MakeShared<FString>("A"));
		DebugComboBoxSourceItems.Add(MakeShared<FString>("B"));

		//可以由某些条件然后设置为新增的某个选项，有点相当于每次打开默认都是
		DebugObjectsComboBox->SetSelectedItem(DebugComboBoxSourceItems[0]);
	}
}

TSharedRef<SWidget> FFSMAssetEditor::GenerateContentInDebugComboBox(TSharedPtr<FString> SourceItem)
{
	TSharedRef <STextBlock> ContructedComboText = SNew(STextBlock)
		.Text(FText::FromString(*SourceItem.Get()));

	return ContructedComboText;
}

void FFSMAssetEditor::DebugOnComboSelectionChanged(TSharedPtr<FString> SelectedOption, ESelectInfo::Type InSelectInfo)
{
	DebugDiplayText->SetText(FText::FromString(*SelectedOption.Get()));
	LastSelectDebugItem = SelectedOption;	//缓存上次的选择

	//UE_LOG(LogTemp,Warning, TEXT("%s"), **LastSelectDebugItem.Pin());
}

void FFSMAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	//不明	    DeepSeek说是在编辑器菜单中创建独立的分类。但是并未找到
	InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_FSMAssetEditor", "FSM Asset Editor"));
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	//调用父类的相当于Super::
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	//注册SDockTab，一个新的窗口一般
	InTabManager->RegisterTabSpawner(TabID_EditorGraphCanvas, FOnSpawnTab::CreateSP(this, &FFSMAssetEditor::SpawnTab_GraphCanvas))
		.SetDisplayName(LOCTEXT("GraphCanvasTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));
}

void FFSMAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	//调用父类的相当于Super::
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	//取消注册的SDockTab
	InTabManager->UnregisterTabSpawner(TabID_EditorGraphCanvas);
}


#undef LOCTEXT_NAMESPACE