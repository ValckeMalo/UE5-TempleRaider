// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.h"
#include "Simon_Manager.generated.h"

class ASimonButton;

USTRUCT(BlueprintType)
struct FSimonButtonSequence
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TArray<ASimonButton*> Buttons;
};

UCLASS()
class CREAJEUX_UE_TP2_API ASimon_Manager : public AActor
{
	GENERATED_BODY()

public:
	ASimon_Manager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void PlaySequence();
	void ButtonPressed(ASimonButton* Button);
	void CheckSequence(ASimonButton* Button);
	void TriggerWinProcess();
	int GetSequence();
	void Reset();

	UPROPERTY(EditAnywhere) ADoor* door;
	UPROPERTY(EditAnywhere) ASimonButton* resetButton = nullptr;
	UPROPERTY(EditAnywhere) TArray<FSimonButtonSequence> Sequences;
	int currentIndexSequence = 0;
	int indexInSequence = 0;
	bool isWin = false;
	bool isReset = true;
};
