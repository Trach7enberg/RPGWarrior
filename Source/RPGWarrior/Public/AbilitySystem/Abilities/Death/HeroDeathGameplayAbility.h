// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroDeathGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UHeroDeathGameplayAbility : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TArray<UAnimMontage*> DeathMontages{};
};
