#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_UIComponent.generated.h"

//class UC_ElementPanel;
//class UC_MainMenu;
//class UC_OptionMenu;

USTRUCT(BlueprintType)
struct FWidgetInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UUserWidget> WidgetClasses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ZOrder;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIVECIRCLEMAGE_API UC_UIComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, UUserWidget*> Widgets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, FWidgetInfo> WidgetInfos;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UC_ElementPanel* ElementPanel;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UC_MainMenu* MainMenu;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UC_OptionMenu* OptionMenu;

public:	
	UC_UIComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	template<typename T>
	T* GetUI(FString key) { return Cast<T>(Widgets.FindRef(key)); }
	
	void CallUI(FString key);

private:
	void CreateUI();
};
