// Garrett Gan All Right Reserved


#include "Widgets/WidgetHero.h"

#include "Component/UI/HeroUIComponent.h"
#include "Interface/PawnUiInterface.h"

void UWidgetHero::InitializeWidget() { BP_OnInitializedWidget(GetHeroUIComponent()); }

void UWidgetHero::BroadcastInitializeState()
{
	if (!GetHeroUIComponent()) { return; }
	HeroUIComponent->BroadcastInitialAttributeValues();
}

UHeroUIComponent* UWidgetHero::GetHeroUIComponent()
{
	if (!HeroUIComponent.IsValid())
	{
		const auto Interface = Cast<IPawnUiInterface>(GetOwningPlayerPawn());
		if (!Interface) { return nullptr; }

		HeroUIComponent = Interface->GetHeroUIComponent();
	}
	return HeroUIComponent.Get();
}
