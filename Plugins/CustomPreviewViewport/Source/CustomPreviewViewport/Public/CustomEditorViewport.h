#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class SCustomEditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SCustomEditorViewport) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);
	SCustomEditorViewport();
	~SCustomEditorViewport();

protected:
	/** SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
};
