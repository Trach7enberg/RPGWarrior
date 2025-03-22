// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GiSubSystem.generated.h"

class UDataAssetStartUp;

/**
 * 
 */
UCLASS()
class RPGWARRIOR_API UGiSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGiSubSystem();

	virtual void                  Initialize(FSubsystemCollectionBase& Collection) override;

};
