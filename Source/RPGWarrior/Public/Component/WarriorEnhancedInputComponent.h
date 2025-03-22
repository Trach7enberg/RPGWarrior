// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "DataAssets/DataAssetInputConfig.h"
#include "WarriorEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWarriorEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	/// 绑定非战斗输入,例如移动、查看
	/// @tparam UserObject 
	/// @tparam CallbackFunc 
	/// @param InInputConfig 输入配置数据资产
	/// @param InInputTag 输入标签
	/// @param TriggerEvent 触发动作
	/// @param ContextObj 上下文
	/// @param CallbackFunction 回调函数
	template <class UserObject, typename CallbackFunc>
	void BindNormalInputAction(const UDataAssetInputConfig* InInputConfig,
	                           const FGameplayTag&          InInputTag,
	                           ETriggerEvent                TriggerEvent,
	                           UserObject*                  ContextObj,
	                           CallbackFunc                 CallbackFunction);

	/// 绑定能力输入
	/// @tparam UserObject 
	/// @tparam CallbackFunc 
	/// @param InInputConfig 输入配置数据资产
	/// @param ContextObj 上下文
	/// @param InputPressedCallback 按下时的回调
	/// @param InputReleasedCallback 释放时的回调
	template <class UserObject, typename CallbackFunc>
	void BindAbilityInputActions(const UDataAssetInputConfig* InInputConfig,
	                            UserObject*                  ContextObj,
	                            CallbackFunc                 InputPressedCallback,
	                            CallbackFunc                 InputReleasedCallback);
};

template <class UserObject, typename CallbackFunc>
void UWarriorEnhancedInputComponent::BindNormalInputAction(const UDataAssetInputConfig* InInputConfig,
                                                           const FGameplayTag&          InInputTag,
                                                           ETriggerEvent                TriggerEvent,
                                                           UserObject*                  ContextObj,
                                                           CallbackFunc                 CallbackFunction)
{
	checkf(InInputConfig, TEXT("DataAssetInputConfig cant be null"));
	if (auto FoundAction = InInputConfig->FindInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObj, CallbackFunction);
	}
}

template <class UserObject, typename CallbackFunc>
void UWarriorEnhancedInputComponent::BindAbilityInputActions(const UDataAssetInputConfig* InInputConfig,
	UserObject* ContextObj,
	CallbackFunc InputPressedCallback,
	CallbackFunc InputReleasedCallback)
{
	checkf(InInputConfig, TEXT("DataAssetInputConfig cant be null"));

	for (const auto & Config : InInputConfig->AbilityInputActionConfigs)
	{
		if (!Config.IsValid()){continue;}
		// 绑定回调函数,最后的多个参数均为函数参数,这里为GT
		BindAction(Config.InputAction,ETriggerEvent::Started,ContextObj,InputPressedCallback,Config.InputTag);
		BindAction(Config.InputAction,ETriggerEvent::Completed,ContextObj,InputReleasedCallback,Config.InputTag);
	}
	
}
