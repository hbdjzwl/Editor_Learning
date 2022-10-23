#pragma once

#include "CoreMinimal.h"
#include "CommonType.generated.h"

USTRUCT(BlueprintType)
struct  FMyToDay
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Ãû×Ö")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "ÈÕÆÚ")
	int32  Day;
};