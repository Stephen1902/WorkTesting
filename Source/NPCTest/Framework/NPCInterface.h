// Copyright 2024 DME Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NPCInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNPCInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NPCTEST_API INPCInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "NPC Functions")
	FString ReactToTimeChange();
};
