// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/Building/LargeDebrisController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeLargeDebrisController() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AInGame_GameState_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ALargeDebrisActor_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ALargeDebrisController();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ALargeDebrisController_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ALargeDebrisController ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ALargeDebrisController;
UClass* ALargeDebrisController::GetPrivateStaticClass()
{
	using TClass = ALargeDebrisController;
	if (!Z_Registration_Info_UClass_ALargeDebrisController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("LargeDebrisController"),
			Z_Registration_Info_UClass_ALargeDebrisController.InnerSingleton,
			StaticRegisterNativesALargeDebrisController,
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
	return Z_Registration_Info_UClass_ALargeDebrisController.InnerSingleton;
}
UClass* Z_Construct_UClass_ALargeDebrisController_NoRegister()
{
	return ALargeDebrisController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ALargeDebrisController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/Building/LargeDebrisController.h" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase2DebrisActors_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase3DebrisActors_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialImpulseStrength_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedGameState_MetaData[] = {
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPhase2Triggered_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPhase3Triggered_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ALargeDebrisController constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Phase2DebrisActors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Phase2DebrisActors;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Phase3DebrisActors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Phase3DebrisActors;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialImpulseStrength;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedGameState;
	static void NewProp_bPhase2Triggered_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPhase2Triggered;
	static void NewProp_bPhase3Triggered_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPhase3Triggered;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ALargeDebrisController constinit property declarations *********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALargeDebrisController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ALargeDebrisController_Statics

// ********** Begin Class ALargeDebrisController Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisController, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase2DebrisActors_Inner = { "Phase2DebrisActors", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ALargeDebrisActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase2DebrisActors = { "Phase2DebrisActors", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisController, Phase2DebrisActors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase2DebrisActors_MetaData), NewProp_Phase2DebrisActors_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase3DebrisActors_Inner = { "Phase3DebrisActors", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ALargeDebrisActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase3DebrisActors = { "Phase3DebrisActors", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisController, Phase3DebrisActors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase3DebrisActors_MetaData), NewProp_Phase3DebrisActors_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_InitialImpulseStrength = { "InitialImpulseStrength", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisController, InitialImpulseStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialImpulseStrength_MetaData), NewProp_InitialImpulseStrength_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_CachedGameState = { "CachedGameState", nullptr, (EPropertyFlags)0x0124080000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisController, CachedGameState), Z_Construct_UClass_AInGame_GameState_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedGameState_MetaData), NewProp_CachedGameState_MetaData) };
void Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase2Triggered_SetBit(void* Obj)
{
	((ALargeDebrisController*)Obj)->bPhase2Triggered = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase2Triggered = { "bPhase2Triggered", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALargeDebrisController), &Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase2Triggered_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPhase2Triggered_MetaData), NewProp_bPhase2Triggered_MetaData) };
void Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase3Triggered_SetBit(void* Obj)
{
	((ALargeDebrisController*)Obj)->bPhase3Triggered = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase3Triggered = { "bPhase3Triggered", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALargeDebrisController), &Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase3Triggered_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPhase3Triggered_MetaData), NewProp_bPhase3Triggered_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALargeDebrisController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase2DebrisActors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase2DebrisActors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase3DebrisActors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_Phase3DebrisActors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_InitialImpulseStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_CachedGameState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase2Triggered,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisController_Statics::NewProp_bPhase3Triggered,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisController_Statics::PropPointers) < 2048);
// ********** End Class ALargeDebrisController Property Definitions ********************************
UObject* (*const Z_Construct_UClass_ALargeDebrisController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALargeDebrisController_Statics::ClassParams = {
	&ALargeDebrisController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ALargeDebrisController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisController_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisController_Statics::Class_MetaDataParams), Z_Construct_UClass_ALargeDebrisController_Statics::Class_MetaDataParams)
};
void ALargeDebrisController::StaticRegisterNativesALargeDebrisController()
{
}
UClass* Z_Construct_UClass_ALargeDebrisController()
{
	if (!Z_Registration_Info_UClass_ALargeDebrisController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALargeDebrisController.OuterSingleton, Z_Construct_UClass_ALargeDebrisController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALargeDebrisController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ALargeDebrisController);
ALargeDebrisController::~ALargeDebrisController() {}
// ********** End Class ALargeDebrisController *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisController_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALargeDebrisController, ALargeDebrisController::StaticClass, TEXT("ALargeDebrisController"), &Z_Registration_Info_UClass_ALargeDebrisController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALargeDebrisController), 3213162213U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisController_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisController_h__Script_Claim_Of_Core_3967642688{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisController_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisController_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
