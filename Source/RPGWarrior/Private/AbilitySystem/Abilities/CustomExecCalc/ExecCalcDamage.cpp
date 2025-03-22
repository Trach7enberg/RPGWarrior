// Garrett Gan All Right Reserved


#include "AbilitySystem/Abilities/CustomExecCalc/ExecCalcDamage.h"

#include "AbilitySystem/WarriorAttributeSet.h"
#include "CoreTypes/GlobalGameplayTags.h"
#include "RPGWarrior/RPGWarrior.h"

struct FAttributeCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefendPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(InComingDamage);

	FAttributeCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefendPower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, InComingDamage, Target, false);
	}
};

static const FAttributeCapture& GetAttributeCapture()
{
	static FAttributeCapture AttributeCapture;
	return AttributeCapture;
}

UExecCalcDamage::UExecCalcDamage()
{
	RelevantAttributesToCapture.Add(GetAttributeCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().DefendPowerDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().InComingDamageDef);
}

void UExecCalcDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                             FGameplayEffectCustomExecutionOutput&           OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const auto EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluatePrams{};
	EvaluatePrams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluatePrams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	// 捕获此时源的AttackPower属性 
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAttributeCapture().AttackPowerDef,
	                                                           EvaluatePrams,
	                                                           SourceAttackPower);

	// 捕获此时目标的的DefendPower属性 
	float TargetDefendPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAttributeCapture().DefendPowerDef,
	                                                           EvaluatePrams,
	                                                           TargetDefendPower);


	float BaseDamage      = 0;
	int32 LightComboCount = 0;
	int32 HeavyComboCount = 0;

	// 获取SetByCallerTag对应的Magnitudes
	for (const auto& Pair : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (Pair.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage)) { BaseDamage = Pair.Value; }
		if (Pair.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_AttackType_Light))
		{
			LightComboCount = Pair.Value;
		}
		if (Pair.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_AttackType_Heavy))
		{
			HeavyComboCount = Pair.Value;
		}
	}

	// 轻击每连击提升0.05
	BaseDamage *= (LightComboCount > 0) ? (LightComboCount - 1) * 0.05f + 1.f : 1.f;
	// 重击每连击提升0.15
	BaseDamage *= (HeavyComboCount > 0) ? HeavyComboCount * 0.15f + 1.f : 1.f;

	const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefendPower;

	RPGWarriorDebug::Print(FString::Printf(TEXT("Final Damage: %.1f, LightComboCount: %d , HeavyComboCount: %d"),
	                                       FinalDamage,
	                                       LightComboCount,
	                                       HeavyComboCount));

	// 覆盖
	OutExecutionOutput.AddOutputModifier(
	                                     FGameplayModifierEvaluatedData(GetAttributeCapture().InComingDamageProperty,
	                                                                    EGameplayModOp::Override,
	                                                                    FinalDamage));
}
