// Copyright 2024 DME Games


#include "TriggeredLightActor.h"

// Sets default values
ATriggeredLightActor::ATriggeredLightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetReplicates(true);

	
}

// Called when the game starts or when spawned
void ATriggeredLightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

