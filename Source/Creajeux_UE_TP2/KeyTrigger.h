#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "KeyTrigger.generated.h"

#define NB_LOCK 4

class UStaticMeshComponent;
class ADoor;

UCLASS()
class CREAJEUX_UE_TP2_API AKeyTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	AKeyTrigger();
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION() void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	void TriggerOpenSequence();

	UPROPERTY(VisibleAnywhere) TArray<UStaticMeshComponent*> locks = {};
	UPROPERTY(EditAnywhere) ADoor* door = nullptr;
	int indexLock = 0;
};
