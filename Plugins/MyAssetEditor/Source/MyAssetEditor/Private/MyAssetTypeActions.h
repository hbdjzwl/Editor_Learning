#pragma once

#include "AssetTypeActions_Base.h"

class FMyAssetTypeActions : public FAssetTypeActions_Base
{
public:
	
	virtual FText GetName() const override;				//Asset的名字
	
	virtual FColor GetTypeColor() const override;		//Asset图标的颜色
	
	virtual uint32 GetCategories() override;			//Asset所属的分类

	virtual FText GetAssetDescription(const struct FAssetData& AssetData) const override;	//Asset的描述

	virtual bool CanFilter() override;					//Asset筛选

	virtual UClass* GetSupportedClass() const override;	//Asset的UObject是什么

	//每次打开GetSupportedClass资产实例对象时候会调用该函数，用来生成编辑界面调用。
	//如果不重写该函数则使用UPROPERTY()反射的界面
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
};



