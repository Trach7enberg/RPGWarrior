// Garrett Gan All Right Reserved


#include "Characters/EnemyCharacter.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "Component/Combat/EnemyCombatComp.h"
#include "Component/UI/EnemyUIComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/DataAssetEnemyStartUp.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPGWarrior/RPGWarrior.h"
#include "Widgets/WidgetEnemy.h"

AEnemyCharacter::AEnemyCharacter()
{
	EnemyCombatComp             = CreateDefaultSubobject<UEnemyCombatComp>("EnemyCombatComp");
	EnemyUIComponent            = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");
	EnemyHealthWidgetComp       = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthComp");
	AutoPossessAI               = EAutoPossessAI::PlacedInWorld;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll  = false;
	bUseControllerRotationYaw   = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement     = true;
	GetCharacterMovement()->RotationRate                  = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed                  = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking    = 1000.f;

	EnemyHealthWidgetComp->SetupAttachment(GetMesh());
}

void AEnemyCharacter::BeginPlay() { Super::BeginPlay(); }

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (DataAssetStarUpAbilities.IsNull()) { return; }

	// [异步]加载资源,
	UAssetManager::GetStreamableManager().RequestAsyncLoad(DataAssetStarUpAbilities.ToSoftObjectPath(),
	                                                       FStreamableDelegate::CreateLambda([this]()
	                                                       {
		                                                       const auto DataAsset = Cast<
			                                                       UDataAssetEnemyStartUp>(DataAssetStarUpAbilities
		                                                        .Get());
		                                                       if (DataAsset)
		                                                       {
			                                                       WarriorAbilitySysComp->
					                                                       GiveInitialAbilities(DataAsset->
					                                                        EnemyCombatAbilities);
			                                                       WarriorAbilitySysComp->
					                                                       GiveInitialAbilities(DataAsset->
						                                                       StartUpAbilities,
						                                                       true);
			                                                       WarriorAbilitySysComp->
					                                                       GiveInitialAbilities(DataAsset->
					                                                        ReactAbilities);
			                                                       WarriorAbilitySysComp->
					                                                       ApplyInitialGameplayEffect(DataAsset->
					                                                        StartupGameplayEffect);
		                                                       }

		                                                       // 先调用UI绑定回调再初始化血量UI
		                                                       EnemyUIComponent->BindAttributeChangeCallBack();
		                                                       const auto HealthWidget = Cast<
			                                                       UWidgetEnemy>(EnemyHealthWidgetComp->
		                                                        GetUserWidgetObject());
		                                                       if (!HealthWidget) { return; }
		                                                       // 初始化敌方UI
		                                                       HealthWidget->InitializeWidget(EnemyUIComponent);
	                                                       }));
}

void AEnemyCharacter::EnableCombatDetect(bool bShouldEnable) {}

void AEnemyCharacter::EnemyDied()
{
	if (!GetMesh() || !GetEnemyCombatComp()) { return; }

	GetMesh()->bPauseAnims = true;
	GetMesh()->CastShadow  = false;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	GetEnemyCombatComp()->DestroyWeapon();


	// 异步加载资源,加载成功再死亡
	// TODO GameplayCue实现 ?
	UAssetManager::GetStreamableManager()
			.RequestAsyncLoad(DissolveNiagaraSystem.ToSoftObjectPath(),
			                  [this]()
			                  {
				                  if (!GetMesh()) { return; }
				                  const TWeakObjectPtr<UMaterialInstanceDynamic> DynamicMi = GetMesh()->
						                  CreateDynamicMaterialInstance(0, GetMesh()->GetMaterial(0));
				                  if (!DynamicMi.IsValid()) { return; }
				                  const auto Vfx =
						                  UNiagaraFunctionLibrary::SpawnSystemAttached(DissolveNiagaraSystem
							                  .Get(),
							                  GetMesh(),
							                  NAME_None,
							                  {},
							                  {},
							                  EAttachLocation::Type::SnapToTarget,
							                  false);
				                  Vfx->SetVariableLinearColor(NiagaraParameterName,
				                                              DynamicMi->K2_GetVectorParameterValue({
					                                              DynamicMaterialParameterName
				                                              }));
				                  Vfx->OnSystemFinished.AddDynamic(this, &ThisClass::OnDissolveVfxCompDestroyed);
				                  StartDissolveTimeline();
			                  });
}

UPawnUIComponent*  AEnemyCharacter::GetPawnUIComponent() { return EnemyUIComponent; }
UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() { return EnemyUIComponent; }

void AEnemyCharacter::OnDissolveVfxCompDestroyed(UNiagaraComponent* PSystem) { Destroy(); }
