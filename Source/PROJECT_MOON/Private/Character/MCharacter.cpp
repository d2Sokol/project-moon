// All rights reserved


#include "Character/MCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Components/InteractComponent.h"
#include "Components/BoxComponent.h"
#include "Character/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Components/InventoryComponent.h"
#include "Widgets/InventoryWidget.h"


AMCharacter::AMCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("Interact Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));

	Camera->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(GetRootComponent());
	InteractComponent->GetInteractBox()->SetupAttachment(RootComponent);
}

void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetupMappingContext();
	SetupPlayerInfo();
	SetupPlayerHUD();

	PlayerState = EPlayerState::PLAYING;
}

void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMCharacter::Look);
		Input->BindAction(SprintAction, ETriggerEvent::Started, this, &AMCharacter::ToogleSprint); // Sprint button down
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMCharacter::ToogleSprint); // Sprint button relesed
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AMCharacter::TryJump);
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AMCharacter::Interact);
		Input->BindAction(ToogleInventoryAction, ETriggerEvent::Started, this, &AMCharacter::ToogleInventory);
	}

}

void AMCharacter::SetupMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMCharacter::SetupPlayerInfo()
{
	bIsSprinting = false;
}

void AMCharacter::SetupPlayerHUD()
{
	if (IsLocallyControlled() && PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerHUDClass, "Player_HUD_Widget");
		PlayerHUD->AddToViewport();
		PlayerHUD->OnGameStart(); // Custom function for playing fadein anim etc

		if (InventoryWidgetClass)
		{
			PlayerHUD->SetupInventoryWidget(InventoryWidgetClass);
			InventoryComponent->SetupInventoryWidgetRef();
		}
	}
}

void AMCharacter::Move(const FInputActionValue& ActionValue)
{
	if (PlayerState != EPlayerState::PLAYING) { return; }

	const FVector2D MovementVector = ActionValue.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AMCharacter::Look(const FInputActionValue& ActionValue)
{
	if (PlayerState != EPlayerState::PLAYING) { return; }

	const FVector2D LookVector = ActionValue.Get<FVector2D>();

	AddControllerPitchInput(LookVector.Y * -1.0f);
	AddControllerYawInput(LookVector.X);
}

void AMCharacter::ToogleSprint()
{
	if (PlayerState != EPlayerState::PLAYING) { return; }

	bIsSprinting = !bIsSprinting;

	if (bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}
}

void AMCharacter::TryJump()
{
	if (PlayerState != EPlayerState::PLAYING) { return; }

	Jump();
}

void AMCharacter::Interact()
{
	if (PlayerState != EPlayerState::PLAYING) { return; }

	InteractComponent->Interact();
}

void AMCharacter::ToogleInventory()
{
	bool bShow = PlayerHUD->IsPlayerInventoryOpen();

	if (!bShow)
	{
		PlayerState = EPlayerState::IN_INVENTORY;
		PlayerHUD->ShowPlayerInventory(true);
	}
	else {
		PlayerState = EPlayerState::PLAYING;
		PlayerHUD->ShowPlayerInventory(false);
	}
	
}

UPlayerHUD* AMCharacter::GetPlayerHUD()
{
	return PlayerHUD;
}

UInventoryComponent* AMCharacter::GetInventoryComponent()
{
	return InventoryComponent;
}

UCameraComponent* AMCharacter::GetCameraComponent() const
{
	return Camera;
}

