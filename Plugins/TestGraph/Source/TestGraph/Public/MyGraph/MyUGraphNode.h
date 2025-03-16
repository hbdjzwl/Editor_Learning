#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"

#include "MyUGraphNode.generated.h"


UCLASS()
class UMyGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

	// UEdGraphNode implementation
	virtual void AllocateDefaultPins() override;
	// End UEdGraphNode implementation

	//如果SGraphNode使用默认的UpdateGraphNode。则最终会从该函数读取节点名称。
	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;



	//输入引脚
	UEdGraphPin* InputPin1;
	UEdGraphPin* InputPin2;

	//输出引脚
	UEdGraphPin* OutputPin;

	//名字
	FString TestInfo;
};
