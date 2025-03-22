// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/GameplayAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "Component/Combat/PawnCombatComp.h"
#include "CoreTypes/GlobalGameplayTags.h"

UPawnCombatComp* UGameplayAbilityBase::GetPawnCombatCompFromActorInfo() const
{
	if (!GetAvatarActorFromActorInfo()) { return nullptr; }

	// TODO 注意如果有多个相同的组件、可能不会按照预期作用 
	return GetAvatarActorFromActorInfo()->GetComponentByClass<UPawnCombatComp>();
}

UWarriorAbilitySysComp* UGameplayAbilityBase::GetWarriorAbilitySysComp() const
{
	return Cast<UWarriorAbilitySysComp>(GetAbilitySystemComponentFromActorInfo_Ensured());
}


void UGameplayAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	switch (AbilityActivationPolicy)
	{
		case EWarriorAbilityActivationPolicy::OnTriggered:
			break;
		case EWarriorAbilityActivationPolicy::OnGiven:
			if (ActorInfo && !Spec.IsActive()) { ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle); }
			break;
	}
}

void UGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle     Handle,
                                      const FGameplayAbilityActorInfo*     ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      bool                                 bReplicateEndAbility,
                                      bool                                 bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	switch (AbilityActivationPolicy)
	{
		case EWarriorAbilityActivationPolicy::OnTriggered:
			break;
		case EWarriorAbilityActivationPolicy::OnGiven:
			if (ActorInfo && HasAuthority(&CurrentActivationInfo))
			{
				ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
			}
			break;
	}
}


FGameplayEffectSpecHandle UGameplayAbilityBase::MakeDamageEffectSpecHandle(
	const TSubclassOf<UGameplayEffect>& GeClass,
	const FGameplayTag                  InCurrentAttackTypeTag,
	const float                         InComboCount,
	const float                         InWeaponBaseDamage) const
{
	ensureMsgf(GeClass, TEXT("GameplayEffect Cant be Null"));
	if (!GeClass || !GetWarriorAbilitySysComp() || !GetAvatarActorFromActorInfo()) { return {}; }

	auto ContextHandle = GetWarriorAbilitySysComp()->MakeEffectContext();
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	auto EffectSpecHandle = GetWarriorAbilitySysComp()->MakeOutgoingSpec(GeClass, GetAbilityLevel(), ContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle,
	                                                              WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
	                                                              InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle,
		                                                              InCurrentAttackTypeTag,
		                                                              InComboCount);
	}

	return EffectSpecHandle;
}


FActiveGameplayEffectHandle UGameplayAbilityBase::ApplyDamageEffectSpecToTarget(AActor* Target,
	const FGameplayEffectSpecHandle&                                                    InSpecHandle,
	EWarriorConfirmType&                                                                OutConfirm)
{
	const auto Asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!GetWarriorAbilitySysComp() || !Asc || !InSpecHandle.IsValid())
	{
		OutConfirm = EWarriorConfirmType::Failed;
		return {};
	}

	const auto ActiveEffectHandle = GetWarriorAbilitySysComp()->
			ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, Asc);

	OutConfirm                                       = ActiveEffectHandle.WasSuccessfullyApplied()
		                                ? OutConfirm = EWarriorConfirmType::Successful
		                                : OutConfirm = EWarriorConfirmType::Failed;

	return ActiveEffectHandle;
}

void UGameplayAbilityBase::SetHitReactScalarParameterOnMaterials(FName InParameterName, float InParameterValue)
{
	if (!GetOwningComponentFromActorInfo()) { return; }

	GetOwningComponentFromActorInfo()->SetScalarParameterValueOnMaterials(InParameterName, InParameterValue);
}

UAnimMontage* UGameplayAbilityBase::GetRandomMontage(const TArray<UAnimMontage*>& InMontages) const
{
	ensure(!InMontages.IsEmpty());

	return InMontages.IsEmpty() ? nullptr : InMontages[FMath::RandRange(0, InMontages.Num() - 1)];
}
