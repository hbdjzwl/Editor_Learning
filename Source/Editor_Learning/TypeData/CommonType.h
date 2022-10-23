#pragma once

#include "CoreMinimal.h"
#include "CommonType.generated.h"

USTRUCT(BlueprintType)
struct  FMyToDay
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "����")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "����")
	int32  Day;
};