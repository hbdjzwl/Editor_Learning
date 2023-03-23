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
	//使用自己的预览空间对象
	PreviewScene = MakeShareable(new FPreviewScene());

	//向预览场景中加一个测试模型
	{
		//读取模型
		UStaticMesh* SM = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"), NULL, LOAD_None, NULL);
		//创建组件
		UStaticMeshComponent* SMC = NewObject<UStaticMeshComponent>();
		SMC->SetStaticMesh(SM);
		//向预览场景中增加组件
		PreviewScene->AddComponent(SMC, FTransform::Identity);
	}


	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr, PreviewScene.Get()));

	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SCustomEditorViewport::MakeViewportToolbar()
{
	//创建通用编辑器视图工具栏，但是SCommonEditorViewportToolbarBase()构造函数需要一个TSharedPtr<class ICommonEditorViewportToolbarInfoProvider>参数。
	//所以该类会继承ICommonEditorViewportToolbarInfoProvider;
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}


//ICommonEditorViewportToolbarInfoProvider 抽象接口
TSharedRef<class SEditorViewport> SCustomEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

//ICommonEditorViewportToolbarInfoProvider 抽象接口
TSharedPtr<FExtender> SCustomEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

//ICommonEditorViewportToolbarInfoProvider 抽象接口
void SCustomEditorViewport::OnFloatingButtonClicked()
{
}
