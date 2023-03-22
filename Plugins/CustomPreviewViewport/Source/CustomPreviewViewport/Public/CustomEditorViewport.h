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

	// ����Ԥ����ͼ�Ľӿ�
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

	// ������ͼ��������
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;

	// �Զ�����ͼ������ݡ�����ͻ���GWorld,���ѡ��Ĭ�Ϲؿ�����ͼ
	TSharedPtr<class FPreviewScene> PreviewScene;


public:	
	//ICommonEditorViewportToolbarInfoProvider ������ӿں���
	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
};
