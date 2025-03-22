// Garrett Gan All Right Reserved


#include "DataAssets/DataAssetInputConfig.h"

UInputAction* UDataAssetInputConfig::FindInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const auto& [InputTag, InputAction] : InputActionConfigs)
	{
		if (InputTag == InInputTag && InputAction) { return InputAction; }
	}
	return nullptr;
}
