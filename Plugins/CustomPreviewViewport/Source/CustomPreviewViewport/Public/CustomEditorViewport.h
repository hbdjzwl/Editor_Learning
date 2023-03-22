#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"
//#include "StaticMeshEditorViewportToolBar.h"

class SCustomEditorViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider
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

	// 自定义视图里的内容。否则就会用GWorld,则会选择默认关卡里视图
	TSharedPtr<class FPreviewScene> PreviewScene;


public:	
	//ICommonEditorViewportToolbarInfoProvider 抽象类接口函数
	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
};
