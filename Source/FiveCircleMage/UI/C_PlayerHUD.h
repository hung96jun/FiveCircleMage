#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/C_UnitType.h"
#include "Utilities/Defines.h"
#include "C_PlayerHUD.generated.h"

/**
 * 
 */
class UImage;
class UProgressBar;

UCLASS()
class FIVECIRCLEMAGE_API UC_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* Thumnail;
	
public:
	UC_PlayerHUD(const FObjectInitializer& ObjectInitializer);

protected:
	//virtual void NativeOnInitialized();
	//virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	/**
	* A function that passes the address value using a
	* float pointer when creating a widget
	* @param	Max			MaxHealth
	* @param	Cur			CurHealth
	*/
	void SetHealth(float* Max, float* Cur);

private:
	float* MaxHealth = nullptr;
	float* CurHealth = nullptr;
	float HPPer = 0.0f;

	bool* bDebuffActives[CAST(int, EUnitState::Size)];
};
