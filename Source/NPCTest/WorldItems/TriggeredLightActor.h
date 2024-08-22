// Copyright 2024 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggeredLightActor.generated.h"

UCLASS()
class NPCTEST_API ATriggeredLightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggeredLightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Set up")
	USceneComponent* SceneComp;
	
	UPROPERTY(EditAnywhere, Category = "Set up")
	UStaticMeshComponent* DisplayMesh;

	UPROPERTY(EditAnywhere, Category = "Set up")
	ULightComponent* LightComp;


};
