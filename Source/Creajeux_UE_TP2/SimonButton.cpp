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
	pushBtnMaterial->SetVectorParameterValue("Color_Tint_R", this->color);
	LightDown();
}

void ASimonButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimonButton::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	pushBtnMaterial = btnPushMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (pushBtnMaterial)
	{
		pushBtnMaterial->SetVectorParameterValue("Color_Tint_R", color);
		pushBtnMaterial->SetScalarParameterValue("EmissiveStrength_Final", 0.f);
	}
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
	pushBtnMaterial->SetScalarParameterValue("EmissiveStrength_Final", 1.f);
}

void ASimonButton::LightDown()
{
	pushBtnMaterial->SetScalarParameterValue("EmissiveStrength_Final", 0.f);
}

void ASimonButton::PressAnim()
{
	LightUp();

	FTimerHandle PlaySequenceTimer;
	GetWorldTimerManager().SetTimer(PlaySequenceTimer, this, &ASimonButton::LightDown, 0.8f, false);
}