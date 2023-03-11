// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Item.generated.h"

class USphereComponent;
class UWidgetComponent;
class UInventoryComponent;

USTRUCT()
struct FItemData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName ItemName = "ITEM_DEFAULT";

	UPROPERTY(EditAnywhere)
		FName ItemDisplayName = "Item Default";

	UPROPERTY(EditAnywhere)
		FName ItemDescription = "Item Default";

	UPROPERTY(EditAnywhere)
		float ItemWeight = 0.0f;

	UPROPERTY(EditAnywhere)
		UTexture2D* InventoryThumbnail;
};

UCLASS()
class PROJECT_MOON_API AItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void UseItem();

protected:

	UPROPERTY(EditAnywhere)
		USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Data")
		FItemData ItemData;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractHintWidget;

	UInventoryComponent* InventoryComponent;

protected:

	virtual void Interact() override;

	virtual void SetShowInteractHintWidget(bool bVisible) override;

	virtual void SetShowInteractWidget(bool bVisible) override;

private:
	
	void SetupWidgets();

	void SetupInventoryComponent();

public:
	FItemData GetItemData() const;
};
