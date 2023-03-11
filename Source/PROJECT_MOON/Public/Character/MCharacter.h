// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInteractComponent;
class UInputMappingContext;
class UInputAction;
class UPlayerHUD;
class UInventoryComponent;
class UInventoryWidget;

UENUM()
enum EPlayerState {
	PLAYING = 0,
	IN_INVENTORY
};

UCLASS()
class PROJECT_MOON_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
		UInteractComponent* InteractComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
		UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, Category = "Subclass")
		TSubclassOf<UPlayerHUD> PlayerHUDClass;

	UPROPERTY(EditAnywhere, Category = "Subclass")
		TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPlayerHUD* PlayerHUD;

	EPlayerState PlayerState;


protected: // Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* ToogleInventoryAction;

private:
	void SetupMappingContext();

	void SetupPlayerInfo();

	void SetupPlayerHUD();

	void ToogleInventory();

protected:
	bool bIsSprinting;

protected:

	void Move(const FInputActionValue& ActionValue);

	void Look(const FInputActionValue& ActionValue);

	void ToogleSprint();

	void TryJump();

	void Interact();

public:

	UCameraComponent* GetCameraComponent() const;

	UPlayerHUD* GetPlayerHUD();

	UInventoryComponent* GetInventoryComponent();
};
