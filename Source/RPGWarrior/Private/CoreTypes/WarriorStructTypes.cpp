// Garrett Gan All Right Reserved


#include "CoreTypes/WarriorStructTypes.h"

#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "Animation/Hero/WarriorHeroLinkedAnimLayer.h"

bool FWarriorHeroAbilityStruct::IsValid() const { return InputTag.IsValid() && Ability; }

bool FWarriorHeroWeaponData::IsValid() const { return WeaponAnimLayerToLink && WeaponInputMappingContext; }
