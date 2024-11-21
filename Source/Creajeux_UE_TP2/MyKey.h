// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grabbable.h"
#include "MyKey.generated.h"

UCLASS()
class CREAJEUX_UE_TP2_API AMyKey : public AActor ,public IGrabbable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
