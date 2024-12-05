#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Engine/TriggerCapsule.h"
#include "Door.h"
#include "ScalePuzzle.generated.h"

UCLASS()
class CREAJEUX_UE_TP2_API AScalePuzzle : public ATriggerCapsule
{
	GENERATED_BODY()
public:
	AScalePuzzle();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent) void OnWeightChanged(float weight, FColor BarColor);
	UFUNCTION() void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION() void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	FColor SetBarColor(float weight);
	void CheckSuccess(float weightPercent);


	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.1f, UIMax = 500.f)) float targetWeight = 100.f;
	UPROPERTY(EditAnywhere) ADoor* door = nullptr;
	UPROPERTY(VisibleAnywhere) float currentWeight = 0.f;
};
