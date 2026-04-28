// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CharacterInfoWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterRoleSelected, int32, SelectedRoleType);

UCLASS()
class CLAIM_OF_CORE_API UCharacterInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintAssignable, Category = "Character")
    FOnCharacterRoleSelected OnCharacterRoleSelected;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* StrikerButton;

    UPROPERTY(meta = (BindWidget))
    UButton* GuardianButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ManipulatorButton;

    UPROPERTY(BlueprintReadOnly, Category = "Character")
    int32 SelectedRoleType = -1;

private:
    UFUNCTION()
    void OnStrikerClicked();

    UFUNCTION()
    void OnGuardianClicked();

    UFUNCTION()
    void OnManipulatorClicked();

    void HandleRoleSelected(int32 InRoleType);
};
