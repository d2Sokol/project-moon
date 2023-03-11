// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Interactable/Item.h"
#include "PickupItem.generated.h"

UENUM(BlueprintType)
enum EPickupType
{
	USABLE = 0 UMETA(DisplayName = "Usable Item"),
	MISC UMETA(DisplayName = "Misc Item"),
	DEFAULT UMETA(DisplayName = "Default")
};

UCLASS()
class PROJECT_MOON_API APickupItem : public AItem
{
	GENERATED_BODY()

public:
	APickupItem();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Pickup Data")
		TEnumAsByte<EPickupType> PickupType;
};
