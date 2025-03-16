
#include "MyGraph/MyUGraphNode.h"
#include "EdGraphSchema_K2.h"


UMyGraphNode::UMyGraphNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMyGraphNode::AllocateDefaultPins()
{
	//����1:���뻹���������
	//����2:����Category�����ܿ������ڸ�������ѯ���š�
	//����3:��������
	InputPin1 = CreatePin(EEdGraphPinDirection::EGPD_Input, NAME_None, NAME_None);

	InputPin2 =CreatePin(EEdGraphPinDirection::EGPD_Input, UEdGraphSchema_K2::PC_Boolean, NAME_None);
	OutputPin = CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("UMyGraphNode_Category"), TEXT("OutputPin"));
}

FText UMyGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	//�ڵ������
	return FText::FromString(TestInfo);
}
