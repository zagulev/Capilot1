#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

UCLASS()
class YOURPROJECT_API ALobbyPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated)
    FString PlayerName;

    UPROPERTY(Replicated)
    bool bIsReady;
};