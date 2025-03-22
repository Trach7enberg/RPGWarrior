// Garrett Gan All Right Reserved


#include "Component/Combat/PawnCombatComp.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CoreTypes/GlobalGameplayTags.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "RPGWarrior/RPGWarrior.h"

DEFINE_LOG_CATEGORY_STATIC(PawnCombatCompLog, All, All);

UPawnCombatComp::UPawnCombatComp() {}


void UPawnCombatComp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPawnCombatComp, WeaponArrays);
}


void UPawnCombatComp::RegisterSpawnedWeapon(const FGameplayTag& InGt,
                                            AWarriorWeaponBase* InWeapon,
                                            bool                RegisterAndEquippedNow)
{
	if (!ensureMsgf(InWeapon, TEXT("Weapon is null"))) { return; }

	// if (WeaponMap.Find(InGt))
	// {
	// 	UE_LOG(PawnCombatCompLog, Log, TEXT("Weapon %s has been registered"), *InGt.ToString());
	// 	return;
	// }
	//
	// WeaponMap.Emplace(InGt, InWeapon);
	WeaponArrays.AddUnique({InGt, InWeapon});

	// TODO 解除武器需要取消绑定?
	if (!InWeapon->OnWeaponBeginOverlapDelegate.IsBoundToObject(this))
	{
		InWeapon->OnWeaponBeginOverlapDelegate.BindUObject(this, &ThisClass::OnWeaponBeginHit);
	}
	if (!InWeapon->OnWeaponEndOverlapDelegate.IsBoundToObject(this))
	{
		InWeapon->OnWeaponEndOverlapDelegate.BindUObject(this, &ThisClass::OnWeaponEndHit);
	}

	if (RegisterAndEquippedNow) { CurrentEquippedWeaponTag = InGt; }
}

AWarriorWeaponBase* UPawnCombatComp::GetWeaponByTag(const FGameplayTag& InGt)
{
	if (!InGt.IsValid())
	{
		UE_LOG(PawnCombatCompLog, Log, TEXT("WeaponTag Invalid!"));
		return nullptr;
	}

	// if (const auto Weapon = WeaponMap.Find(InGt)) { return *Weapon; }

	for (const auto& WeaponMapping : WeaponArrays)
	{
		if (!WeaponMapping.WeaponTag.IsValid()) { continue; }
		if (WeaponMapping.WeaponTag == InGt) { return WeaponMapping.Weapon; }
	}

	return nullptr;
}

void UPawnCombatComp::SetCurrentWeaponTag(const FGameplayTag& InGt) { this->CurrentEquippedWeaponTag = InGt; }

AWarriorWeaponBase* UPawnCombatComp::GetCurrentWeapon() { return GetWeaponByTag(CurrentEquippedWeaponTag); }

void UPawnCombatComp::EnableWeaponCollision(const bool bShouldEnable, const EEquippedState EquippedState)
{
	if (!GetOwner() && !GetOwner()->HasAuthority()) { return; }
	if (EquippedState == EEquippedState::CurrentEquippedWeapon)
	{
		const auto Weapon = GetCurrentWeapon();
		if (!Weapon) { return; }
		Weapon->EnableCollision(bShouldEnable);
		if (!bShouldEnable) { OverlappedActors.Empty(); }
	}
}

void UPawnCombatComp::DestroyWeapon()
{
	for (const auto& WeaponMapping : WeaponArrays)
	{
		if (WeaponMapping.Weapon) { WeaponMapping.Weapon->DestroyWeapon(); }
	}
}


void UPawnCombatComp::OnWeaponBeginHit(AActor* HitActor, const FHitResult*)
{
	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Payload{};
	Payload.Instigator = GetOwner();
	Payload.Target     = HitActor;

	// 发送MeleeHit事件,激活Hero_Attack能力中的wait事件来应用GE
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),
	                                                         WarriorGameplayTags::Player_EventTag_MeleeHit,
	                                                         Payload);

	// 发送HitPause事件,激活GA_HitPause能力
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),
	                                                         WarriorGameplayTags::Player_EventTag_HitPause,
	                                                         {});
}

void UPawnCombatComp::OnWeaponEndHit(AActor* HitActor, const FHitResult*)
{
	// 发送HitPause事件,激活GA_HitPause能力
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),
	                                                         WarriorGameplayTags::Player_EventTag_HitPause,
	                                                         {});
}

void UPawnCombatComp::OnRep_WeaponArrays() {}
