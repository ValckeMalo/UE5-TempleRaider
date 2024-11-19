#include "MyCharacter.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "Camera/CameraComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
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
		this->HandleComponent->GrabComponent(hitResult.GetComponent(), NAME_None, hitResult.Location, false);
		isGrabing = true;
	}
}

void AMyCharacter::Release()
{
	if (isGrabing)
	{
		this->HandleComponent->ReleaseComponent();
		isGrabing = false;
		this->HoldDistance = this->sightLenght;
	}
}

void AMyCharacter::CheckSight()
{
	if (!isGrabing)
	{
		GetWorld()->LineTraceSingleByChannel(this->hitResult, this->CameraComponent->GetComponentLocation(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->sightLenght, ECollisionChannel::ECC_Visibility);
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
	if (!hitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Actor found"));
		return false;
	}
	return true;
}