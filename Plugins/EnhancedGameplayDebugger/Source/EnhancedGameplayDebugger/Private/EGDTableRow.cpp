// Copyright 2023 devran. All Rights Reserved.

#include "EGDTableRow.h"

void SEGDTableRow::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(20.0f)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FSlateColor(FLinearColor::Blue))
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Prop1"))
			]
		]
	];
}
