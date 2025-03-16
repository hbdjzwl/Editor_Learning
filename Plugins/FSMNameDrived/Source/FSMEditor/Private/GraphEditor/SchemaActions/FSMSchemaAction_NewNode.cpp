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

	// ���������ڵ����������Ȼ������ӵ��ʲ�Asset�С�
	FString NodeNameStr = FString("NewNode_");
	NodeNameStr.AppendInt(FMath::RandRange(0, 1000));		//Temporary
	FName NewStateNode(*NodeNameStr);

	FSM->AddState(NewStateNode);

	//UObject::Modify()˵�����ֱ���޸����Զ���������Ϸ���棬����Ͳ�֪������仯��Ҫ����¼�����ܵ������޷����������򱣴�ʧ�ܡ�
	//������Ӧ�þ��Ǳ����ˣ�
	verify(FSM->Modify());
	// Mark for modification
	verify(ParentGraph->Modify());

	if (FromPin)
	{
		verify(FromPin->Modify());
	}

	// Maximum distance a drag can be off a node edge to require 'push off' from node
	//constexpr int32 NodeDistance = 60;

	// ����ͼ��ĳ�������
	FGraphNodeCreator<UFSMGraphNode> NodeCreator(*ParentGraph);
	UFSMGraphNode* GraphNode = NodeCreator.CreateUserInvokedNode(bSelectNewNode);//�ڲ������� AddNode(NewNode, bFromUI, bSelectNewNode);

	//GraphNode->SetFlags(RF_Transactional);	//��һ����о�û��Ҫ��UEdGraph::CreateNode-->NewObject<UEdGraphNode>�������ݵ�Flag���������
	GraphNode->Rename(*(FString("GraphNode_") + NodeNameStr), ParentGraph);	//�޸�UObject::NamePrivate����
	GraphNode->SetName(NewStateNode);	//UFSMGraphNode�Զ���ĺ���

	// ���ͼ��Ĵ���
	NodeCreator.Finalize(); // �ڽڵ��ϵ��ã�CreateNewGuid�� PostPlacedNewNode, AllocateDefaultPins

	// ����Ǵ�һ���ڵ�������ק�����ģ��ͳ�������
	if (FromPin)
	{
		GraphNode->AutowireNewNode(FromPin);	//�ú�����Ҫ�Լ�ʵ�֣������ǿյ�
	}

	//�ڵ�����λ��
	GraphNode->NodePosX = Location.X;
	GraphNode->NodePosY = Location.Y;
	//ResultNode->SnapToGrid(SNAP_GRID);
	
	//ӵ�����Uͼ����ʲ�ˢ�°�
	FSM->PostEditChange();
	FSM->MarkPackageDirty();

	//ͼ���޸ĵĻص���
	ParentGraph->NotifyGraphChanged();

	return GraphNode;
}
#undef LOCTEXT_NAMESPACE