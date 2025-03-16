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
	 * 对图表空白处右键 或 从某个节点的Pin拖放释放 可以进行的操作
	 *
	 * @param [in,out]	ContextMenuBuilder	上下文（图形、拖动的引脚等）和输出菜单生成器。
	 */
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	/**
	 * 右键点击一个节点或右键点击一个引脚时 可以进行的操作
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
	 * 用任何默认节点填充新图，类似动画图表总会有一个入口，函数图表也是。
	 *
	 * @param	Graph			Graph to add the default nodes to
	 */
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;

	/** Copies pin links from one pin to another without breaking the original links */
	//virtual FPinConnectionResponse CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy = false) const override;

	/**
	 * 确定两个引脚之间是否可以建立连接。
	 *
	 * @param	PinA	The first pin.
	 * @param	PinB	The second pin.
	 *
	 * @return	An empty string if the connection is legal, otherwise a message describing why the connection would fail.
	 */
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;

	/**
	 * 试着将两个引脚连接起来，返回FPinConnectionResponse提供给CreateAutomaticConversionNodeAndConnections函数使用。
	 *
	 * @param	PinA	The first pin.
	 * @param	PinB	The second pin.
	 *
	 * @return	如果建立了/断开了连接（图被修改），则为真；如果连接失败且没有产生副作用，则为假。
	 */
	virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;

	/**
	 * 对节点右键BreakNodeLinks选项，断掉这个节点的所有Pin的所有链接(断Node的所有Pin的所有线)
	 *
	 * @param	TargetNode	The node to break links on
	 */
	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;

	/**
	 * 断掉一个引脚Pin的所有链接(断1个Pin的所有线)
	 *
	 * @param	TargetPin	The pin to break links on
	 * @param	bSendsNodeNotifcation	whether to send a notification to the node post pin connection change
	 */
	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;

	/**
	 * 断掉一个引脚到另外一个引脚的，单个链接(断1根线)
	 *
	 * @param	SourcePin	The pin where the link begins.
	 * @param	TargetPin	The pin where the link ends.
	 */
	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;

	//  更像是状态机中的过渡节点。
	// 
	//  原文注释:
	//  尝试创建一个自动转换节点或其他转换节点，以方便两个引脚之间的连接。它创建一个转换节点，A 与转换节点之间的连接，以及从转换节点到 B 的连接。
	//  当 CanCreateConnection 返回 bCanAutoConvert 时，会调用此方法来建立连接。
	// 
	// switch:当UFSMGraphSchema::CanCreateConnection的返回参数为CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE才会进入下面函数
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