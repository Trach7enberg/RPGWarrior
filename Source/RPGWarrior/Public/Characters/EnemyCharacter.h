// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorCharacterBase.h"
#include "Interface/CombatInterface.h"
#include "EnemyCharacter.generated.h"

class UEnemyUIComponent;
class UEnemyCombatComp;
/**
 * 
 */
UCLASS()
class RPGWARRIOR_API AEnemyCharacter : public AWarriorCharacterBase, public ICombatInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;

	TObjectPtr<UEnemyCombatComp> GetEnemyCombatComp() { return EnemyCombatComp; }

	//~ Begin CombatInterface
	virtual void EnableCombatDetect(bool bShouldEnable) override;
	virtual void EnemyDied() override;
	//~ End CombatInterface

	//~ Begin IPawnUiInterface 
	virtual UPawnUIComponent* GetPawnUIComponent() override;
	//~ End IPawnUiInterface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Combat")
	TObjectPtr<UEnemyCombatComp> EnemyCombatComp{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|UI")
	TObjectPtr<UEnemyUIComponent> EnemyUIComponent{};

private:
	/// 特效完成时才死亡
	UFUNCTION()
	virtual void OnDissolveVfxCompDestroyed(UNiagaraComponent* PSystem) override;
};
