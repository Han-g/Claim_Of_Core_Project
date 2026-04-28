// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameState/InGame_GameState.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInGame_GameState() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AInGame_GameState();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AInGame_GameState_NoRegister();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_EMapPhase();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_ERoundState();
ENGINE_API UClass* Z_Construct_UClass_AGameStateBase();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ERoundState ***************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ERoundState;
static UEnum* ERoundState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ERoundState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ERoundState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_ERoundState, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("ERoundState"));
	}
	return Z_Registration_Info_UEnum_ERoundState.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERoundState>()
{
	return ERoundState_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Finished.DisplayName", "Finished" },
		{ "Finished.Name", "ERoundState::Finished" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
		{ "Playing.DisplayName", "Playing" },
		{ "Playing.Name", "ERoundState::Playing" },
		{ "Waiting.DisplayName", "Waiting" },
		{ "Waiting.Name", "ERoundState::Waiting" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ERoundState::Waiting", (int64)ERoundState::Waiting },
		{ "ERoundState::Playing", (int64)ERoundState::Playing },
		{ "ERoundState::Finished", (int64)ERoundState::Finished },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"ERoundState",
	"ERoundState",
	Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_ERoundState()
{
	if (!Z_Registration_Info_UEnum_ERoundState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ERoundState.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_ERoundState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ERoundState.InnerSingleton;
}
// ********** End Enum ERoundState *****************************************************************

// ********** Begin Enum EMapPhase *****************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMapPhase;
static UEnum* EMapPhase_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EMapPhase.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EMapPhase.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_EMapPhase, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("EMapPhase"));
	}
	return Z_Registration_Info_UEnum_EMapPhase.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMapPhase>()
{
	return EMapPhase_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "End.DisplayName", "End" },
		{ "End.Name", "EMapPhase::End" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "EMapPhase::None" },
		{ "Phase1.DisplayName", "Phase 1" },
		{ "Phase1.Name", "EMapPhase::Phase1" },
		{ "Phase2.DisplayName", "Phase 2" },
		{ "Phase2.Name", "EMapPhase::Phase2" },
		{ "Phase3.DisplayName", "Phase 3" },
		{ "Phase3.Name", "EMapPhase::Phase3" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMapPhase::None", (int64)EMapPhase::None },
		{ "EMapPhase::Phase1", (int64)EMapPhase::Phase1 },
		{ "EMapPhase::Phase2", (int64)EMapPhase::Phase2 },
		{ "EMapPhase::Phase3", (int64)EMapPhase::Phase3 },
		{ "EMapPhase::End", (int64)EMapPhase::End },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"EMapPhase",
	"EMapPhase",
	Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_EMapPhase()
{
	if (!Z_Registration_Info_UEnum_EMapPhase.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMapPhase.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_EMapPhase_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EMapPhase.InnerSingleton;
}
// ********** End Enum EMapPhase *******************************************************************

// ********** Begin Class AInGame_GameState Function GetElapsedPlayTime ****************************
struct Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics
{
	struct InGame_GameState_eventGetElapsedPlayTime_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetElapsedPlayTime constinit property declarations ********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetElapsedPlayTime constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetElapsedPlayTime Property Definitions *******************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InGame_GameState_eventGetElapsedPlayTime_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::PropPointers) < 2048);
// ********** End Function GetElapsedPlayTime Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInGame_GameState, nullptr, "GetElapsedPlayTime", 	Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::InGame_GameState_eventGetElapsedPlayTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::InGame_GameState_eventGetElapsedPlayTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInGame_GameState::execGetElapsedPlayTime)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetElapsedPlayTime();
	P_NATIVE_END;
}
// ********** End Class AInGame_GameState Function GetElapsedPlayTime ******************************

// ********** Begin Class AInGame_GameState Function UpdatePhase ***********************************
struct Z_Construct_UFunction_AInGame_GameState_UpdatePhase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdatePhase constinit property declarations ***************************
// ********** End Function UpdatePhase constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AInGame_GameState_UpdatePhase_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AInGame_GameState, nullptr, "UpdatePhase", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AInGame_GameState_UpdatePhase_Statics::Function_MetaDataParams), Z_Construct_UFunction_AInGame_GameState_UpdatePhase_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AInGame_GameState_UpdatePhase()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AInGame_GameState_UpdatePhase_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AInGame_GameState::execUpdatePhase)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdatePhase();
	P_NATIVE_END;
}
// ********** End Class AInGame_GameState Function UpdatePhase *************************************

// ********** Begin Class AInGame_GameState ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AInGame_GameState;
UClass* AInGame_GameState::GetPrivateStaticClass()
{
	using TClass = AInGame_GameState;
	if (!Z_Registration_Info_UClass_AInGame_GameState.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("InGame_GameState"),
			Z_Registration_Info_UClass_AInGame_GameState.InnerSingleton,
			StaticRegisterNativesAInGame_GameState,
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
	return Z_Registration_Info_UClass_AInGame_GameState.InnerSingleton;
}
UClass* Z_Construct_UClass_AInGame_GameState_NoRegister()
{
	return AInGame_GameState::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInGame_GameState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "GameState/InGame_GameState.h" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoundState_MetaData[] = {
		{ "Category", "Round" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReadyTime_MetaData[] = {
		{ "Category", "Round" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GameTime_MetaData[] = {
		{ "Category", "Round" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentPhase_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase1Time_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase2Time_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase3Time_MetaData[] = {
		{ "Category", "Phase" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentReadyTime_MetaData[] = {
		{ "Category", "Round" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentGameTime_MetaData[] = {
		{ "Category", "Round" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bGameplayActivated_MetaData[] = {
		{ "Category", "Round" },
		{ "ModuleRelativePath", "GameState/InGame_GameState.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AInGame_GameState constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_RoundState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_RoundState;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReadyTime;
	static const UECodeGen_Private::FIntPropertyParams NewProp_GameTime;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentPhase_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentPhase;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase1Time;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase2Time;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Phase3Time;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentReadyTime;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentGameTime;
	static void NewProp_bGameplayActivated_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bGameplayActivated;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AInGame_GameState constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetElapsedPlayTime"), .Pointer = &AInGame_GameState::execGetElapsedPlayTime },
		{ .NameUTF8 = UTF8TEXT("UpdatePhase"), .Pointer = &AInGame_GameState::execUpdatePhase },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AInGame_GameState_GetElapsedPlayTime, "GetElapsedPlayTime" }, // 1533245498
		{ &Z_Construct_UFunction_AInGame_GameState_UpdatePhase, "UpdatePhase" }, // 150920670
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInGame_GameState>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AInGame_GameState_Statics

// ********** Begin Class AInGame_GameState Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_RoundState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_RoundState = { "RoundState", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, RoundState), Z_Construct_UEnum_Claim_Of_Core_ERoundState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoundState_MetaData), NewProp_RoundState_MetaData) }; // 2171649069
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_ReadyTime = { "ReadyTime", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, ReadyTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReadyTime_MetaData), NewProp_ReadyTime_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_GameTime = { "GameTime", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, GameTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GameTime_MetaData), NewProp_GameTime_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentPhase_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentPhase = { "CurrentPhase", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, CurrentPhase), Z_Construct_UEnum_Claim_Of_Core_EMapPhase, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentPhase_MetaData), NewProp_CurrentPhase_MetaData) }; // 2195778762
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_Phase1Time = { "Phase1Time", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, Phase1Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase1Time_MetaData), NewProp_Phase1Time_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_Phase2Time = { "Phase2Time", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, Phase2Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase2Time_MetaData), NewProp_Phase2Time_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_Phase3Time = { "Phase3Time", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, Phase3Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase3Time_MetaData), NewProp_Phase3Time_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentReadyTime = { "CurrentReadyTime", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, CurrentReadyTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentReadyTime_MetaData), NewProp_CurrentReadyTime_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentGameTime = { "CurrentGameTime", nullptr, (EPropertyFlags)0x0010000000000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInGame_GameState, CurrentGameTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentGameTime_MetaData), NewProp_CurrentGameTime_MetaData) };
void Z_Construct_UClass_AInGame_GameState_Statics::NewProp_bGameplayActivated_SetBit(void* Obj)
{
	((AInGame_GameState*)Obj)->bGameplayActivated = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AInGame_GameState_Statics::NewProp_bGameplayActivated = { "bGameplayActivated", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AInGame_GameState), &Z_Construct_UClass_AInGame_GameState_Statics::NewProp_bGameplayActivated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bGameplayActivated_MetaData), NewProp_bGameplayActivated_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AInGame_GameState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_RoundState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_RoundState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_ReadyTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_GameTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentPhase_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentPhase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_Phase1Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_Phase2Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_Phase3Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentReadyTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_CurrentGameTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInGame_GameState_Statics::NewProp_bGameplayActivated,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInGame_GameState_Statics::PropPointers) < 2048);
// ********** End Class AInGame_GameState Property Definitions *************************************
UObject* (*const Z_Construct_UClass_AInGame_GameState_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameStateBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInGame_GameState_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInGame_GameState_Statics::ClassParams = {
	&AInGame_GameState::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AInGame_GameState_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AInGame_GameState_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInGame_GameState_Statics::Class_MetaDataParams), Z_Construct_UClass_AInGame_GameState_Statics::Class_MetaDataParams)
};
void AInGame_GameState::StaticRegisterNativesAInGame_GameState()
{
	UClass* Class = AInGame_GameState::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AInGame_GameState_Statics::Funcs));
}
UClass* Z_Construct_UClass_AInGame_GameState()
{
	if (!Z_Registration_Info_UClass_AInGame_GameState.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInGame_GameState.OuterSingleton, Z_Construct_UClass_AInGame_GameState_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInGame_GameState.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void AInGame_GameState::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_RoundState(TEXT("RoundState"));
	static FName Name_ReadyTime(TEXT("ReadyTime"));
	static FName Name_GameTime(TEXT("GameTime"));
	static FName Name_CurrentPhase(TEXT("CurrentPhase"));
	static FName Name_Phase1Time(TEXT("Phase1Time"));
	static FName Name_Phase2Time(TEXT("Phase2Time"));
	static FName Name_Phase3Time(TEXT("Phase3Time"));
	static FName Name_CurrentReadyTime(TEXT("CurrentReadyTime"));
	static FName Name_CurrentGameTime(TEXT("CurrentGameTime"));
	const bool bIsValid = true
		&& Name_RoundState == ClassReps[(int32)ENetFields_Private::RoundState].Property->GetFName()
		&& Name_ReadyTime == ClassReps[(int32)ENetFields_Private::ReadyTime].Property->GetFName()
		&& Name_GameTime == ClassReps[(int32)ENetFields_Private::GameTime].Property->GetFName()
		&& Name_CurrentPhase == ClassReps[(int32)ENetFields_Private::CurrentPhase].Property->GetFName()
		&& Name_Phase1Time == ClassReps[(int32)ENetFields_Private::Phase1Time].Property->GetFName()
		&& Name_Phase2Time == ClassReps[(int32)ENetFields_Private::Phase2Time].Property->GetFName()
		&& Name_Phase3Time == ClassReps[(int32)ENetFields_Private::Phase3Time].Property->GetFName()
		&& Name_CurrentReadyTime == ClassReps[(int32)ENetFields_Private::CurrentReadyTime].Property->GetFName()
		&& Name_CurrentGameTime == ClassReps[(int32)ENetFields_Private::CurrentGameTime].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AInGame_GameState"));
}
#endif
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AInGame_GameState);
AInGame_GameState::~AInGame_GameState() {}
// ********** End Class AInGame_GameState **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h__Script_Claim_Of_Core_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ERoundState_StaticEnum, TEXT("ERoundState"), &Z_Registration_Info_UEnum_ERoundState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2171649069U) },
		{ EMapPhase_StaticEnum, TEXT("EMapPhase"), &Z_Registration_Info_UEnum_EMapPhase, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2195778762U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInGame_GameState, AInGame_GameState::StaticClass, TEXT("AInGame_GameState"), &Z_Registration_Info_UClass_AInGame_GameState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInGame_GameState), 3337770875U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h__Script_Claim_Of_Core_3676646896{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h__Script_Claim_Of_Core_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h__Script_Claim_Of_Core_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
