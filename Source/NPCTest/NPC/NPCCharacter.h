// Copyright 2024 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCTest/Framework/NPCTestGameStateBase.h"
#include "NPCCharacter.generated.h"

UENUM(BlueprintType)
enum class ETasks : uint8
{
	ETA_Sleep		UMETA(DisplayName="Sleeping"),
	ETA_GetUp		UMETA(DisplayName="Get Up"),
	ETA_TravelWork	UMETA(DisplayName="Travel To Work"),
	ETA_TravelHome	UMETA(DisplayName="Travel Home"),
	ETA_Work		UMETA(DisplayName="Work"),
	ETA_School		UMETA(DisplayName="School"),
	ETA_Eat			UMETA(DisplayName="Eat"),
	ETA_Relax		UMETA(DisplayName="Relax"),
	ETA_Settle		UMETA(DisplayName="Settle Down"),
	ETA_Nothing		UMETA(DisplayName="Nothing"),
	ETA_Shopping	UMETA(DisplayName="Shopping")
};

class ABuildingBaseClass;

UCLASS()
class NPCTEST_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();

	void SetBuildingForWork(ABuildingBaseClass* BuildingToGoTo);
	ABuildingBaseClass* GetBuildingForWork() const;

	void SetIsBuildingUser(const bool NewUserState);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timetable");
	TMap<ETime, ETasks> NPCTimetable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timetable")
	ABuildingBaseClass* WorkLocation;

	// Whether this person is using the building for its purpose even if they "work" there ie a waiter buying food
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timetable")
	bool bIsBuildingUser;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	ANPCTestGameStateBase* GameStateRef;

	UFUNCTION()
	void TimeHasChanged(ETime NewTimeIn);

	UPROPERTY()
	ETasks CurrentTask;
	bool bIsAtWork;
};
