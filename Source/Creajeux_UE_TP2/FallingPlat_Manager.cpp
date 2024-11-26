// Fill out your copyright notice in the Description page of Project Settings.

#include "FallingPlat_Manager.h"
#include "Components/BillboardComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FallingPlat.h"

// Sets default values
AFallingPlat_Manager::AFallingPlat_Manager()
{
	PrimaryActorTick.bCanEverTick = true;

	this->root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->root->SetupAttachment(this->RootComponent);

	this->billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	this->billboard->SetupAttachment(this->root);
}

// Called when the game starts or when spawned
void AFallingPlat_Manager::BeginPlay()
{
	Super::BeginPlay();
	RefreshPreview();
	this->sequenceIndex = FMath::RandRange(0, 2);
}

void AFallingPlat_Manager::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	RefreshPreview();
}

// Called every frame
void AFallingPlat_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFallingPlat_Manager::RefreshPreview()
{
	TArray<AActor*> fallingsPlat;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFallingPlat::StaticClass(), fallingsPlat);

	for (AActor* actorFound : fallingsPlat)
	{
		AFallingPlat* fallingPlat = Cast<AFallingPlat>(actorFound);
		if (fallingPlat)
		{
			fallingPlat->sequenceIndex = this->sequenceIndex;
			DrawDebugSphere(GetWorld(), fallingPlat->GetActorLocation(), 150, 16, fallingPlat->FindStatus(this->sequenceIndex) ? FColor::Red : FColor::Green,true);
		}
	}
}