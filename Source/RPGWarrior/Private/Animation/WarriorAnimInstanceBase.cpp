// Garrett Gan All Right Reserved


#include "Animation/WarriorAnimInstanceBase.h"

#include "Characters/WarriorCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(WarriorAnimInstanceBaseLog, All, All);

void UWarriorAnimInstanceBase::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWarriorCharacterBase>(TryGetPawnOwner());
	if (!OwningCharacter) { return; }
	OwningMovementComp = OwningCharacter->GetCharacterMovement();
}

void UWarriorAnimInstanceBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComp) { return; }

	GroundSpeed      = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComp->GetCurrentAcceleration().Size2D() > 0.f;

	if (bHasAcceleration)
	{
		IdleElapsedTime        = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
