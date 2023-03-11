// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AItem;
class UInventoryWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MOON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Values")
		float InventoryWeight;

	UPROPERTY(EditAnywhere, Category = "Values")
		float MaxInventoryWeight;

	TArray<AItem*> Inventory;

	UInventoryWidget* InventoryWidget;

public:
	void AddItemToInventory(AItem* Item);

	void RemoveItemFromInventory(AItem* Item);

	bool CheckIfItemInInventory(AItem* Item);
	bool CheckIfItemInInventory(FName ItemName);

	void SetupInventoryWidgetRef();

	float GetCurrentInventoryWeight();
	float GetMaxInventoryWeight();

	void UseItem(AItem* Item);
	void DropItem(AItem* Item);
};
