// Garrett Gan All Right Reserved


#include "SubSystem/GiSubSystem.h"
#include "DataAssets/DataAssetStartUp.h"

DEFINE_LOG_CATEGORY_STATIC(GiSubSystemLog, All, All);

UGiSubSystem::UGiSubSystem() {}

void UGiSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//
	// Ds_CharacterStartUp = LoadObject<UDataAssetStartUp>(
	//                                                     this,
	//                                                     TEXT("/Script/RPGWarrior.DataAssetStartUp'/Game/_Blueprints/DataAsset/DA_Abilities_CharacterStarUp.DA_Abilities_CharacterStarUp'"));
	//
	// if (!Ds_CharacterStartUp) { UE_LOG(GiSubSystemLog, Error, TEXT("Load DataAssetStartUp Failed!")); }
}
