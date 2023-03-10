#include "MyAssetFactory.h"
#include "MyAsset.h"
#include "AssetTypeCategories.h"

#define LOCTEXT_NAMESPACE "MyTest"

UMyAssetFactory::UMyAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//��bCreateNew����ShouldShowInNewMenu��������trueʱ������Դ����ͨ����Դ�˵�����
	bCreateNew = true;

	//Դ��ע���Ǵ�����Դ�󣬴򿪹����༭������û�з�����ʲôʵ�����ã����ڷ������ú��ٲ���	
	bEditAfterNew = true;

	//����Դ��Ӧ��֧�ֵĶ�����
	SupportedClass = UMyAsset::StaticClass();
	/* ����ע��һ�£�����UE4�Լ�ʵ�ֵ�һЩ�������У�SupportedClass��������Դ��ͼ�࣬��ParentClass�������ࣩ������Դʵ���ࡣ
	һ������Դ��ͼ�࣬һ����������Ϸ��ʵ�������ࡣע�����֡�*/
}

UObject* UMyAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	//������Դ��ͼ���ʵ��
	UMyAsset* CreatedAsset = NewObject<UMyAsset>(InParent, Class, Name, Flags | RF_Transactional);
	return CreatedAsset;
}

#undef LOCTEXT_NAMESPACE
