// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyLiftBubble.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sub/MyCharacter.h"

// Sets default values
ASkyLiftBubble::ASkyLiftBubble()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    PrimaryActorTick.bCanEverTick = true;

    LiftCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LiftCollision"));
    SetRootComponent(LiftCollision);

    LiftCollision->SetSphereRadius(220.f);
    LiftCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    LiftCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    LiftCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    LiftCollision->SetGenerateOverlapEvents(true);

    LiftCollision->OnComponentBeginOverlap.AddDynamic(this, &ASkyLiftBubble::OnBubbleBeginOverlap);
    LiftCollision->OnComponentEndOverlap.AddDynamic(this, &ASkyLiftBubble::OnBubbleEndOverlap);

    BubbleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleMesh"));
    BubbleMeshComponent->SetupAttachment(LiftCollision);
    BubbleMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BubbleMeshComponent->SetGenerateOverlapEvents(false);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (DefaultMesh.Succeeded())
    {
        BubbleMeshComponent->SetStaticMesh(DefaultMesh.Object);
        BubbleMeshComponent->SetRelativeScale3D(FVector(2.2f, 2.2f, 4.0f));
    }
}

// Called when the game starts or when spawned
void ASkyLiftBubble::BeginPlay()
{
    Super::BeginPlay();

    Tags.Add(TEXT("SkyLiftBubble"));

    ApplyVisualSettings();
    SetBubbleActive(true);
}

// Called every frame
void ASkyLiftBubble::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bBubbleActive || DeltaTime <= 0.f)
    {
        return;
    }

    ActiveElapsed += DeltaTime;

    ApplyUpdraft();

    if (ActiveElapsed >= ActiveDuration)
    {
        Destroy();
    }
}

void ASkyLiftBubble::OnBubbleBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
    if (!bBubbleActive || !Character || Character->IsDead())
    {
        return;
    }

    OverlappingCharacters.Add(Character);
}

void ASkyLiftBubble::OnBubbleEndOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
    {
        OverlappingCharacters.Remove(Character);
    }
}

void ASkyLiftBubble::SetBubbleActive(bool bNewActive)
{
    bBubbleActive = bNewActive;

    SetActorHiddenInGame(!bBubbleActive);
    SetActorEnableCollision(bBubbleActive);

    if (LiftCollision)
    {
        LiftCollision->SetCollisionEnabled(
            bBubbleActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision
        );

        LiftCollision->SetGenerateOverlapEvents(bBubbleActive);
    }

    if (BubbleMeshComponent)
    {
        BubbleMeshComponent->SetHiddenInGame(!bBubbleActive);
        BubbleMeshComponent->SetVisibility(bBubbleActive, true);
    }
}

void ASkyLiftBubble::ApplyUpdraft()
{
    for (auto It = OverlappingCharacters.CreateIterator(); It; ++It)
    {
        AMyCharacter* Character = It->Get();

        if (!Character || Character->IsDead())
        {
            It.RemoveCurrent();
            continue;
        }

        UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
        if (!MoveComp)
        {
            continue;
        }

        FVector Velocity = MoveComp->Velocity;
        Velocity.Z = FMath::Max(Velocity.Z, UpdraftSpeed);
        MoveComp->Velocity = Velocity;
    }
}

void ASkyLiftBubble::ApplyVisualSettings()
{
    if (!BubbleMeshComponent)
    {
        return;
    }

    if (BubbleMesh)
    {
        BubbleMeshComponent->SetStaticMesh(BubbleMesh);
    }

    if (BubbleMaterial)
    {
        BubbleMeshComponent->SetMaterial(0, BubbleMaterial);
    }
}