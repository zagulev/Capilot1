#include "LobbyGameMode.h"
#include "Kismet/GameplayStatics.h"

ALobbyGameMode::ALobbyGameMode()
{
    // Set default pawn, player controller, etc. if needed
}

void ALobbyGameMode::StartMatch()
{
    UGameplayStatics::OpenLevel(GetWorld(), "GameMap", true);
}