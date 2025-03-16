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

	//创建每个节点里UI展示的细节
	// SGraphNode implementation
//	virtual void UpdateGraphNode() override;
	// End SGraphNode implementation



	//节点UI的下部分。引脚那块的(非标题) 如果想重写自己的引脚的话可以覆盖它
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
};