// Copyright 2023 devran. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class ENHANCEDGAMEPLAYDEBUGGER_API SEGDTableRow : public SCompoundWidget
{

private:
	TSharedRef<SBox> RowItems = SNew(SBox);

public:
	SLATE_BEGIN_ARGS(SEGDTableRow)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};
