// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/Building/DebrisSpawner.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDebrisSpawner() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ADebrisSpawner();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ADebrisSpawner_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AInGame_GameState_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ASmallDebrisActor_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ADebrisSpawner ***********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ADebrisSpawner;
UClass* ADebrisSpawner::GetPrivateStaticClass()
{
	using TClass = ADebrisSpawner;
	if (!Z_Registration_Info_UClass_ADebrisSpawner.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DebrisSpawner"),
			Z_Registration_Info_UClass_ADebrisSpawner.InnerSingleton,
			StaticRegisterNativesADebrisSpawner,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_ADebrisSpawner.InnerSingleton;
}
UClass* Z_Construct_UClass_ADebrisSpawner_NoRegister()
{
	return ADebrisSpawner::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ADebrisSpawner_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/Building/DebrisSpawner.h" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnArea_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DebrisClass_MetaData[] = {
		{ "Category", "Spawner" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnHeightOffset_MetaData[] = {
		{ "Category", "Spawner" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RandomHeightOffset_MetaData[] = {
		{ "Category", "Spawner" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase1MinSpawnInterval_MetaData[] = {
		{ "Category", "Spawner|Phase1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Phase 1\n" },
#endif
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Phase 1" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase1MaxSpawnInterval_MetaData[] = {
		{ "Category", "Spawner|Phase1" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase1MinSpawnCount_MetaData[] = {
		{ "Category", "Spawner|Phase1" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase1MaxSpawnCount_MetaData[] = {
		{ "Category", "Spawner|Phase1" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase2MinSpawnInterval_MetaData[] = {
		{ "Category", "Spawner|Phase2" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Phase 2\n" },
#endif
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Phase 2" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase2MaxSpawnInterval_MetaData[] = {
		{ "Category", "Spawner|Phase2" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase2MinSpawnCount_MetaData[] = {
		{ "Category", "Spawner|Phase2" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase2MaxSpawnCount_MetaData[] = {
		{ "Category", "Spawner|Phase2" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase3MinSpawnInterval_MetaData[] = {
		{ "Category", "Spawner|Phase3" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Phase 3\n" },
#endif
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Phase 3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase3MaxSpawnInterval_MetaData[] = {
		{ "Category", "Spawner|Phase3" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase3MinSpawnCount_MetaData[] = {
		{ "Category", "Spawner|Phase3" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase3MaxSpawnCount_MetaData[] = {
		{ "Category", "Spawner|Phase3" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDrawDebugBox_MetaData[] = {
		{ "Category", "Spawner" },
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedGameState_MetaData[] = {
		{ "ModuleRelativePath", "Map/Building/DebrisSpawner.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ADebrisSpawner constinit property declarations ***************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnArea;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DebrisClass;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpawnHeightOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RandomHeightOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase1MinSpawnInterval;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase1MaxSpawnInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase1MinSpawnCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase1MaxSpawnCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase2MinSpawnInterval;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase2MaxSpawnInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase2MinSpawnCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase2MaxSpawnCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase3MinSpawnInterval;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase3MaxSpawnInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase3MinSpawnCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase3MaxSpawnCount;
	static void NewProp_bDrawDebugBox_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawDebugBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedGameState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADebrisSpawner constinit property declarations *****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADebrisSpawner>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ADebrisSpawner_Statics

// ********** Begin Class ADebrisSpawner Property Definitions **************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_SpawnArea = { "SpawnArea", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, SpawnArea), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnArea_MetaData), NewProp_SpawnArea_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_DebrisClass = { "DebrisClass", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, DebrisClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_ASmallDebrisActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DebrisClass_MetaData), NewProp_DebrisClass_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_SpawnHeightOffset = { "SpawnHeightOffset", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, SpawnHeightOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnHeightOffset_MetaData), NewProp_SpawnHeightOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_RandomHeightOffset = { "RandomHeightOffset", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, RandomHeightOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RandomHeightOffset_MetaData), NewProp_RandomHeightOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MinSpawnInterval = { "Phase1MinSpawnInterval", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase1MinSpawnInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase1MinSpawnInterval_MetaData), NewProp_Phase1MinSpawnInterval_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MaxSpawnInterval = { "Phase1MaxSpawnInterval", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase1MaxSpawnInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase1MaxSpawnInterval_MetaData), NewProp_Phase1MaxSpawnInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MinSpawnCount = { "Phase1MinSpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase1MinSpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase1MinSpawnCount_MetaData), NewProp_Phase1MinSpawnCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MaxSpawnCount = { "Phase1MaxSpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase1MaxSpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase1MaxSpawnCount_MetaData), NewProp_Phase1MaxSpawnCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MinSpawnInterval = { "Phase2MinSpawnInterval", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase2MinSpawnInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase2MinSpawnInterval_MetaData), NewProp_Phase2MinSpawnInterval_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MaxSpawnInterval = { "Phase2MaxSpawnInterval", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase2MaxSpawnInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase2MaxSpawnInterval_MetaData), NewProp_Phase2MaxSpawnInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MinSpawnCount = { "Phase2MinSpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase2MinSpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase2MinSpawnCount_MetaData), NewProp_Phase2MinSpawnCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MaxSpawnCount = { "Phase2MaxSpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase2MaxSpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase2MaxSpawnCount_MetaData), NewProp_Phase2MaxSpawnCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MinSpawnInterval = { "Phase3MinSpawnInterval", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase3MinSpawnInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase3MinSpawnInterval_MetaData), NewProp_Phase3MinSpawnInterval_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MaxSpawnInterval = { "Phase3MaxSpawnInterval", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase3MaxSpawnInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase3MaxSpawnInterval_MetaData), NewProp_Phase3MaxSpawnInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MinSpawnCount = { "Phase3MinSpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase3MinSpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase3MinSpawnCount_MetaData), NewProp_Phase3MinSpawnCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MaxSpawnCount = { "Phase3MaxSpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, Phase3MaxSpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase3MaxSpawnCount_MetaData), NewProp_Phase3MaxSpawnCount_MetaData) };
void Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_bDrawDebugBox_SetBit(void* Obj)
{
	((ADebrisSpawner*)Obj)->bDrawDebugBox = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_bDrawDebugBox = { "bDrawDebugBox", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ADebrisSpawner), &Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_bDrawDebugBox_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDrawDebugBox_MetaData), NewProp_bDrawDebugBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_CachedGameState = { "CachedGameState", nullptr, (EPropertyFlags)0x0124080000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADebrisSpawner, CachedGameState), Z_Construct_UClass_AInGame_GameState_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedGameState_MetaData), NewProp_CachedGameState_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADebrisSpawner_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_SpawnArea,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_DebrisClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_SpawnHeightOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_RandomHeightOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MinSpawnInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MaxSpawnInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MinSpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase1MaxSpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MinSpawnInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MaxSpawnInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MinSpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase2MaxSpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MinSpawnInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MaxSpawnInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MinSpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_Phase3MaxSpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_bDrawDebugBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebrisSpawner_Statics::NewProp_CachedGameState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADebrisSpawner_Statics::PropPointers) < 2048);
// ********** End Class ADebrisSpawner Property Definitions ****************************************
UObject* (*const Z_Construct_UClass_ADebrisSpawner_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADebrisSpawner_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ADebrisSpawner_Statics::ClassParams = {
	&ADebrisSpawner::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ADebrisSpawner_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ADebrisSpawner_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADebrisSpawner_Statics::Class_MetaDataParams), Z_Construct_UClass_ADebrisSpawner_Statics::Class_MetaDataParams)
};
void ADebrisSpawner::StaticRegisterNativesADebrisSpawner()
{
}
UClass* Z_Construct_UClass_ADebrisSpawner()
{
	if (!Z_Registration_Info_UClass_ADebrisSpawner.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADebrisSpawner.OuterSingleton, Z_Construct_UClass_ADebrisSpawner_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ADebrisSpawner.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADebrisSpawner);
ADebrisSpawner::~ADebrisSpawner() {}
// ********** End Class ADebrisSpawner *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_DebrisSpawner_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADebrisSpawner, ADebrisSpawner::StaticClass, TEXT("ADebrisSpawner"), &Z_Registration_Info_UClass_ADebrisSpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADebrisSpawner), 949727627U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_DebrisSpawner_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_DebrisSpawner_h__Script_Claim_Of_Core_2040566081{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_DebrisSpawner_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_DebrisSpawner_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
