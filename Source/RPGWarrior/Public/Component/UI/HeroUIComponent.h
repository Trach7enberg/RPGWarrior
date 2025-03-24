// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="UI|Delegate")
	FOnEquippedWeaponDelegate OnEquippedWeaponDelegate;
};
