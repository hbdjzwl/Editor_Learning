#include "MyGraph/MyEdGraphSchema.h"
#include "MyGraph/MyEdGraphSchemaAction.h"
#include "ToolMenu.h"
#include "TestEdGraphCommands.h"

UMyEdGraphSchema::UMyEdGraphSchema(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const FPinConnectionResponse UMyEdGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT("OK OK OK"));
}

void UMyEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	//��ͼ�����Test��Ϊ���˵���
	TSharedPtr<FMyGraphSchemaAction_Test> NewAction1(new FMyGraphSchemaAction_Test());
	ContextMenuBuilder.AddAction(NewAction1);
	
	//��ͼ�����NewNode��Ϊ���˵���
	TSharedPtr<FMyGraphSchemaAction_NewNode> NewAction2(new FMyGraphSchemaAction_NewNode());
	ContextMenuBuilder.AddAction(NewAction2);

}

void UMyEdGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	//����Ҽ������������
	if (Context->Pin)
	{
		FToolMenuSection& Section = Menu->AddSection("GraphMenuPinSection", FText::FromString("GraphMenuPinSection"));
		Section.AddMenuEntry(FTestEdGraphCommands::Get().CommandPin);
	}
	//����Ҽ�������ǽڵ�
	else if (Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection("GraphMenuNodeSection", FText::FromString("GraphMenuNodeSection"));
		Section.AddMenuEntry(FTestEdGraphCommands::Get().CommandNode);
	}
}
