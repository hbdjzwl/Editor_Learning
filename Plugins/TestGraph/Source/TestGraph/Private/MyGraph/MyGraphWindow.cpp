#include "MyGraph/MyGraphWindow.h"
#include "MyGraph/MyEdGraph.h"
#include "MyGraph/MyEdGraphSchema.h"


void SMyGraphWindow::Construct(const FArguments& InArgs)
{
	//创建图表对象
	GraphObj = NewObject<UMyEdGraph>();
	GraphObj->Schema = UMyEdGraphSchema::StaticClass();
	GraphObj->AddToRoot();
	

	//创建图表编辑器控件
	GraphEditorPtr = SNew(SGraphEditor)
		.AdditionalCommands(InArgs._TestEdGraphCommands)
		.GraphToEdit(GraphObj)
		.IsEditable(true);
		

	//指定本控件的UI：
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().FillHeight(1.0f)
		[
			GraphEditorPtr.ToSharedRef()
		]

		//图标下面Button按钮，用于测试节点引脚链接信息
		+ SVerticalBox::Slot().AutoHeight()
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			.OnClicked_Lambda([this]()
				{
					GraphObj->TestFunc();
					return FReply::Handled();
				})
		]
	];


	GraphObj->RebuildGraph();

}
