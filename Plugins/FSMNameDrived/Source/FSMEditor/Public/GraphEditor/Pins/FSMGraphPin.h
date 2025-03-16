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
#if 0	//�˴��о�û�ã�Ӧ���Ǿɰ汾����ĺ������麯�����Ա���ʵ�֡�
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	//~ End SGraphPin Interface
#endif
};
