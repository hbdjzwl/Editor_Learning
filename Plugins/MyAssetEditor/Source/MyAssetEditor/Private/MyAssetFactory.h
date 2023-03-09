#pragma once

#include "Factories/Factory.h"
#include "MyAssetFactory.generated.h"

UCLASS(config = Editor)
class UMyAssetFactory : public UFactory
{
    GENERATED_UCLASS_BODY()
public:
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual uint32 GetMenuCategories() const override;
	// End of UFactory interface
};
