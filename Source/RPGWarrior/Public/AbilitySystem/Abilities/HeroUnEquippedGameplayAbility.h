// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroUnEquippedGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UHeroUnEquippedGameplayAbility : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="WarriorAbility")
	void UnEquipped(UPARAM(ref) const FGameplayTag& InTag,const FName& InSocketName);
	
};
