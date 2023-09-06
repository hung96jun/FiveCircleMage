// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_BossUI.generated.h"

class UProgressBar;
class AC_Unit;
struct FUnitStatus;

UCLASS()
class FIVECIRCLEMAGE_API UC_BossUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HP;

public:
	UC_BossUI(const FObjectInitializer& ObjectInitializer);

	void Update();
	void Show(FUnitStatus* Status);
	void Hind();


protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void ShakeUI();

	UFUNCTION()
		void Shaking();

	void ClearTimer();
	void SetHPWidgetTransform(float TranslationAxisY);
	
private:
	FUnitStatus* UnitStatus;

	const float TimerInterval = 0.01f;

	FTimerHandle ShakingHandle;
	const float ShakingPower = 0.4f;
	const float ShakingRange = 12.0f;
	float ShakingTime = 0.0f;
	float ShakingAxis = 0.0f;
	bool ShakingSwitch = true;
};
