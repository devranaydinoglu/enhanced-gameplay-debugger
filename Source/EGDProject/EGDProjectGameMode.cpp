// Copyright Epic Games, Inc. All Rights Reserved.

#include "EGDProjectGameMode.h"
#include "EGDProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEGDProjectGameMode::AEGDProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
