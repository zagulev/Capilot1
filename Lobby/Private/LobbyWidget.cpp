#include "LobbyWidget.h"
#include "LobbyPlayerController.h"

void ULobbyWidget::OnReadyClicked()
{
    if (APlayerController* PC = GetOwningPlayer())
    {
        if (ALobbyPlayerController* LPC = Cast<ALobbyPlayerController>(PC))
        {
            LPC->SetReady(true);
        }
    }
}