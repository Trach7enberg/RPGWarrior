// Garrett Gan All Right Reserved


#include "Characters/WarriorCharacterBase.h"

#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "AbilitySystem/WarriorAttributeSet.h"
#include "Components/TimelineComponent.h"
#include "DataAssets/DataAssetStartUp.h"
#include "SubSystem/GiSubSystem.h"

DEFINE_LOG_CATEGORY_STATIC(WarriorCharacterBaseLog, All, All);

AWarriorCharacterBase::AWarriorCharacterBase()
{
	WarriorAbilitySysComp = CreateDefaultSubobject<UWarriorAbilitySysComp>("WarriorAbilitySysComp");
	WarriorAttributeSet   = CreateDefaultSubobject<UWarriorAttributeSet>("WarriorAttributeSet");
	DissolveTimeLineComp  = CreateDefaultSubobject<UTimelineComponent>("DissolveTimeLineComp");

	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->SetReceivesDecals(false);
}

UGiSubSystem* AWarriorCharacterBase::GetGiSubSystem()
{
	if (!GetGameInstance()) { return nullptr; }

	if (!GiSubSystem) { GiSubSystem = GetGameInstance()->GetSubsystem<UGiSubSystem>(); }
	return GiSubSystem;
}


void AWarriorCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitialDissolveTimeline();
}


void AWarriorCharacterBase::InitializeAscInfo()
{
	if (!WarriorAbilitySysComp)
	{
		UE_LOG(WarriorCharacterBaseLog, Error, TEXT("Character ASC Cant be nullptr!"))
		return;
	}


	WarriorAbilitySysComp->InitAbilityActorInfo(this, this);
}

void AWarriorCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeAscInfo();

	// 检查软指针是否分配了数据资产
	ensureMsgf(!DataAssetStarUpAbilities.IsNull(), TEXT("DataAssetStarUpAbilities Can be null!"));
}


void AWarriorCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitializeAscInfo();
	// 检查软指针是否分配了数据资产
	ensureMsgf(!DataAssetStarUpAbilities.IsNull(), TEXT("DataAssetStarUpAbilities Can be null!"));
}

UAbilitySystemComponent* AWarriorCharacterBase::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent();
}

UPawnUIComponent* AWarriorCharacterBase::GetPawnUIComponent() { return nullptr; }

#pragma  region Asc

UWarriorAbilitySysComp* AWarriorCharacterBase::GetWarriorAbilitySystemComponent() const
{
	return WarriorAbilitySysComp;
}

UWarriorAttributeSet* AWarriorCharacterBase::GetUWarriorAttributeSet() const { return WarriorAttributeSet; }

#pragma endregion

void AWarriorCharacterBase::InitialDissolveTimeline()
{
	if (!DissolveCurve || !DissolveTimeLineComp) { return; }
	if (DissolveCurve->GetCurves().IsEmpty()) { return; }
	// update事件
	FOnTimelineFloat OnUpdate;
	OnUpdate.BindDynamic(this, &ThisClass::OnTimelineTick);

	// 绑定 Timeline 结束事件
	FOnTimelineEvent OnFinished;
	OnFinished.BindDynamic(this, &ThisClass::OnTimelineFinished);


	DissolveTimeLineComp->SetLooping(false);
	DissolveTimeLineComp->AddInterpFloat(DissolveCurve, OnUpdate, DissolveCurve->GetCurves().Top().CurveName);
	DissolveTimeLineComp->SetTimelineFinishedFunc(OnFinished);
	DissolveTimeLineComp->SetTimelineLengthMode(TL_LastKeyFrame);
}


void AWarriorCharacterBase::StartDissolveTimeline()
{
	if (!DissolveCurve || !DissolveTimeLineComp) { return; }
	if (DissolveCurve->GetCurves().IsEmpty()) { return; }

	DissolveTimeLineComp->SetPlayRate(1.f / DissolveTimelinePlayRate);
	DissolveTimeLineComp->PlayFromStart();
}

void AWarriorCharacterBase::OnTimelineTick(float Value)
{
	if (!GetMesh()) { return; }
	GetMesh()->SetScalarParameterValueOnMaterials(DissolveParamMaterialName, Value);
}

void AWarriorCharacterBase::OnTimelineFinished() {}

void AWarriorCharacterBase::OnDissolveVfxCompDestroyed(UNiagaraComponent* PSystem) {}
