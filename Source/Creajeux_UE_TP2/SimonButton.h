// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "SimonButton.generated.h"

class UStaticMeshComponent;
class ASimon_Manager;

UCLASS()
class CREAJEUX_UE_TP2_API ASimonButton : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	ASimonButton();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void PressButton_Implementation() override;

	void LightUp();
	void LightDown();
	void PressAnim();

	UPROPERTY(EditAnywhere) ASimon_Manager* simonManager = nullptr;

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* btnRingMesh = nullptr;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* btnPushMesh = nullptr;

	UPROPERTY(VisibleAnywhere) UMaterialInstanceDynamic* pushBtnMaterial = nullptr;
	UPROPERTY(EditAnywhere) FColor normalColor;
	UPROPERTY(EditAnywhere) FColor higlightColor;
};