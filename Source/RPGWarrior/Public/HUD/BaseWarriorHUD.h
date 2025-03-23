// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseWarriorHUD.generated.h"

class UWidgetBase;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API ABaseWarriorHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="HUD|WidgetClass")
	TSubclassOf<UWidgetBase> MainWidgetClass;

	/// 初始化HUD的主要widget到屏幕上
	void InitHud();

private:
	TObjectPtr<UWidgetBase> CurrentMainWidget;
};