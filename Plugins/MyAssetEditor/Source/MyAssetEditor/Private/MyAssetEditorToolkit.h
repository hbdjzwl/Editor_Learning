#pragma once

#include "Toolkits/AssetEditorToolkit.h"

class FMyAssetEditorToolkit : public FAssetEditorToolkit
{
public:

	//四个虚函数接口，得重写才能实例化。具体用处不明。
 	virtual FName GetToolkitFName() const override;
 	virtual FText GetBaseToolkitName() const override;
 	virtual FString GetWorldCentricTabPrefix() const override;
 	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	//注册Tab
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//初始化，在AssetTypeActions::OpenAssetEditor中调用
	void Initialize(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UMyAsset* Asset);

	//生成TestTab时调用
	TSharedRef<SDockTab> SpawnTestTab(const FSpawnTabArgs& Args);

private:
	TWeakObjectPtr<class UMyAsset> EditingAsset;

	TSharedPtr<STextBlock> NumberText;
};
