// Copyright 2023 devran. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EGDPanel.h"
#include "EGDManagerSubsystem.generated.h"

class EGDDebugContainer;

UCLASS()
class ENHANCEDGAMEPLAYDEBUGGER_API UEGDManagerSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

private:
	// The max number of allowed debug containers
	int DebugContainerLimit;

	// All active debug containers
	TArray<EGDDebugContainer> DebugContainers;

	uint32 LastTickFrame = INDEX_NONE;
	float AccumulatedTick;
	float UpdateDelay;

	TSharedRef<SEGDPanel> Panel = SNew(SEGDPanel);

public:
	UEGDManagerSubsystem();

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UEGDManagerSubsystem, STATGROUP_Tickables);
	}

	/**
	 * Automatically adds the specified property to the correct category determined by the class of the debug object.
	 * A new category will be created for each debug object class (8 category limit).
	 *
	 * @param DebugObject Owning object of the property
	 * @param PropertyName Name of the property to add
	 */
	UFUNCTION(BlueprintCallable)
	void AddProperty(UObject* DebugObject, FName PropertyName);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	/**
	 * Finds a debug container based on its name.
	 *
	 * @param DebugContainerName Name of the debug container to find
	 * @return Found debug container
	 */
	EGDDebugContainer* FindDebugContainer(FName DebugContainerName);

	void AddDebugPanelToViewport();

	/**
	* Main update loop to update properties of debug objects in all containers.
	*/
	void Update();
};
