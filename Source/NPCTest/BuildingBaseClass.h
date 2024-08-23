// Copyright 2024 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Framework/NPCTestGameStateBase.h"
#include "BuildingBaseClass.generated.h"

UENUM(BlueprintType)
enum EBuildingType
{
	EBT_House		UMETA(DisplayName="House"),
	EBT_Work		UMETA(DisplayName="Workplace"),
	EBT_School		UMETA(DisplayName="School"),
	EBT_Relax		UMETA(DisplayName="Relaxation"),
	EBT_Food		UMETA(DisplayName="Food"),
	EBT_Water		UMETA(DisplayName="Water"),
	EBT_Entertain	UMETA(DisplayName="Entertainment")
};

USTRUCT(BlueprintType)
struct FBuildingStruct
{
	GENERATED_BODY()

	// The name of this building
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
	FName BuildingName;

	// A short description of what this building is
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
	FName BuildingDescription;
	
	// What type(s) of building this is
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
	TArray<TEnumAsByte<EBuildingType>> BuildingTypes;

	// "Opening" hour for this building 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
    ETime OpeningTime;

	// "Closing" hour for this building
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
	ETime ClosingTime;

	// Maximum number of hours a worker can be here for a day
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
	int32 MaxWorkingHours;
	
	FBuildingStruct()
	{
		BuildingName = FName("Default Name");
		BuildingDescription = FName("Default Description");
		BuildingTypes.Add(EBT_House);
		OpeningTime = ETime::ET_0000;
		ClosingTime = ETime::ET_0000;
		MaxWorkingHours = 8;
	}
};

USTRUCT(BlueprintType)
struct FWorkforceStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Workforce Struct")
	class ANPCCharacter* NPCWhoWorksHere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
	ETime StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building Struct")
	ETime EndTime;
};

UCLASS()
class NPCTEST_API ABuildingBaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBaseClass();

	void AdjustCondition(const float AmountToAdjust);
	float GetCondition() const { return Condition; }
	void GetOpeningTimes(ETime& OpeningTime, ETime& ClosingTime, int32& MaxWorkingHours) const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	class UBoxComponent* MainEntranceBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	UBoxComponent* SecondEntranceBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	FBuildingStruct BuildingStruct;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	TArray<FWorkforceStruct> WorkforceArray;

	// The amount the condition of this building falls per day through normal wear and tear
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	float DegradationPerDay;

	// Amount this building costs to use if a bar or restaurant etc.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	float AmountToUse;

	// Amount this building pays its workers
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	float AmountToPay;

	// Maximum number of people who can work here
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Set Up")
	int32 MaxWorkers;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float Condition = 100.f;

	UFUNCTION()
	void MainEntranceBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void SecondEntranceBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void MainEntranceEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void SecondEntranceEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool CheckIfOverlappingWorksHere(AActor* OverlappingActor) const;

	int32 CurrentWorkers = 0;
};

