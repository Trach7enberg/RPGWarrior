// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBasel.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, Percent);

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UPawnUIComponent : public UPawnExtensionComponentBasel
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnPercentChangedDelegate;
};
