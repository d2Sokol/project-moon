// All rights reserved


#include "Character/Components/InteractComponent.h"
#include "Components/BoxComponent.h"
#include "Character/MCharacter.h"
#include "Interactable/InteractInterface.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));

	InteractDistance = 200.0f;
}


void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = CastChecked<AMCharacter>(GetOwner());
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateInteract();
}

void UInteractComponent::UpdateInteract()
{
	TArray<AActor*> OverlappingActors;
	InteractBox->GetOverlappingActors(OverlappingActors);

	HideOldHints(); // That hides old hints and clears Hints Array

	if (InteractInterface)
	{
		InteractInterface->SetShowInteractWidget(false);
		InteractInterface = nullptr;
	}

	for (AActor* FoundActor : OverlappingActors)
	{
		// If true show hint and push to actual hints array
		if (IInteractInterface* InteractActor = Cast<IInteractInterface>(FoundActor)) 
		{
			InteractActor->SetShowInteractHintWidget(true);
			HintActors.Push(InteractActor);

			// Check if player distance to interactable actor is less than InteractDistance 
			if (Character->GetDistanceTo(FoundActor) <= InteractDistance) // if there is interactabe actor near player
			{
				if (InteractInterface == nullptr) // Check if there is one interactable actor near player or more actors
				{
					InteractActor->SetShowInteractWidget(true);
					InteractInterface = InteractActor; // Set actor to interact
				}
				else // if there is more than one interactable actors in InteractDistance
				{
					if (IInteractInterface* LookingAtInteractActor = Cast<IInteractInterface>(GetActorPlayerIsLookingAt())) // Check what actor is player looking at
					{																											// and setup this actor as Actor to interact
						InteractActor->SetShowInteractWidget(false); // Hide old interact
						InteractInterface->SetShowInteractWidget(false); // Hide old interact

						InteractInterface = LookingAtInteractActor; // Set actor to interact
						InteractInterface->SetShowInteractWidget(true); // show new interact
					}
				}
			}
		}
	}
}

void UInteractComponent::HideOldHints()
{
	if (HintActors.IsEmpty()) { return; } // Check if there is hints to hide;

	for (IInteractInterface* HintToHide : HintActors)
	{
		HintToHide->SetShowInteractHintWidget(false);
		HintToHide = nullptr;
	}
	
	HintActors.Empty(); // Clear array of old hints
}

// Check if player is looking at interactable actor and return if true
AActor* UInteractComponent::GetActorPlayerIsLookingAt() const
{
	FHitResult HitRes;
	FVector CameraStart = Character->GetCameraComponent()->GetComponentLocation();
	FVector	CameraForward = Character->GetCameraComponent()->GetForwardVector();
	FVector End = CameraStart + (CameraForward * 400.0f);
	FCollisionShape SphereCollision = FCollisionShape::MakeSphere(30.0f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->SweepSingleByChannel(HitRes, CameraStart, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, SphereCollision, QueryParams);

	if (bHit)
	{
		return HitRes.GetActor();
	}

	return nullptr;
}

void UInteractComponent::Interact()
{
	if (InteractInterface)
	{
		InteractInterface->Interact();
	}
}

UBoxComponent* UInteractComponent::GetInteractBox()
{
	return InteractBox;
}

