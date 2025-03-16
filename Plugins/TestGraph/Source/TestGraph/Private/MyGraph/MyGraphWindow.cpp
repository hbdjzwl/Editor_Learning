#include "MyGraph/MyGraphWindow.h"
#include "MyGraph/MyEdGraph.h"
#include "MyGraph/MyEdGraphSchema.h"


void SMyGraphWindow::Construct(const FArguments& InArgs)
{
	//����ͼ�����
	GraphObj = NewObject<UMyEdGraph>();
	GraphObj->Schema = UMyEdGraphSchema::StaticClass();
	GraphObj->AddToRoot();
	

	//����ͼ��༭���ؼ�
	GraphEditorPtr = SNew(SGraphEditor)
		.AdditionalCommands(InArgs._TestEdGraphCommands)
		.GraphToEdit(GraphObj)
		.IsEditable(true);
		

	//ָ�����ؼ���UI��
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().FillHeight(1.0f)
		[
			GraphEditorPtr.ToSharedRef()
		]

		//ͼ������Button��ť�����ڲ��Խڵ�����������Ϣ
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
