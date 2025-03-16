#include "GraphEditor/FSMGraph.h"
#include "FSM.h"

UFSM * UFSMGraph::GetFSM() const
{
	//return CastChecked<UFSM>(GetOuter());
	
	//在CreateNewGraph的时候将UFSM对象传递进去作为了NewObject的Outer，所以通过获取自己的GetOuter()技能获取到指定的对象。
	return GetTypedOuter<UFSM>();
}

bool UFSMGraph::Modify(bool bAlwaysMarkDirty)
{
	if (!CanModify()) 
	{
		return false;
	}
	
#if 0
	//UFSM的PreEditUndo会自动调用，内部就是调用的FMS->Modify()
	if (UFSM* FMS = GetFSM())
	{
		FMS->Modify();
	}
	for (UEdGraphNode* Node : Nodes)
	{
		Node->Modify();
	}
#endif
	bool bSaved = Super::Modify(bAlwaysMarkDirty);
	return bSaved;
}

void UFSMGraph::PostEditUndo()
{
	Super::PostEditUndo();

	//通知到图表修改了，不然撤回删除不会立马显示，必须得重新打开这个图表。有了下面的调用就会立马显示。
	NotifyGraphChanged();
}
