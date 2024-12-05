#include "Door.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	frameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	doorLeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left Mesh"));
	doorRightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right Mesh"));

	frameMesh->SetupAttachment(this->RootComponent);
	doorLeftMesh->SetupAttachment(this->frameMesh);
	doorRightMesh->SetupAttachment(this->frameMesh);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaTime) {}

void ADoor::OpenDoor()
{
	GetWorldTimerManager().ClearTimer(this->timerDoor);
	GetWorldTimerManager().SetTimer(this->timerDoor, this, &ADoor::RotateDoors, 0.01f, true);
}

void ADoor::RotateDoors()
{
	this->timeElapsed += GetWorld()->GetDeltaSeconds();

	this->doorRightMesh->SetRelativeRotation(FMath::Lerp(FRotator::ZeroRotator, FRotator(0.f, 90.f, 0.f), this->timeElapsed));
	this->doorLeftMesh->SetRelativeRotation(FMath::Lerp(FRotator::ZeroRotator, FRotator(0.f, -90.f, 0.f), this->timeElapsed));

	if (timeElapsed >= duration)
	{
		GetWorldTimerManager().ClearTimer(this->timerDoor);
	}
}