// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CageTrigger.generated.h"

/**
 *
 */

class AStaticMeshActor;

UCLASS()
class CREAJEUX_UE_TP2_API ACageTrigger : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	ACageTrigger();
	virtual void Tick(float deltaTime) override;

	UFUNCTION() void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION() void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	FVector StartingLocation;
	FVector EndLocation;
	UPROPERTY(EditAnywhere) float EndZLocation = 0.f;
	bool isLerping = false;
	UPROPERTY(EditAnywhere) float lerpSpeed = 5.f;
	FVector TargetLocation;
	UPROPERTY(EditAnywhere) AStaticMeshActor* MovingActorRef;
};