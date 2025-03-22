// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WarriorAnimInstanceBase.generated.h"

class UCharacterMovementComponent;
class AWarriorCharacterBase;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	/// 用于 线程安全地更新动画 的函数，通常用来在多线程环境下进行动画更新时,确保动画状态的安全性
	/// 在多核处理器中,该函数可以使得某些动画计算任务在后台线程进行,而主线程不需要等待它们完成,从而提高游戏的帧率和响应速度
	/// @param DeltaSeconds 
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	// 当前动画蓝图owner的角色的基类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
	TObjectPtr<AWarriorCharacterBase> OwningCharacter{};

	// 当前动画蓝图owner的角色的基类的移动组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
	TObjectPtr<UCharacterMovementComponent> OwningMovementComp{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation|Locomotion")
	float GroundSpeed{};

	// 是否有加速度,在移动?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation|Locomotion")
	bool bHasAcceleration{};

	// 是否进入空闲状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation|Locomotion")
	bool bShouldEnterRelaxState = false;

	// 空闲阈值,空闲N秒则进入relax
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Animation|Locomotion")
	float EnterRelaxStateThreshold = 5.f;

	// 当前已经空闲了的时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation|Locomotion")
	float IdleElapsedTime{};
};
