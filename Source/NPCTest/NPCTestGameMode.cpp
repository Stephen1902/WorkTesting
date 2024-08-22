// Copyright Epic Games, Inc. All Rights Reserved.

#include "NPCTestGameMode.h"
#include "NPCTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANPCTestGameMode::ANPCTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
