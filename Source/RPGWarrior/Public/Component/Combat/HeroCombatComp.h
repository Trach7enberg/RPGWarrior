// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/PawnCombatComp.h"
#include "HeroCombatComp.generated.h"

class AWarriorHeroWeapon;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UHeroCombatComp : public UPawnCombatComp
{
	GENERATED_BODY()

public:
	/// 获取英雄的武器
	/// @param InGt 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	AWarriorHeroWeapon* GetHeroWeaponByTag(const FGameplayTag& InGt);
	
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	AWarriorHeroWeapon* GetHeroCurrentWeapon();

	/// 获取当前正在装备武器的基础伤害值
	/// @param InLevel 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	float GetCurrentEquippedWeaponDamage(float InLevel);
};
