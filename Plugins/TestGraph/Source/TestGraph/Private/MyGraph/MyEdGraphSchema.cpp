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
	//本图表添加Test行为到菜单中
	TSharedPtr<FMyGraphSchemaAction_Test> NewAction1(new FMyGraphSchemaAction_Test());
	ContextMenuBuilder.AddAction(NewAction1);
	
	//本图表添加NewNode行为到菜单中
	TSharedPtr<FMyGraphSchemaAction_NewNode> NewAction2(new FMyGraphSchemaAction_NewNode());
	ContextMenuBuilder.AddAction(NewAction2);

}

void UMyEdGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	//如果右键点击的是引脚
	if (Context->Pin)
	{
		FToolMenuSection& Section = Menu->AddSection("GraphMenuPinSection", FText::FromString("GraphMenuPinSection"));
		Section.AddMenuEntry(FTestEdGraphCommands::Get().CommandPin);
	}
	//如果右键点击的是节点
	else if (Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection("GraphMenuNodeSection", FText::FromString("GraphMenuNodeSection"));
		Section.AddMenuEntry(FTestEdGraphCommands::Get().CommandNode);
	}
}
