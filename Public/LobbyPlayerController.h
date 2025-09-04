#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

UCLASS()
class YOURPROJECT_API ALobbyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(Server, Reliable)
    void SetReady(bool bReady);

    UPROPERTY(Replicated)
    bool bIsReady;
};