// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssetStartUp.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/**
 * 初始启动能力数据资产
 */
UCLASS()
class RPGWARRIOR_API UDataAssetStartUp : public UDataAsset
{
	GENERATED_BODY()

public:
	/// 默认各种角色的通用初始能力数组
	/// (某些GA会在给予时根据@ref EWarriorAbilityActivationPolicy 完成后在ASC中移除掉该能力)  
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities{};

	// 默认某个特定条件下触发的能力数组
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp")
	TArray<TSubclassOf<UGameplayAbility>> ReactAbilities{};

	// 角色的初始GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffect{};
};
