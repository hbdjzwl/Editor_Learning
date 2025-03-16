#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "GraphEditor.h"


class SMyGraphWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyGraphWindow) {}

	//由于生成SGraphEditor的环境是在SMyGraphWindow中，而命令表是在模块的Commands类中，因此为了把命令表传递给SGraphEditor，需要给SMyGraphWindow添加一个参数，
	SLATE_ARGUMENT(TSharedPtr<FUICommandList>, TestEdGraphCommands)
	SLATE_END_ARGS()

	/** 在这里面创建UEdGraph */
	void Construct(const FArguments& InArgs);

	//图表编辑器控件
	TSharedPtr<SGraphEditor> GraphEditorPtr;

	//图表对象
	class UMyEdGraph* GraphObj;
};
