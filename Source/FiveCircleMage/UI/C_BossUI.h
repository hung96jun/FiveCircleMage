// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_BossUI.generated.h"

class UProgressBar;
class AC_Unit;
class UImage;
struct FUnitStatus;

UCLASS()
class FIVECIRCLEMAGE_API UC_BossUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* Armor;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* HPL;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* HPR;

public:
	UFUNCTION()
		void Hide();

	UFUNCTION()
		void Shaking();

public:
	UC_BossUI(const FObjectInitializer& ObjectInitializer);

	void Update();
	void Show(FUnitStatus* Status, float* ArmorValue, float OriginArmorValue);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void ShakeUI();

	void ClearTimer();
	void SetHPWidgetTransform(float TranslationAxisY);

private:
	FUnitStatus* UnitStatus;

	const float TimerInterval = 0.01f;

	float* GroggyArmor = nullptr;
	float OriginGroggyArmor = 9999;

	FTimerHandle ShakingHandle;
	FTimerDelegate TimerDelegate;
	const float ShakingPower = 6.0f;
	const float ShakingRange = 4.0f;
	float ShakingTime = 0.0f;
	float ShakingAxis = 0.0f;
	bool ShakingSwitch = true;
};
