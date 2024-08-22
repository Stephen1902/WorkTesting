// Copyright 2024 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReppedActor.generated.h"

UCLASS()
class NPCTEST_API AReppedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReppedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UTextRenderComponent* TextRenderComp;

public:	
	// BlueprintReadOnly,lled every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterial;

	UPROPERTY(ReplicatedUsing=OnRep_ColourChange)
	FLinearColor ColourToChangeTo;

	UFUNCTION()
	void OnRep_ColourChange();

	UPROPERTY(ReplicatedUsing=OnRep_CounterChanged)
	int32 TextRenderCounter;

	UFUNCTION()
	void OnRep_CounterChanged();
};
