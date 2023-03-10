#include "MyAssetTypeActions.h"
#include "MyAsset.h"
#include "MyAssetEditorToolkit.h"
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

//Asset所属的分类
uint32 FMyAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FText FMyAssetTypeActions::GetAssetDescription(const struct FAssetData& AssetData) const
{
	return LOCTEXT("My Custom Description", "My Custom Description");
}

bool FMyAssetTypeActions::CanFilter()
{
	return false;
}

//Asset的UObject是什么
UClass* FMyAssetTypeActions::GetSupportedClass() const
{
	return UMyAsset::StaticClass();
}

void FMyAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Asset = Cast<UMyAsset>(*ObjIt);
		if (Asset != NULL)
		{
			//
			TSharedRef<FMyAssetEditorToolkit> NewToolkit(new FMyAssetEditorToolkit());
			NewToolkit->Initialize(Mode, EditWithinLevelEditor, Asset);
		}
	}
}

#undef LOCTEXT_NAMESPACE
