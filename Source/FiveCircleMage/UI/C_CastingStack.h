// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_CastingStack.generated.h"

class UImage;
class AC_Mage;

UCLASS()
class FIVECIRCLEMAGE_API UC_CastingStack : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* CStack_0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* CStack_1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* CStack_2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* CStack_3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* CStack_4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* FX_0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* FX_1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* FX_2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* FX_3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* FX_4;
	
public:
	UC_CastingStack(const FObjectInitializer& ObjectInitializer);

	void SetOwner(AC_Mage* Unit) { Owner = Unit; }

	void ShowPanel();
	void ShakePanel();
	void HidePanel();

	void SetStackSlot(int32 SlotNum, int32 ElementNum, float DelayTime = 0.0f);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void InitStack();

	void SetImageTransformX(int32 SlotNum);

private:
	AC_Mage* Owner = nullptr;

	FString ElementRefs[5];
	TArray<UImage*> Images;
	TArray<UImage*> FXs;

	int32 CurSlotNum;
	int32 CurOpeningSlotNum;
	float CurCastingTime;
	float TargetCastingTime;
	float OpeningOpacity;
	bool IsSlotOpening = false;

	bool bIsActive = false;
};
