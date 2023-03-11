// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

class AItem;
class UWidgetAnimation;
class UButton;
class UImage;
class UTextBlock;
class UCanvasPanel;
class UInventoryWidget;

UCLASS()
class PROJECT_MOON_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryItemWidget(const FObjectInitializer& ObjectInitializer);

	/*virtual void NativeConstruct() override;*/

	void PlayItemHUDAnimation(FString AnimationName);

	void SetupWidget(AItem* ItemRef);

	void SetOwnerRef(UInventoryWidget* InvWidgetRef);

	AItem* GetItemReference() const;

private:
	AItem* Item;

	UInventoryWidget* OwnerWidget;

	UImage* ItemThumbnail;

	UTextBlock* ItemWeight;

	UButton* ItemButton;

	bool bActionsVisible;

private:

	UFUNCTION(BlueprintCallable)
		void ItemButtonOnClicked();

	UFUNCTION(BlueprintCallable)
		void ItemButtonOnHovered();

	UFUNCTION(BlueprintCallable)
		void ItemButtonOnUnhovered();

	UWidgetAnimation* GetWidgetAnimation(FString AnimationName) const;

	template <typename T>
	T* GetWidgetReference(FName WidgetName);

};

template<typename T>
inline T* UInventoryItemWidget::GetWidgetReference(FName WidgetName)
{
	if (T* Widget = dynamic_cast<T*>(GetWidgetFromName(WidgetName)))
	{
		return Widget;
	}

	return nullptr;
}
