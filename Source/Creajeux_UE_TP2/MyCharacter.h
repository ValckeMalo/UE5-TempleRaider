#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "MyCharacter.generated.h"

UCLASS()
class CREAJEUX_UE_TP2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	float sightLenght = 5.f;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 5.f;

	UPROPERTY(EditAnywhere)
	FHitResult hitResult;

	UPROPERTY(VisibleAnywhere)
	UPhysicsHandleComponent* HandleComponent;

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void Scroll(float Direction);

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	void CheckSight();
	void UpdateHandleLocation();
	bool CanGrabActor(FHitResult Hit);
};