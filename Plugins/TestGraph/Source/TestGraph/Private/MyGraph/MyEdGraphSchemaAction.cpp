#include "MyGraph/MyEdGraphSchemaAction.h"
#include "Misc/MessageDialog.h"
#include "MyGraph/MyEdGraph.h"
#include "MyGraph/MyUGraphNode.h"

UEdGraphNode* FMyGraphSchemaAction_Test::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	if (FromPin)//���������(��ĳ���ڵ��������ק�������б�)
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("GragPin Drag"));
	else
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("MouseRight Click"));

	return nullptr;
}

UEdGraphNode* FMyGraphSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	//ת��ΪUEdGraph_Yaksue����
	UMyEdGraph* Graph = Cast<UMyEdGraph>(ParentGraph);

	//�����½ڵ�
	UMyGraphNode* NewNode = Graph->CreateMyNode();

	//������Ϣ���ڵ��λ��
	NewNode->TestInfo = "NewNode";
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;

	//����������������½ڵ��InputPin1������ȥ��
	if (FromPin)
		Graph->GetSchema()->TryCreateConnection(FromPin, NewNode->InputPin1);

	return nullptr;
}
