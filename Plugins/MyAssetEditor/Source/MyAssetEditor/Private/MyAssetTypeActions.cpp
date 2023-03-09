#include"MyAssetTypeActions.h"
#include"MyAsset.h"

#define LOCTEXT_NAMESPACE "MyAsset"

//Asset的名字
FText FMyAssetTypeActions::GetName() const
{
	return LOCTEXT("MyAssetTypeActions", "MyAsset");
}
//Asset图标的颜色
FColor FMyAssetTypeActions::GetTypeColor() const
{
	return FColor(0, 255, 255);
}
//Asset的UObject是什么
UClass * FMyAssetTypeActions::GetSupportedClass() const
{
	return UMyAsset::StaticClass();
}
//Asset所属的分类
uint32 FMyAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

#undef LOCTEXT_NAMESPACE
