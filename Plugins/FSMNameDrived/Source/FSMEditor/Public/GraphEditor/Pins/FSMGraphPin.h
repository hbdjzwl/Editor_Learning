#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SGraphPin.h"

class FSMEDITOR_API SFSMGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SFSMGraphPin) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

	
	virtual FSlateColor GetPinColor() const override;
protected:
#if 0	//此处感觉没用，应该是旧版本下面的函数是虚函数所以必须实现。
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	//~ End SGraphPin Interface
#endif
};
