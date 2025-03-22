// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "DeathEnemyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UDeathEnemyGameplayAbility : public UWarriorEnemyGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TArray<UAnimMontage*> DeathMontages{};
};
