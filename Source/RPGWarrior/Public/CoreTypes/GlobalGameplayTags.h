// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
#pragma region InputTag
	// RPGWARRIOR_API宏意思是允许这个标签可以被其他模块使用
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InpuTag_Move);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InpuTag_Look);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InpuTag_Equip);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InpuTag_UnEquip);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InpuTag_LightAttack);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InpuTag_HeavyAttack);
#pragma endregion

#pragma region WeaponTag
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_WarriorAxe);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon_Grunting_1);

#pragma endregion

	// 通过能力触发的Event
#pragma region EventTag

	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_EventTag_Equip_Axe);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_EventTag_UnEquip_Axe);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_EventTag_MeleeHit);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_EventTag_HitPause);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_EventTag_Death);

	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_EventTag_HitReact);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_EventTag_Death);

#pragma endregion

#pragma region AbilityTag
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UnEquip_Axe);

	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Death);

	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_HitReact);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Death);
#pragma endregion

#pragma region AbilityStatusTag

	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Status_Attack_JumpToFinisher);

#pragma endregion

#pragma region SetByCallerTag
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_AttackType_Light);
	RPGWARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_AttackType_Heavy);
#pragma endregion
}
