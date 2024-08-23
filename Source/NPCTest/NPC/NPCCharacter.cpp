// Copyright 2024 DME Games

#include "NPCCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "NPCTest/BuildingBaseClass.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	WorkLocation = nullptr;
	GameStateRef = nullptr;
	bIsBuildingUser = false;
	CurrentTask = ETasks::ETA_Nothing;
	bIsAtWork = false;
}

void ANPCCharacter::SetBuildingForWork(ABuildingBaseClass* BuildingToGoTo)
{
	if (BuildingToGoTo != WorkLocation && BuildingToGoTo != nullptr)
	{
		WorkLocation = BuildingToGoTo;
	}
}

ABuildingBaseClass* ANPCCharacter::GetBuildingForWork() const
{
	return WorkLocation;
}

void ANPCCharacter::SetIsBuildingUser(const bool NewUserState)
{
	bIsBuildingUser = NewUserState;
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameStateRef = Cast<ANPCTestGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameStateRef)
	{
		// Register this NPC with the Game State which will give the info to buildings for job vacancies
		GameStateRef->AddNPCCharacter(this);
		GameStateRef->OnMinutesUpdated.AddDynamic(this, &ANPCCharacter::TimeHasChanged);
	}
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCCharacter::TimeHasChanged(ETime NewTimeIn)
{
	if (NPCTimetable.Contains(NewTimeIn))
	{
		// Check whether the current task is to travel to work or home, get the destination of where they're going
		
	}
}

void ANPCCharacter::SetWorkingHours()
{
	if (WorkLocation)
	{
		WorkLocation->GetOpeningTimes(WorkStartTime, WorkEndTime, WorkingHoursPerDay);
		if (WorkStartTime == WorkEndTime)
		{
			
		}
	}
}


