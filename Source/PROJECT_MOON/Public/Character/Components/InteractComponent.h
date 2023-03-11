// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

class UBoxComponent;
class IInteractInterface;
class AMCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MOON_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractBox;
private:

	AMCharacter* Character;

	IInteractInterface* InteractInterface;

	TArray<IInteractInterface*> HintActors;

	UPROPERTY(EditAnywhere, Category = "Interact Settings")
		float InteractDistance;

private:

	void UpdateInteract();
	void HideOldHints();

	AActor* GetActorPlayerIsLookingAt() const;
		
public:

	void Interact();

	UBoxComponent* GetInteractBox();
};
