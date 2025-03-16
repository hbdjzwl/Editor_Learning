#pragma once

#pragma once

#include "CoreTypes.h"
#include "EdGraph/EdGraphSchema.h"

#include "FSMGraphSchema.generated.h"

class UDialogueGraphNode;

UCLASS()
class UFSMGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
public:
	/**
	 * ��ͼ��հ״��Ҽ� �� ��ĳ���ڵ��Pin�Ϸ��ͷ� ���Խ��еĲ���
	 *
	 * @param [in,out]	ContextMenuBuilder	�����ģ�ͼ�Ρ��϶������ŵȣ�������˵���������
	 */
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	/**
	 * �Ҽ����һ���ڵ���Ҽ����һ������ʱ ���Խ��еĲ���
	 *
	 * @param	CurrentGraph		The current graph.
	 * @param	InGraphNode			The node to get the context menu for, if any.
	 * @param	InGraphPin			The pin clicked on, if any, to provide additional context
	 * @param	MenuBuilder			The menu builder to append actions to.
	 * @param	bIsDebugging		Is the graph editor currently part of a debugging session (any non-debugging commands should be disabled)
	 */
	//virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;
	virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const;

	/**
	 * ���κ�Ĭ�Ͻڵ������ͼ�����ƶ���ͼ���ܻ���һ����ڣ�����ͼ��Ҳ�ǡ�
	 *
	 * @param	Graph			Graph to add the default nodes to
	 */
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;

	/** Copies pin links from one pin to another without breaking the original links */
	//virtual FPinConnectionResponse CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy = false) const override;

	/**
	 * ȷ����������֮���Ƿ���Խ������ӡ�
	 *
	 * @param	PinA	The first pin.
	 * @param	PinB	The second pin.
	 *
	 * @return	An empty string if the connection is legal, otherwise a message describing why the connection would fail.
	 */
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;

	/**
	 * ���Ž�����������������������FPinConnectionResponse�ṩ��CreateAutomaticConversionNodeAndConnections����ʹ�á�
	 *
	 * @param	PinA	The first pin.
	 * @param	PinB	The second pin.
	 *
	 * @return	���������/�Ͽ������ӣ�ͼ���޸ģ�����Ϊ�棻�������ʧ����û�в��������ã���Ϊ�١�
	 */
	virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;

	/**
	 * �Խڵ��Ҽ�BreakNodeLinksѡ��ϵ�����ڵ������Pin����������(��Node������Pin��������)
	 *
	 * @param	TargetNode	The node to break links on
	 */
	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;

	/**
	 * �ϵ�һ������Pin����������(��1��Pin��������)
	 *
	 * @param	TargetPin	The pin to break links on
	 * @param	bSendsNodeNotifcation	whether to send a notification to the node post pin connection change
	 */
	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;

	/**
	 * �ϵ�һ�����ŵ�����һ�����ŵģ���������(��1����)
	 *
	 * @param	SourcePin	The pin where the link begins.
	 * @param	TargetPin	The pin where the link ends.
	 */
	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;

	//  ������״̬���еĹ��ɽڵ㡣
	// 
	//  ԭ��ע��:
	//  ���Դ���һ���Զ�ת���ڵ������ת���ڵ㣬�Է�����������֮������ӡ�������һ��ת���ڵ㣬A ��ת���ڵ�֮������ӣ��Լ���ת���ڵ㵽 B �����ӡ�
	//  �� CanCreateConnection ���� bCanAutoConvert ʱ������ô˷������������ӡ�
	// 
	// switch:��UFSMGraphSchema::CanCreateConnection�ķ��ز���ΪCONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE�Ż�������溯��
	virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;

private:
	static const FText NODE_CATEGORY;
	static const FText CREATE_NODE_DESC;
	static const FText CREATE_NODE_TOOL_TIP;

	static const FText GRAPH_CATEGORY;

public:
	static const FName PC_Trans;
	static const FName PC_Entry;
};