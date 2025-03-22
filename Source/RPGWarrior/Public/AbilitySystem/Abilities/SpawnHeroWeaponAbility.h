// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "SpawnHeroWeaponAbility.generated.h"

class AWarriorWeaponBase;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API USpawnHeroWeaponAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="WarriorAbility")
	TSubclassOf<AWarriorWeaponBase> WeaponMeshClass{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(Categories="Player.Weapon,Enemy.Weapon"), Category="WarriorAbility")
	FGameplayTag WeaponTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="WarriorAbility")
	FName SocketNameAttach{};
};
