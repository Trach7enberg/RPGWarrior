// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

#include "Characters/EnemyCharacter.h"

UWarriorEnemyGameplayAbility::UWarriorEnemyGameplayAbility() {}

AEnemyCharacter* UWarriorEnemyGameplayAbility::GetCurrentEnemyCharacter()
{
	if (!CurrentEnemyCharacter.IsValid())
	{
		CurrentEnemyCharacter = Cast<AEnemyCharacter>(GetAvatarActorFromActorInfo());
	}
	return (CurrentEnemyCharacter.IsValid()) ? CurrentEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComp* UWarriorEnemyGameplayAbility::GetCurrentEnemyCombatComp()
{
	if (!GetCurrentEnemyCharacter()) { return nullptr; }

	return GetCurrentEnemyCharacter()->GetEnemyCombatComp();
}
