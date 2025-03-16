#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphSchema.h"
#include "MyEdGraphSchema.generated.h"


UCLASS(MinimalAPI)
class UMyEdGraphSchema : public UEdGraphSchema
{ 
	GENERATED_UCLASS_BODY()

	//是否可连接节点的引脚
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	//右键或从节点拖拽出的Pin到空白处时显示的行为菜单。
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	//当用户右键点击一个节点或右键点击一个引脚时可以进行的操作。
	void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	//Pin引脚点的颜色
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const { return FLinearColor::Yellow; }
};
