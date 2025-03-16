#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraph.h"
#include "MyEdGraph.generated.h"


UCLASS()
class UMyEdGraph : public UEdGraph
{
	GENERATED_UCLASS_BODY()

	//���¹���ͼ��
	void RebuildGraph();

	//����һ���ڵ�
	class UMyGraphNode* CreateMyNode();


	//��¼�²��Դ����Ľڵ㣬�������Ĳ���
	void TestFunc();
	class UMyGraphNode* Node1;
	class UMyGraphNode* Node2;

};
