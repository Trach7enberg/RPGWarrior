// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorAbilitySysComp.generated.h"

class UWarriorEnemyGameplayAbility;
struct FWarriorHeroAbilityStruct;
class UGameplayAbilityBase;
class UDataAssetStartUp;
class UGiSubSystem;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorAbilitySysComp : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void InitializeComponent() override;

	/// 赋予初始能力 (默认给予时不启用能力)
	/// @param InGameAbilitiesClass 
	/// @param AbilityLevel
	/// @param GrandAndActivateOnce 为true时则在赋予能力时并启用一次,默认值为false
	virtual void GiveInitialAbilities(TArray<TSubclassOf<UGameplayAbility>>& InGameAbilitiesClass,
	                                  bool                                   GrandAndActivateOnce = false,
	                                  float                                  AbilityLevel         = 1.f);

	/// 赋予初始(敌人的)能力 (默认给予时不启用能力)
	/// @param InEnemyGameAbilitiesClass 
	/// @param AbilityLevel 
	/// @param GrandAndActivateOnce 
	virtual void GiveInitialAbilities(TArray<TSubclassOf<UWarriorEnemyGameplayAbility>>& InEnemyGameAbilitiesClass,
	                                  float                                              AbilityLevel         = 1.f,
	                                  bool                                               GrandAndActivateOnce = true);

	/// 赋予初始(英雄的)能力 (默认给予时不启用能力)
	/// @param InWarriorHeroAbilityStruct 
	/// @param GrandAndActivateOnce 
	/// @param AbilityLevel 
	virtual void GiveInitialAbilities(TArray<FWarriorHeroAbilityStruct>& InWarriorHeroAbilityStruct,
	                                  bool                               GrandAndActivateOnce = false,
	                                  float                              AbilityLevel         = 1.f);

	/// 
	/// @param InWarriorHeroAbilityStruct 
	/// @param OutSpecHandles 
	/// @param AbilityLevel
	virtual void GiveInitialAbilities(const TArray<FWarriorHeroAbilityStruct>& InWarriorHeroAbilityStruct,
	                                  TArray<FGameplayAbilitySpecHandle>&      OutSpecHandles,
	                                  float                                    AbilityLevel = 1.f);

	virtual void ApplyInitialGameplayEffect(TArray<TSubclassOf<UGameplayEffect>> GameplayEffects,
	                                        float                                AbilityLevel = 1.f);

	virtual void GrantAbility(TSubclassOf<UGameplayAbility> InAbility,
	                          float                         AbilityLevel,
	                          bool                          GrandAndActivateOnce = true);


	/// 取消并且清除SpecHandle数组里对应spec的能力
	/// @param InSpecHandles 
	void ClearAbilities(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputRelease(const FGameplayTag& InInputTag);

private:
	UPROPERTY()
	TObjectPtr<UGiSubSystem> GiSubSystem = nullptr;
};
