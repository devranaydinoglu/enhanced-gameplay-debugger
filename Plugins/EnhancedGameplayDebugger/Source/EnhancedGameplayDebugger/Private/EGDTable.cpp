// Copyright 2023 devran. All Rights Reserved.

#include "EGDTable.h"
#include "EGDTableRow.h"

SEGDTable::SEGDTable()
	: DebugContainer(nullptr)
{

}

void SEGDTable::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.Padding(10.0f)
		[
			SNew(SEGDTableRow)
		]
	];
}
