// Copyright 2024 DME Games


#include "ReppedActor.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AReppedActor::AReppedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	CollisionComp->SetupAttachment(RootComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Comp");
	MeshComp->SetupAttachment(CollisionComp);
	MeshComp->SetIsReplicated(true);

	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	TextRenderComp->SetupAttachment(MeshComp);
	TextRenderComp->SetIsReplicated(true);

	TextRenderCounter = 0;
}

// Called when the game starts or when spawned
void AReppedActor::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* CurrentMat = MeshComp->GetMaterial(0);
	DynMaterial = UMaterialInstanceDynamic::Create(CurrentMat, this);
	MeshComp->SetMaterial(0, DynMaterial);

	if (HasAuthority())
	{
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AReppedActor::OnBeginOverlap);
	}
}

// Called every frame
void AReppedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReppedActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	const float RGBRed = UKismetMathLibrary::RandomFloat();
	const float RGBGreen = UKismetMathLibrary::RandomFloat();
	const float RGBBlue = UKismetMathLibrary::RandomFloat();

	ColourToChangeTo = FLinearColor(RGBRed, RGBGreen, RGBBlue);
	if (HasAuthority())
	{
		OnRep_ColourChange();
	}

	TextRenderCounter += 1;
	if (HasAuthority())
	{
		OnRep_CounterChanged();
	}
}

void AReppedActor::OnRep_ColourChange()
{
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("MatColour", ColourToChangeTo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Something tried to change material but DynMaterial is not valid."));
	}
}

void AReppedActor::OnRep_CounterChanged()
{
	TextRenderComp->SetText(FText::FromString(FString::FromInt((TextRenderCounter))));
}

void AReppedActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AReppedActor, ColourToChangeTo);
	DOREPLIFETIME(AReppedActor, TextRenderCounter);
}
