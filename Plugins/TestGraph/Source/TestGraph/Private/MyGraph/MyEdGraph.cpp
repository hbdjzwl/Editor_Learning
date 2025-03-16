
#include "MyGraph/MyEdGraph.h"
#include "MyGraph/MyUGraphNode.h"

UMyEdGraph::UMyEdGraph(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UMyEdGraph::RebuildGraph()
{
// 	//�����ڵ�,��Ҫ�ֶ�����AlloPins�Ⱥ�����
// 	auto Node = CreateNode(UMyGraphNode::StaticClass());
// 	//Ҫ��������ж�ק���ߣ�����ִ��1��3
// 	Node->CreateNewGuid();			//1
// 	Node->PostPlacedNewNode();		//2
// 	Node->AllocateDefaultPins();	//3
	
	//����һ���ڵ�
	Node1 = CreateMyNode();
	Node1->TestInfo = "A";

	//������һ���ڵ������������ӹ�ϵ
	Node2 = CreateMyNode();
	Node2->TestInfo = "B";
	Node2->NodePosX += 300;

}

UMyGraphNode* UMyEdGraph::CreateMyNode()
{
	//FGraphNodeCreator��һ�������࣬����ȷ��һ���ڵ���Ա���ȷ������
	FGraphNodeCreator<UMyGraphNode> NodeCreator(*this);
	UMyGraphNode* result = NodeCreator.CreateNode();

	//ͨ���ڵ����ִ����ڵ�����Finalize()��1.����Gui��2.PostPlacedNewNode.3.��������
	NodeCreator.Finalize();
	return result;
}

void UMyEdGraph::TestFunc()
{
	//Ҫ��ʾ����Ϣ��
	FString Message = "TestFunc():";

	for (auto p : Node1->OutputPin->LinkedTo)//�������е�����
	{
		//��ʾ����Ϣ�����TestInfo
		Message += ((UMyGraphNode*)p->GetOwningNode())->TestInfo;
	}

	//��ʾ�Ի���
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
}
