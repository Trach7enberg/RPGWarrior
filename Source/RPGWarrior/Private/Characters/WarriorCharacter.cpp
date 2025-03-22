// Garrett Gan All Right Reserved


#include "Characters/WarriorCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/WarriorAbilitySysComp.h"
#include "Camera/CameraComponent.h"
#include "Component/WarriorEnhancedInputComponent.h"
#include "Component/Combat/HeroCombatComp.h"
#include "Component/UI/HeroUIComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreTypes/GlobalGameplayTags.h"
#include "DataAssets/DataAssetHeroStartup.h"
#include "DataAssets/DataAssetInputConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPGWarrior/RPGWarrior.h"

DEFINE_LOG_CATEGORY_STATIC(WarriorCharacterLog, All, All);

AWarriorCharacter::AWarriorCharacter()
{
	CameraFollow   = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraBoom     = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	HeroCombatComp = CreateDefaultSubobject<UHeroCombatComp>("HeroCombatComp");
	HeroUIComp     = CreateDefaultSubobject<UHeroUIComponent>("HeroUIComp");

	CameraBoom->SetupAttachment(GetRootComponent());
	CameraFollow->SetupAttachment(CameraBoom);

	CameraBoom->TargetArmLength           = 200.f;
	CameraBoom->SocketOffset              = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation   = true;
	CameraFollow->bUsePawnControlRotation = false;

	// 角色停止时的减速度(刹车效果),较高的值 会使角色快速停止，较低的值 会让角色慢慢滑行停下
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->bOrientRotationToMovement  = true;
	GetCharacterMovement()->RotationRate               = FRotator(.0f, 500.f, .0f);
	GetCharacterMovement()->MaxWalkSpeed               = 400.f;
	bUseControllerRotationPitch                        = false;
	bUseControllerRotationRoll                         = false;
	bUseControllerRotationYaw                          = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -96.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, .0f));
}


void AWarriorCharacter::BeginPlay() { Super::BeginPlay(); }

void AWarriorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	checkf(DataAssetInputConfig, TEXT("DataAssetInputConfig cant be null"));

	// 获得增强输入的本地玩家子系统,通过这个根据添加我们的上下文映射
	const auto SubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetController<APlayerController>()->GetLocalPlayer());

	checkf(SubSystem, TEXT("EnhancedInputLocalPlayerSubsystem Cant be null"))
	SubSystem->AddMappingContext(DataAssetInputConfig->DefaultMappingContext, 0);

	const auto WarriorInputComp = CastChecked<UWarriorEnhancedInputComponent>(PlayerInputComponent);

	WarriorInputComp->BindNormalInputAction(DataAssetInputConfig,
	                                        WarriorGameplayTags::InpuTag_Move,
	                                        ETriggerEvent::Triggered,
	                                        this,
	                                        &ThisClass::InputMove);
	WarriorInputComp->BindNormalInputAction(DataAssetInputConfig,
	                                        WarriorGameplayTags::InpuTag_Look,
	                                        ETriggerEvent::Triggered,
	                                        this,
	                                        &ThisClass::InputLook);

	WarriorInputComp->BindAbilityInputActions(DataAssetInputConfig,
	                                          this,
	                                          &ThisClass::InputAbilityPressed,
	                                          &ThisClass::InputAbilityReleased);
}

void AWarriorCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 检查软指针是否分配了初始能力数据资产
	if (DataAssetStarUpAbilities.IsNull())
	{
		UE_LOG(WarriorCharacterLog, Error, TEXT("DataAssetStarUpAbilities Cant be nullptr!"))
		return;
	}

	if (const auto Asset = Cast<UDataAssetHeroStartup>(DataAssetStarUpAbilities.LoadSynchronous()))
	{
		WarriorAbilitySysComp->GiveInitialAbilities(Asset->StartUpAbilities);
		WarriorAbilitySysComp->GiveInitialAbilities(Asset->ReactAbilities);
		WarriorAbilitySysComp->GiveInitialAbilities(Asset->HeroStartupAbilities);
		WarriorAbilitySysComp->ApplyInitialGameplayEffect(Asset->StartupGameplayEffect);
	}
}

void AWarriorCharacter::OnRep_PlayerState() { Super::OnRep_PlayerState(); }

void AWarriorCharacter::InputMove(const FInputActionValue& InputActionValue)
{
	if (!GetController()) { return; }

	const auto MovementVector = InputActionValue.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MovementVector.Y))
	{
		AddMovementInput(GetController()->GetControlRotation().Vector(), MovementVector.Y);
	}
	if (!FMath::IsNearlyZero(MovementVector.X))
	{
		AddMovementInput(GetController()->GetControlRotation().RotateVector(FVector::RightVector), MovementVector.X);
	}
}

void AWarriorCharacter::InputLook(const FInputActionValue& InputActionValue)
{
	if (!GetController()) { return; }
	const auto MovementVector = InputActionValue.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MovementVector.Y)) { AddControllerPitchInput(MovementVector.Y); }
	if (!FMath::IsNearlyZero(MovementVector.X)) { AddControllerYawInput(MovementVector.X); }
}

void AWarriorCharacter::InputAbilityPressed(FGameplayTag InGt)
{
	if (!WarriorAbilitySysComp) { return; }
	WarriorAbilitySysComp->OnAbilityInputPressed(InGt);
}

void AWarriorCharacter::InputAbilityReleased(FGameplayTag InGt)
{
	if (!WarriorAbilitySysComp) { return; }
	WarriorAbilitySysComp->OnAbilityInputRelease(InGt);
}


void AWarriorCharacter::EnableCombatDetect(const bool bShouldEnable)
{
	if (!HeroCombatComp || !HasAuthority()) { return; }
	HeroCombatComp->EnableWeaponCollision(bShouldEnable);
}

void AWarriorCharacter::EnemyDied() {}

UPawnUIComponent* AWarriorCharacter::GetPawnUIComponent()
{
	return HeroUIComp;
	
}
