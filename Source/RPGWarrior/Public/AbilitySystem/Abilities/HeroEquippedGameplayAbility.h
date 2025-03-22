// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroEquippedGameplayAbility.generated.h"

/**
 * 英雄装备武器能力
 */
UCLASS()
class RPGWARRIOR_API UHeroEquippedGameplayAbility : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable,Category="WarriorAbility")
	void Equipped( const FGameplayTag InTag, const FName InSocketName);
};
