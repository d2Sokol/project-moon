// All rights reserved


#include "Widgets/InventoryItemWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Interactable/Item.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Widgets/InventoryWidget.h"

UInventoryItemWidget::UInventoryItemWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bActionsVisible = false;
}

void UInventoryItemWidget::PlayItemHUDAnimation(FString AnimationName)
{
	PlayAnimation(GetWidgetAnimation(AnimationName));
}

void UInventoryItemWidget::SetupWidget(AItem* ItemRef)
{
	Item = ItemRef;
	
	ItemThumbnail = GetWidgetReference<UImage>("ItemThumbnail");
	ItemWeight = GetWidgetReference<UTextBlock>("ItemWeight");

	if (ItemThumbnail == nullptr) { return; }
	if (ItemWeight == nullptr) { return; }

	ItemThumbnail->SetBrushFromTexture(Item->GetItemData().InventoryThumbnail);
	FNumberFormattingOptions FormattingOptions;
	FormattingOptions.SetMaximumFractionalDigits(3);
	FormattingOptions.SetMinimumFractionalDigits(2);
	ItemWeight->SetText(FText::AsNumber(Item->GetItemData().ItemWeight, &FormattingOptions));

	ItemButton = GetWidgetReference<UButton>("ItemButton");

}

void UInventoryItemWidget::SetOwnerRef(UInventoryWidget* InvWidgetRef)
{
	OwnerWidget = InvWidgetRef;
}

AItem* UInventoryItemWidget::GetItemReference() const
{
	return Item;
}

void UInventoryItemWidget::ItemButtonOnClicked()
{

	OwnerWidget->ShowItemActions(Item);
}

void UInventoryItemWidget::ItemButtonOnHovered()
{
	if(ItemButton)
		ItemButton->SetBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.3f));
}

void UInventoryItemWidget::ItemButtonOnUnhovered()
{
	if (ItemButton)
		ItemButton->SetBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
}

UWidgetAnimation* UInventoryItemWidget::GetWidgetAnimation(FString AnimationName) const
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	for (UWidgetAnimation* WidgetAnimation : WidgetClass->Animations)
	{
		if (WidgetAnimation->GetName() == AnimationName)
		{
			return WidgetAnimation;
		}
	}

	return nullptr;
}