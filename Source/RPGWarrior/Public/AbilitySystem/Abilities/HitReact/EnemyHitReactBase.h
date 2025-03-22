// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "EnemyHitReactBase.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UEnemyHitReactBase : public UWarriorEnemyGameplayAbility
{
	GENERATED_BODY()

public:
	UEnemyHitReactBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TArray<UAnimMontage*> Montages{};


};
