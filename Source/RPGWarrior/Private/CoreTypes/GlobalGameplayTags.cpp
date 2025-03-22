// Garrett Gan All Right Reserved


#include "CoreTypes/GlobalGameplayTags.h"

namespace WarriorGameplayTags
{
#pragma region InputTag
	// RPGWARRIOR_API宏意思是允许这个标签可以被其他模块使用
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InpuTag_Move, "InputTag.Move", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InpuTag_Look, "InputTag.Look", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InpuTag_Equip, "InputTag.Equip", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InpuTag_UnEquip, "InputTag.UnEquip", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InpuTag_LightAttack, "InputTag.LightAttack", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InpuTag_HeavyAttack, "InputTag.HeavyAttack", "");
#pragma endregion

#pragma region WeaponTag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Weapon_WarriorAxe, "Player.Weapon.WarriorAxe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Enemy_Weapon_Grunting_1, "Enemy.Weapon.Grunting.01", "");
#pragma endregion

#pragma region EvenTag

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_EventTag_Equip_Axe, "Player.EventTag.Equip.Axe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_EventTag_UnEquip_Axe, "Player.EventTag.UnEquip.Axe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_EventTag_MeleeHit, "Player.EventTag.MeleeHit", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_EventTag_HitPause, "Player.EventTag.HitPause", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_EventTag_Death, "Player.EventTag.Death", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Enemy_EventTag_HitReact, "Enemy.EventTag.HitReact", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Enemy_EventTag_Death, "Enemy.EventTag.Death", "");

#pragma endregion


#pragma region AbilityTag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_UnEquip_Axe, "Player.Ability.UnEquip.Axe", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_Attack, "Player.Ability.Attack", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_Attack_Light_Axe, "Player.Ability.Attack.Light.Axe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_Attack_Heavy_Axe, "Player.Ability.Attack.Heavy.Axe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_HitPause, "Player.Ability.HitPause", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_Death, "Player.Ability.Death", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Enemy_Ability_Melee, "Enemy.Ability.Melee", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Enemy_Ability_Ranged, "Enemy.Ability.Ranged", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Enemy_Ability_HitReact, "Enemy.Ability.HitReact", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Enemy_Ability_Death, "Enemy.Ability.Death", "");
#pragma endregion

#pragma region AbilityStatusTag

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Player_Ability_Status_Attack_JumpToFinisher,
	                               "Player.Ability.Status.Attack.JumpToFinisher",
	                               "");


#pragma endregion

#pragma region SetByCallerTag

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shared_SetByCaller_AttackType_Light, "Shared.SetByCaller.AttackType.Light", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shared_SetByCaller_AttackType_Heavy, "Shared.SetByCaller.AttackType.Heavy", "");

#pragma endregion
}
