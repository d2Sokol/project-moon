// All rights reserved


#include "Interactable/Item.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/MCharacter.h"
#include "Character/Components/InventoryComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget"));
	InteractHintWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Hint Widget"));

	RootComponent = SphereCollision;

	Mesh->SetupAttachment(RootComponent);
	InteractWidget->SetupAttachment(InteractHintWidget);
	InteractHintWidget->SetupAttachment(RootComponent);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	SetupWidgets();
	SetupInventoryComponent();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::UseItem()
{
	
}


void AItem::Interact()
{
	Destroy();
	InventoryComponent->AddItemToInventory(this);
}

void AItem::SetShowInteractHintWidget(bool bVisible)
{
	InteractHintWidget->SetVisibility(bVisible);
}

void AItem::SetShowInteractWidget(bool bVisible)
{
	InteractWidget->SetVisibility(bVisible);
}

void AItem::SetupWidgets()
{
	InteractHintWidget->SetVisibility(false);
	InteractWidget->SetVisibility(false);
}

void AItem::SetupInventoryComponent()
{
	if (AMCharacter* Character = Cast<AMCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		InventoryComponent = Character->GetInventoryComponent();
	}
}

FItemData AItem::GetItemData() const
{
	return ItemData;
}

