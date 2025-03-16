#include "GraphEditor/SchemaActions/FSMSchemaAction_NewNode.h"
#include "UnrealEd.h"
#include "Math/UnrealMath.h"
#include "ScopedTransaction.h"
#include "FSM.h"
#include "GraphEditor/FSMGraph.h"
#include "GraphEditor/Nodes/FSMGraphNode.h"

#define LOCTEXT_NAMESPACE "FSMAssetEditorNativeNames"

UEdGraphNode * FFSMSchemaAction_NewNode::PerformAction(UEdGraph * ParentGraph, UEdGraphPin * FromPin, const FVector2D Location, bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("EditorNewNode", "FSM Editor: New Node"));
	UFSM* FSM = CastChecked<UFSMGraph>(ParentGraph)->GetFSM();

	// 创建后续节点的数据名，然后先添加到资产Asset中。
	FString NodeNameStr = FString("NewNode_");
	NodeNameStr.AppendInt(FMath::RandRange(0, 1000));		//Temporary
	FName NewStateNode(*NodeNameStr);

	FSM->AddState(NewStateNode);

	//UObject::Modify()说是如果直接修改属性而不告诉游戏引擎，引擎就不知道这个变化需要被记录，可能导致你无法撤销操作或保存失败。
	//看样子应该就是保存了？
	verify(FSM->Modify());
	// Mark for modification
	verify(ParentGraph->Modify());

	if (FromPin)
	{
		verify(FromPin->Modify());
	}

	// Maximum distance a drag can be off a node edge to require 'push off' from node
	//constexpr int32 NodeDistance = 60;

	// 创建图表的常规流程
	FGraphNodeCreator<UFSMGraphNode> NodeCreator(*ParentGraph);
	UFSMGraphNode* GraphNode = NodeCreator.CreateUserInvokedNode(bSelectNewNode);//内部包含了 AddNode(NewNode, bFromUI, bSelectNewNode);

	//GraphNode->SetFlags(RF_Transactional);	//这一步骤感觉没必要，UEdGraph::CreateNode-->NewObject<UEdGraphNode>参数传递的Flag就是这个。
	GraphNode->Rename(*(FString("GraphNode_") + NodeNameStr), ParentGraph);	//修改UObject::NamePrivate名称
	GraphNode->SetName(NewStateNode);	//UFSMGraphNode自定义的函数

	// 完成图表的创建
	NodeCreator.Finalize(); // 在节点上调用：CreateNewGuid， PostPlacedNewNode, AllocateDefaultPins

	// 如果是从一个节点引脚拖拽出来的，就尝试连接
	if (FromPin)
	{
		GraphNode->AutowireNewNode(FromPin);	//该函数需要自己实现，父类是空的
	}

	//节点坐标位置
	GraphNode->NodePosX = Location.X;
	GraphNode->NodePosY = Location.Y;
	//ResultNode->SnapToGrid(SNAP_GRID);
	
	//拥有这个U图表的资产刷新吧
	FSM->PostEditChange();
	FSM->MarkPackageDirty();

	//图表修改的回调。
	ParentGraph->NotifyGraphChanged();

	return GraphNode;
}
#undef LOCTEXT_NAMESPACE