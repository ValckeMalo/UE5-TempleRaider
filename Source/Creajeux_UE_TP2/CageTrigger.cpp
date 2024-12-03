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

	if (isLerping && MovingActorRef)
	{

		FVector CurrentLocation = MovingActorRef->GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, deltaTime, lerpSpeed);
		MovingActorRef->SetActorLocation(NewLocation);


		if (FVector::Dist(NewLocation, TargetLocation) < UE_KINDA_SMALL_NUMBER)
		{
			isLerping = false;
		}
	}
}

void ACageTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this) && OtherActor->GetClass()->ImplementsInterface(UGrabbable::StaticClass()))
	{
		if (MovingActorRef)
		{
			TargetLocation = StartingLocation;
			isLerping = true;
		}
	}
}

void ACageTrigger::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this) && OtherActor->GetClass()->ImplementsInterface(UGrabbable::StaticClass()))
	{
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);
		if (MovingActorRef && !IsOverlappingActor(this) && OverlappingActors.Num() == 0)
		{
			TargetLocation = EndLocation;
			isLerping = true;
		}
	}
}