// Garrett Gan All Right Reserved


#include "Items/Weapons/WarriorHeroWeapon.h"

#include "AbilitySystem/WarriorAbilitySysComp.h"

void AWarriorHeroWeapon::RemoveWeaponGrantedAbilities()
{
	if (!GetOwnerAsc()) { return; }

	GetOwnerAsc()->ClearAbilities(GrantedAbilitySpecHandles);
}

void AWarriorHeroWeapon::StoreWeaponGrantedAbilities(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	if (!GetOwnerAsc()) { return; }

	GetOwnerAsc()->ClearAbilities(GrantedAbilitySpecHandles);
	GrantedAbilitySpecHandles.Empty();
	GrantedAbilitySpecHandles.Append(InSpecHandles);
}
