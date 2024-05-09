// Copyright 2023 devran. All Rights Reserved.


#include "EGDManagerSubsystem.h"
#include "UObject/UnrealType.h"

#include "EGDDebugContainer.h"

UEGDManagerSubsystem::UEGDManagerSubsystem()
	: DebugContainerLimit(8), AccumulatedTick(0.0f), UpdateDelay(0.1f)
{

}

void UEGDManagerSubsystem::Tick(float DeltaTime)
{
	if (LastTickFrame == GFrameCounter)
		return;

	if (AccumulatedTick > UpdateDelay)
	{
		Update();
		AccumulatedTick = 0.0f;
	}
	else
	{
		AccumulatedTick += DeltaTime;
	}
}

void UEGDManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UEGDManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

EGDDebugContainer* UEGDManagerSubsystem::FindDebugContainer(FName DebugContainerName)
{
	for (EGDDebugContainer& Container : DebugContainers)
	{
		if (DebugContainerName == Container.DebugContainerName)
		{
			return &Container;
		}
	}

	return nullptr;
}

void UEGDManagerSubsystem::AddDebugPanelToViewport()
{
	if (GEngine)
	{
		GEngine->GameViewport->AddViewportWidgetContent(Panel, 999);
	}
}

void UEGDManagerSubsystem::AddProperty(UObject* DebugObject, FName PropertyName)
{
	if (!IsValid(DebugObject)) return;

	EGDDebugContainer* DebugContainer = FindDebugContainer(DebugObject->GetClass()->GetFName());
	if (DebugContainer)
	{
		DebugContainer->AddProperty(DebugObject, PropertyName);
		return;
	}

	if (DebugContainers.Num() < DebugContainerLimit)
	{
		EGDDebugContainer NewDebugContainer(DebugObject->GetClass()->GetFName());
		FDebugObjectData* NewDebugObjectData = NewDebugContainer.AddDebugObject(DebugObject);
		NewDebugContainer.AddProperty(*NewDebugObjectData, PropertyName);
		
		DebugContainers.Add(NewDebugContainer);
	}
}

void UEGDManagerSubsystem::Update()
{
	if (DebugContainers.Num() > 0)
	{
		for (EGDDebugContainer& Container : DebugContainers)
		{
			Container.UpdateProperties();
		}
	}
}
