#pragma once

#include "Factories/Factory.h"
#include "MyAssetFactory.generated.h"

UCLASS(config = Editor)
class UMyAssetFactory : public UFactory
{
    GENERATED_UCLASS_BODY()
public:

	//返回对象，这里一般返回SupportedClass的实例对象。当创建完资源并确认命名后，该方法将会被执行。
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
	//默认为true 
	//当返回true时，该资源可以通过资源菜单创建，则会调用CanCreateNew方法来判断是否可以通过菜单创建，CanCreateNew是返回bCreateNew的值。
	//bool ShouldShowInNewMenu() const;

	//资源分类
	//virtual uint32 GetMenuCategories() const override;
};
