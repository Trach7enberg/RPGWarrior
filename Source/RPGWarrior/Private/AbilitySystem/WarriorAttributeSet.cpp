// Garrett Gan All Right Reserved


#include "AbilitySystem/WarriorAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Abilities/Tasks/AbilityTask_WaitAbilityCommit.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "Characters/EnemyCharacter.h"
#include "CoreTypes/GlobalGameplayTags.h"
#include "FunctionLibrary/WarriorFunctionLibrary.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));
	}

	if (Data.EvaluatedData.Attribute == GetInComingDamageAttribute())
	{
		const auto OldHealth  = GetCurrentHealth();
		const auto DamageDone = GetInComingDamage();
		const auto NewHealth  = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);


		if (FMath::IsNearlyEqual(NewHealth, 0.f))
		{
			if (const auto ThisSuffer = Cast<AWarriorCharacterBase>(Data.Target.GetAvatarActor()))
			{
				const auto EnemyOrPlayer = Cast<AEnemyCharacter>(ThisSuffer);
				UWarriorFunctionLibrary::AddGameplayTagToActor(ThisSuffer,
													   (EnemyOrPlayer)
														   ? WarriorGameplayTags::Enemy_EventTag_Death
														   : WarriorGameplayTags::Player_EventTag_Death);
				
			}
		}
	}
}

