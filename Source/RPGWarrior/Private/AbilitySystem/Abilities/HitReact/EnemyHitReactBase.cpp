// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/HitReact/EnemyHitReactBase.h"

#include "CoreTypes/GlobalGameplayTags.h"
#include "Kismet/KismetArrayLibrary.h"

UEnemyHitReactBase::UEnemyHitReactBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	FAbilityTriggerData Data{};
	Data.TriggerTag    = WarriorGameplayTags::Enemy_EventTag_HitReact;
	Data.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Data);
}


