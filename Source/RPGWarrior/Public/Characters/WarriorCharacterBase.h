// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/PawnUiInterface.h"
#include "WarriorCharacterBase.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class UTimelineComponent;
class UDataAssetStartUp;
class UGiSubSystem;
class UWarriorAttributeSet;
class UWarriorAbilitySysComp;

UCLASS()
class RPGWARRIOR_API AWarriorCharacterBase : public ACharacter, public IAbilitySystemInterface,public IPawnUiInterface
{
	GENERATED_BODY()

public:
	AWarriorCharacterBase();
	UGiSubSystem* GetGiSubSystem();


#pragma region Interface
	//~ Begin APawn Interface

	/// 只在服务器端调用 这里用于初始化服务器端的Asc
	/// @param NewController 
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	//~ Begin IAbilitySystem Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystem Interface

	//~ Begin IPawnUiInterface Interface
	
	/// 用于处理角色UI相关内容的组件,子类需要重写
	virtual UPawnUIComponent* GetPawnUIComponent() override;
	
	//~ End IPawnUiInterface Interface
#pragma endregion


#pragma region DataAssets
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="DataAssets")
	TSoftObjectPtr<UDataAssetStartUp> DataAssetStarUpAbilities;

#pragma endregion

	FORCEINLINE virtual UWarriorAbilitySysComp* GetWarriorAbilitySystemComponent() const;
	FORCEINLINE virtual UWarriorAttributeSet*   GetUWarriorAttributeSet() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UWarriorAbilitySysComp> WarriorAbilitySysComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UWarriorAttributeSet> WarriorAttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeline")
	TObjectPtr<UCurveFloat> DissolveCurve;

	/// 死亡时的时间线溶解材质所需要的参数名字
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeline")
	FName DissolveParamMaterialName = FName("DissolveAmount");

	/// 溶解时间线播放速率,数值越大播放速度越慢
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeline")
	float DissolveTimelinePlayRate = 1.0f;

	/// 溶解VFX里的颜色的参数名字,用于设置特效参数的值
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Niagara")
	FName NiagaraParameterName = FName("DissolveParticleColor");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Niagara")
	TSoftObjectPtr<UNiagaraSystem> DissolveNiagaraSystem;

	/// 角色材质中指定名字参数的颜色
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Material")
	FName DynamicMaterialParameterName = FName("DissolveEdgeColor");

	UPROPERTY()
	TObjectPtr<UGiSubSystem> GiSubSystem = nullptr;

	virtual void BeginPlay() override;
	void         InitializeAscInfo();

	// 客户端初始化ASC
	virtual void OnRep_PlayerState() override;

	void InitialDissolveTimeline();
	void StartDissolveTimeline();

private:
	UPROPERTY()
	TObjectPtr<UTimelineComponent> DissolveTimeLineComp;

	UFUNCTION()
	void OnTimelineTick(float Value);

	UFUNCTION()
	void OnTimelineFinished();
	
	virtual void OnDissolveVfxCompDestroyed(UNiagaraComponent* PSystem);
};
