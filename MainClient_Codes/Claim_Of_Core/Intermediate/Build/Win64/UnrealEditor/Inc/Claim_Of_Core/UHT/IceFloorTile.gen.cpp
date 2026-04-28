// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/IceCave/IceFloorTile.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeIceFloorTile() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIceFloorTile();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIceFloorTile_NoRegister();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_EIceFloorState();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EIceFloorState ************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EIceFloorState;
static UEnum* EIceFloorState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EIceFloorState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EIceFloorState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_EIceFloorState, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("EIceFloorState"));
	}
	return Z_Registration_Info_UEnum_EIceFloorState.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EIceFloorState>()
{
	return EIceFloorState_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Breaking.Name", "EIceFloorState::Breaking" },
		{ "Broken.Name", "EIceFloorState::Broken" },
		{ "Cracked.Name", "EIceFloorState::Cracked" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
		{ "Normal.Name", "EIceFloorState::Normal" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EIceFloorState::Normal", (int64)EIceFloorState::Normal },
		{ "EIceFloorState::Cracked", (int64)EIceFloorState::Cracked },
		{ "EIceFloorState::Breaking", (int64)EIceFloorState::Breaking },
		{ "EIceFloorState::Broken", (int64)EIceFloorState::Broken },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"EIceFloorState",
	"EIceFloorState",
	Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_EIceFloorState()
{
	if (!Z_Registration_Info_UEnum_EIceFloorState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EIceFloorState.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_EIceFloorState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EIceFloorState.InnerSingleton;
}
// ********** End Enum EIceFloorState **************************************************************

// ********** Begin Class AIceFloorTile Function BP_OnBreaking *************************************
static FName NAME_AIceFloorTile_BP_OnBreaking = FName(TEXT("BP_OnBreaking"));
void AIceFloorTile::BP_OnBreaking()
{
	UFunction* Func = FindFunctionChecked(NAME_AIceFloorTile_BP_OnBreaking);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AIceFloorTile_BP_OnBreaking_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnBreaking constinit property declarations *************************
// ********** End Function BP_OnBreaking constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceFloorTile_BP_OnBreaking_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceFloorTile, nullptr, "BP_OnBreaking", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_BP_OnBreaking_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceFloorTile_BP_OnBreaking_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIceFloorTile_BP_OnBreaking()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceFloorTile_BP_OnBreaking_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AIceFloorTile Function BP_OnBreaking ***************************************

// ********** Begin Class AIceFloorTile Function BP_OnBroken ***************************************
static FName NAME_AIceFloorTile_BP_OnBroken = FName(TEXT("BP_OnBroken"));
void AIceFloorTile::BP_OnBroken()
{
	UFunction* Func = FindFunctionChecked(NAME_AIceFloorTile_BP_OnBroken);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AIceFloorTile_BP_OnBroken_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnBroken constinit property declarations ***************************
// ********** End Function BP_OnBroken constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceFloorTile_BP_OnBroken_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceFloorTile, nullptr, "BP_OnBroken", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_BP_OnBroken_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceFloorTile_BP_OnBroken_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIceFloorTile_BP_OnBroken()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceFloorTile_BP_OnBroken_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AIceFloorTile Function BP_OnBroken *****************************************

// ********** Begin Class AIceFloorTile Function BP_OnCracked **************************************
static FName NAME_AIceFloorTile_BP_OnCracked = FName(TEXT("BP_OnCracked"));
void AIceFloorTile::BP_OnCracked()
{
	UFunction* Func = FindFunctionChecked(NAME_AIceFloorTile_BP_OnCracked);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AIceFloorTile_BP_OnCracked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnCracked constinit property declarations **************************
// ********** End Function BP_OnCracked constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceFloorTile_BP_OnCracked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceFloorTile, nullptr, "BP_OnCracked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_BP_OnCracked_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceFloorTile_BP_OnCracked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIceFloorTile_BP_OnCracked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceFloorTile_BP_OnCracked_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AIceFloorTile Function BP_OnCracked ****************************************

// ********** Begin Class AIceFloorTile Function BreakFloor ****************************************
struct Z_Construct_UFunction_AIceFloorTile_BreakFloor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BreakFloor constinit property declarations ****************************
// ********** End Function BreakFloor constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceFloorTile_BreakFloor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceFloorTile, nullptr, "BreakFloor", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_BreakFloor_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceFloorTile_BreakFloor_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIceFloorTile_BreakFloor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceFloorTile_BreakFloor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIceFloorTile::execBreakFloor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BreakFloor();
	P_NATIVE_END;
}
// ********** End Class AIceFloorTile Function BreakFloor ******************************************

// ********** Begin Class AIceFloorTile Function IsBroken ******************************************
struct Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics
{
	struct IceFloorTile_eventIsBroken_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsBroken constinit property declarations ******************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsBroken constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsBroken Property Definitions *****************************************
void Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((IceFloorTile_eventIsBroken_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(IceFloorTile_eventIsBroken_Parms), &Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::PropPointers) < 2048);
// ********** End Function IsBroken Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceFloorTile, nullptr, "IsBroken", 	Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::IceFloorTile_eventIsBroken_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::IceFloorTile_eventIsBroken_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AIceFloorTile_IsBroken()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceFloorTile_IsBroken_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIceFloorTile::execIsBroken)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsBroken();
	P_NATIVE_END;
}
// ********** End Class AIceFloorTile Function IsBroken ********************************************

// ********** Begin Class AIceFloorTile Function SetCracked ****************************************
struct Z_Construct_UFunction_AIceFloorTile_SetCracked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetCracked constinit property declarations ****************************
// ********** End Function SetCracked constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceFloorTile_SetCracked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceFloorTile, nullptr, "SetCracked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_SetCracked_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceFloorTile_SetCracked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIceFloorTile_SetCracked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceFloorTile_SetCracked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIceFloorTile::execSetCracked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetCracked();
	P_NATIVE_END;
}
// ********** End Class AIceFloorTile Function SetCracked ******************************************

// ********** Begin Class AIceFloorTile Function StartBreaking *************************************
struct Z_Construct_UFunction_AIceFloorTile_StartBreaking_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartBreaking constinit property declarations *************************
// ********** End Function StartBreaking constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIceFloorTile_StartBreaking_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIceFloorTile, nullptr, "StartBreaking", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIceFloorTile_StartBreaking_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIceFloorTile_StartBreaking_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIceFloorTile_StartBreaking()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIceFloorTile_StartBreaking_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIceFloorTile::execStartBreaking)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartBreaking();
	P_NATIVE_END;
}
// ********** End Class AIceFloorTile Function StartBreaking ***************************************

// ********** Begin Class AIceFloorTile ************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AIceFloorTile;
UClass* AIceFloorTile::GetPrivateStaticClass()
{
	using TClass = AIceFloorTile;
	if (!Z_Registration_Info_UClass_AIceFloorTile.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("IceFloorTile"),
			Z_Registration_Info_UClass_AIceFloorTile.InnerSingleton,
			StaticRegisterNativesAIceFloorTile,
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
	return Z_Registration_Info_UClass_AIceFloorTile.InnerSingleton;
}
UClass* Z_Construct_UClass_AIceFloorTile_NoRegister()
{
	return AIceFloorTile::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AIceFloorTile_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/IceCave/IceFloorTile.h" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "IceFloorTile" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FloorMesh_MetaData[] = {
		{ "Category", "IceFloorTile" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TriggerBox_MetaData[] = {
		{ "Category", "IceFloorTile" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "Category", "Floor" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BreakDelay_MetaData[] = {
		{ "Category", "Floor" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFallWhenBroken_MetaData[] = {
		{ "Category", "Floor" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FallenLifeSpan_MetaData[] = {
		{ "Category", "Floor" },
		{ "ModuleRelativePath", "Map/IceCave/IceFloorTile.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AIceFloorTile constinit property declarations ****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FloorMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TriggerBox;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BreakDelay;
	static void NewProp_bFallWhenBroken_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFallWhenBroken;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FallenLifeSpan;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AIceFloorTile constinit property declarations ******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("BreakFloor"), .Pointer = &AIceFloorTile::execBreakFloor },
		{ .NameUTF8 = UTF8TEXT("IsBroken"), .Pointer = &AIceFloorTile::execIsBroken },
		{ .NameUTF8 = UTF8TEXT("SetCracked"), .Pointer = &AIceFloorTile::execSetCracked },
		{ .NameUTF8 = UTF8TEXT("StartBreaking"), .Pointer = &AIceFloorTile::execStartBreaking },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AIceFloorTile_BP_OnBreaking, "BP_OnBreaking" }, // 1038445095
		{ &Z_Construct_UFunction_AIceFloorTile_BP_OnBroken, "BP_OnBroken" }, // 1620123375
		{ &Z_Construct_UFunction_AIceFloorTile_BP_OnCracked, "BP_OnCracked" }, // 2032374473
		{ &Z_Construct_UFunction_AIceFloorTile_BreakFloor, "BreakFloor" }, // 2569283810
		{ &Z_Construct_UFunction_AIceFloorTile_IsBroken, "IsBroken" }, // 2399587184
		{ &Z_Construct_UFunction_AIceFloorTile_SetCracked, "SetCracked" }, // 1399206069
		{ &Z_Construct_UFunction_AIceFloorTile_StartBreaking, "StartBreaking" }, // 3625793295
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AIceFloorTile>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AIceFloorTile_Statics

// ********** Begin Class AIceFloorTile Property Definitions ***************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceFloorTile, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_FloorMesh = { "FloorMesh", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceFloorTile, FloorMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FloorMesh_MetaData), NewProp_FloorMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_TriggerBox = { "TriggerBox", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceFloorTile, TriggerBox), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TriggerBox_MetaData), NewProp_TriggerBox_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_CurrentState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceFloorTile, CurrentState), Z_Construct_UEnum_Claim_Of_Core_EIceFloorState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 1523045879
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_BreakDelay = { "BreakDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceFloorTile, BreakDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BreakDelay_MetaData), NewProp_BreakDelay_MetaData) };
void Z_Construct_UClass_AIceFloorTile_Statics::NewProp_bFallWhenBroken_SetBit(void* Obj)
{
	((AIceFloorTile*)Obj)->bFallWhenBroken = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_bFallWhenBroken = { "bFallWhenBroken", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AIceFloorTile), &Z_Construct_UClass_AIceFloorTile_Statics::NewProp_bFallWhenBroken_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFallWhenBroken_MetaData), NewProp_bFallWhenBroken_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIceFloorTile_Statics::NewProp_FallenLifeSpan = { "FallenLifeSpan", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIceFloorTile, FallenLifeSpan), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FallenLifeSpan_MetaData), NewProp_FallenLifeSpan_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AIceFloorTile_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_FloorMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_TriggerBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_CurrentState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_CurrentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_BreakDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_bFallWhenBroken,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIceFloorTile_Statics::NewProp_FallenLifeSpan,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIceFloorTile_Statics::PropPointers) < 2048);
// ********** End Class AIceFloorTile Property Definitions *****************************************
UObject* (*const Z_Construct_UClass_AIceFloorTile_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIceFloorTile_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AIceFloorTile_Statics::ClassParams = {
	&AIceFloorTile::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AIceFloorTile_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AIceFloorTile_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AIceFloorTile_Statics::Class_MetaDataParams), Z_Construct_UClass_AIceFloorTile_Statics::Class_MetaDataParams)
};
void AIceFloorTile::StaticRegisterNativesAIceFloorTile()
{
	UClass* Class = AIceFloorTile::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AIceFloorTile_Statics::Funcs));
}
UClass* Z_Construct_UClass_AIceFloorTile()
{
	if (!Z_Registration_Info_UClass_AIceFloorTile.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AIceFloorTile.OuterSingleton, Z_Construct_UClass_AIceFloorTile_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AIceFloorTile.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AIceFloorTile);
AIceFloorTile::~AIceFloorTile() {}
// ********** End Class AIceFloorTile **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h__Script_Claim_Of_Core_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EIceFloorState_StaticEnum, TEXT("EIceFloorState"), &Z_Registration_Info_UEnum_EIceFloorState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1523045879U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AIceFloorTile, AIceFloorTile::StaticClass, TEXT("AIceFloorTile"), &Z_Registration_Info_UClass_AIceFloorTile, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AIceFloorTile), 2460186027U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h__Script_Claim_Of_Core_147583858{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h__Script_Claim_Of_Core_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h__Script_Claim_Of_Core_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
