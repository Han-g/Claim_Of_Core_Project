// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Space/BlackHoleGrenadeItem.h"

#include "Map/Space/BlackHoleActor.h"
#include "Sub/MyCharacter.h"
#include "NetworkInstance.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

ABlackHoleGrenadeItem::ABlackHoleGrenadeItem()
{
    BlackHoleClass = ABlackHoleActor::StaticClass();

    Damage = 0.f;
    KnockbackPower = 0.f;
    Range = 0.f;
    Radius = 0.f;
    ItemAnimPoseType = EItemAnimPoseType::Grenade;
}

void ABlackHoleGrenadeItem::DoHit()
{
    if (!OwnerCharacter || !GetWorld() || bHasBeenThrown)
    {
        return;
    }

    AMyCharacter* Thrower = OwnerCharacter;
    const FVector Forward = Thrower->GetActorForwardVector().GetSafeNormal();
    const FVector ThrowLocation =
        Thrower->GetActorLocation()
        + Forward * ThrowSpawnForwardOffset
        + FVector::UpVector * ThrowSpawnUpOffset;

    bHasBeenThrown = true;

    Thrower->DropCurrentItem();

    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    SetActorLocation(ThrowLocation, false, nullptr, ETeleportType::TeleportPhysics);
    SetActorRotation(Forward.Rotation());
    SetActorEnableCollision(true);

    UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(GetRootComponent());
    if (!Prim)
    {
        Destroy();
        return;
    }

    Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Prim->SetCollisionResponseToAllChannels(ECR_Block);
    Prim->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    Prim->SetGenerateOverlapEvents(true);
    Prim->SetSimulatePhysics(true);
    Prim->SetEnableGravity(true);
    Prim->SetNotifyRigidBodyCollision(true);
    Prim->OnComponentHit.RemoveDynamic(this, &ABlackHoleGrenadeItem::OnGrenadeHit);
    Prim->OnComponentHit.AddDynamic(this, &ABlackHoleGrenadeItem::OnGrenadeHit);
    Prim->SetPhysicsLinearVelocity(Forward * ThrowSpeed + FVector::UpVector * ThrowUpwardSpeed);
}

void ABlackHoleGrenadeItem::OnGrenadeHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    if (!bHasBeenThrown || bHasExploded)
    {
        return;
    }

    if (Hit.ImpactNormal.Z < GroundNormalThreshold)
    {
        return;
    }

    UE_LOG(LogTemp, Warning,
        TEXT("[BlackHoleGrenade] Hit Other=%s NormalZ=%.2f"),
        *GetNameSafe(OtherActor),
        Hit.ImpactNormal.Z);

    bHasExploded = true;

    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(GetRootComponent()))
    {
        Prim->SetSimulatePhysics(false);
        Prim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    //SpawnGrenadeBlackHole(Hit);
    if (UNetworkInstance* NetInst = GetWorld()->GetGameInstance<UNetworkInstance>())
    {
        const FVector SpawnLocation = Hit.ImpactPoint + FVector::UpVector * 8.f;
        NetInst->RequestGrenadeBlackHoleSpawn(GetItemID(), SpawnLocation);
    }
    Destroy();
}

void ABlackHoleGrenadeItem::SpawnGrenadeBlackHole(const FHitResult& Hit)
{
    if (!GetWorld() || !BlackHoleClass)
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ABlackHoleActor* BlackHole = GetWorld()->SpawnActor<ABlackHoleActor>(
        BlackHoleClass,
        Hit.ImpactPoint + FVector::UpVector * 8.f,
        FRotator::ZeroRotator,
        SpawnParams
    );

    if (!BlackHole)
    {
        return;
    }

    UE_LOG(LogTemp, Warning,
        TEXT("[BlackHoleGrenade] Spawn BlackHole Location=%s"),
        *BlackHole->GetActorLocation().ToString());

    BlackHole->SetActorScale3D(GrenadeBlackHoleScale);
    BlackHole->ShowBlackHole();
    BlackHole->ActivateBlackHole();
    BlackHole->SetLifeSpan(BlackHoleLifeSeconds);
}