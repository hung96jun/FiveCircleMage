#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerController.generated.h"

/**
 *
 */
class UInputMappingContext;
class UInputAction;
class UUserWidget;
class APlayerCameraManager;
class UC_UIComponent;

class AC_Mage;

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

	//UC_OptionMenu* GetOptionMenu() { return OptionMenu; }

protected:
	virtual void OnPossess(APawn* aPawn) override;

private:
	void PushViewportSize();

	void AddInputAction(FString Key, FString Path);
	void OnOffMainMenu();

private:
	AC_Mage* Character = nullptr;

	bool bIsFirstTick = true;
	//FVector2D MousePos;
};
