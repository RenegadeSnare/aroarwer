// Copyright notice for ObsMexGames .2025

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	public:
	AAuraEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor()override;
	// UPROPERTY(BlueprintReadOnly)
	//Cos Maybe later I'll put it on a sine wave & Make it breathe
	float HighlightIntensity{1.0f};
	virtual void BeginPlay() override;
	
};
