// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/HeroUnEquippedGameplayAbility.h"

#include "Characters/WarriorCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "Component/Combat/HeroCombatComp.h"
#include "Controllers/WarriorController.h"
#include "Animation/Hero/WarriorHeroLinkedAnimLayer.h"
#include "Component/UI/HeroUIComponent.h"
#include "Interface/PawnUiInterface.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

class UEnhancedInputLocalPlayerSubsystem;

void UHeroUnEquippedGameplayAbility::UnEquipped(const FGameplayTag& InTag, const FName& InSocketName)
{
	const auto OwnerMesh = GetOwningComponentFromActorInfo();

	const auto HeroCombatComp = GetHeroCombatCompFromActorInfo();
	const auto HeroController = GetHeroControllerFromActorInfo();
	const auto HeroAsc        = GetWarriorAbilitySysComp();
	if (!HeroCombatComp || !OwnerMesh || !HeroController || !HeroAsc) { return; }

	const auto WantEquipWeapon = HeroCombatComp->GetHeroWeaponByTag(InTag);

	if (!WantEquipWeapon || !WantEquipWeapon->WeaponData.IsValid()) { return; }


	WantEquipWeapon->AttachToComponent(OwnerMesh,
	                                   FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
	                                   InSocketName);

	// 取消之前链接动画层的动画
	OwnerMesh->UnlinkAnimClassLayers(WantEquipWeapon->WeaponData.WeaponAnimLayerToLink);

	// 设置武器组件当前持有武器的标签为Invalid,才会切换到主动画蓝图中的人物默认动画
	HeroCombatComp->SetCurrentWeaponTag(FGameplayTag::EmptyTag);

	// 移除之前武器装备时的覆盖能力输入映
	if (const auto InputSubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(HeroController->GetLocalPlayer()))
	{
		InputSubSystem->RemoveMappingContext(WantEquipWeapon->WeaponData.WeaponInputMappingContext);
	}

	// 移除之前武器装备时赋予的默认能力
	WantEquipWeapon->RemoveWeaponGrantedAbilities();

	IPawnUiInterface* UiCompInterface = Cast<IPawnUiInterface>(GetHeroCharacterFromActorInfo());
	if (!UiCompInterface) { return; }
	const auto HeroUIComp = UiCompInterface->GetHeroUIComponent();
	if (!HeroUIComp) { return; }
	HeroUIComp->OnEquippedWeaponDelegate.Broadcast(nullptr);
}
