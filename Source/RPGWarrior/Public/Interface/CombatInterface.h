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

	/// 敌人死亡
	/// 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void EnemyDied() = 0;
};
