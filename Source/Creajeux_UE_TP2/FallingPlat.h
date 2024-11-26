// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingPlat.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CREAJEUX_UE_TP2_API AFallingPlat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingPlat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DelayedDestActor();
	UFUNCTION(BlueprintCallable) void OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool FindStatus(int sequence);

	UPROPERTY(EditAnywhere) int sequenceIndex = 0;
	UPROPERTY(EditAnywhere) bool bIsFakeSeq0 = false;
	UPROPERTY(EditAnywhere) bool bIsFakeSeq1 = false;
	UPROPERTY(EditAnywhere) bool bIsFakeSeq2 = false;


	UPROPERTY(VisibleAnyWhere) USceneComponent* root;
	UPROPERTY(VisibleAnyWhere) UStaticMeshComponent* platMesh;
	UPROPERTY(EditAnywhere) UBoxComponent* collisionBox;
};
