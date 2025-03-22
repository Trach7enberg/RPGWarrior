// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

enum class EWarriorConfirmType:uint8;
class UWarriorAbilitySysComp;
class UPawnCombatComp;
// 
UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy :uint8
{
	// 给予能力时不会触发,触发后结束还存在ASC中
	OnTriggered,
	// 给予能力时会触发,触发后结束不存在ASC中
	OnGiven,
};

/**
 * 基础能力类
 */
UCLASS()
class RPGWARRIOR_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	UPawnCombatComp* GetPawnCombatCompFromActorInfo() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	UWarriorAbilitySysComp* GetWarriorAbilitySysComp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WarriorAbility")
	virtual FGameplayEffectSpecHandle MakeDamageEffectSpecHandle(const TSubclassOf<UGameplayEffect>& GeClass,
	                                                             const FGameplayTag InCurrentAttackTypeTag,
	                                                             float InComboCount = 1.f,
	                                                             float InWeaponBaseDamage = 1.f) const;


	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="OutConfirm"), Category="WarriorAbility")
	FActiveGameplayEffectHandle ApplyDamageEffectSpecToTarget(AActor*                          Target,
	                                                          const FGameplayEffectSpecHandle& InSpecHandle,
	                                                          EWarriorConfirmType&             OutConfirm);

	/// 设置被击中时候的反应材质参数值
	/// @param InParameterName 
	/// @param InParameterValue 
	UFUNCTION(BlueprintCallable, Category="WarriorAbility")
	virtual void SetHitReactScalarParameterOnMaterials(FName InParameterName, float InParameterValue);

	UFUNCTION(BlueprintCallable, Category="WarriorAbility")
	virtual UAnimMontage* GetRandomMontage(const TArray<UAnimMontage*>& InMontages) const;

protected:
	//~ Begin UGameAbility Interface
#pragma region UGameAbilityInterface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle     Handle,
	                        const FGameplayAbilityActorInfo*     ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo,
	                        bool                                 bReplicateEndAbility,
	                        bool                                 bWasCancelled) override;

#pragma endregion
	//~ End UGameAbility Interface

	UPROPERTY(EditDefaultsOnly, Category="WarriorAbility")
	EWarriorAbilityActivationPolicy AbilityActivationPolicy = EWarriorAbilityActivationPolicy::OnTriggered;
};
