// Copyright 2024 DME Games


#include "BuildingBaseClass.h"
#include "Components/BoxComponent.h"
#include "NPC/NPCCharacter.h"

// Sets default values
ABuildingBaseClass::ABuildingBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root Comp");
	SetRootComponent(RootComp);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Display Mesh");
	MeshComponent->SetupAttachment(RootComp);

	MainEntranceBox = CreateDefaultSubobject<UBoxComponent>("Main Entrance");
	MainEntranceBox->SetupAttachment(MeshComponent);

	SecondEntranceBox = CreateDefaultSubobject<UBoxComponent>("Second Entrance");
	SecondEntranceBox->SetupAttachment(MeshComponent);
	
	DegradationPerDay = 0.f;
	AmountToUse = 0.f;
	AmountToPay = 0.f;
}

void ABuildingBaseClass::AdjustCondition(const float AmountToAdjust)
{
	Condition += AmountToAdjust;
}

void ABuildingBaseClass::GetOpeningTimes(ETime& OpeningTime, ETime& ClosingTime, int32& MaxWorkingHours) const
{
	OpeningTime = BuildingStruct.OpeningTime;
	ClosingTime = BuildingStruct.ClosingTime;
	MaxWorkingHours = BuildingStruct.MaxWorkingHours;
}

// Called when the game starts or when spawned
void ABuildingBaseClass::BeginPlay()
{
	Super::BeginPlay();

	MainEntranceBox->OnComponentBeginOverlap.AddDynamic(this, &ABuildingBaseClass::MainEntranceBeginOverlap);
	MainEntranceBox->OnComponentEndOverlap.AddDynamic(this, &ABuildingBaseClass::MainEntranceEndOverlap);
	SecondEntranceBox->OnComponentBeginOverlap.AddDynamic(this, &ABuildingBaseClass::SecondEntranceBeginOverlap);
	SecondEntranceBox->OnComponentEndOverlap.AddDynamic(this, &ABuildingBaseClass::SecondEntranceEndOverlap);
}

// Called every frame
void ABuildingBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBaseClass::SecondEntranceEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CheckIfOverlappingWorksHere(OtherActor))
	{
		// DO SOMETHING TO DO WITH THE CHARACTER
	}
}

void ABuildingBaseClass::MainEntranceEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CheckIfOverlappingWorksHere(OtherActor))
	{
		// DO SOMETHING TO DO WITH THE CHARACTER
	}
}

void ABuildingBaseClass::SecondEntranceBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO Consider different events for different entrances
	if (CheckIfOverlappingWorksHere(OtherActor))
	{
		// DO SOMETHING TO DO WITH THE CHARACTER
	}
}

void ABuildingBaseClass::MainEntranceBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CheckIfOverlappingWorksHere(OtherActor))
	{
		// DO SOMETHING TO DO WITH THE CHARACTER
	}
}

bool ABuildingBaseClass::CheckIfOverlappingWorksHere(AActor* OverlappingActor) const
{
	if (const ANPCCharacter* OverlappingChar = Cast<ANPCCharacter>(OverlappingActor))
	{
		if (OverlappingChar->GetBuildingForWork() == this)
		{
			return true;
		}
	}

	return false;
}
