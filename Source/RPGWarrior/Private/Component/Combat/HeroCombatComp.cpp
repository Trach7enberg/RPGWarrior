// Garrett Gan All Right Reserved


#include "Component/Combat/HeroCombatComp.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

AWarriorHeroWeapon* UHeroCombatComp::GetHeroWeaponByTag(const FGameplayTag& InGt)
{
	return GetWeaponByTag<AWarriorHeroWeapon>(InGt);
}

AWarriorHeroWeapon* UHeroCombatComp::GetHeroCurrentWeapon()
{
	if (!CurrentEquippedWeaponTag.IsValid()) { return nullptr; }

	return Cast<AWarriorHeroWeapon>(GetCurrentWeapon());
}

float UHeroCombatComp::GetCurrentEquippedWeaponDamage(const float InLevel)
{
	const auto Weapon = GetHeroCurrentWeapon();

	return (Weapon) ? Weapon->WeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel) : 0.f;
}
