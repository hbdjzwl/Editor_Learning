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
	//ʹ���Լ���Ԥ���ռ����
	PreviewScene = MakeShareable(new FPreviewScene());

	//��Ԥ�������м�һ������ģ��
	{
		//��ȡģ��
		UStaticMesh* SM = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"), NULL, LOAD_None, NULL);
		//�������
		UStaticMeshComponent* SMC = NewObject<UStaticMeshComponent>();
		SMC->SetStaticMesh(SM);
		//��Ԥ���������������
		PreviewScene->AddComponent(SMC, FTransform::Identity);
	}


	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr, PreviewScene.Get()));

	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SCustomEditorViewport::MakeViewportToolbar()
{
	//����ͨ�ñ༭����ͼ������������SCommonEditorViewportToolbarBase()���캯����Ҫһ��TSharedPtr<class ICommonEditorViewportToolbarInfoProvider>������
	//���Ը����̳�ICommonEditorViewportToolbarInfoProvider;
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}


//ICommonEditorViewportToolbarInfoProvider ����ӿ�
TSharedRef<class SEditorViewport> SCustomEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

//ICommonEditorViewportToolbarInfoProvider ����ӿ�
TSharedPtr<FExtender> SCustomEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

//ICommonEditorViewportToolbarInfoProvider ����ӿ�
void SCustomEditorViewport::OnFloatingButtonClicked()
{
}
