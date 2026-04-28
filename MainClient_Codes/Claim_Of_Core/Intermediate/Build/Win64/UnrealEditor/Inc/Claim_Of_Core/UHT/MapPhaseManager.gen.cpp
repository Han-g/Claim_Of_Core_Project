// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/MapPhaseManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMapPhaseManager() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AInGame_GameState_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AMapPhaseManager();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AMapPhaseManager_NoRegister();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_EMapPhase();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_ERoundState();
CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature();
CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature();
ENGINE_API UClass* Z_Construct_UClass_AActor();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnMapPhaseChangedSignature *******************************************
struct Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics
{
	struct _Script_Claim_Of_Core_eventOnMapPhaseChangedSignature_Parms
	{
		EMapPhase NewPhase;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnMapPhaseChangedSignature constinit property declarations ***********
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewPhase_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewPhase;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnMapPhaseChangedSignature constinit property declarations *************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnMapPhaseChangedSignature Property Definitions **********************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::NewProp_NewPhase_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::NewProp_NewPhase = { "NewPhase", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_Claim_Of_Core_eventOnMapPhaseChangedSignature_Parms, NewPhase), Z_Construct_UEnum_Claim_Of_Core_EMapPhase, METADATA_PARAMS(0, nullptr) }; // 2195778762
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::NewProp_NewPhase_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::NewProp_NewPhase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnMapPhaseChangedSignature Property Definitions ************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core, nullptr, "OnMapPhaseChangedSignature__DelegateSignature", 	Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnMapPhaseChangedSignature_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnMapPhaseChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnMapPhaseChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnMapPhaseChangedSignature, EMapPhase NewPhase)
{
	struct _Script_Claim_Of_Core_eventOnMapPhaseChangedSignature_Parms
	{
		EMapPhase NewPhase;
	};
	_Script_Claim_Of_Core_eventOnMapPhaseChangedSignature_Parms Parms;
	Parms.NewPhase=NewPhase;
	OnMapPhaseChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnMapPhaseChangedSignature *********************************************

// ********** Begin Delegate FOnRoundStateChangedSignature *****************************************
struct Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics
{
	struct _Script_Claim_Of_Core_eventOnRoundStateChangedSignature_Parms
	{
		ERoundState NewRoundState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnRoundStateChangedSignature constinit property declarations *********
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewRoundState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewRoundState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnRoundStateChangedSignature constinit property declarations ***********
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnRoundStateChangedSignature Property Definitions ********************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::NewProp_NewRoundState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::NewProp_NewRoundState = { "NewRoundState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_Claim_Of_Core_eventOnRoundStateChangedSignature_Parms, NewRoundState), Z_Construct_UEnum_Claim_Of_Core_ERoundState, METADATA_PARAMS(0, nullptr) }; // 2171649069
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::NewProp_NewRoundState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::NewProp_NewRoundState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnRoundStateChangedSignature Property Definitions **********************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core, nullptr, "OnRoundStateChangedSignature__DelegateSignature", 	Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnRoundStateChangedSignature_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnRoundStateChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnRoundStateChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnRoundStateChangedSignature, ERoundState NewRoundState)
{
	struct _Script_Claim_Of_Core_eventOnRoundStateChangedSignature_Parms
	{
		ERoundState NewRoundState;
	};
	_Script_Claim_Of_Core_eventOnRoundStateChangedSignature_Parms Parms;
	Parms.NewRoundState=NewRoundState;
	OnRoundStateChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnRoundStateChangedSignature *******************************************

// ********** Begin Class AMapPhaseManager Function BP_OnMapPhaseChanged ***************************
struct MapPhaseManager_eventBP_OnMapPhaseChanged_Parms
{
	EMapPhase NewPhase;
};
static FName NAME_AMapPhaseManager_BP_OnMapPhaseChanged = FName(TEXT("BP_OnMapPhaseChanged"));
void AMapPhaseManager::BP_OnMapPhaseChanged(EMapPhase NewPhase)
{
	MapPhaseManager_eventBP_OnMapPhaseChanged_Parms Parms;
	Parms.NewPhase=NewPhase;
	UFunction* Func = FindFunctionChecked(NAME_AMapPhaseManager_BP_OnMapPhaseChanged);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnMapPhaseChanged constinit property declarations ******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewPhase_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewPhase;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnMapPhaseChanged constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnMapPhaseChanged Property Definitions *****************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::NewProp_NewPhase_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::NewProp_NewPhase = { "NewPhase", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MapPhaseManager_eventBP_OnMapPhaseChanged_Parms, NewPhase), Z_Construct_UEnum_Claim_Of_Core_EMapPhase, METADATA_PARAMS(0, nullptr) }; // 2195778762
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::NewProp_NewPhase_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::NewProp_NewPhase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::PropPointers) < 2048);
// ********** End Function BP_OnMapPhaseChanged Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapPhaseManager, nullptr, "BP_OnMapPhaseChanged", 	Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::PropPointers), 
sizeof(MapPhaseManager_eventBP_OnMapPhaseChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(MapPhaseManager_eventBP_OnMapPhaseChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AMapPhaseManager Function BP_OnMapPhaseChanged *****************************

// ********** Begin Class AMapPhaseManager Function BP_OnRoundStateChanged *************************
struct MapPhaseManager_eventBP_OnRoundStateChanged_Parms
{
	ERoundState NewRoundState;
};
static FName NAME_AMapPhaseManager_BP_OnRoundStateChanged = FName(TEXT("BP_OnRoundStateChanged"));
void AMapPhaseManager::BP_OnRoundStateChanged(ERoundState NewRoundState)
{
	MapPhaseManager_eventBP_OnRoundStateChanged_Parms Parms;
	Parms.NewRoundState=NewRoundState;
	UFunction* Func = FindFunctionChecked(NAME_AMapPhaseManager_BP_OnRoundStateChanged);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnRoundStateChanged constinit property declarations ****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewRoundState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewRoundState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnRoundStateChanged constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnRoundStateChanged Property Definitions ***************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::NewProp_NewRoundState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::NewProp_NewRoundState = { "NewRoundState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MapPhaseManager_eventBP_OnRoundStateChanged_Parms, NewRoundState), Z_Construct_UEnum_Claim_Of_Core_ERoundState, METADATA_PARAMS(0, nullptr) }; // 2171649069
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::NewProp_NewRoundState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::NewProp_NewRoundState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::PropPointers) < 2048);
// ********** End Function BP_OnRoundStateChanged Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapPhaseManager, nullptr, "BP_OnRoundStateChanged", 	Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::PropPointers), 
sizeof(MapPhaseManager_eventBP_OnRoundStateChanged_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(MapPhaseManager_eventBP_OnRoundStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AMapPhaseManager Function BP_OnRoundStateChanged ***************************

// ********** Begin Class AMapPhaseManager Function GetCurrentMapPhase *****************************
struct Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics
{
	struct MapPhaseManager_eventGetCurrentMapPhase_Parms
	{
		EMapPhase ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentMapPhase constinit property declarations ********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentMapPhase constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentMapPhase Property Definitions *******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MapPhaseManager_eventGetCurrentMapPhase_Parms, ReturnValue), Z_Construct_UEnum_Claim_Of_Core_EMapPhase, METADATA_PARAMS(0, nullptr) }; // 2195778762
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentMapPhase Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapPhaseManager, nullptr, "GetCurrentMapPhase", 	Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::MapPhaseManager_eventGetCurrentMapPhase_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::MapPhaseManager_eventGetCurrentMapPhase_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapPhaseManager::execGetCurrentMapPhase)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EMapPhase*)Z_Param__Result=P_THIS->GetCurrentMapPhase();
	P_NATIVE_END;
}
// ********** End Class AMapPhaseManager Function GetCurrentMapPhase *******************************

// ********** Begin Class AMapPhaseManager Function GetCurrentRoundState ***************************
struct Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics
{
	struct MapPhaseManager_eventGetCurrentRoundState_Parms
	{
		ERoundState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentRoundState constinit property declarations ******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentRoundState constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentRoundState Property Definitions *****************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MapPhaseManager_eventGetCurrentRoundState_Parms, ReturnValue), Z_Construct_UEnum_Claim_Of_Core_ERoundState, METADATA_PARAMS(0, nullptr) }; // 2171649069
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentRoundState Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapPhaseManager, nullptr, "GetCurrentRoundState", 	Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::MapPhaseManager_eventGetCurrentRoundState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::MapPhaseManager_eventGetCurrentRoundState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapPhaseManager::execGetCurrentRoundState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ERoundState*)Z_Param__Result=P_THIS->GetCurrentRoundState();
	P_NATIVE_END;
}
// ********** End Class AMapPhaseManager Function GetCurrentRoundState *****************************

// ********** Begin Class AMapPhaseManager Function GetInGameGameState *****************************
struct Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics
{
	struct MapPhaseManager_eventGetInGameGameState_Parms
	{
		AInGame_GameState* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetInGameGameState constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetInGameGameState constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetInGameGameState Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MapPhaseManager_eventGetInGameGameState_Parms, ReturnValue), Z_Construct_UClass_AInGame_GameState_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::PropPointers) < 2048);
// ********** End Function GetInGameGameState Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapPhaseManager, nullptr, "GetInGameGameState", 	Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::MapPhaseManager_eventGetInGameGameState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::MapPhaseManager_eventGetInGameGameState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapPhaseManager::execGetInGameGameState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(AInGame_GameState**)Z_Param__Result=P_THIS->GetInGameGameState();
	P_NATIVE_END;
}
// ********** End Class AMapPhaseManager Function GetInGameGameState *******************************

// ********** Begin Class AMapPhaseManager Function InitializeFromGameState ************************
struct Z_Construct_UFunction_AMapPhaseManager_InitializeFromGameState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function InitializeFromGameState constinit property declarations ***************
// ********** End Function InitializeFromGameState constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapPhaseManager_InitializeFromGameState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapPhaseManager, nullptr, "InitializeFromGameState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_InitializeFromGameState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapPhaseManager_InitializeFromGameState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMapPhaseManager_InitializeFromGameState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapPhaseManager_InitializeFromGameState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapPhaseManager::execInitializeFromGameState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeFromGameState();
	P_NATIVE_END;
}
// ********** End Class AMapPhaseManager Function InitializeFromGameState **************************

// ********** Begin Class AMapPhaseManager Function IsRoundPlaying *********************************
struct Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics
{
	struct MapPhaseManager_eventIsRoundPlaying_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsRoundPlaying constinit property declarations ************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsRoundPlaying constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsRoundPlaying Property Definitions ***********************************
void Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MapPhaseManager_eventIsRoundPlaying_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MapPhaseManager_eventIsRoundPlaying_Parms), &Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::PropPointers) < 2048);
// ********** End Function IsRoundPlaying Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapPhaseManager, nullptr, "IsRoundPlaying", 	Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::MapPhaseManager_eventIsRoundPlaying_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::MapPhaseManager_eventIsRoundPlaying_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapPhaseManager::execIsRoundPlaying)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsRoundPlaying();
	P_NATIVE_END;
}
// ********** End Class AMapPhaseManager Function IsRoundPlaying ***********************************

// ********** Begin Class AMapPhaseManager *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMapPhaseManager;
UClass* AMapPhaseManager::GetPrivateStaticClass()
{
	using TClass = AMapPhaseManager;
	if (!Z_Registration_Info_UClass_AMapPhaseManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MapPhaseManager"),
			Z_Registration_Info_UClass_AMapPhaseManager.InnerSingleton,
			StaticRegisterNativesAMapPhaseManager,
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
	return Z_Registration_Info_UClass_AMapPhaseManager.InnerSingleton;
}
UClass* Z_Construct_UClass_AMapPhaseManager_NoRegister()
{
	return AMapPhaseManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMapPhaseManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/MapPhaseManager.h" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedGameState_MetaData[] = {
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedPhase_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedRoundState_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnMapPhaseChanged_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnRoundStateChanged_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "Map/MapPhaseManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMapPhaseManager constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedGameState;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CachedPhase_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CachedPhase;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CachedRoundState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CachedRoundState;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnMapPhaseChanged;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnRoundStateChanged;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMapPhaseManager constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentMapPhase"), .Pointer = &AMapPhaseManager::execGetCurrentMapPhase },
		{ .NameUTF8 = UTF8TEXT("GetCurrentRoundState"), .Pointer = &AMapPhaseManager::execGetCurrentRoundState },
		{ .NameUTF8 = UTF8TEXT("GetInGameGameState"), .Pointer = &AMapPhaseManager::execGetInGameGameState },
		{ .NameUTF8 = UTF8TEXT("InitializeFromGameState"), .Pointer = &AMapPhaseManager::execInitializeFromGameState },
		{ .NameUTF8 = UTF8TEXT("IsRoundPlaying"), .Pointer = &AMapPhaseManager::execIsRoundPlaying },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMapPhaseManager_BP_OnMapPhaseChanged, "BP_OnMapPhaseChanged" }, // 2305225217
		{ &Z_Construct_UFunction_AMapPhaseManager_BP_OnRoundStateChanged, "BP_OnRoundStateChanged" }, // 1578249434
		{ &Z_Construct_UFunction_AMapPhaseManager_GetCurrentMapPhase, "GetCurrentMapPhase" }, // 1908344941
		{ &Z_Construct_UFunction_AMapPhaseManager_GetCurrentRoundState, "GetCurrentRoundState" }, // 2318083960
		{ &Z_Construct_UFunction_AMapPhaseManager_GetInGameGameState, "GetInGameGameState" }, // 3442285178
		{ &Z_Construct_UFunction_AMapPhaseManager_InitializeFromGameState, "InitializeFromGameState" }, // 612260515
		{ &Z_Construct_UFunction_AMapPhaseManager_IsRoundPlaying, "IsRoundPlaying" }, // 3647870539
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMapPhaseManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMapPhaseManager_Statics

// ********** Begin Class AMapPhaseManager Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedGameState = { "CachedGameState", nullptr, (EPropertyFlags)0x0124080000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapPhaseManager, CachedGameState), Z_Construct_UClass_AInGame_GameState_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedGameState_MetaData), NewProp_CachedGameState_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedPhase_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedPhase = { "CachedPhase", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapPhaseManager, CachedPhase), Z_Construct_UEnum_Claim_Of_Core_EMapPhase, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedPhase_MetaData), NewProp_CachedPhase_MetaData) }; // 2195778762
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedRoundState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedRoundState = { "CachedRoundState", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapPhaseManager, CachedRoundState), Z_Construct_UEnum_Claim_Of_Core_ERoundState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedRoundState_MetaData), NewProp_CachedRoundState_MetaData) }; // 2171649069
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_OnMapPhaseChanged = { "OnMapPhaseChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapPhaseManager, OnMapPhaseChanged), Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnMapPhaseChanged_MetaData), NewProp_OnMapPhaseChanged_MetaData) }; // 4146355094
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_OnRoundStateChanged = { "OnRoundStateChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapPhaseManager, OnRoundStateChanged), Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnRoundStateChanged_MetaData), NewProp_OnRoundStateChanged_MetaData) }; // 1662642504
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMapPhaseManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedGameState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedPhase_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedPhase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedRoundState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_CachedRoundState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_OnMapPhaseChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapPhaseManager_Statics::NewProp_OnRoundStateChanged,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMapPhaseManager_Statics::PropPointers) < 2048);
// ********** End Class AMapPhaseManager Property Definitions **************************************
UObject* (*const Z_Construct_UClass_AMapPhaseManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMapPhaseManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMapPhaseManager_Statics::ClassParams = {
	&AMapPhaseManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMapPhaseManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMapPhaseManager_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMapPhaseManager_Statics::Class_MetaDataParams), Z_Construct_UClass_AMapPhaseManager_Statics::Class_MetaDataParams)
};
void AMapPhaseManager::StaticRegisterNativesAMapPhaseManager()
{
	UClass* Class = AMapPhaseManager::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AMapPhaseManager_Statics::Funcs));
}
UClass* Z_Construct_UClass_AMapPhaseManager()
{
	if (!Z_Registration_Info_UClass_AMapPhaseManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMapPhaseManager.OuterSingleton, Z_Construct_UClass_AMapPhaseManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMapPhaseManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMapPhaseManager);
AMapPhaseManager::~AMapPhaseManager() {}
// ********** End Class AMapPhaseManager ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMapPhaseManager, AMapPhaseManager::StaticClass, TEXT("AMapPhaseManager"), &Z_Registration_Info_UClass_AMapPhaseManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMapPhaseManager), 556079920U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h__Script_Claim_Of_Core_2041157100{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
