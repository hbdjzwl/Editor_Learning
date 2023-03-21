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
	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr));

	return EditorViewportClient.ToSharedRef();
}
