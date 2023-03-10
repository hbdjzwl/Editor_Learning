#pragma once

#include "Factories/Factory.h"
#include "MyAssetFactory.generated.h"

UCLASS(config = Editor)
class UMyAssetFactory : public UFactory
{
    GENERATED_UCLASS_BODY()
public:

	//���ض�������һ�㷵��SupportedClass��ʵ�����󡣵���������Դ��ȷ�������󣬸÷������ᱻִ�С�
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
	//Ĭ��Ϊtrue 
	//������trueʱ������Դ����ͨ����Դ�˵�������������CanCreateNew�������ж��Ƿ����ͨ���˵�������CanCreateNew�Ƿ���bCreateNew��ֵ��
	//bool ShouldShowInNewMenu() const;

	//��Դ����
	//virtual uint32 GetMenuCategories() const override;
};
