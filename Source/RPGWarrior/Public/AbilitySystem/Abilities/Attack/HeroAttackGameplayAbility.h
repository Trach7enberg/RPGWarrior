// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroAttackGameplayAbility.generated.h"

class UAnimMontage;

/**
 * 攻击能力
 */
UCLASS()
class RPGWARRIOR_API UHeroAttackGameplayAbility : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()

public:
	UHeroAttackGameplayAbility();

	// 跳转终结技时所使用的通信Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="WarriorAbility")
	FGameplayTag ComboStatusTag{};

	// 分配给GE所使用的SetByCallerTag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	FGameplayTag AttackTypeTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TMap<int32, UAnimMontage*> AttackMontage{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TSubclassOf<UGameplayEffect> DamageEffectClass{};

	UFUNCTION(BlueprintCallable, Category="WarriorAbility")
	virtual UAnimMontage* GetCurrentAttackMontage();

	UFUNCTION(BlueprintCallable, Category="WarriorAbility")
	int32 GetComboCnt() const { return ComboCnt; }

	// 处理连击数决定攻击动画
	UFUNCTION(BlueprintCallable, Category="WarriorAbility")
	void HandleAttackComboCnt();



protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle     Handle,
	                             const FGameplayAbilityActorInfo*     ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData*            TriggerEventData) override;

	UPROPERTY()
	int32 ComboCnt = 1;

	UPROPERTY()
	float AttackComboWaitingTime = .3f;


	virtual void K2_EndAbility() override;

	UPROPERTY()
	FTimerHandle ComboTimer{};


	void ActivateComboTimer();
	void ClearComboTimer();

	void ResetComboCnt(int32 NewComboCnt = 1);

	void HandleAttackComboWaitingTime();
};
