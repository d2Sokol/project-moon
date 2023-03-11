// All rights reserved

#include "Character/PlayerHUD.h"
#include "Animation/WidgetAnimation.h"
#include "Widgets/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"

UPlayerHUD::UPlayerHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SetRenderOpacity(0.0f);
}

void UPlayerHUD::OnGameStart()
{
	PlayHUDAnimation("FadeInHUD_INST");

}

void UPlayerHUD::PlayHUDAnimation(FString AnimationName)
{
	PlayAnimation(GetWidgetAnimation(AnimationName));
}

void UPlayerHUD::ShowPlayerInventory(bool bShow)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (bShow)
		{
			PlayerController->SetShowMouseCursor(true);
			PlayerController->SetInputMode(FInputModeGameAndUI());
			InventoryWidget->AddToViewport();
		}
		else
		{
			PlayerController->SetShowMouseCursor(false);
			PlayerController->SetInputMode(FInputModeGameOnly());
			InventoryWidget->RemoveFromParent();
		}
	}
}

UInventoryWidget* UPlayerHUD::GetInventoryWidget()
{
	return InventoryWidget;
}

bool UPlayerHUD::IsPlayerInventoryOpen()
{
	return InventoryWidget->IsInViewport();
}

void UPlayerHUD::SetupInventoryWidget(TSubclassOf<UInventoryWidget>& InventoryWidgetClass)
{
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InventoryWidgetClass, "Inventory_Widget");
		InventoryWidget->OnCreate();
	}
}

UWidgetAnimation* UPlayerHUD::GetWidgetAnimation(FString AnimationName) const
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
