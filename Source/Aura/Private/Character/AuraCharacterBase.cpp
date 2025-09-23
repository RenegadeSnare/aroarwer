// Copyright notice for ObsMexGames .2025


#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


AAuraCharacterBase::AAuraCharacterBase(){
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
	UAbilitySystemComponent *AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAuraCharacterBase::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
 // void AAuraCharacterBase::Tick(float DeltaTime) {
	// Super::Tick(DeltaTime);
 // }

// // Called to bind functionality to input
// void AAuraCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
//  	Super::SetupPlayerInputComponent(PlayerInputComponent);
// }

