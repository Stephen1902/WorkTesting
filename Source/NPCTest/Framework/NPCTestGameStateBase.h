// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCInterface.h"
#include "GameFramework/GameStateBase.h"
#include "NPCTestGameStateBase.generated.h"

class ANPCCharacter;

UENUM(BlueprintType)
enum class ETime : uint8
{
	ET_0000		UMETA(DisplayName="00:00"),
	ET_0030		UMETA(DisplayName="00:30"),
	ET_0100		UMETA(DisplayName="01:00"),
	ET_0130		UMETA(DisplayName="01:30"),
	ET_0200		UMETA(DisplayName="02:00"),
	ET_0230		UMETA(DisplayName="02:30"),
	ET_0300		UMETA(DisplayName="03:00"),
	ET_0330		UMETA(DisplayName="03:30"),
	ET_0400		UMETA(DisplayName="04:00"),
	ET_0430		UMETA(DisplayName="04:30"),
	ET_0500		UMETA(DisplayName="05:00"),
	ET_0530		UMETA(DisplayName="05:30"),
	ET_0600		UMETA(DisplayName="06:00"),
	ET_0630		UMETA(DisplayName="06:30"),
	ET_0700		UMETA(DisplayName="07:00"),
	ET_0730		UMETA(DisplayName="07:30"),
	ET_0800		UMETA(DisplayName="08:00"),
	ET_0830		UMETA(DisplayName="08:30"),
	ET_0900		UMETA(DisplayName="09:00"),
	ET_0930		UMETA(DisplayName="09:30"),
	ET_1000		UMETA(DisplayName="10:00"),
	ET_1030		UMETA(DisplayName="10:30"),
	ET_1100		UMETA(DisplayName="11:00"),
	ET_1130		UMETA(DisplayName="11:30"),
	ET_1200		UMETA(DisplayName="12:00"),
	ET_1230		UMETA(DisplayName="12:30"),
	ET_1300		UMETA(DisplayName="13:00"),
	ET_1330		UMETA(DisplayName="13:30"),
	ET_1400		UMETA(DisplayName="14:00"),
	ET_1430		UMETA(DisplayName="14:30"),
	ET_1500		UMETA(DisplayName="15:00"),
	ET_1530		UMETA(DisplayName="15:30"),
	ET_1600		UMETA(DisplayName="16:00"),
	ET_1630		UMETA(DisplayName="16:30"),
	ET_1700		UMETA(DisplayName="17:00"),
	ET_1730		UMETA(DisplayName="17:30"),
	ET_1800		UMETA(DisplayName="18:00"),
	ET_1830		UMETA(DisplayName="18:30"),
	ET_1900		UMETA(DisplayName="19:00"),
	ET_1930		UMETA(DisplayName="19:30"),
	ET_2000		UMETA(DisplayName="20:00"),
	ET_2030		UMETA(DisplayName="20:30"),
	ET_2100		UMETA(DisplayName="21:00"),
	ET_2130		UMETA(DisplayName="21:30"),
	ET_2200		UMETA(DisplayName="22:00"),
	ET_2230		UMETA(DisplayName="22:30"),
	ET_2300		UMETA(DisplayName="23:00"),
	ET_2330		UMETA(DisplayName="23:30"),

	ET_FAIL		UMETA(DisplayName="FAIL")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinutesUpdated, ETime, NewTime);

/**
 * 
 */
UCLASS()
class NPCTEST_API ANPCTestGameStateBase : public AGameStateBase, public INPCInterface
{
	GENERATED_BODY()

	ANPCTestGameStateBase();

public:
	UPROPERTY()
	FOnMinutesUpdated OnMinutesUpdated;

	void AddNPCCharacter(ANPCCharacter* CharacterIn);
	void RemoveNPCCharacter(ANPCCharacter* CharacterIn);
	
protected:
	virtual void Tick(float DeltaSeconds) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Date Time")
	int32 Minutes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Date Time")
	int32 Hours;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Date Time", meta=(ClampMin=1, ClampMax=31))
	int32 Day;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Date Time", meta=(ClampMin=1, ClampMax=12))
	int32 Month;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Date Time", meta=(ClampMin=0))
	int32 Year;

	// Speed at which game time passes in the real world.  1500 is one real hour.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Date Time")
	float TimeUnit;
private:	
	float Clockwork;
	int32 Seconds;
	int32 DayTick;
	TArray<int32> GameTime;
	TArray<int32> GameDate;

	void SetDayTickAndClockwork(float DeltaTime);
	void SetClock();
	void SetDate();

	ETime BroadcastTimeChange();

	TMap<ANPCCharacter*, bool> NPCsInWorldWithJobs;
};
