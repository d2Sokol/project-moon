// All rights reserved


#include "Widgets/InventoryWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/WrapBox.h"
#include "Interactable/Item.h"
#include "Components/Button.h"
#include "Widgets/InventoryItemWidget.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Character/MCharacter.h"
#include "Character/Components/InventoryComponent.h"


UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UInventoryWidget::OnCreate()
{
	ItemActionsBorder = GetWidgetReference<UBorder>("ItemActionsBorder");
	ItemActionsBorder->SetVisibility(ESlateVisibility::Hidden);
	ItemActionsBorder->SetRenderOpacity(0.0f);

	CurrentWeight = GetWidgetReference<UTextBlock>("CurrentWeight");
	MaxWeight = GetWidgetReference<UTextBlock>("MaxWeight");
}

void UInventoryWidget::PlayInventoryHUDAnimation(FString AnimationName)
{
	PlayAnimation(GetWidgetAnimation(AnimationName));
}

void UInventoryWidget::AddItemToInventoryWidget(AItem* Item)
{
	if (ItemWidgetClass == nullptr) { return; }
	
	UInventoryItemWidget* ItemWidget = CreateWidget<UInventoryItemWidget>(this, ItemWidgetClass);
	ItemWidget->SetupWidget(Item);
	ItemWidget->SetOwnerRef(this);
	ItemsWidgets.Add(ItemWidget);

	UpdateInventoryWidget();
}

void UInventoryWidget::RemoveItemFromInventoryWidget(AItem* Item)
{
	UInventoryItemWidget* WidgetToDelete = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("REMOVING"));
	for (UInventoryItemWidget* Widget : ItemsWidgets)
	{
		if (Widget->GetItemReference() == Item)
		{
			WidgetToDelete = Widget;
		}
	}

	if (WidgetToDelete)
	{
		ItemsWidgets.Remove(WidgetToDelete);
		HideItemActions();
		UpdateInventoryWidget();
	}
}

void UInventoryWidget::UpdateWeight(float CurrentInvWeight, float MaxInvWeight)
{
	FNumberFormattingOptions FormattingOptions;
	FormattingOptions.SetMaximumFractionalDigits(3);
	FormattingOptions.SetMinimumFractionalDigits(2);

	CurrentWeight->SetText(FText::AsNumber(CurrentInvWeight, &FormattingOptions));
	MaxWeight->SetText(FText::AsNumber(MaxInvWeight, &FormattingOptions));
}

void UInventoryWidget::ShowItemActions(AItem* Item)
{
	if (ItemActionsBorder == nullptr) { return; }

	if (ItemActionsBorder->IsVisible())
	{
		HideItemActions();
	}
	else {
		FNumberFormattingOptions FormattingOptions;
		FormattingOptions.SetMaximumFractionalDigits(3);
		FormattingOptions.SetMinimumFractionalDigits(2);

		SelectedItem = Item;

		GetWidgetReference<UImage>("ItemThumbnail")->SetBrushFromTexture(Item->GetItemData().InventoryThumbnail);
		GetWidgetReference<UTextBlock>("ItemDisplayName")->SetText(FText::FromName(Item->GetItemData().ItemDisplayName));
		GetWidgetReference<UTextBlock>("ItemWeight")->SetText(FText::AsNumber(Item->GetItemData().ItemWeight, &FormattingOptions));
		GetWidgetReference<UTextBlock>("ItemDescription")->SetText(FText::FromName(Item->GetItemData().ItemDescription));

		ItemActionsBorder->SetVisibility(ESlateVisibility::Visible);
		ItemActionsBorder->SetRenderOpacity(1.0f);
	}
}

void UInventoryWidget::HideItemActions()
{
	if (ItemActionsBorder->IsVisible()) {
		ItemActionsBorder->SetVisibility(ESlateVisibility::Hidden);
		ItemActionsBorder->SetRenderOpacity(0.0f);
	}
}

UWidgetAnimation* UInventoryWidget::GetWidgetAnimation(FString AnimationName) const
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

void UInventoryWidget::UpdateInventoryWidget()
{
	UWrapBox* ItemsPanel = GetWidgetReference<UWrapBox>("ItemsGrid");

	if (ItemsPanel == nullptr) { return; }

	ItemsPanel->ClearChildren();

	for (UInventoryItemWidget* WidgetToAdd : ItemsWidgets)
	{
		ItemsPanel->AddChildToWrapBox(WidgetToAdd);
	}
}

void UInventoryWidget::UseButtonClicked()
{
	if (SelectedItem == nullptr) { return; }

	if (AMCharacter* Character = Cast<AMCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Character->GetInventoryComponent()->UseItem(SelectedItem);
	}
}

void UInventoryWidget::DropButtonClicked()
{
	if (SelectedItem == nullptr) { return; }

	if (AMCharacter* Character = Cast<AMCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Character->GetInventoryComponent()->DropItem(SelectedItem);

	}
}

void UInventoryWidget::InspectButtonClicked()
{
}
