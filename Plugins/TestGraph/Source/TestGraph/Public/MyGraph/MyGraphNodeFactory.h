#pragma once

#include "EdGraphUtilities.h"
#include "Templates/SharedPointer.h"

#include "EdGraphUtilities.h"
#include "MyUGraphNode.h"
#include "MySGraphNode.h"


//定义图表节点工厂
class FMyGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		//判断是否是这个工厂想创建的Node
		if (UMyGraphNode* YaksueGraphNode = Cast<UMyGraphNode>(Node))
		{
			return SNew(SMyGraphNode, YaksueGraphNode);
		}
		return nullptr;
	}
};
