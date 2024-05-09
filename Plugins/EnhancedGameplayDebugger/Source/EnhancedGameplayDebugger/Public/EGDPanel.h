// Copyright 2023 devran. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * Represents the debug panel in which the tables reside
 */
class ENHANCEDGAMEPLAYDEBUGGER_API SEGDPanel : public SCompoundWidget
{

private:
	TSharedRef<SVerticalBox> Tables = SNew(SVerticalBox);

public:
	SLATE_BEGIN_ARGS(SEGDPanel)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};
