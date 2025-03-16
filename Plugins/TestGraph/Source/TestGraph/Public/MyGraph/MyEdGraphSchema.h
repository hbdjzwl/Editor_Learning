#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphSchema.h"
#include "MyEdGraphSchema.generated.h"


UCLASS(MinimalAPI)
class UMyEdGraphSchema : public UEdGraphSchema
{ 
	GENERATED_UCLASS_BODY()

	//�Ƿ�����ӽڵ������
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	//�Ҽ���ӽڵ���ק����Pin���հ״�ʱ��ʾ����Ϊ�˵���
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	//���û��Ҽ����һ���ڵ���Ҽ����һ������ʱ���Խ��еĲ�����
	void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	//Pin���ŵ����ɫ
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const { return FLinearColor::Yellow; }
};
