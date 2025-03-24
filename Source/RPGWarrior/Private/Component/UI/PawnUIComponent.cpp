// Garrett Gan All Right Reserved


#include "Component/UI/PawnUIComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorAttributeSet.h"

void UPawnUIComponent::BeginPlay() { Super::BeginPlay(); }

void UPawnUIComponent::BindAttributeChangeCallBack()
{
	const auto OwnerAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	
	if (!OwnerAsc) { return; }

	const auto OwnerAs = Cast<UWarriorAttributeSet>(OwnerAsc->GetAttributeSet(UWarriorAttributeSet::StaticClass()));
	if (!OwnerAs) { return; }

	OwnerAsc->GetGameplayAttributeValueChangeDelegate(OwnerAs->GetCurrentHealthAttribute()).
	          AddLambda([this, OwnerAs](const FOnAttributeChangeData& Data)
	          {
		          OnCurrentHealthChanged.Broadcast(Data.NewValue / OwnerAs->GetMaxHealth(),
		                                           Data.NewValue > Data.OldValue);
	          });
	OwnerAsc->GetGameplayAttributeValueChangeDelegate(OwnerAs->GetCurrentRageAttribute()).
	          AddLambda([this, OwnerAs](const FOnAttributeChangeData& Data)
	          {
		          OnCurrentRageChanged.Broadcast(Data.NewValue / OwnerAs->GetMaxRage(),
		                                         Data.NewValue > Data.OldValue);
	          });
}

void UPawnUIComponent::BroadcastInitialAttributeValues()
{
	const auto OwnerAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	if (!OwnerAsc) { return; }

	const auto OwnerAs = Cast<UWarriorAttributeSet>(OwnerAsc->GetAttributeSet(UWarriorAttributeSet::StaticClass()));
	if (!OwnerAs) { return; }
	OnCurrentHealthChanged.Broadcast(OwnerAs->GetCurrentHealth(), false);
	OnCurrentRageChanged.Broadcast(OwnerAs->GetCurrentRage(), false);
}
