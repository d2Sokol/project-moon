// All rights reserved


#include "Character/Components/InventoryComponent.h"
#include "Interactable/Item.h"
#include "Character/MCharacter.h"
#include "Character/PlayerHUD.h"
#include "Widgets/InventoryWidget.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InventoryWeight = 0.0f;
	MaxInventoryWeight = 30.0f;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddItemToInventory(AItem* Item)
{
	if (Item == nullptr) { return; }

	if ((InventoryWeight + Item->GetItemData().ItemWeight) <= MaxInventoryWeight)
	{
		Inventory.Add(Item);
		InventoryWeight += Item->GetItemData().ItemWeight;
		if (InventoryWidget)
		{
			InventoryWidget->AddItemToInventoryWidget(Item);
			InventoryWidget->UpdateWeight(InventoryWeight, MaxInventoryWeight);
		}
	}
	else
	{
		// Inventory Full
		DropItem(Item);
	}
}

void UInventoryComponent::RemoveItemFromInventory(AItem* Item)
{
	if (Item == nullptr) { return; }

	if (CheckIfItemInInventory(Item))
	{
		InventoryWeight -= Item->GetItemData().ItemWeight;
		InventoryWidget->UpdateWeight(InventoryWeight, MaxInventoryWeight);
		InventoryWidget->RemoveItemFromInventoryWidget(Item);
		Inventory.Remove(Item);
	}
}

bool UInventoryComponent::CheckIfItemInInventory(AItem* Item)
{
	for (AItem* InventoryItem : Inventory)
	{
		if (InventoryItem == Item)
		{
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::CheckIfItemInInventory(FName ItemName)
{
	for (AItem* InventoryItem : Inventory)
	{
		if (InventoryItem->GetItemData().ItemName == ItemName)
		{
			return true;
		}
	}

	return false;
}

void UInventoryComponent::SetupInventoryWidgetRef()
{
	if (AMCharacter* Character = Cast<AMCharacter>(GetOwner()))
	{
		InventoryWidget = Character->GetPlayerHUD()->GetInventoryWidget();
		InventoryWidget->UpdateWeight(InventoryWeight, MaxInventoryWeight);
	}
}

float UInventoryComponent::GetCurrentInventoryWeight()
{
	return InventoryWeight;
}

float UInventoryComponent::GetMaxInventoryWeight()
{
	return MaxInventoryWeight;
}

void UInventoryComponent::UseItem(AItem* Item)
{
	RemoveItemFromInventory(Item);
	Item->UseItem();
	Item = nullptr;
}

void UInventoryComponent::DropItem(AItem* Item)
{
	if (AMCharacter* Character = Cast<AMCharacter>(GetOwner()))
	{
		RemoveItemFromInventory(Item);

		AItem* ItemToDrop = GetWorld()->SpawnActor<AItem>(Item->GetClass());
		Item = nullptr;

		FHitResult HitRes;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor((AActor*)Character);
		FVector DropLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f;
		DropLocation.X += FMath::RandRange(-20.0f, 20.0f);
		DropLocation.Y += FMath::RandRange(-50.0f, 50.0f);
		FVector EndRay = DropLocation;
		EndRay.Z -= 500.0f;

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitRes, DropLocation, EndRay, ECC_Camera, QueryParams);

		if (bHit)
		{
			ItemToDrop->SetActorLocation(HitRes.Location);
		}
		else
		{
			ItemToDrop->SetActorLocation(DropLocation);
		}
	}
}

