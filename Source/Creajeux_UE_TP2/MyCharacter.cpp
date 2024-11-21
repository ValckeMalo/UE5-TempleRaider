#include "MyCharacter.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "Camera/CameraComponent.h"
#include "InteractInterface.h"
#include "Grabbable.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	this->CameraComponent->bUsePawnControlRotation = true;
	this->CameraComponent->SetupAttachment(GetMesh());

	this->HandleComponent = CreateDefaultSubobject< UPhysicsHandleComponent>(TEXT("HandleComponent"));

	this->HoldDistance = this->sightLenght;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->HoldDistance = this->sightLenght;
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckSight();
	UpdateHandleLocation();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyCharacter::Interact()
{
	if (IsImplementingInteractInterface(this->hitResult.GetActor()))
	{
		Cast<IInteractInterface>(this->ActorInSight)->Execute_PressButton(this->ActorInSight);
	}
}

void AMyCharacter::Scroll(float Direction)
{
	if (isGrabing)
	{
		this->HoldDistance += Direction * scrollPower;
		this->HoldDistance = FMath::Clamp(this->HoldDistance, 100.f, this->sightLenght);
	}
}

void AMyCharacter::Grab()
{
	if (!this->isGrabing && CanGrabActor(hitResult))
	{
		this->GrabActor = hitResult.GetActor();
		Cast<IGrabbable>(this->GrabActor)->Execute_Grab(this->GrabActor);
		this->HandleComponent->GrabComponentAtLocation(hitResult.GetComponent(), NAME_None, hitResult.Location);
		this->isGrabing = true;
	}
}

void AMyCharacter::Release()
{
	if (this->isGrabing)
	{
		UE_LOG(LogTemp, Warning, TEXT("release"));
		ResetGrabActor();
		this->HandleComponent->ReleaseComponent();
		this->isGrabing = false;
		this->HoldDistance = this->sightLenght;
	}
}

bool AMyCharacter::IsImplementingInteractInterface(AActor* Actor)
{
	if (!Actor)
	{
		return false;
	}

	if (Actor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		return true;
	}

	return false;
}

bool AMyCharacter::IsImplementingIGrabbable(AActor* Actor)
{
	if (!Actor)
	{
		return false;
	}

	if (Actor->GetClass()->ImplementsInterface(UGrabbable::StaticClass()))
	{
		return true;
	}

	return false;
}

void AMyCharacter::ResetActorInSight()
{
	if (this->ActorInSight)
	{
		Cast<IInteractInterface>(this->ActorInSight)->Execute_StopLookAt(this->ActorInSight);
		this->ActorInSight = nullptr;
	}
}

void AMyCharacter::ResetGrabActor()
{
	if (this->GrabActor)
	{
		Cast<IGrabbable>(this->GrabActor)->Execute_Release(this->GrabActor);
		this->GrabActor = nullptr;
	}
}

void AMyCharacter::CheckSight()
{
	if (!this->isGrabing)
	{
		GetWorld()->LineTraceSingleByChannel(this->hitResult, this->CameraComponent->GetComponentLocation(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->sightLenght, ECollisionChannel::ECC_Visibility);
	}

	AActor* hitActor = this->hitResult.GetActor();
	if (hitActor)
	{
		if (hitActor != this->ActorInSight)
		{
			ResetActorInSight();
			if (IsImplementingInteractInterface(hitActor))
			{
				this->ActorInSight = hitActor;
				Cast<IInteractInterface>(hitActor)->Execute_LookAt(hitActor);
			}
		}
	}
	else
	{
		ResetActorInSight();
	}
}

void AMyCharacter::UpdateHandleLocation()
{
	if (isGrabing)
	{
		this->HandleComponent->SetTargetLocation(this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->HoldDistance);
	}

	DrawDebugSphere(GetWorld(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->HoldDistance, 10, 32, isGrabing ? FColor::Green : FColor::Red);
}

bool AMyCharacter::CanGrabActor(FHitResult Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("can grab"));

	AActor* hitActor = Hit.GetActor();
	if (hitActor && IsImplementingIGrabbable(hitActor))
	{
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No IGrabbable found"));
	return false;
}