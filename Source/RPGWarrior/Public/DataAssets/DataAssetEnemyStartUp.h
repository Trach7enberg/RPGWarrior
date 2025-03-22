// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/DataAssetStartUp.h"
#include "DataAssetEnemyStartUp.generated.h"

class UWarriorEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UDataAssetEnemyStartUp : public UDataAssetStartUp
{
	GENERATED_BODY()

public:
	UDataAssetEnemyStartUp();

	// 敌人的初始战斗能力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>> EnemyCombatAbilities{};
};
