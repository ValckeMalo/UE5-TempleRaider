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
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

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
	UE_LOG(LogTemp, Warning, TEXT("Scroll : %f"), Direction);
}

void AMyCharacter::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab"));

	if (CanGrabActor(hitResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab COMPONENT"));
		this->HandleComponent->GrabComponent(hitResult.GetComponent(), NAME_None, hitResult.Location, false);
		UpdateHandleLocation();
	}
}

void AMyCharacter::Release()
{
	this->HandleComponent->ReleaseComponent();
}

void AMyCharacter::CheckSight()
{
	GetWorld()->LineTraceSingleByChannel(this->hitResult, this->CameraComponent->GetComponentLocation(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->sightLenght, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(), this->CameraComponent->GetComponentLocation(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->sightLenght, FColor::Red);
}

void AMyCharacter::UpdateHandleLocation()
{
	this->HandleComponent->SetTargetLocation(this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->HoldDistance);
	DrawDebugSphere(GetWorld(), this->CameraComponent->GetComponentLocation() + this->CameraComponent->GetForwardVector() * this->HoldDistance, 10, 32, FColor::Blue);
}

bool AMyCharacter::CanGrabActor(FHitResult Hit)
{
	AActor* hitActor = Hit.GetActor();
	if (!hitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("NoActor"));
		return false;
	}
	return true;
}