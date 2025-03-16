#include "MyGraph/MyEdGraphSchemaAction.h"
#include "Misc/MessageDialog.h"
#include "MyGraph/MyEdGraph.h"
#include "MyGraph/MyUGraphNode.h"

UEdGraphNode* FMyGraphSchemaAction_Test::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	if (FromPin)//如果有引脚(从某个节点的引脚拖拽出来的列表)
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("GragPin Drag"));
	else
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("MouseRight Click"));

	return nullptr;
}

UEdGraphNode* FMyGraphSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	//转换为UEdGraph_Yaksue类型
	UMyEdGraph* Graph = Cast<UMyEdGraph>(ParentGraph);

	//创建新节点
	UMyGraphNode* NewNode = Graph->CreateMyNode();

	//设置信息、节点的位置
	NewNode->TestInfo = "NewNode";
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;

	//如果有引脚则连接新节点的InputPin1引脚上去。
	if (FromPin)
		Graph->GetSchema()->TryCreateConnection(FromPin, NewNode->InputPin1);

	return nullptr;
}
