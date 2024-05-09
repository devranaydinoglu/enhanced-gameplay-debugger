// Copyright 2023 devran. All Rights Reserved.

#include "EGDPanel.h"

#include "EGDTable.h"
#include "Widgets/Layout/SGridPanel.h"

void SEGDPanel::Construct(const FArguments& InArgs)
{
	UE_LOG(LogTemp, Error, TEXT("Panel Construct()"));

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(20.0f)
		[
			//SNew(SEGDTable)
			SNew(SGridPanel)
			+ SGridPanel::Slot(0, 0)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FSlateColor(FLinearColor::Blue))
				//.Padding(10.0f)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Prop1"))
				]
			]
			+ SGridPanel::Slot(1, 0)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FSlateColor(FLinearColor::Blue))
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Prop2"))
				]
			]
		]
	];
}
