#pragma once

#include "AssetTypeActions_Base.h"

class FMyAssetTypeActions : public FAssetTypeActions_Base
{
public:
	
	virtual FText GetName() const override;				//Asset的名字
	
	virtual FColor GetTypeColor() const override;		//Asset图标的颜色
	
	virtual UClass* GetSupportedClass() const override;	//Asset的UObject是什么
	
	virtual uint32 GetCategories() override;			//Asset所属的分类
};



