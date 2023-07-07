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
class UC_ElementPanel;

UCLASS()
class FIVECIRCLEMAGE_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, UInputAction*> InputActions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UC_ElementPanel* ElementPanel;

public:
	AC_PlayerController();

protected:
	virtual void BeginPlay() final;

public:
	virtual void Tick(float DeltaTime) final;

	virtual void SetupInputComponent() override;

private:
	void PushViewportSize();

private:
	bool bIsFirstTick = true;
};
