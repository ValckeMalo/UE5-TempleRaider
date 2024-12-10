#include "KeyTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Grabbable.h"
#include "Door.h"
#include "MyCharacter.h"

AKeyTrigger::AKeyTrigger()
{
	for (int i = 0; i < NB_LOCK; i++)
	{
		FString lockName = FString::Printf(TEXT("LockMesh_%d"), i);
		UStaticMeshComponent* currentLock = CreateDefaultSubobject<UStaticMeshComponent>(*lockName);
		currentLock->SetupAttachment(this->RootComponent);
		this->locks.Add(currentLock);
	}
}

void AKeyTrigger::BeginPlay()
{
	this->indexLock = 0;

	OnActorBeginOverlap.AddDynamic(this, &AKeyTrigger::OnOverlapBegin);
}

void AKeyTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OverlappedActor || !OtherActor) return;

	if (OtherActor->GetClass()->ImplementsInterface(UGrabbable::StaticClass()) && OtherActor->ActorHasTag(FName("Key")))
	{
		OtherActor->Tags.Remove("Key");
		Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->Release();
		OtherActor->AttachToComponent(this->locks[this->indexLock], FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		this->indexLock++;

		if (!this->door)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Door Found"));
			return;
		}

		if (this->indexLock >= this->locks.Num() && !this->door->IsDoorOpen())
		{
			TriggerOpenSequence();
		}
	}
}

void AKeyTrigger::TriggerOpenSequence()
{
	this->door->OpenDoor();

	for (int i = 0; i < this->locks.Num(); i++)
	{
		this->locks[i]->DestroyComponent();
		this->locks[i] = nullptr;
	}

	Destroy();
}