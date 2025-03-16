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

	//���SGraphNodeʹ��Ĭ�ϵ�UpdateGraphNode�������ջ�Ӹú�����ȡ�ڵ����ơ�
	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;



	//��������
	UEdGraphPin* InputPin1;
	UEdGraphPin* InputPin2;

	//�������
	UEdGraphPin* OutputPin;

	//����
	FString TestInfo;
};
