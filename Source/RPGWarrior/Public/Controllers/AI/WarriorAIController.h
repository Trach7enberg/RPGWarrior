// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarriorAIController.generated.h"

class UCrowdFollowingComponent;
struct FAIStimulus;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API AWarriorAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWarriorAIController();
	AWarriorAIController(const FObjectInitializer& ObjectInitializer);
	//~ Begin GenericTeamAgentInterface
	/// 判断 AI 对某个 AActor 的态度（友好、敌对、中立）
	/// AI Perception 和 AI 行为逻辑通常会依赖它来决定如何与目标交互,比如配置中的对不同阵营的检测
	/// @param Other 
	/// @return 
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~ End GenericTeamAgentInterface
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAI")
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAI|Config")
	bool bEnableDetourCrowAvoidance = true;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		meta=(EditCondition="bEnableDetourCrowAvoidance", ClampMin="1", ClampMax="4"),
		Category="WarriorAI|Config")
	int32 DetourCrowedAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		meta=(EditCondition="bEnableDetourCrowAvoidance"),
		Category="WarriorAI|Config")
	float CollisionQueryRange = 600.f;

	virtual void OnPossess(APawn* InPawn) override;

private:
	/// 根据感知到的目标更新 BT 黑板中的目标键
	/// @param Actor 
	/// @param Stimulus 
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY()
	TSoftObjectPtr<UCrowdFollowingComponent> CrowdFollowingComponentRef{};
};
