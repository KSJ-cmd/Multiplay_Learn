// Copyright Epic Games, Inc. All Rights Reserved.

#include "Multiplay_LearnGameMode.h"
#include "Multiplay_LearnCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplay_LearnGameMode::AMultiplay_LearnGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
