// Garrett Gan All Right Reserved


#include "AbilitySystem/WarriorAbilitySysComp.h"

#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "CoreTypes/WarriorStructTypes.h"
#include "DataAssets/DataAssetHeroStartup.h"
#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "SubSystem/GiSubSystem.h"

DEFINE_LOG_CATEGORY_STATIC(WarriorAbilitySysCompLog, All, All);

void UWarriorAbilitySysComp::InitializeComponent()
{
	Super::InitializeComponent();
	if (!GetWorld() || !GetWorld()->GetGameInstance()) { return; }

	GiSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UGiSubSystem>();
}

void UWarriorAbilitySysComp::GiveInitialAbilities(TArray<TSubclassOf<UGameplayAbility>>& InGameAbilitiesClass,
                                                  bool                                   GrandAndActivateOnce,
                                                  float                                  AbilityLevel)
{
	if (InGameAbilitiesClass.IsEmpty()) { return; }

	for (const auto& Ga : InGameAbilitiesClass) { GrantAbility(Ga, AbilityLevel, GrandAndActivateOnce); }
}

void UWarriorAbilitySysComp::GiveInitialAbilities(
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>>& InEnemyGameAbilitiesClass,
	const float                                        AbilityLevel,
	const bool                                         GrandAndActivateOnce)
{
	if (InEnemyGameAbilitiesClass.IsEmpty()) { return; }

	for (const auto& Ga : InEnemyGameAbilitiesClass)
	{
		GrantAbility(Ga, AbilityLevel, GrandAndActivateOnce);
	}
}

void UWarriorAbilitySysComp::GiveInitialAbilities(TArray<FWarriorHeroAbilityStruct>& InWarriorHeroAbilityStruct,
                                                  bool                               GrandAndActivateOnce,
                                                  const float                        AbilityLevel)
{
	if (InWarriorHeroAbilityStruct.IsEmpty()) { return; }

	for (const auto& GaHeroStruct : InWarriorHeroAbilityStruct)
	{
		if (!GaHeroStruct.Ability || !GaHeroStruct.IsValid()) { continue; }
		FGameplayAbilitySpec AbilitySpec(GaHeroStruct.Ability, AbilityLevel);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.DynamicAbilityTags.AddTag(GaHeroStruct.InputTag);

		if (GrandAndActivateOnce) { GiveAbilityAndActivateOnce(AbilitySpec); }
		else { GiveAbility(AbilitySpec); }
	}
}


void UWarriorAbilitySysComp::GiveInitialAbilities(const TArray<FWarriorHeroAbilityStruct>& InWarriorHeroAbilityStruct,
                                                  TArray<FGameplayAbilitySpecHandle>&      OutSpecHandles,
                                                  const float                              AbilityLevel)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (InWarriorHeroAbilityStruct.IsEmpty()) { return; }
	ClearAbilities(OutSpecHandles);
	OutSpecHandles.Empty();

	for (const auto& GaHeroStruct : InWarriorHeroAbilityStruct)
	{
		if (!GaHeroStruct.Ability || !GaHeroStruct.IsValid()) { continue; }
		FGameplayAbilitySpec AbilitySpec(GaHeroStruct.Ability, AbilityLevel);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.DynamicAbilityTags.AddTag(GaHeroStruct.InputTag);

		OutSpecHandles.Add(GiveAbility(AbilitySpec));
	}
}

void UWarriorAbilitySysComp::ApplyInitialGameplayEffect(TArray<TSubclassOf<UGameplayEffect>> GameplayEffects,
                                                        const float                          AbilityLevel)
{
	if (GameplayEffects.IsEmpty()) { return; }

	for (const auto& Effect : GameplayEffects)
	{
		if (!Effect) { continue; }
		ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), AbilityLevel, MakeEffectContext());
	}
}

void UWarriorAbilitySysComp::GrantAbility(const TSubclassOf<UGameplayAbility> InAbility,
                                          const float                         AbilityLevel,
                                          const bool                          GrandAndActivateOnce)
{
	if (!InAbility) { return; }
	FGameplayAbilitySpec AbilitySpec(InAbility, AbilityLevel);
	AbilitySpec.SourceObject = GetAvatarActor();

	if (GrandAndActivateOnce) { GiveAbilityAndActivateOnce(AbilitySpec); }
	else { GiveAbility(AbilitySpec); }
}

void UWarriorAbilitySysComp::ClearAbilities(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (InSpecHandles.IsEmpty()) { return; }
	FScopedAbilityListLock AbilityListLock(*this);
	for (const auto& SpecHandle : InSpecHandles)
	{
		CancelAbilityHandle(SpecHandle);
		ClearAbility(SpecHandle);
	}
}

void UWarriorAbilitySysComp::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) { return; }

	FScopedAbilityListLock ScopedAbilityListLock(*this);
	for (const auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) { continue; }
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UWarriorAbilitySysComp::OnAbilityInputRelease(const FGameplayTag& InInputTag) {}
