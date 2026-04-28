// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "NetworkInstance.h"

void ULoginWidget::FocusInitialWidget()
{
	if (!ID_BOX)
	{
		return;
	}

	if (APlayerController* PC = GetOwningPlayer())
	{
		ID_BOX->SetUserFocus(PC);
	}

	ID_BOX->SetKeyboardFocus();
}

void ULoginWidget::ShowPopup(const FText& PopupMessage)
{
	if (FailLoginPopUp) {
		FailLoginPopUp->SetText(PopupMessage);
		FailLoginPopUp->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().ClearTimer(FailPopupTimerHandle);

		GetWorld()->GetTimerManager().SetTimer(FailPopupTimerHandle, this,
			&ULoginWidget::HidePopup, 3.f, false);
	}
}

void ULoginWidget::HidePopup()
{
	if (FailLoginPopUp) {
		FailLoginPopUp->SetVisibility(ESlateVisibility::Hidden);
	}

	GetWorld()->GetTimerManager().ClearTimer(FailPopupTimerHandle);
}

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Popup Setting
	if (FailLoginPopUp)
	{
		FailLoginPopUp->SetVisibility(ESlateVisibility::Hidden);
	}

	// Click Event
	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ULoginWidget::OnLoginClicked);
	}

	if (RegisterButton)
	{
		RegisterButton->OnClicked.AddDynamic(this, &ULoginWidget::OnRegisterCliecked);
	}
}

FReply ULoginWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (FailLoginPopUp && FailLoginPopUp->GetVisibility() == ESlateVisibility::Visible) {
		HidePopup();

		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void ULoginWidget::OnLoginClicked()
{
	if (ID_BOX && PW_BOX)
	{
		// Get Input Text (ID/PW)
		FString UserID = ID_BOX->GetText().ToString();
		FString UserPW = PW_BOX->GetText().ToString();

		UE_LOG(LogTemp, Log, TEXT("Input ID: %s / PW: %s"), *UserID, *UserPW);

		// Send to Server used by NetworkInstance
		UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
		if (GI) { GI->TryLogin(UserID, UserPW); }
	}
}

void ULoginWidget::OnRegisterCliecked()
{
	if (ID_BOX && PW_BOX)
	{
		FString UserID = ID_BOX->GetText().ToString();
		FString UserPW = PW_BOX->GetText().ToString();

		UE_LOG(LogTemp, Log, TEXT("Register Request - ID: %s / PW: %s"), *UserID, *UserPW);

		UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
		if (GI)
		{
			GI->TryRegister(UserID, UserPW);
		}
	}
}
