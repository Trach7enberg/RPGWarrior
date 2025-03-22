// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

class UTimelineComponent;
DECLARE_DELEGATE_TwoParams(FOnWeaponOverlapDelegate, AActor*, const FHitResult*);

class UStaticMeshComponent;
class UWarriorAbilitySysComp;
class UBoxComponent;

UCLASS()
class RPGWARRIOR_API AWarriorWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWarriorWeaponBase();

	void EnableCollision(bool Enabled) const;

	void DestroyWeapon();

	FOnWeaponOverlapDelegate OnWeaponBeginOverlapDelegate;
	FOnWeaponOverlapDelegate OnWeaponEndOverlapDelegate;

	FORCEINLINE TObjectPtr<UBoxComponent> GetWeaponCollisionBox() const { return WeaponCollisionBox; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_WeaponMesh, Category="Weapons")
	TObjectPtr<UStaticMeshComponent> WeaponMesh{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapons")
	TObjectPtr<UBoxComponent> WeaponCollisionBox{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeline")
	TObjectPtr<UCurveFloat> DissolveCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeline")
	FName DissolveParamMaterialName = FName("DissolveAmount");

	/// 溶解时间线播放速率,数值越大播放速度越慢
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeline")
	float DissolveTimelinePlayRate = 2.0f;

	TObjectPtr<UWarriorAbilitySysComp> GetOwnerAsc();

	UFUNCTION()
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                  AActor*              OtherActor,
	                                  UPrimitiveComponent* OtherComp,
	                                  int32                OtherBodyIndex,
	                                  bool                 bFromSweep,
	                                  const FHitResult&    SweepResult);

	UFUNCTION()
	virtual void OnEndWeaponOverlap(UPrimitiveComponent* OverlappedComponent,
	                                AActor*              OtherActor,
	                                UPrimitiveComponent* OtherComp,
	                                int32                OtherBodyIndex);

	UFUNCTION()
	virtual void OnRep_WeaponMesh(UStaticMeshComponent* OldValue);

	void InitialDissolveTimeline();
	void StartDissolveTimeline();

private:
	UPROPERTY()
	TObjectPtr<UWarriorAbilitySysComp> OwnerAsc{};

	UPROPERTY()
	TObjectPtr<UTimelineComponent> DissolveTimeLineComp;

	UFUNCTION()
	void OnDissolveTimelineUpdate(float Value);

	UFUNCTION()
	void OnDissolveTimelineFinished();
};
