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
		FText::FromString("category_test")			//InNodeCategory	节点分类
		, FText::FromString("test")					//InMenuDesc		在菜单中的描述
		, FText::FromString("test_tooltip")			//InToolTip			鼠标悬浮时的提示
		, 0	//InGrouping:							//这是一个优先级数字，用于覆盖操作列表中的字母顺序(更高的值==列表中更高的值)				
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
		FText::FromString("CreateNode")				//InNodeCategory	节点分类
		, FText::FromString("NewNode")				//InMenuDesc		在菜单中的描述
		, FText::FromString("Create a new Node")	//InToolTip			鼠标悬浮时的提示
		, 0	//InGrouping:							//这是一个优先级数字，用于覆盖操作列表中的字母顺序(更高的值==列表中更高的值)				
	) {};

	/*--------------------点击菜单中的选项后，所执行的行为----------------*/
	// FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	// End of FEdGraphSchemaAction interface
};