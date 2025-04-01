// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/HitReact/WarriorHitReactBase.h"

#include "CoreTypes/GlobalGameplayTags.h"

UWarriorHitReactBase::UWarriorHitReactBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	FAbilityTriggerData Data{};
	Data.TriggerTag    = WarriorGameplayTags::Player_EventTag_HitReact;
	Data.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Data);
}

UAnimMontage* UWarriorHitReactBase::GetHitReactMontage(const FGameplayTag& HitReactTag) 
{
	if (!HitReactTag.IsValid()){return nullptr;}
	const auto Montage = Montages.Find(HitReactTag);
	if (!Montage)
	{
		return nullptr;
	}
	
	return *Montage;
}
