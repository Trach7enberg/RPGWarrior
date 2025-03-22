// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorCharacterBase.h"
#include "Interface/CombatInterface.h"
#include "WarriorCharacter.generated.h"

class UHeroUIComponent;
struct FGameplayTag;
class UHeroCombatComp;
class UDataAssetStartUp;
struct FInputActionValue;
class UDataAssetInputConfig;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API AWarriorCharacter : public AWarriorCharacterBase, public ICombatInterface
{
	GENERATED_BODY()


#pragma region PublicArea

public:
	AWarriorCharacter();
	virtual void PossessedBy(AController* NewController) override;

	/// 获取角色的战斗组件
	/// @return 
	FORCEINLINE TObjectPtr<UHeroCombatComp> GetHeroCombatComp() const { return HeroCombatComp; }

	//~ Begin ICombatInterface
	
	/// 战斗武器检测 (montage中的AnimState区间触发)
	/// @warning 只在服务端进行检测
	/// @param bShouldEnable 
	virtual void              EnableCombatDetect(bool bShouldEnable) override;
	virtual void              EnemyDied() override;

	//~ End ICombatInterface


	//~ Begin IPawnUiInterface 
	virtual UPawnUIComponent* GetPawnUIComponent() override;
	//~ End IPawnUiInterface

#pragma endregion


#pragma region ProtectedArea

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;
#pragma endregion


#pragma region PrivateArea

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components")
	TObjectPtr<UCameraComponent> CameraFollow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	// 角色的战斗组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components|Combat")
	TObjectPtr<UHeroCombatComp> HeroCombatComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components|UI")
	TObjectPtr<UHeroUIComponent> HeroUIComp;

#pragma endregion

#pragma region DataAsset
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="DataAssets")
	TObjectPtr<UDataAssetInputConfig> DataAssetInputConfig;


#pragma endregion

#pragma region InputCallBack
	void InputMove(const FInputActionValue& InputActionValue);
	void InputLook(const FInputActionValue& InputActionValue);
	void InputAbilityPressed(FGameplayTag InGt);
	void InputAbilityReleased(FGameplayTag InGt);

#pragma endregion

#pragma endregion
};
