#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraph.h"
#include "MyEdGraph.generated.h"


UCLASS()
class UMyEdGraph : public UEdGraph
{
	GENERATED_UCLASS_BODY()

	//重新构建图表
	void RebuildGraph();

	//创建一个节点
	class UMyGraphNode* CreateMyNode();


	//记录下测试创建的节点，用来随后的测试
	void TestFunc();
	class UMyGraphNode* Node1;
	class UMyGraphNode* Node2;

};
