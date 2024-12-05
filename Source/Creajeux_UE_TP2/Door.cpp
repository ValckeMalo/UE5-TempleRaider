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

	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "RotateDoors", this->doorRightMesh->GetRelativeRotation(), this->doorLeftMesh->GetRelativeRotation(), FRotator(0.f, 90.f, 0.f), FRotator(0.f, -90.f, 0.f));
	GetWorldTimerManager().SetTimer(this->timerDoor, Delegate, 0.01f, true);

	this->isOpen = true;
}

void ADoor::CloseDoor()
{
	GetWorldTimerManager().ClearTimer(this->timerDoor);

	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "RotateDoors", this->doorRightMesh->GetRelativeRotation(), this->doorLeftMesh->GetRelativeRotation(), FRotator::ZeroRotator, FRotator::ZeroRotator);
	GetWorldTimerManager().SetTimer(this->timerDoor, Delegate, 0.01f, true);

	this->isOpen = false;
}

bool ADoor::IsDoorOpen()
{
	return this->isOpen;
}

void ADoor::RotateDoors(FRotator startRight, FRotator startLeft, FRotator targetRight, FRotator targetLeft)
{
	this->timeElapsed += GetWorld()->GetDeltaSeconds();

	this->doorRightMesh->SetRelativeRotation(FMath::Lerp(startRight, targetRight, this->timeElapsed));
	this->doorLeftMesh->SetRelativeRotation(FMath::Lerp(startLeft, targetLeft, this->timeElapsed));

	if (timeElapsed >= duration)
	{
		GetWorldTimerManager().ClearTimer(this->timerDoor);
	}
}