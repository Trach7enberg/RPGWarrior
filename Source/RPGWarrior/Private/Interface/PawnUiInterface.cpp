// Garrett Gan All Right Reserved


#include "Interface/PawnUiInterface.h"

// Add default functionality here for any IPawnUiInterface functions that are not pure virtual.
UHeroUIComponent* IPawnUiInterface::GetHeroUIComponent()
{
	return nullptr;
}

UEnemyUIComponent* IPawnUiInterface::GetEnemyUIComponent()
{
	return nullptr;
}
