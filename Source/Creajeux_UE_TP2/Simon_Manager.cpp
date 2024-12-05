#include "Simon_Manager.h"
#include "SimonButton.h"

ASimon_Manager::ASimon_Manager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASimon_Manager::BeginPlay()
{
	Super::BeginPlay();
}

void ASimon_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimon_Manager::PlaySequence()
{
	if (!this->Sequences.IsEmpty())
	{
		TArray<ASimonButton*> currentSequence = this->Sequences[this->currentIndexSequence].Buttons;
		if (!currentSequence.IsEmpty())
		{
			int index = 0;
			for (ASimonButton* btn : currentSequence)
			{
				if (btn == nullptr) continue;

				if (!index)
				{
					btn->PressAnim();
				}
				else
				{
					FTimerHandle PlaySequenceTimer;
					GetWorldTimerManager().SetTimer(PlaySequenceTimer, btn, &ASimonButton::PressAnim, 0.9f * index, false);
				}
				index++;
			}
		}
	}
}

void ASimon_Manager::ButtonPressed(ASimonButton* Button)
{
	if (Button == resetButton)
	{
		if (isReset)
		{
			isReset = false;
			PlaySequence();
		}
		else
		{
			isReset = true;
			Reset();
		}
	}
	else
	{
		CheckSequence(Button);
	}
}

void ASimon_Manager::CheckSequence(ASimonButton* Button)
{
	if (Button == this->Sequences[this->currentIndexSequence].Buttons[this->indexInSequence])
	{
		this->indexInSequence++;

		if (this->indexInSequence >= this->Sequences[this->currentIndexSequence].Buttons.Num())
		{

			this->indexInSequence = 0;
			this->currentIndexSequence++;

			if (this->currentIndexSequence >= this->Sequences.Num())
			{
				Reset();
				TriggerWinProcess();
			}
			else
			{
				FTimerHandle PlaySequenceTimer;
				GetWorldTimerManager().SetTimer(PlaySequenceTimer, this, &ASimon_Manager::PlaySequence, 1.f, false);
			}
		}
	}
	else
	{
		Reset();
	}
}

void ASimon_Manager::TriggerWinProcess()
{
	isWin = true;
	if (door)
	{
		door->OpenDoor();
	}
}

int ASimon_Manager::GetSequence()
{
	return this->currentIndexSequence;
}

void ASimon_Manager::Reset()
{
	this->currentIndexSequence = 0;
	this->indexInSequence = 0;
}