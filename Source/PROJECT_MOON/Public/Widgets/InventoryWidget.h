// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UWidgetAnimation;
class AItem;
class UInventoryItemWidget;
class UBorder;
class UTextBlock;

UCLASS()
class PROJECT_MOON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, Category = "Subclass")
		TSubclassOf<UInventoryItemWidget> ItemWidgetClass;

public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

	void OnCreate();

	void PlayInventoryHUDAnimation(FString AnimationName);

	void AddItemToInventoryWidget(AItem* Item);

	void RemoveItemFromInventoryWidget(AItem* Item);

	void UpdateWeight(float CurrentInvWeight, float MaxInvWeight);

	void ShowItemActions(AItem* Item);

	void HideItemActions();

private:
	TArray<UInventoryItemWidget*> ItemsWidgets;

	UBorder* ItemActionsBorder;
	UTextBlock* CurrentWeight;
	UTextBlock* MaxWeight;

	AItem* SelectedItem;

private:

	UWidgetAnimation* GetWidgetAnimation(FString AnimationName) const;

	void UpdateInventoryWidget();

	template <typename T>
	T* GetWidgetReference(FName WidgetName);

protected:

	UFUNCTION(BlueprintCallable)
		void UseButtonClicked();

	UFUNCTION(BlueprintCallable)
		void DropButtonClicked();

	UFUNCTION(BlueprintCallable)
		void InspectButtonClicked();
};

template<typename T>
inline T* UInventoryWidget::GetWidgetReference(FName WidgetName)
{
	if(T* Widget = dynamic_cast<T*>(GetWidgetFromName(WidgetName)))
	{
		return Widget;
	}

	return nullptr;
}
