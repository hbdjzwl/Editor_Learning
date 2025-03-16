#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SGraphNode.h"

class UMyGraphNode;

class SMyGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SMyGraphNode) {}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, UMyGraphNode* InNode);

	//����ÿ���ڵ���UIչʾ��ϸ��
	// SGraphNode implementation
//	virtual void UpdateGraphNode() override;
	// End SGraphNode implementation



	//�ڵ�UI���²��֡������ǿ��(�Ǳ���) �������д�Լ������ŵĻ����Ը�����
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
};