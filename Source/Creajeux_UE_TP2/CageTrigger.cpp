// Fill out your copyright notice in the Description page of Project Settings.
#include "CageTrigger.h"
#include "Engine/StaticMeshActor.h"
#include "Grabbable.h"

ACageTrigger::ACageTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACageTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACageTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACageTrigger::OnOverlapEnd);

	if (MovingActorRef)
	{
		StartingLocation = MovingActorRef->GetActorLocation();
		EndLocation = StartingLocation;
		EndLocation.Z = EndZLocation;
	}
}

void ACageTrigger::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Tick"));

	if (isLerping && MovingActorRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interp"));

		FVector CurrentLocation = MovingActorRef->GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, deltaTime, lerpSpeed);
		MovingActorRef->SetActorLocation(NewLocation);

		UE_LOG(LogTemp, Warning, TEXT("Interp"));

		if (FVector::Dist(NewLocation, TargetLocation) < UE_KINDA_SMALL_NUMBER)
		{
			isLerping = false;
		}
	}
}

void ACageTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Start"));

	if (OtherActor && (OtherActor != this) && OtherActor->GetClass()->ImplementsInterface(UGrabbable::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("OK"));

		if (MovingActorRef)
		{
			TargetLocation = StartingLocation;
			isLerping = true;
		}
	}
}

void ACageTrigger::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("End"));

	if (OtherActor && (OtherActor != this) && OtherActor->GetClass()->ImplementsInterface(UGrabbable::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("OK"));

		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);
		if (MovingActorRef && !IsOverlappingActor(this) && OverlappingActors.Num() == 0)
		{
			TargetLocation = EndLocation;
			isLerping = true;
		}
	}
}