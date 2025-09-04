#include "LobbyPlayerController.h"
#include "Net/UnrealNetwork.h"

void ALobbyPlayerController::SetReady_Implementation(bool bReady)
{
    bIsReady = bReady;
}

void ALobbyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ALobbyPlayerController, bIsReady);
}