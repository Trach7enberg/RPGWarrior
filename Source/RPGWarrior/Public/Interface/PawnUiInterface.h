// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUiInterface.generated.h"

class UPawnUIComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UPawnUiInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGWARRIOR_API IPawnUiInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/// 用于处理角色UI相关内容的组件
	/// @return 
	UFUNCTION(BlueprintCallable, Category="PawnUiInterface")
	virtual UPawnUIComponent* GetPawnUIComponent() = 0;
};
