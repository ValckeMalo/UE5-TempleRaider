#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

FVector UMyBlueprintFunctionLibrary::GetDirectionBetweenTwoActors(const AActor* fromActor, const AActor* toActor)
{
	return (toActor->GetActorLocation() - fromActor->GetActorLocation());
}

float UMyBlueprintFunctionLibrary::GetDistanceFromActorToPoint(const AActor* fromActor, const FVector toPoint)
{
	return FVector::Dist(fromActor->GetActorLocation(), toPoint);
}

void UMyBlueprintFunctionLibrary::PlaysoundAtRandomizedPitch(const UObject* worldContextObject, USoundBase* sound, FVector location, float minPitch, float maxPitch)
{
	UGameplayStatics::PlaySoundAtLocation(worldContextObject, sound, location, 1.0f, FMath::RandRange(minPitch, maxPitch));
}

void UMyBlueprintFunctionLibrary::SpawnParticleAtActorLocation(UParticleSystem* particleSystem, const AActor* actor)
{
	UGameplayStatics::SpawnEmitterAtLocation(actor->GetWorld(), particleSystem, actor->GetActorTransform());
}

void UMyBlueprintFunctionLibrary::SetObjectMaterialWithIndex(UMeshComponent* meshComponent, UMaterial* material, int materialIndex)
{
	meshComponent->SetMaterial(materialIndex, material);
}

void UMyBlueprintFunctionLibrary::RotateActorTowardsTarget(AActor* actor, const AActor* target, float rotationSpeed, float deltaTime)
{
	FVector actorLocation = actor->GetActorLocation();
	FVector targetLocation = target->GetActorLocation();

	FRotator desiredRotation = UKismetMathLibrary::FindLookAtRotation(actorLocation, targetLocation);

	FRotator currentRotation = actor->GetActorRotation();

	FRotator newRotation = FMath::RInterpTo(currentRotation, desiredRotation, deltaTime, rotationSpeed);

	actor->SetActorRotation(newRotation);
}

void UMyBlueprintFunctionLibrary::DisableMultipleActor(TArray<AActor*> actors, bool disable)
{
	for (AActor* actor : actors)
	{
		if (!actor) continue;

		actor->SetActorHiddenInGame(disable);
	}
}

void UMyBlueprintFunctionLibrary::ModifyActorScaleOverTime(AActor* actor, FVector targetScale, float scaleSpeed, float deltaTime)
{
	actor->SetActorScale3D(FMath::Lerp(actor->GetActorScale3D(), targetScale, deltaTime * scaleSpeed));
}

bool UMyBlueprintFunctionLibrary::CheckIfActorIsInLineOfSigth(const AActor* fromActor, const AActor* toActor, const ECollisionChannel traceChannel, const bool drawDebug)
{
	FHitResult result;
	FVector fromActorLocation = fromActor->GetActorLocation();
	float lineLenght = (fromActorLocation - toActor->GetActorLocation()).Length();

	if (drawDebug)
	{
		DrawDebugLine(fromActor->GetWorld(), fromActorLocation, fromActorLocation * lineLenght, FColor(255, 0, 0));
	}

	return fromActor->GetWorld()->LineTraceSingleByChannel(result, fromActorLocation, fromActorLocation * lineLenght, traceChannel);
}

AActor* UMyBlueprintFunctionLibrary::FindClosestActorOfClass(const TSubclassOf<AActor> actorClass, const AActor* fromActor)
{
	TArray<AActor*> actorsClass;
	UGameplayStatics::GetAllActorsOfClass(fromActor->GetWorld(), actorClass, actorsClass);

	float closestDist = -1.0f;
	AActor* closestActor = nullptr;

	for (AActor* actor : actorsClass)
	{
		if (!actor)continue;

		float dist = (fromActor->GetActorLocation() - actor->GetActorLocation()).Length();
		if (closestDist == -1.0f || dist < closestDist)
		{
			closestDist = dist;
			closestActor = actor;
		}
	}

	return closestActor;
}

FVector2D UMyBlueprintFunctionLibrary::GetScreenPositionForObject(const APlayerController* playerController, const AActor* actor)
{
	FVector actorLocation = actor->GetActorLocation();
	FVector2D actorLoactionOnScreen;
	playerController->ProjectWorldLocationToScreen(actorLocation, actorLoactionOnScreen);
	return actorLoactionOnScreen;
}

void UMyBlueprintFunctionLibrary::ApplyRadialForceToObjects(const UObject* worldContextObject, const FVector origin, const float radius, const float strength, const bool impulse)
{
	TArray<AActor*> hitActors;
	TArray<FHitResult> HitResults;
	bool hit = UKismetSystemLibrary::SphereTraceMulti(worldContextObject, origin, origin, radius, UEngineTypes::ConvertToTraceType(ECC_PhysicsBody), true, {}, EDrawDebugTrace::ForDuration, HitResults, true, FLinearColor::Red, FLinearColor::Green, 0.0f);

	if (hit)
	{
		for (const FHitResult hitResult : HitResults)
		{
			AActor* HitActor = hitResult.GetActor();
			if (HitActor)
			{
				UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(HitActor->GetRootComponent());
				if (primitive && primitive->IsSimulatingPhysics())
				{
					FVector forceDirection = (HitActor->GetActorLocation() - origin).GetSafeNormal();
					if (impulse)
					{
						primitive->AddImpulse(forceDirection * strength, NAME_None, true);
					}
					else
					{
						primitive->AddForce(forceDirection * strength, NAME_None, true);
					}
				}
			}
		}
	}
}