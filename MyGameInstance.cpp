#include "MyGameInstance.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UMyGameInstance::UMyGameInstance()
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        SessionInterface = Subsystem->GetSessionInterface();
    }
}

void UMyGameInstance::Init()
{
    if (SessionInterface.IsValid())
    {
        SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnCreateSessionComplete);
        SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMyGameInstance::OnFindSessionsComplete);
        SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnJoinSessionComplete);
    }
}

void UMyGameInstance::HostSession()
{
    if (SessionInterface.IsValid())
    {
        FOnlineSessionSettings SessionSettings;
        SessionSettings.bIsLANMatch = true;
        SessionSettings.NumPublicConnections = 4;
        SessionSettings.bShouldAdvertise = true;

        SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
    }
}

void UMyGameInstance::FindSession()
{
    if (SessionInterface.IsValid())
    {
        SessionSearch = MakeShareable(new FOnlineSessionSearch());
        SessionSearch->bIsLanQuery = true;
        SessionSearch->MaxSearchResults = 10;

        SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    }
}

void UMyGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UGameplayStatics::OpenLevel(GetWorld(), "LobbyMap", true, "listen");
    }
}

void UMyGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    if (bWasSuccessful && SessionSearch.IsValid())
    {
        for (const auto& Result : SessionSearch->SearchResults)
        {
            SessionInterface->JoinSession(0, NAME_GameSession, Result);
            break;
        }
    }
}

void UMyGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    FString Address;
    if (SessionInterface->GetResolvedConnectString(SessionName, Address))
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PC)
        {
            PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
        }
    }
}