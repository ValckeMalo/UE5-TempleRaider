// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingPlat_Manager.generated.h"

class UBillboardComponent;

UCLASS()
class CREAJEUX_UE_TP2_API AFallingPlat_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	AFallingPlat_Manager();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform &transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable) void RefreshPreview();

	UPROPERTY() USceneComponent* root;
	UPROPERTY(VisibleAnywhere) UBillboardComponent* billboard = nullptr;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "2")) int sequenceIndex = 0;

};
