#include "ScalePuzzle.h"

AScalePuzzle::AScalePuzzle()
{
}

void AScalePuzzle::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AScalePuzzle::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AScalePuzzle::OnOverlapEnd);
}

void AScalePuzzle::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor)
	{
		currentWeight += OtherActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		float TempWeight = currentWeight / targetWeight;
		OnWeightChanged(TempWeight, SetBarColor(TempWeight));
	}
}

void AScalePuzzle::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor)
	{
		currentWeight -= OtherActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		float TempWeight = currentWeight / targetWeight;
		OnWeightChanged(TempWeight, SetBarColor(TempWeight));
	}
}

FColor AScalePuzzle::SetBarColor(float weightPercent)
{
	if (weightPercent < 1.f) //not enough
	{
		return FColor::Blue;
	}
	else if (weightPercent == 1.f) //good weight
	{
		return FColor::Green;
	}
	else //too much
	{
		return FColor::Red;
	}
}