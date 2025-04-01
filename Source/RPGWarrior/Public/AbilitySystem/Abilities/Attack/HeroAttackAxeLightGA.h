// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Attack/HeroAttackGameplayAbility.h"
#include "HeroAttackAxeLightGA.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UHeroAttackAxeLightGA : public UHeroAttackGameplayAbility
{
	GENERATED_BODY()

public:
	virtual UAnimMontage* GetCurrentAttackMontage() override;
	
};
