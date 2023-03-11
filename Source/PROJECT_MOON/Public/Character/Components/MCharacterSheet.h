// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MCharacterSheet.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MOON_API UMCharacterSheet : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMCharacterSheet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth;
public:

	UFUNCTION(BlueprintCallable, Category = Health)
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = Health)
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = Health)
		void SetHealth(float NewValue);

	UFUNCTION(BlueprintCallable, Category = Health)
		void SetMaxHealth(float NewValue);

	UFUNCTION(BlueprintCallable, Category = Health)
		void AddHealth(float AddValue);
};
