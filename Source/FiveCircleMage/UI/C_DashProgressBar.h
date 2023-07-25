// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_DashProgressBar.generated.h"

/**
 * 
 */
class UImage;
class UProgressBar;

UCLASS()
class FIVECIRCLEMAGE_API UC_DashProgressBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnimation))
		UWidgetAnimation* EnableDashAnim;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* DashProgressBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* EnableDashImg;

public:
	UC_DashProgressBar(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct(); 
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetDashCoolTime(float CoolTime);
	void CallDashProgressBar();

private:
	bool bIsActive = false;

	float DashValue = 0.0f;
	float DashCooltime = 0.0f;
};
