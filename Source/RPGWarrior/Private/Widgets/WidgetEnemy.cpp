// Garrett Gan All Right Reserved


#include "Widgets/WidgetEnemy.h"

#include "Component/UI/EnemyUIComponent.h"
#include "Interface/PawnUiInterface.h"

void UWidgetEnemy::InitializeWidget() {}

void UWidgetEnemy::InitializeWidget(UEnemyUIComponent* InEnemyUIComp)
{
	if (!InEnemyUIComp) { return; }
	EnemyUIComponent = InEnemyUIComp;
	BP_OnInitializedWidget(EnemyUIComponent.Get());
}

void UWidgetEnemy::BroadcastInitializeState()
{
	if (!GetEnemyUIComponent()) { return; }
	EnemyUIComponent->BroadcastInitialAttributeValues();
}

UEnemyUIComponent* UWidgetEnemy::GetEnemyUIComponent()
{
	if (!EnemyUIComponent.IsValid())
	{
		const auto Ai = GetOuter();
		if (!Ai) { return nullptr; }
		const auto Interface = Cast<IPawnUiInterface>(Ai);
		if (!Interface) { return nullptr; }

		EnemyUIComponent = Interface->GetEnemyUIComponent();
	}
	return EnemyUIComponent.Get();
}
