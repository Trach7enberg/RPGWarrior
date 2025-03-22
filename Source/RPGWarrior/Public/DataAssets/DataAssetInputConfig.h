// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAssetInputConfig.generated.h"


class UInputMappingContext;
class UInputAction;

USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
	GENERATED_BODY()

	// Categories用于限制下拉框选择标签为InputTag类的
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	bool IsValid() const { return InputAction && InputTag.IsValid(); }
};

/**
 * 输入标签对应的配置数据资产
 */
UCLASS()
class RPGWARRIOR_API UDataAssetInputConfig : public UDataAsset
{
	GENERATED_BODY()

	// TitleProperty 让 Details 面板显示对应变量的值,而不是默认的对象名称
	// 这里数组的元素属性面板改为显示为结构体中InputTag的值
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext{};

	// 非战斗输入
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FWarriorInputActionConfig> InputActionConfigs{};

	// 能力、战斗输入
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FWarriorInputActionConfig> AbilityInputActionConfigs{};

	UInputAction* FindInputActionByTag(const FGameplayTag& InInputTag) const;
};
