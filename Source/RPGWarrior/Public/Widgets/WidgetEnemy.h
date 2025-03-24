// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "WidgetEnemy.generated.h"

class UEnemyUIComponent;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWidgetEnemy : public UWidgetBase
{
	GENERATED_BODY()

public:
	/// 初始化玩家widget
	UFUNCTION(BlueprintCallable, Category="WarriorWidget")
	virtual void InitializeWidget() override;

	/// 初始化敌人widget ()
	/// @param InEnemyUIComp 
	virtual void InitializeWidget(UEnemyUIComponent* InEnemyUIComp);

	/// 广播Widget所需要的初始值进行初始化
	UFUNCTION(BlueprintCallable, Category="WarriorWidget")
	virtual void BroadcastInitializeState() override;
	/// 初始化widget完成
	UFUNCTION(BlueprintImplementableEvent, Category="WarriorWidget")
	void BP_OnInitializedWidget(UEnemyUIComponent* OwningEnemyUIComp);

	UEnemyUIComponent* GetEnemyUIComponent();

private:
	UPROPERTY()
	TSoftObjectPtr<UEnemyUIComponent> EnemyUIComponent;
};
