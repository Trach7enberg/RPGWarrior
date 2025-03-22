// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "WarriorHeroGameplayAbility.generated.h"

class UHeroCombatComp;
class AWarriorCharacter;
class AWarriorController;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorHeroGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	AWarriorCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	AWarriorController* GetHeroControllerFromActorInfo() ;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	UHeroCombatComp* GetHeroCombatCompFromActorInfo();

private:
	// 只持有对象引用不会增加计数
	TWeakObjectPtr<AWarriorCharacter>  CurrentHeroCharacter  = nullptr;
	TWeakObjectPtr<AWarriorController> CurrentHeroController = nullptr;
	TWeakObjectPtr<UHeroCombatComp> CurrentHeroCombatComp = nullptr;
};
