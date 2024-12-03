#include "SimonButton.h"
#include "Components/StaticMeshComponent.h"
#include "Simon_Manager.h"

ASimonButton::ASimonButton()
{
	PrimaryActorTick.bCanEverTick = true;

	btnRingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingMesh"));
	btnPushMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PushMesh"));

	btnRingMesh->SetupAttachment(RootComponent);
	btnPushMesh->SetupAttachment(btnRingMesh);
}

void ASimonButton::BeginPlay()
{
	Super::BeginPlay();

	pushBtnMaterial = btnPushMesh->CreateDynamicMaterialInstance(0);
	LightDown();
}

void ASimonButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimonButton::PressButton_Implementation()
{
	if (simonManager)
	{
		simonManager->ButtonPressed(this);
		PressAnim();
	}
}

void ASimonButton::LightUp()
{
	pushBtnMaterial->SetVectorParameterValue("Color_Tint_R", this->higlightColor);
}

void ASimonButton::LightDown()
{
	pushBtnMaterial->SetVectorParameterValue("Color_Tint_R", this->normalColor);
}

void ASimonButton::PressAnim()
{
	LightUp();

	UE_LOG(LogTemp, Display, TEXT("Press Anim"));

	FTimerHandle PlaySequenceTimer;
	GetWorldTimerManager().SetTimer(PlaySequenceTimer, this, &ASimonButton::LightDown, 0.8f, false);
}