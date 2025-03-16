
#include "MyGraph/MyEdGraph.h"
#include "MyGraph/MyUGraphNode.h"

UMyEdGraph::UMyEdGraph(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UMyEdGraph::RebuildGraph()
{
// 	//创建节点,需要手动调用AlloPins等函数。
// 	auto Node = CreateNode(UMyGraphNode::StaticClass());
// 	//要想从引脚中多拽出线，必须执行1和3
// 	Node->CreateNewGuid();			//1
// 	Node->PostPlacedNewNode();		//2
// 	Node->AllocateDefaultPins();	//3
	
	//创建一个节点
	Node1 = CreateMyNode();
	Node1->TestInfo = "A";

	//创建另一个节点用来测试连接关系
	Node2 = CreateMyNode();
	Node2->TestInfo = "B";
	Node2->NodePosX += 300;

}

UMyGraphNode* UMyEdGraph::CreateMyNode()
{
	//FGraphNodeCreator是一个助手类，负责确保一个节点可以被正确构建。
	FGraphNodeCreator<UMyGraphNode> NodeCreator(*this);
	UMyGraphNode* result = NodeCreator.CreateNode();

	//通过节点助手创建节点后调用Finalize()。1.分配Gui。2.PostPlacedNewNode.3.分配引脚
	NodeCreator.Finalize();
	return result;
}

void UMyEdGraph::TestFunc()
{
	//要显示的信息：
	FString Message = "TestFunc():";

	for (auto p : Node1->OutputPin->LinkedTo)//访问所有的引脚
	{
		//显示的信息中添加TestInfo
		Message += ((UMyGraphNode*)p->GetOwningNode())->TestInfo;
	}

	//显示对话框
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
}
