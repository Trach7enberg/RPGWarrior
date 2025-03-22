// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Attack/HeroAttackGameplayAbility.h"
#include "HeroAttackAxeHeavyGA.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UHeroAttackAxeHeavyGA : public UHeroAttackGameplayAbility
{
	GENERATED_BODY()

public:
	virtual UAnimMontage* GetCurrentAttackMontage() override;
};
