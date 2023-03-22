#include"CustomEditorViewport.h"

#include"EditorViewportClient.h"

void SCustomEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}
SCustomEditorViewport::SCustomEditorViewport()
{
}
SCustomEditorViewport::~SCustomEditorViewport()
{
}

TSharedRef<FEditorViewportClient> SCustomEditorViewport::MakeEditorViewportClient()
{
	//使用自己的预览空间
	PreviewScene = MakeShareable(new FPreviewScene());

	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr, PreviewScene.Get()));

	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SCustomEditorViewport::MakeViewportToolbar()
{
	return SNew(SStaticMeshEditorViewportToolbar, SharedThis(this));
}


TSharedRef<class SEditorViewport> SCustomEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> SCustomEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void SCustomEditorViewport::OnFloatingButtonClicked()
{
}
