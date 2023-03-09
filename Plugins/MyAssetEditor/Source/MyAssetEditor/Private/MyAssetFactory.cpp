#include "MyAssetFactory.h"
#include "MyAsset.h"
#include "AssetTypeCategories.h"

#define LOCTEXT_NAMESPACE "MyTest"

UMyAssetFactory::UMyAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;//true if the associated editor should be opened after creating a new object
	SupportedClass = UMyAsset::StaticClass();
}

UObject* UMyAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UMyAsset* CreatedAsset = NewObject<UMyAsset>(InParent, Class, Name, Flags | RF_Transactional);
	return CreatedAsset;
}

uint32 UMyAssetFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Misc;
}

#undef LOCTEXT_NAMESPACE
