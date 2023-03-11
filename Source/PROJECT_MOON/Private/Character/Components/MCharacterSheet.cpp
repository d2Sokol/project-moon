// All rights reserved


#include "Character/Components/MCharacterSheet.h"

UMCharacterSheet::UMCharacterSheet()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMCharacterSheet::BeginPlay()
{
	Super::BeginPlay();

	
}

void UMCharacterSheet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UMCharacterSheet::GetHealth() const
{
	return Health;
}

float UMCharacterSheet::GetMaxHealth() const
{
	return MaxHealth;
}

void UMCharacterSheet::SetHealth(float NewValue)
{
	Health = NewValue;
}

void UMCharacterSheet::SetMaxHealth(float NewValue)
{
	MaxHealth = NewValue;
}

void UMCharacterSheet::AddHealth(float AddValue)
{
	Health += AddValue;
}

