// Copyright 2023 devran. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class EGDDebugContainer;
/**
 * Represents the table for each debug object class / debug container
 */
class ENHANCEDGAMEPLAYDEBUGGER_API SEGDTable : public SCompoundWidget
{

private:
	TSharedRef<SHorizontalBox> TableRows = SNew(SHorizontalBox);

	// The logical representation of this table
	EGDDebugContainer* DebugContainer;

public:
	SEGDTable();

	SLATE_BEGIN_ARGS(SEGDTable)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};
