// Garrett Gan All Right Reserved

#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"

#include "WarriorStructTypes.generated.h"


struct FScalableFloat;
class AWarriorWeaponBase;
class UGameplayAbilityBase;
class UInputMappingContext;
class UWarriorHeroLinkedAnimLayer;


UENUM(Blueprintable)
enum class EWarriorConfirmType:uint8
{
	Successful UMETA(DisplayName="Successful"),
	Failed UMETA(DisplayName="Failed"),
};


/**
 *  英雄人物技能结构体
 */
USTRUCT(BlueprintType)
struct FWarriorHeroAbilityStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag,Player.Ability"))
	FGameplayTag InputTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbilityBase> Ability{};

	bool IsValid() const;
};

/**
 * 每把武器所携带的数据
 */
USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()

	// 要链接到主人物蓝图的当前武器(装备时的)动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorHeroLinkedAnimLayer> WeaponAnimLayerToLink{};

	// 当前武器装备时对应的一套输入映射
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext{};

	// 当前武器装备时所能拥有的能力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWarriorHeroAbilityStruct> WeaponDefaultAbilities{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> WeaponIcon{};

	bool IsValid() const;
};

/**
 * 表示单把武器的结构体
 */
USTRUCT(BlueprintType)
struct FWeaponMapping
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag WeaponTag{};

	UPROPERTY()
	TObjectPtr<AWarriorWeaponBase> Weapon{};

	FWeaponMapping() {}

	FWeaponMapping(const FGameplayTag& InGt, const TObjectPtr<AWarriorWeaponBase>& InWeapon)
	{
		WeaponTag = InGt;
		Weapon    = InWeapon;
	}

	friend bool operator==(const FWeaponMapping& Lhs, const FWeaponMapping& RHS)
	{
		return Lhs.WeaponTag == RHS.WeaponTag;
	}

	friend bool operator!=(const FWeaponMapping& Lhs, const FWeaponMapping& RHS)
	{
		return Lhs.WeaponTag != RHS.WeaponTag;
	}
};
