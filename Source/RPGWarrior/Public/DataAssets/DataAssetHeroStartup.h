// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/DataAssetStartUp.h"
#include "DataAssetHeroStartup.generated.h"


struct FWarriorHeroAbilityStruct;
/**
 * 英雄角色的初始数据
 */
UCLASS()
class RPGWARRIOR_API UDataAssetHeroStartup : public UDataAssetStartUp
{
	GENERATED_BODY()

public:
	// 英雄角色的初始技能,默认会给予时不会触发
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		DisplayName="Activate on Given Abilities",
		meta=(TitleProperty="InputTag"))
	TArray<FWarriorHeroAbilityStruct> HeroStartupAbilities{};
};
