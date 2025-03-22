// Garrett Gan All Right Reserved


#include "Items/Weapons/WarriorWeaponBase.h"

#include "Characters/WarriorCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Interface/CombatInterface.h"
#include "Net/UnrealNetwork.h"

AWarriorWeaponBase::AWarriorWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates                   = true;

	WeaponMesh           = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponCollisionBox   = CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	DissolveTimeLineComp = CreateDefaultSubobject<UTimelineComponent>("DissolveTimeLineComp");


	SetRootComponent(WeaponMesh);
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnWeaponBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndWeaponOverlap);
}

void AWarriorWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWarriorWeaponBase, WeaponMesh);
}

void AWarriorWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	InitialDissolveTimeline();
}

TObjectPtr<UWarriorAbilitySysComp> AWarriorWeaponBase::GetOwnerAsc()
{
	if (!OwnerAsc)
	{
		if (!GetOwner()) { return nullptr; }
		const auto Character = Cast<AWarriorCharacter>(GetOwner());
		if (!Character) { return nullptr; }

		OwnerAsc = Character->GetWarriorAbilitySystemComponent();
	}

	return OwnerAsc;
}

void AWarriorWeaponBase::EnableCollision(bool Enabled) const
{
	WeaponCollisionBox->SetCollisionEnabled(Enabled
		                                        ? ECollisionEnabled::Type::QueryOnly
		                                        : ECollisionEnabled::Type::NoCollision);
}


void AWarriorWeaponBase::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                              AActor*              OtherActor,
                                              UPrimitiveComponent* OtherComp,
                                              int32                OtherBodyIndex,
                                              bool                 bFromSweep,
                                              const FHitResult&    SweepResult)
{
	if (!OtherActor) { return; }

	if (OtherActor != GetOwner()) { OnWeaponBeginOverlapDelegate.ExecuteIfBound(OtherActor, &SweepResult); }
}

void AWarriorWeaponBase::OnEndWeaponOverlap(UPrimitiveComponent* OverlappedComponent,
                                            AActor*              OtherActor,
                                            UPrimitiveComponent* OtherComp,
                                            int32                OtherBodyIndex)
{
	if (!OtherActor) { return; }

	if (OtherActor != GetOwner()) { OnWeaponEndOverlapDelegate.ExecuteIfBound(OtherActor, nullptr); }
}

void AWarriorWeaponBase::OnRep_WeaponMesh(UStaticMeshComponent* OldValue) {}

void AWarriorWeaponBase::InitialDissolveTimeline()
{
	if (!DissolveCurve || !DissolveTimeLineComp) { return; }
	if (DissolveCurve->GetCurves().IsEmpty()) { return; }
	// update事件
	FOnTimelineFloat OnUpdate;
	OnUpdate.BindDynamic(this, &ThisClass::OnDissolveTimelineUpdate);

	// 绑定 Timeline 结束事件
	FOnTimelineEvent OnFinished;
	OnFinished.BindDynamic(this, &ThisClass::OnDissolveTimelineFinished);


	DissolveTimeLineComp->SetLooping(false);
	DissolveTimeLineComp->AddInterpFloat(DissolveCurve, OnUpdate, DissolveCurve->GetCurves().Top().CurveName);
	DissolveTimeLineComp->SetTimelineFinishedFunc(OnFinished);
	DissolveTimeLineComp->SetTimelineLengthMode(TL_LastKeyFrame);
}


void AWarriorWeaponBase::DestroyWeapon() { StartDissolveTimeline(); }

void AWarriorWeaponBase::StartDissolveTimeline()
{
	if (!DissolveCurve || !DissolveTimeLineComp) { return; }
	if (DissolveCurve->GetCurves().IsEmpty()) { return; }

	DissolveTimeLineComp->SetPlayRate(1.f / DissolveTimelinePlayRate);
	DissolveTimeLineComp->PlayFromStart();
}

void AWarriorWeaponBase::OnDissolveTimelineUpdate(float Value)
{
	if (!WeaponMesh) { return; }
	WeaponMesh->SetScalarParameterValueOnMaterials(DissolveParamMaterialName, Value);
}

void AWarriorWeaponBase::OnDissolveTimelineFinished() { Destroy(); }
