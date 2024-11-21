#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Character.h>
#include <Camera/CameraComponent.h>
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "MyCharacter.generated.h"

UCLASS()
class CREAJEUX_UE_TP2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere) UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere) FHitResult hitResult;
	UPROPERTY(VisibleAnywhere) UPhysicsHandleComponent* HandleComponent;

	UPROPERTY(EditAnywhere) float sightLenght = 300.f;
	UPROPERTY(EditAnywhere) float scrollPower = 3.f;

public:
	UFUNCTION(BlueprintCallable) void Interact();
	UFUNCTION(BlueprintCallable) void Scroll(float Direction);
	UFUNCTION(BlueprintCallable) void Grab();
	UFUNCTION(BlueprintCallable) void Release();
	UFUNCTION(BlueprintCallable) bool IsImplementingInteractInterface(AActor* Actor);
	UFUNCTION(BlueprintCallable) void ResetActorInSight();

private:
	float HoldDistance;
	bool isGrabing = false;
	AActor* ActorInSight = nullptr;

	void CheckSight();
	void UpdateHandleLocation();
	bool CanGrabActor(FHitResult Hit);
};