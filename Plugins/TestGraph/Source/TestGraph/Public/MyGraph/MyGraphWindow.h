#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "GraphEditor.h"


class SMyGraphWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyGraphWindow) {}

	//��������SGraphEditor�Ļ�������SMyGraphWindow�У������������ģ���Commands���У����Ϊ�˰�������ݸ�SGraphEditor����Ҫ��SMyGraphWindow���һ��������
	SLATE_ARGUMENT(TSharedPtr<FUICommandList>, TestEdGraphCommands)
	SLATE_END_ARGS()

	/** �������洴��UEdGraph */
	void Construct(const FArguments& InArgs);

	//ͼ��༭���ؼ�
	TSharedPtr<SGraphEditor> GraphEditorPtr;

	//ͼ�����
	class UMyEdGraph* GraphObj;
};
