#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class SCustomEditorViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider /*工具栏的接口，搭配MakeViewportToolbar使用*/
{
public:
	SLATE_BEGIN_ARGS(SCustomEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	SCustomEditorViewport();
	~SCustomEditorViewport();

protected:

	// 创建预览视图的接口
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

	// 创建视图工具栏。
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;

	// 自定义视图里的内容。否则就会用GWorld,则会选择默认关卡里视图，且预览场景中的组件也是添加在他下面的。
	TSharedPtr<class FPreviewScene> PreviewScene;


public:	
	//ICommonEditorViewportToolbarInfoProvider 抽象类接口函数
	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
};
