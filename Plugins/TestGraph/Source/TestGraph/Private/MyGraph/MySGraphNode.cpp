
#include "MyGraph/MySGraphNode.h"
#include "MyGraph/MyUGraphNode.h"
#include "Widgets/Input/SButton.h"
#include "SGraphPin.h"



void SMyGraphNode::Construct(const FArguments& InArgs, UMyGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

TSharedRef<SWidget> SMyGraphNode::CreateNodeContentArea()
{
	return SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("NoBorder"))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin(0, 3))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.FillWidth(1.0f)
			[
				// 左边所有引脚的VerticalBox
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
		/*-----------中间是自己新增自定义的部分---------*/
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.FillWidth(1.0f)
			[
				SNew(SButton)
			]
		/*---------------------------------------*/
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			[
				// 右边所有引脚的VerticalBox
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		];
}

// 
// void SMyGraphNode::UpdateGraphNode()
// {
// 
// 	RightNodeBox.Reset();
// 	LeftNodeBox.Reset();
// 
// 
// 	//控件界面：
// 	GetOrAddSlot( ENodeZone::Center )
// 	.HAlign(HAlign_Center)
// 	.VAlign(VAlign_Center)
// 	[
// 		SNew(SBorder)
// 		//.BorderImage( FEditorStyle::GetBrush( "Menu.Background" ) )
// 		.BorderImage( FEditorStyle::GetBrush("Graph.Node.Body"))
// 		.Padding(0)
// 		[
// 			SNew(SHorizontalBox)
// 			+SHorizontalBox::Slot()
// 			.AutoWidth()
// 			.VAlign(VAlign_Center)
// 			[
// 				// LEFT
// 				SNew(SBox)
// 				.WidthOverride(40)
// 				[
// 					SAssignNew(LeftNodeBox, SVerticalBox)
// 				]
// 			]
// 			+ SHorizontalBox::Slot()
// 			.VAlign(VAlign_Center)
// 			.HAlign(HAlign_Center)
// 			.FillWidth(1.0f)
// 			[
// 				SNew(STextBlock)
// 				.Text(FText::FromString(((UMyGraphNode*)GraphNode)->TestInfo))
// 			]
// 			+SHorizontalBox::Slot()
// 			.AutoWidth()
// 			.VAlign(VAlign_Center)
// 			[
// 				// RIGHT
// 				SNew(SBox)
// 				.WidthOverride(40)
// 				[
// 					SAssignNew(RightNodeBox, SVerticalBox)
// 				]
// 			]
// 		]
// 	];
// 
// 	CreatePinWidgets();
// }
