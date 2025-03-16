#include "GraphEditor/FSMGraph.h"
#include "FSM.h"

UFSM * UFSMGraph::GetFSM() const
{
	//return CastChecked<UFSM>(GetOuter());
	
	//��CreateNewGraph��ʱ��UFSM���󴫵ݽ�ȥ��Ϊ��NewObject��Outer������ͨ����ȡ�Լ���GetOuter()���ܻ�ȡ��ָ���Ķ���
	return GetTypedOuter<UFSM>();
}

bool UFSMGraph::Modify(bool bAlwaysMarkDirty)
{
	if (!CanModify()) 
	{
		return false;
	}
	
#if 0
	//UFSM��PreEditUndo���Զ����ã��ڲ����ǵ��õ�FMS->Modify()
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

	//֪ͨ��ͼ���޸��ˣ���Ȼ����ɾ������������ʾ����������´����ͼ����������ĵ��þͻ�������ʾ��
	NotifyGraphChanged();
}
