// Copyright notice for ObsMexGames .2025


#include "Player/Aura_PlayerController.h"

#include "GameFramework/PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"




AAura_PlayerController::AAura_PlayerController()
{
	bReplicates = true;
}
void AAura_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem	*SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) ;
	check(SubSystem);
	SubSystem->AddMappingContext(AuraContext,0);
	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAura_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent	*EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	InputComponent;
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&AAura_PlayerController::Move);
}

void AAura_PlayerController::Move(const FInputActionValue& InputActionvalue)
{
		const FVector2D InputAxisVector = InputActionvalue.Get<FVector2D>();
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);
		//Get a forwardvector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		if (
			//Notecreating the pointer in the call
			APawn *ControlledPawn = GetPawn<APawn>()
			)
			//if sucesssfully cast
		{
			ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
			ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
		}
}
//delete this later
// void AAura_PlayerController::Move(Const& InputActionvalue)
// {
// 	const FVector2D InputAxisVector = InputActionvalue.Get<FVector2D>();
// 	const FRotator Rotation = GetControlRotation();
// 	const FRotator YawRotation(0,Rotation.Yaw,0);
// 	//Get a forwardvector
// 	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 	if (APawn *ControlledPawn = GetPawn<APawn())
// 	{
// 		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
// 		ControlledPawn->AddMovementInput(RightDirectionDirection,InputAxisVector.X);
// 	}
// }
