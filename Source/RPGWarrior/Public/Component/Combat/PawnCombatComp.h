// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/PawnExtensionComponentBasel.h"
#include "CoreTypes/WarriorStructTypes.h"
#include "Interface/CombatInterface.h"
#include "PawnCombatComp.generated.h"


UENUM(BlueprintType)
enum class EEquippedState : uint8
{
	CurrentEquippedWeapon,
	LeftWeapon,
	RightWeapon
};

class AWarriorWeaponBase;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UPawnCombatComp : public UPawnExtensionComponentBasel
{
	GENERATED_BODY()

public:
	UPawnCombatComp();

	// 当前(正装备的)武器的标签
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CombatComp")
	FGameplayTag CurrentEquippedWeaponTag{};

	/// 注册武器并存储起来
	/// @param InGt 武器标签
	/// @param InWeapon 武器实体
	/// @param RegisterAndEquippedNow 注册时并立马装备
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	void RegisterSpawnedWeapon(UPARAM(ref) const FGameplayTag& InGt,
	                           AWarriorWeaponBase*             InWeapon,
	                           bool                            RegisterAndEquippedNow);

	/// 通过GT获取武器
	/// @param InGt 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	AWarriorWeaponBase* GetWeaponByTag(UPARAM(ref) const FGameplayTag& InGt);

	UFUNCTION(BlueprintCallable, Category="CombatComp")
	void SetCurrentWeaponTag(UPARAM(ref) const FGameplayTag& InGt);

	/// 获取当前已准备的武器
	/// @return 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	AWarriorWeaponBase* GetCurrentWeapon();


	/// 
	/// @tparam T 
	/// @param InGt 
	/// @return 
	template <class T = AWarriorWeaponBase>
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	T* GetWeaponByTag(UPARAM(ref) const FGameplayTag& InGt)
	{
		static_assert(TPointerIsConvertibleFromTo<T, AWarriorWeaponBase>::Value,
		              "T must be inherited from WarriorWeaponBase");
		const auto TmpWeapon = GetWeaponByTag(InGt);
		return TmpWeapon ? CastChecked<T>(TmpWeapon) : nullptr;
	}

	virtual void EnableWeaponCollision(bool           bShouldEnable,
	                                   EEquippedState EquippedState = EEquippedState::CurrentEquippedWeapon);

	void DestroyWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	UPROPERTY()
	TArray<AActor*> OverlappedActors{};

	
private:
	// GT 对应武器的Map, TODO TMAP无法网络同步 
	TMap<FGameplayTag, AWarriorWeaponBase*> WeaponMap{};

	UPROPERTY(Replicated, ReplicatedUsing=OnRep_WeaponArrays)
	TArray<FWeaponMapping> WeaponArrays{};

	

	void OnWeaponBeginHit(AActor* HitActor, const FHitResult*);
	void OnWeaponEndHit(AActor* HitActor, const FHitResult*);


	UFUNCTION()
	void OnRep_WeaponArrays();
};
