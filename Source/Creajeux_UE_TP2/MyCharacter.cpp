#include "MyCharacter.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "Camera/CameraComponent.h"
#include "InteractInterface.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	this->CameraComponent->bUsePawnControlRotation = true;
	this->CameraComponent->SetupAttachment(GetMesh());

	this->HandleComponent = CreateDefaultSubobject< UPhysicsHandleComponent>(TEXT("HandleComponent"));

	this->HoldDistance = this->sightLenght;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->HoldDistance = this->sightLenght;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckSight();
	UpdateHandleLocation();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyCharacter::Interact()
{
	if (IsImplementingInteractInterface(this->hitResult.GetActor()))
	{
		Cast<IInteractInterface>(this->ActorInSight)->Execute_PressButton(this->ActorInSight);
		UE_LOG(LogTemp, Warning, TEXT("Interact"));
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
	if (CanGrabActor(hitResult))
	{
		Cast<IInteractInterface>(hitResult.GetActor())->Execute_StopLookAt(hitResult.GetActor());
		this->HandleComponent->GrabComponent(hitResult.GetComponent(), NAME_None, hitResult.Location, false);
		this->isGrabing = true;
	}
}

void AMyCharacter::Release()
{
	if (this->isGrabing)
	{
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

void AMyCharacter::ResetActorInSight()
{
	if (this->ActorInSight)
	{
		Cast<IInteractInterface>(this->ActorInSight)->Execute_StopLookAt(this->ActorInSight);
		this->ActorInSight = nullptr;
	}
}

void AMyCharacter::CheckSight()
{
	GetWorld()->LineTraceSingleByChannel(this->hitResult, this->CameraComponent->GetComponentLocation(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->sightLenght, ECollisionChannel::ECC_Visibility);

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

	DrawDebugLine(GetWorld(), this->CameraComponent->GetComponentLocation(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->sightLenght, FColor::Blue);
}

void AMyCharacter::UpdateHandleLocation()
{
	FColor color = FColor::Red;
	if (isGrabing)
	{
		color = FColor::Green;
		this->HandleComponent->SetTargetLocation(this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->HoldDistance);
	}

	DrawDebugSphere(GetWorld(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->HoldDistance, 10, 32, color);
}

bool AMyCharacter::CanGrabActor(FHitResult Hit)
{
	if (isGrabing)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already grab something"));
		return false;
	}

	AActor* hitActor = Hit.GetActor();
	if (hitActor && IsImplementingInteractInterface(hitActor))
	{
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("No IInteractInterface found"));
	return false;
}