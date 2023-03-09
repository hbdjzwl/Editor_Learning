#pragma once

#include "UObject/Object.h"
#include "MyAsset.generated.h"

UCLASS(EditInlineNew, config = Engine)
class UMyAsset : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY(EditAnywhere)
	int TestData;
};
