// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "WarriorHitReactBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorHitReactBase : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()

public:
	UWarriorHitReactBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TMap<FGameplayTag, UAnimMontage*> Montages{};

	UFUNCTION(BlueprintCallable, Category="WarriorAbility")
	UAnimMontage* GetHitReactMontage(UPARAM(ref) const FGameplayTag& HitReactTag);
};
