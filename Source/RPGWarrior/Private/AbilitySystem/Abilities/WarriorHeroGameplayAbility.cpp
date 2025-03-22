// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

#include "Characters/WarriorCharacter.h"
#include "Controllers/WarriorController.h"

AWarriorCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CurrentHeroCharacter.IsValid()) { CurrentHeroCharacter = Cast<AWarriorCharacter>(GetAvatarActorFromActorInfo()); }
	return (CurrentHeroCharacter.IsValid()) ? CurrentHeroCharacter.Get() : nullptr;
}

AWarriorController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!GetCurrentActorInfo()) { return nullptr; }

	if (!CurrentHeroController.IsValid())
	{
		CurrentHeroController = Cast<AWarriorController>(GetCurrentActorInfo()->PlayerController);
	}
	return (CurrentHeroController.IsValid()) ? CurrentHeroController.Get() : nullptr;
}

UHeroCombatComp* UWarriorHeroGameplayAbility::GetHeroCombatCompFromActorInfo()
{
	if (!GetHeroCharacterFromActorInfo()){return  nullptr;}

	return GetHeroCharacterFromActorInfo()->GetHeroCombatComp();
}
