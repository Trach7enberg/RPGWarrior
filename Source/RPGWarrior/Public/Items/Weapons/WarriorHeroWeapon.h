// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes/WarriorStructTypes.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorHeroWeapon.generated.h"

struct FGameplayAbilitySpecHandle;
struct FWarriorHeroWeaponData;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapons")
	FWarriorHeroWeaponData WeaponData;

	void RemoveWeaponGrantedAbilities();

	void StoreWeaponGrantedAbilities(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	TArray<FGameplayAbilitySpecHandle>& GetGrantedAbilitySpecHandles() { return GrantedAbilitySpecHandles; }

private:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles{};
};
