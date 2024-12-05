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
	UFUNCTION() void RotateDoors(FRotator startRight, FRotator startLeft, FRotator targetRight, FRotator targetLeft);

	float timeElapsed = 0.f;
	float duration = 1.f;
	FTimerHandle timerDoor;
	bool isOpen = false;
public:
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();
	void CloseDoor();
	bool IsDoorOpen();

	UPROPERTY(EditAnywhere) UStaticMeshComponent* frameMesh = nullptr;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* doorLeftMesh = nullptr;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* doorRightMesh = nullptr;
};
