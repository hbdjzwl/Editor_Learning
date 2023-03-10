#include "MyAssetFactory.h"
#include "MyAsset.h"
#include "AssetTypeCategories.h"

#define LOCTEXT_NAMESPACE "MyTest"

UMyAssetFactory::UMyAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//当bCreateNew或者ShouldShowInNewMenu方法返回true时，该资源可以通过资源菜单创建
	bCreateNew = true;

	//源码注解是创建资源后，打开关联编辑器，但没有发现有什么实际作用，后期发现作用后再补充	
	bEditAfterNew = true;

	//该资源对应或支持的对象类
	SupportedClass = UMyAsset::StaticClass();
	/* 这里注意一下，就是UE4自己实现的一些工厂类中，SupportedClass的类是资源蓝图类，而ParentClass（的子类）才是资源实例类。
	一个是资源蓝图类，一个是真正游戏中实例化的类。注意区分。*/
}

UObject* UMyAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	//创建资源蓝图类的实例
	UMyAsset* CreatedAsset = NewObject<UMyAsset>(InParent, Class, Name, Flags | RF_Transactional);
	return CreatedAsset;
}

#undef LOCTEXT_NAMESPACE
