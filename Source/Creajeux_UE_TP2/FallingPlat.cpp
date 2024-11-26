// Fill out your copyright notice in the Description page of Project Settings.

#include "FallingPlat.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FallingPlat_Manager.h"
#include "TimerManager.h"
#include "MyCharacter.h"

// Sets default values
AFallingPlat::AFallingPlat()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->root->SetupAttachment(this->RootComponent);

	this->platMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plat Mesh"));
	this->platMesh->SetupAttachment(this->root);

	this->collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	this->collisionBox->SetupAttachment(this->platMesh);
}

void AFallingPlat::BeginPlay()
{
	Super::BeginPlay();
	this->collisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFallingPlat::OnTriggerOverlap);
}

void AFallingPlat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFallingPlat::DelayedDestActor()
{
	Destroy();
}

void AFallingPlat::OnTriggerOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy"));

	if (FindStatus(sequenceIndex) && OtherActor->IsA(AMyCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy"));
		FTimerHandle PlaySequenceTimer;
		GetWorldTimerManager().SetTimer(PlaySequenceTimer, this, &AFallingPlat::DelayedDestActor, 0.8f, false);
	}
}

bool AFallingPlat::FindStatus(int sequence)
{
	if (!sequence && bIsFakeSeq0) //0
	{
		return true;
	}
	else if (sequence == 1 && bIsFakeSeq1) //1
	{
		return true;
	}
	else if (sequence == 2 && bIsFakeSeq2) //2
	{
		return true;
	}

	return false;
}