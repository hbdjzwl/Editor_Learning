#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphSchema.h"
#include "MyEdGraphSchemaAction.generated.h"


USTRUCT()
struct FMyGraphSchemaAction_Test : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()

public:

	FMyGraphSchemaAction_Test() :FEdGraphSchemaAction(
		FText::FromString("category_test")			//InNodeCategory	�ڵ����
		, FText::FromString("test")					//InMenuDesc		�ڲ˵��е�����
		, FText::FromString("test_tooltip")			//InToolTip			�������ʱ����ʾ
		, 0	//InGrouping:							//����һ�����ȼ����֣����ڸ��ǲ����б��е���ĸ˳��(���ߵ�ֵ==�б��и��ߵ�ֵ)				
	) {};

	// FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	// End of FEdGraphSchemaAction interface
};


USTRUCT()
struct FMyGraphSchemaAction_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()

public:

	FMyGraphSchemaAction_NewNode() :FEdGraphSchemaAction(
		FText::FromString("CreateNode")				//InNodeCategory	�ڵ����
		, FText::FromString("NewNode")				//InMenuDesc		�ڲ˵��е�����
		, FText::FromString("Create a new Node")	//InToolTip			�������ʱ����ʾ
		, 0	//InGrouping:							//����һ�����ȼ����֣����ڸ��ǲ����б��е���ĸ˳��(���ߵ�ֵ==�б��и��ߵ�ֵ)				
	) {};

	/*--------------------����˵��е�ѡ�����ִ�е���Ϊ----------------*/
	// FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	// End of FEdGraphSchemaAction interface
};