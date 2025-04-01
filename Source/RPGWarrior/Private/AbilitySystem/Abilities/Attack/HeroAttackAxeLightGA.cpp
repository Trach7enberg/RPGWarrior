// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/Attack/HeroAttackAxeLightGA.h"

#include "Characters/WarriorCharacter.h"
#include "FunctionLibrary/WarriorFunctionLibrary.h"

UAnimMontage* UHeroAttackAxeLightGA::GetCurrentAttackMontage()
{
	// TODO 判断Tag 的类型 例如轻击的还是重击的？ 
	// 如果被授予了跳跃到终结重击的tag,则动画应该直接执行重击终结技
	if(UWarriorFunctionLibrary::DoseActorHaveTag(GetHeroCharacterFromActorInfo(),ComboStatusTag))
	{
		ComboCnt = AttackMontage.Num();
	}
	return Super::GetCurrentAttackMontage();
}
