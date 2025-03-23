// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "WidgetHero.generated.h"

class UHeroUIComponent;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWidgetHero : public UWidgetBase
{
	GENERATED_BODY()

public:
	/// 初始化玩家widget
	UFUNCTION(BlueprintCallable, Category="WarriorWidget")
	virtual void InitializeWidget() override;

	/// 广播Widget所需要的初始值进行初始化
	UFUNCTION(BlueprintCallable, Category="WarriorWidget")
	virtual void BroadcastInitializeState() override;
	/// 初始化widget完成
	UFUNCTION(BlueprintImplementableEvent, Category="WarriorWidget")
	void BP_OnInitializedWidget(UHeroUIComponent* OwningHeroUIComp);

protected:
	UHeroUIComponent* GetHeroUIComponent();

private:
	UPROPERTY()
	TSoftObjectPtr<UHeroUIComponent> HeroUIComponent;
};
