
#include "MyGraph/MyUGraphNode.h"
#include "EdGraphSchema_K2.h"


UMyGraphNode::UMyGraphNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMyGraphNode::AllocateDefaultPins()
{
	//参数1:输入还是输出引脚
	//参数2:类别吧Category，可能可以用于根据类别查询引脚。
	//参数3:引脚名字
	InputPin1 = CreatePin(EEdGraphPinDirection::EGPD_Input, NAME_None, NAME_None);

	InputPin2 =CreatePin(EEdGraphPinDirection::EGPD_Input, UEdGraphSchema_K2::PC_Boolean, NAME_None);
	OutputPin = CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("UMyGraphNode_Category"), TEXT("OutputPin"));
}

FText UMyGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	//节点的名称
	return FText::FromString(TestInfo);
}
