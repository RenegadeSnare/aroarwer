// Copyright notice for ObsMexGames .2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Aura_PlayerController.generated.h"
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class AURA_API AAura_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
AAura_PlayerController();
	
protected:
virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext>	AuraContext;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction>				MoveAction;

	void Move(const   FInputActionValue& InputActionValue);
};
