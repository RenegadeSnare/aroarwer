// Copyright notice for ObsMexGames .2025


#include "Player/Aura_PlayerController.h"

#include "GameFramework/PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAura_PlayerController::AAura_PlayerController()
{
	bReplicates = true;
}

void AAura_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//perform Trace
	CursorTrace();
	
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

void AAura_PlayerController::CursorTrace()
{
	LastActor =ThisActor;
	FHitResult CursorTraceHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorTraceHit);
	if (!CursorTraceHit.bBlockingHit){return;}
	ThisActor = (CursorTraceHit.GetActor());
	/*
	 * this line trace from cursor we can leave us in   several scenarios
	 * a)LastActor is Null & ThisActor is NullDO NOTHING*/
	if (LastActor == nullptr && ThisActor==nullptr){return;}
	/*
	 * b)LastActor is Null & ThisActor is Valid */
	if (LastActor==NULL&& ThisActor!=nullptr)
	{
		ThisActor->HighlightActor();
	}
	// c)LastActor is Valid&& ThisActorIs Null
	if(LastActor != nullptr &&ThisActor==nullptr)
	{
		LastActor->UnHighlightActor();
	}
	/*
	*D)Both Actors are valid but Last Actor != ThisActor*/
	if (LastActor!=nullptr &&ThisActor!=nullptr)
	{
		if (LastActor!=ThisActor)
		{
			LastActor->UnHighlightActor();
			ThisActor->HighlightActor();
		}
	}
	
	 
	//
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

