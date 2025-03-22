// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimIns.generated.h"

class AWarriorCharacter;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorHeroAnimIns : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

protected:
	// 当前蓝图owner英雄战士的实例
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
	TObjectPtr<AWarriorCharacter> OwningHeroCharacter = nullptr;
};
