// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/Attack/HeroAttackGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "Characters/WarriorCharacter.h"
#include "Component/Combat/HeroCombatComp.h"
#include "CoreTypes/GlobalGameplayTags.h"
#include "FunctionLibrary/WarriorFunctionLibrary.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

UHeroAttackGameplayAbility::UHeroAttackGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ComboStatusTag   = WarriorGameplayTags::Player_Ability_Status_Attack_JumpToFinisher;
	AbilityTags.AddTag(WarriorGameplayTags::Player_Ability_Attack_Heavy_Axe.GetTag().RequestDirectParent().
	                                                                        RequestDirectParent());

	FGameplayTagContainer Tmp{};
	Tmp.AddTag(WarriorGameplayTags::Player_Ability_Attack_Heavy_Axe.GetTag().RequestDirectParent().
	                                                                RequestDirectParent());

	Tmp.AddTag(WarriorGameplayTags::Player_Ability_Equip_Axe.GetTag().RequestDirectParent());
	Tmp.AddTag(WarriorGameplayTags::Player_Ability_UnEquip_Axe.GetTag().RequestDirectParent());
	BlockAbilitiesWithTag.AppendTags(Tmp);
}


void UHeroAttackGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle     Handle,
                                                 const FGameplayAbilityActorInfo*     ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData*            TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// 能力启用时候清除计时器
	ClearComboTimer();
}


void UHeroAttackGameplayAbility::K2_EndAbility()
{
	Super::K2_EndAbility();

	// 能力一结束就开始计时连击计时器,未在指定阈值内重新触发当前能力就会清除连击数
	ActivateComboTimer();
}

UAnimMontage* UHeroAttackGameplayAbility::GetCurrentAttackMontage()

{
	const auto InBool = ComboCnt >= 1 && ComboCnt <= AttackMontage.Num();
	ensureMsgf(InBool, TEXT("0 <  ComboCount <= MontageMapSize"));
	if (!InBool) { return nullptr; }

	const auto Result = AttackMontage.Find(ComboCnt);
	ensureMsgf(Result, TEXT("Cant Find AttackMontage"));
	if (!Result || !*Result) { return nullptr; }

	return *Result;
}

void UHeroAttackGameplayAbility::ActivateComboTimer()
{
	if (!GetWorld()) { return; }
	GetWorld()->GetTimerManager().SetTimer(ComboTimer,
	                                       this,
	                                       &ThisClass::HandleAttackComboWaitingTime,
	                                       AttackComboWaitingTime,
	                                       false);
}

void UHeroAttackGameplayAbility::ClearComboTimer()
{
	if (!GetWorld()) { return; }

	GetWorld()->GetTimerManager().ClearTimer(ComboTimer);
}

void UHeroAttackGameplayAbility::HandleAttackComboCnt()
{
	if (!ComboStatusTag.IsValid() || AttackMontage.IsEmpty()) { return; }

	//  到达攻击动画集结尾则继续循环攻击动画
	if (ComboCnt == AttackMontage.Num())
	{
		ResetComboCnt();
		return;
	}

	// 未到达结尾,判断当前连击动画是否到达连击动画集的倒数第二个时可以[触发重击终结技]
	if (AttackMontage.Num() >= 2 && ComboCnt == AttackMontage.Num() - 1)
	{
		UWarriorFunctionLibrary::AddGameplayTagToActor(GetHeroCharacterFromActorInfo(), ComboStatusTag);
	}
	ComboCnt++;
}



void UHeroAttackGameplayAbility::ResetComboCnt(const int32 NewComboCnt)
{
	ComboCnt = NewComboCnt;
	UWarriorFunctionLibrary::RemoveGameplayTagFromActor(GetHeroCharacterFromActorInfo(), ComboStatusTag);
}

void UHeroAttackGameplayAbility::HandleAttackComboWaitingTime() { ResetComboCnt(); }
