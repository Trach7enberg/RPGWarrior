// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"


UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGWARRIOR_API ICombatInterface
{
	GENERATED_BODY()

public:
	/// 只在服务器端进行检测
	/// @param bShouldEnable 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void EnableCombatDetect(bool bShouldEnable) = 0;

	/// 执行死亡
	/// 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void Died() = 0;

	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual bool IsDead() = 0;

	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void UpdateMotionWarpingTarget(FVector  InTargetLoc,
	                                       FRotator InRotator,
	                                       FName    InWarpTargetName = FName("FacingTarget")) = 0;

	/// 显示当前角色的被锁定时的指示器
	/// @param bEnable 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void ShowCurrentLockIndicator(bool bEnable = true) = 0;
};
