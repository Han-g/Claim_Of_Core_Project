// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "NetworkInstance.h"

void ULoginWidget::FocusInitialWidget()
{
	if (!IsValid(ID_BOX) || !IsInViewport())
	{
		return;
	}

	if (ID_BOX)
	{
		ID_BOX->SetKeyboardFocus();
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

	bLoginUIOpened = false;

	if (BG_Overlay)
	{
		BG_Overlay->SetVisibility(ESlateVisibility::Visible);
		BG_Overlay->SetRenderOpacity(0.0f);
	}

	if (LoginBorder)
	{
		LoginBorder->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (LoginBox)
	{
		LoginBox->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (ClickToStartText)
	{
		ClickToStartText->SetVisibility(ESlateVisibility::Visible);
	}

	// Popup Setting
	if (FailLoginPopUp)
	{
		FailLoginPopUp->SetVisibility(ESlateVisibility::Hidden);
	}

	SetIsFocusable(true);
	SetKeyboardFocus();

	// Click Event
	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ULoginWidget::OnLoginClicked);
	}

	if (RegisterButton)
	{
		RegisterButton->OnClicked.AddDynamic(this, &ULoginWidget::OnRegisterClicked);
	}
}

FReply ULoginWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bLoginUIOpened)
	{
		OpenLoginUI();
		return FReply::Handled();
	}

	if (FailLoginPopUp && FailLoginPopUp->GetVisibility() == ESlateVisibility::Visible) {
		HidePopup();

		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply ULoginWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (!bLoginUIOpened)
	{
		OpenLoginUI();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void ULoginWidget::OpenLoginUI()
{
	bLoginUIOpened = true;

	if (ClickToStartText)
	{
		ClickToStartText->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (BG_Overlay)
	{
		BG_Overlay->SetVisibility(ESlateVisibility::Visible);
		BG_Overlay->SetRenderOpacity(1.0f);
	}

	if (LoginBorder)
	{
		LoginBorder->SetVisibility(ESlateVisibility::Visible);
	}

	if (LoginBox)
	{
		LoginBox->SetVisibility(ESlateVisibility::Visible);
	}

	FocusInitialWidget();
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

void ULoginWidget::OnRegisterClicked()
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
