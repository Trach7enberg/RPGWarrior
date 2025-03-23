// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	/// 初始化Widget(非系统调用,由人控制)
	virtual void InitializeWidget();

	/// 广播初始化值
	virtual void BroadcastInitializeState();
};
