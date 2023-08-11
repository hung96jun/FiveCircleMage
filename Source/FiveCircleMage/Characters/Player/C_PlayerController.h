#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Structs/C_DebuffInfo.h"
#include "C_PlayerController.generated.h"

/**
 *
 */
class UInputMappingContext;
class UInputAction;
class UUserWidget;
class APlayerCameraManager;

class UC_ElementPanel;
class UC_PlayerHUD;
class AC_Mage;
class UC_UIComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		APlayerCameraManager* CameraManager;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, UInputAction*> InputActions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UC_UIComponent* UIComponent;

public:
	AC_PlayerController();

protected:
	virtual void BeginPlay() final;

public:
	virtual void Tick(float DeltaTime) final;

	virtual void SetupInputComponent() override;

protected:
	virtual void OnPossess(APawn* aPawn) override;

	///////////////////////////////////////////////////////////////////////////
	// Key Bind Functions
	///////////////////////////////////////////////////////////////////////////
 	//void OnOffElementPanel(const FInputActionInstance& Instance);
	void OnOffElementPanel(const FInputActionInstance& Instance);

	void OnOffMainMenu();
	///////////////////////////////////////////////////////////////////////////

private:
	void AddInputAction(FString Key, FString Path);

	void OpenElementPanel();
	void CloseElementPanel();

private:
	AC_Mage* Character = nullptr;

	bool bIsFirstTick = true;
};
