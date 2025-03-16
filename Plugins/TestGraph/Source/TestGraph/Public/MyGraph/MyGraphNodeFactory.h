#pragma once

#include "EdGraphUtilities.h"
#include "Templates/SharedPointer.h"

#include "EdGraphUtilities.h"
#include "MyUGraphNode.h"
#include "MySGraphNode.h"


//����ͼ��ڵ㹤��
class FMyGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		//�ж��Ƿ�����������봴����Node
		if (UMyGraphNode* YaksueGraphNode = Cast<UMyGraphNode>(Node))
		{
			return SNew(SMyGraphNode, YaksueGraphNode);
		}
		return nullptr;
	}
};
