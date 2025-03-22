// Garrett Gan All Right Reserved


#include "Component/PawnExtensionComponentBasel.h"

UPawnExtensionComponentBasel::UPawnExtensionComponentBasel()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}


void UPawnExtensionComponentBasel::BeginPlay() { Super::BeginPlay(); }
