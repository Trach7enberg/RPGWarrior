// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/HeroEquippedGameplayAbility.h"

#include "Characters/WarriorCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "Animation/Hero/WarriorHeroLinkedAnimLayer.h"
#include "Component/Combat/HeroCombatComp.h"
#include "Component/UI/HeroUIComponent.h"
#include "Controllers/WarriorController.h"
#include "Interface/PawnUiInterface.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

void UHeroEquippedGameplayAbility::Equipped(const FGameplayTag InTag, const FName InSocketName)
{
	const auto OwnerMesh      = GetOwningComponentFromActorInfo();
	const auto HeroCombatComp = GetHeroCombatCompFromActorInfo();
	const auto HeroController = GetHeroControllerFromActorInfo();
	const auto HeroAsc        = GetWarriorAbilitySysComp();
	if (!HeroCombatComp || !OwnerMesh || !HeroController || !HeroAsc) { return; }

	const auto WantEquipWeapon = HeroCombatComp->GetHeroWeaponByTag(InTag);

	if (!WantEquipWeapon || !WantEquipWeapon->WeaponData.IsValid()) { return; }

	WantEquipWeapon->AttachToComponent(OwnerMesh,
	                                   FAttachmentTransformRules::SnapToTargetIncludingScale,
	                                   InSocketName);

	// 设置链接动画层的动画,设置为当前武器对应的装备动画
	OwnerMesh->LinkAnimClassLayers(WantEquipWeapon->WeaponData.WeaponAnimLayerToLink);

	// 设置武器组件当前持有武器的标签,才会切换到主动画蓝图中的装备动画 很关键
	HeroCombatComp->SetCurrentWeaponTag(InTag);

	// 授予当前武器所附带的默认能力,并存储其SpecHandle用于取消
	HeroAsc->GiveInitialAbilities(WantEquipWeapon->WeaponData.WeaponDefaultAbilities,
	                              WantEquipWeapon->GetGrantedAbilitySpecHandles(),
	                              GetAbilityLevel());

	// 覆盖原来的能力输入映射 [仅在客户端运行,服务端无法运行]
	if (const auto InputSubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(HeroController->GetLocalPlayer()))
	{
		InputSubSystem->AddMappingContext(WantEquipWeapon->WeaponData.WeaponInputMappingContext, 1);
	}

	IPawnUiInterface* UiCompInterface = Cast<IPawnUiInterface>(GetHeroCharacterFromActorInfo());
	if (!UiCompInterface) { return; }
	const auto HeroUIComp = UiCompInterface->GetHeroUIComponent();
	if (!HeroUIComp) { return; }
	HeroUIComp->OnEquippedWeaponDelegate.Broadcast(WantEquipWeapon->WeaponData.WeaponIcon);
}
