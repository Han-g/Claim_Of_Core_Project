// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/IceCave/IceMapController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeIceMapController() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIceFloorTile_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIceMapController();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIceMapController_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIcicleActor_NoRegister();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase();
ENGINE_API UClass* Z_Construct_UClass_AActor();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EIceMapPhase **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EIceMapPhase;
static UEnum* EIceMapPhase_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EIceMapPhase.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EIceMapPhase.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("EIceMapPhase"));
	}
	return Z_Registration_Info_UEnum_EIceMapPhase.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EIceMapPhase>()
{
	return EIceMapPhase_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
		{ "Phase1.Name", "EIceMapPhase::Phase1" },
		{ "Phase2.Name", "EIceMapPhase::Phase2" },
		{ "Phase3.Name", "EIceMapPhase::Phase3" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EIceMapPhase::Phase1", (int64)EIceMapPhase::Phase1 },
		{ "EIceMapPhase::Phase2", (int64)EIceMapPhase::Phase2 },
		{ "EIceMapPhase::Phase3", (int64)EIceMapPhase::Phase3 },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"EIceMapPhase",
	"EIceMapPhase",
	Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase()
{
	if (!Z_Registration_Info_UEnum_EIceMapPhase.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EIceMapPhase.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EIceMapPhase.InnerSingleton;
}
// ********** End Enum EIceMapPhase ****************************************************************

// ********** Begin Class AIceMapController Function BP_OnPhaseChanged *****************************
struct IceMapController_eventBP_OnPhaseChanged_Parms
{
	EIceMapPhase NewPhase;
};
static FName NAME_AIceMapController_BP_OnPhaseChanged = FName(TEXT("BP_OnPhaseChanged"));
void AIceMapController::BP_OnPhaseChanged(EIceMapPhase NewPhase)
{
	IceMapController_eventBP_OnPhaseChanged_Parms Parms;
	Parms.NewPhase=NewPhase;
	UFunction* Func = FindFunctionChecked(NAME_AIceMapController_BP_OnPhaseChanged);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnPhaseChanged constinit property declarations *********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewPhase_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewPhase;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnPhaseChanged constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnPhaseChanged Property Definitions ********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::NewProp_NewPhase_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::NewProp_NewPhase = { "NewPhase", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(IceMapController_eventBP_OnPhaseChanged_Parms, NewPhase), Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase, METADATA_PARAMS(0, nullptr) }; // 4258058693
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::NewProp_NewPhase_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::NewProp_NewPhase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::PropPointers) < 2048);
// ********** End Function BP_OnPhaseChanged Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceMapController, nullptr, "BP_OnPhaseChanged", 	Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::PropPointers), 
sizeof(IceMapController_eventBP_OnPhaseChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(IceMapController_eventBP_OnPhaseChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AIceMapController Function BP_OnPhaseChanged *******************************

// ********** Begin Class AIceMapController Function StartIceMap ***********************************
struct Z_Construct_UFunction_AIceMapController_StartIceMap_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartIceMap constinit property declarations ***************************
// ********** End Function StartIceMap constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceMapController_StartIceMap_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceMapController, nullptr, "StartIceMap", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceMapController_StartIceMap_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceMapController_StartIceMap_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIceMapController_StartIceMap()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceMapController_StartIceMap_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIceMapController::execStartIceMap)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartIceMap();
	P_NATIVE_END;
}
// ********** End Class AIceMapController Function StartIceMap *************************************

// ********** Begin Class AIceMapController ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AIceMapController;
UClass* AIceMapController::GetPrivateStaticClass()
{
	using TClass = AIceMapController;
	if (!Z_Registration_Info_UClass_AIceMapController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("IceMapController"),
			Z_Registration_Info_UClass_AIceMapController.InnerSingleton,
			StaticRegisterNativesAIceMapController,
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
	return Z_Registration_Info_UClass_AIceMapController.InnerSingleton;
}
UClass* Z_Construct_UClass_AIceMapController_NoRegister()
{
	return AIceMapController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AIceMapController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/IceCave/IceMapController.h" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentPhase_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase2StartTime_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase3StartTime_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IcicleSpawnIntervalPhase2_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IcicleSpawnIntervalPhase3_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FloorBreakIntervalPhase3_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IcicleActors_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FloorTiles_MetaData[] = {
		{ "Category", "IceMap" },
		{ "ModuleRelativePath", "Map/IceCave/IceMapController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AIceMapController constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentPhase_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentPhase;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase2StartTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Phase3StartTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_IcicleSpawnIntervalPhase2;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_IcicleSpawnIntervalPhase3;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FloorBreakIntervalPhase3;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_IcicleActors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_IcicleActors;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FloorTiles_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FloorTiles;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AIceMapController constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("StartIceMap"), .Pointer = &AIceMapController::execStartIceMap },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AIceMapController_BP_OnPhaseChanged, "BP_OnPhaseChanged" }, // 3395276579
		{ &Z_Construct_UFunction_AIceMapController_StartIceMap, "StartIceMap" }, // 3567775178
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AIceMapController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AIceMapController_Statics

// ********** Begin Class AIceMapController Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_CurrentPhase_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_CurrentPhase = { "CurrentPhase", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, CurrentPhase), Z_Construct_UEnum_Claim_Of_Core_EIceMapPhase, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentPhase_MetaData), NewProp_CurrentPhase_MetaData) }; // 4258058693
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_Phase2StartTime = { "Phase2StartTime", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, Phase2StartTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase2StartTime_MetaData), NewProp_Phase2StartTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_Phase3StartTime = { "Phase3StartTime", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, Phase3StartTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase3StartTime_MetaData), NewProp_Phase3StartTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleSpawnIntervalPhase2 = { "IcicleSpawnIntervalPhase2", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, IcicleSpawnIntervalPhase2), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IcicleSpawnIntervalPhase2_MetaData), NewProp_IcicleSpawnIntervalPhase2_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleSpawnIntervalPhase3 = { "IcicleSpawnIntervalPhase3", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, IcicleSpawnIntervalPhase3), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IcicleSpawnIntervalPhase3_MetaData), NewProp_IcicleSpawnIntervalPhase3_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_FloorBreakIntervalPhase3 = { "FloorBreakIntervalPhase3", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, FloorBreakIntervalPhase3), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FloorBreakIntervalPhase3_MetaData), NewProp_FloorBreakIntervalPhase3_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleActors_Inner = { "IcicleActors", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AIcicleActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleActors = { "IcicleActors", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, IcicleActors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IcicleActors_MetaData), NewProp_IcicleActors_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_FloorTiles_Inner = { "FloorTiles", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AIceFloorTile_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AIceMapController_Statics::NewProp_FloorTiles = { "FloorTiles", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceMapController, FloorTiles), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FloorTiles_MetaData), NewProp_FloorTiles_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AIceMapController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_CurrentPhase_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_CurrentPhase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_Phase2StartTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_Phase3StartTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleSpawnIntervalPhase2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleSpawnIntervalPhase3,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_FloorBreakIntervalPhase3,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleActors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_IcicleActors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_FloorTiles_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceMapController_Statics::NewProp_FloorTiles,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIceMapController_Statics::PropPointers) < 2048);
// ********** End Class AIceMapController Property Definitions *************************************
UObject* (*const Z_Construct_UClass_AIceMapController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIceMapController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AIceMapController_Statics::ClassParams = {
	&AIceMapController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AIceMapController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AIceMapController_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AIceMapController_Statics::Class_MetaDataParams), Z_Construct_UClass_AIceMapController_Statics::Class_MetaDataParams)
};
void AIceMapController::StaticRegisterNativesAIceMapController()
{
	UClass* Class = AIceMapController::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AIceMapController_Statics::Funcs));
}
UClass* Z_Construct_UClass_AIceMapController()
{
	if (!Z_Registration_Info_UClass_AIceMapController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AIceMapController.OuterSingleton, Z_Construct_UClass_AIceMapController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AIceMapController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AIceMapController);
AIceMapController::~AIceMapController() {}
// ********** End Class AIceMapController **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h__Script_Claim_Of_Core_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EIceMapPhase_StaticEnum, TEXT("EIceMapPhase"), &Z_Registration_Info_UEnum_EIceMapPhase, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4258058693U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AIceMapController, AIceMapController::StaticClass, TEXT("AIceMapController"), &Z_Registration_Info_UClass_AIceMapController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AIceMapController), 267771107U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h__Script_Claim_Of_Core_4141552907{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h__Script_Claim_Of_Core_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h__Script_Claim_Of_Core_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
