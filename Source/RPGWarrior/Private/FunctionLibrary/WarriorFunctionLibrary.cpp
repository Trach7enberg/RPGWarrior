// Garrett Gan All Right Reserved


#include "FunctionLibrary/WarriorFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "CoreTypes/WarriorStructTypes.h"

DEFINE_LOG_CATEGORY_STATIC(WarriorFunctionLibraryLog, All, All);

UWarriorAbilitySysComp* UWarriorFunctionLibrary::GetWarriorAsc(AActor* Context)
{
	if (!ensureMsgf(Context, TEXT("the context for ASC cannot be nullptr"))) { return nullptr; }
	if (!Context)
	{
		UE_LOG(WarriorFunctionLibraryLog, Error, TEXT("the context for ASC cannot be nullptr"));
		return nullptr;
	}

	return Cast<UWarriorAbilitySysComp>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Context));
}

void UWarriorFunctionLibrary::AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd)
{
	const auto Asc = GetWarriorAsc(InActor);
	if (!Asc) { return; }

	if (!Asc->HasMatchingGameplayTag(TagToAdd))
	{
		Asc->AddLooseGameplayTag(TagToAdd);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActor(AActor* InActor, FGameplayTag TagToRemove)
{
	const auto Asc = GetWarriorAsc(InActor);
	if (!Asc) { return; }
	if (Asc->HasMatchingGameplayTag(TagToRemove))
	{
		Asc->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UWarriorFunctionLibrary::DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	const auto Asc = GetWarriorAsc(InActor);
	if (!Asc) { return false; }

	return Asc->HasMatchingGameplayTag(TagToCheck);
}

void UWarriorFunctionLibrary::BP_DoseActorHaveTag(AActor*              InActor,
                                                  FGameplayTag         TagToCheck,
                                                  EWarriorConfirmType& OutConfirm)
{
	OutConfirm = DoseActorHaveTag(InActor, TagToCheck) ? EWarriorConfirmType::Successful : EWarriorConfirmType::Failed;
}
