// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorFunctionLibrary.generated.h"

enum class EWarriorConfirmType:uint8;
class UGameplayEffect;


struct FGameplayTag;
class UWarriorAbilitySysComp;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Warrior|FunctionLibrary")
	static UWarriorAbilitySysComp* GetWarriorAsc(AActor* Context);

	/// 通过InActor的ASC给其添加GT(注意该方法不是replicated的)
	/// @param InActor 
	/// @param TagToAdd 
	UFUNCTION(BlueprintCallable, Category="Warrior|FunctionLibrary")
	static void AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category="Warrior|FunctionLibrary")
	static void RemoveGameplayTagFromActor(AActor* InActor, FGameplayTag TagToRemove);

	static bool DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	/// 
	/// @param InActor 
	/// @param TagToCheck 
	/// @param OutConfirm 
	UFUNCTION(BlueprintCallable,
		meta=(DisplayName="Dose Actor Have Tag", ExpandEnumAsExecs="OutConfirm"),
		Category="Warrior|FunctionLibrary")
	static void BP_DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirm);
};
