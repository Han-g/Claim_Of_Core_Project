#include "HPComponent.h"
#include "Net/UnrealNetwork.h"

UHPComponent::UHPComponent()
{
	SetIsReplicatedByDefault(true);

	MaxHP = 100;
	CurrentHP = MaxHP;
}

void UHPComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		CurrentHP = FMath::Clamp(CurrentHP, 0, MaxHP);
	}
}

void UHPComponent::ApplyDamage(int32 DamageAmount)
{
	if (DamageAmount <= 0) return;

	if (GetOwner() && !GetOwner()->HasAuthority())
	{
		ServerApplyDamage(DamageAmount);
		return;
	}

	const int32 OldHP = CurrentHP;
	CurrentHP = FMath::Clamp(CurrentHP - DamageAmount, 0, MaxHP);

	HandleHPChanged(OldHP);
}

void UHPComponent::Heal(int32 HealAmount)
{
	if (HealAmount <= 0) return;

	if (GetOwner() && !GetOwner()->HasAuthority())
	{
		ServerHeal(HealAmount);
		return;
	}

	const int32 OldHP = CurrentHP;
	CurrentHP = FMath::Clamp(CurrentHP + HealAmount, 0, MaxHP);

	HandleHPChanged(OldHP);
}

void UHPComponent::ResetHP()
{
	if (GetOwner() && !GetOwner()->HasAuthority())
	{
		return;
	}

	const int32 OldHP = CurrentHP;
	CurrentHP = MaxHP;
	HandleHPChanged(OldHP);
}

void UHPComponent::OnRep_CurrentHP(int32 OldHP)
{
	HandleHPChanged(OldHP);
}

void UHPComponent::HandleHPChanged(int32 OldHP)
{
	OnHPChanged.Broadcast(CurrentHP, OldHP);

	if (OldHP > 0 && CurrentHP <= 0)
	{
		OnHPZero.Broadcast();
	}
}

void UHPComponent::ServerApplyDamage_Implementation(int32 DamageAmount)
{
	ApplyDamage(DamageAmount);
}

void UHPComponent::ServerHeal_Implementation(int32 HealAmount)
{
	Heal(HealAmount);
}

void UHPComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHPComponent, MaxHP);
	DOREPLIFETIME(UHPComponent, CurrentHP);
}
