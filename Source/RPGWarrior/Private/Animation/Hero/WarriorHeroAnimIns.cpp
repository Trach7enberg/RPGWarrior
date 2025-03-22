// Garrett Gan All Right Reserved


#include "Animation/Hero/WarriorHeroAnimIns.h"

#include "Characters/WarriorCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(WarriorHeroAnimInsLog, All, All);

void UWarriorHeroAnimIns::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (!OwningCharacter) { return; }

	OwningHeroCharacter = Cast<AWarriorCharacter>(OwningCharacter);
	if (!OwningHeroCharacter) { UE_LOG(WarriorHeroAnimInsLog, Error, TEXT("Cant get OwningHeroCharacter!")); }
}
