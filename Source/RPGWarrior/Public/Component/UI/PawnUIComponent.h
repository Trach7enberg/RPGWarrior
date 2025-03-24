// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBasel.h"
#include "PawnUIComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFloatChangedDelegate, float Percent, bool bIncreased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPercentChangedDelegate, float, Percent, bool, bIncreased);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UPawnUIComponent : public UPawnExtensionComponentBasel
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="UI|Delegate")
	FOnPercentChangedDelegate OnCurrentHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="UI|Delegate")
	FOnPercentChangedDelegate OnCurrentRageChanged;

	virtual void BeginPlay() override;

	/// 绑定到当AS中的属性值发生变化时发生的回调
	virtual void BindAttributeChangeCallBack();


	/// 广播属性值的初始值
	virtual void BroadcastInitialAttributeValues();
};
