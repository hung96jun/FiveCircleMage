// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_MonsterUI.generated.h"

/**
 * 
 */
class UImage;
class UProgressBar;

UCLASS()
class FIVECIRCLEMAGE_API UC_MonsterUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HP;

	UPROPERTY(BlueprintReadOnly)
		float OriginHiddenTime = 3.0f;

private:
	UFUNCTION()
		void Hiding();

	UFUNCTION()
		void SetOff();

public:
	UC_MonsterUI(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void Init();
	void SetHealth(float Percent);

private:
	void ClearTimer();

private:
	FTimerHandle TimerHandle;
	float CurHiddenTime = 0.0f;
};
