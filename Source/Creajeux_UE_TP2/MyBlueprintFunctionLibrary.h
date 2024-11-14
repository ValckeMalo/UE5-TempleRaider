// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class CREAJEUX_UE_TP2_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector GetDirectionBetweenTwoActors(const AActor* fromActor, const AActor* toActor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetDistanceFromActorToPoint(const AActor* fromActor, const FVector toPoint);

	UFUNCTION(BlueprintCallable)
	static void PlaysoundAtRandomizedPitch(const UObject* worldContextObject, USoundBase* sound, FVector location, float minPitch, float maxPitch);

	UFUNCTION(BlueprintCallable)
	static void SpawnParticleAtActorLocation(UParticleSystem* particleSystem, const AActor* actor);

	UFUNCTION(BlueprintCallable)
	static void SetObjectMaterialWithIndex(UMeshComponent* meshComponent, UMaterial* material, int materialIndex);

	UFUNCTION(BlueprintCallable)
	static void RotateActorTowardsTarget(AActor* actor, const AActor* target, float rotationSpeed, float deltaTime);

	UFUNCTION(BlueprintCallable)
	static void DisableMultipleActor(TArray<AActor*> actors, bool disable);

	UFUNCTION(BlueprintCallable)
	static void ModifyActorScaleOverTime(AActor* actor, FVector targetScale, float scaleSpeed, float deltaTime);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool CheckIfActorIsInLineOfSigth(const AActor* fromActor, const AActor* toActor, const ECollisionChannel traceChannel, const bool drawDebug);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static AActor* FindClosestActorOfClass(const TSubclassOf<AActor> actorClass, const AActor* fromActor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector2D GetScreenPositionForObject(const APlayerController* playerController, const AActor* actor);
};