// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UWidgetAnimation;
class UInventoryWidget;

UCLASS()
class PROJECT_MOON_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPlayerHUD(const FObjectInitializer& ObjectInitializer);
	
protected:

	UInventoryWidget* InventoryWidget;
	
public:
	void OnGameStart();

	void PlayHUDAnimation(FString AnimationName);

	void SetupInventoryWidget(TSubclassOf<UInventoryWidget>& InventoryWidgetClass);

	bool IsPlayerInventoryOpen();

	void ShowPlayerInventory(bool bShow);

	UInventoryWidget* GetInventoryWidget();
private:

	UWidgetAnimation* GetWidgetAnimation(FString AnimationName) const;
};
