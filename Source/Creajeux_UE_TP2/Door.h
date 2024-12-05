// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class CREAJEUX_UE_TP2_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	virtual void BeginPlay() override;
private:
	void RotateDoors();

	float timeElapsed = 0.f;
	float duration = 1.f;
	FTimerHandle timerDoor;

public:
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();

	UPROPERTY(EditAnywhere) UStaticMeshComponent* frameMesh = nullptr;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* doorLeftMesh = nullptr;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* doorRightMesh = nullptr;
};
