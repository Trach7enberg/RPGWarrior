// Garrett Gan All Right Reserved


#include "HUD/BaseWarriorHUD.h"

#include "Widgets/WidgetBase.h"

void ABaseWarriorHUD::InitHud()
{
	if (!GetOwner() || !MainWidgetClass) { return; }

	if (CurrentMainWidget) { return; }

	CurrentMainWidget = CreateWidget<UWidgetBase>(GetOwningPlayerController(), MainWidgetClass);
	if (!CurrentMainWidget) { return; }

	CurrentMainWidget->InitializeWidget();
	CurrentMainWidget->AddToViewport();
}
