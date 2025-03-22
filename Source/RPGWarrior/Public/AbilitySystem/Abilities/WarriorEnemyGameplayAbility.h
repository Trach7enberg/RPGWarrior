// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "WarriorEnemyGameplayAbility.generated.h"

class AEnemyCharacter;
class UEnemyCombatComp;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorEnemyGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UWarriorEnemyGameplayAbility();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	UEnemyCombatComp* GetCurrentEnemyCombatComp();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	AEnemyCharacter* GetCurrentEnemyCharacter();

protected:
	UPROPERTY()
	TWeakObjectPtr<UEnemyCombatComp> CurrentEnemyCombatComp{};

	UPROPERTY()
	TWeakObjectPtr<AEnemyCharacter> CurrentEnemyCharacter{};
};
