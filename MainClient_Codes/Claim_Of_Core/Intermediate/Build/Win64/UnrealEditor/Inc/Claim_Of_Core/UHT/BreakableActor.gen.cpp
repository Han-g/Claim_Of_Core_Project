// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/BreakableActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBreakableActor() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ABreakableActor();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ABreakableActor_NoRegister();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EBreakableActorState ******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBreakableActorState;
static UEnum* EBreakableActorState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBreakableActorState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBreakableActorState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("EBreakableActorState"));
	}
	return Z_Registration_Info_UEnum_EBreakableActorState.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EBreakableActorState>()
{
	return EBreakableActorState_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Active.Name", "EBreakableActorState::Active" },
		{ "BlueprintType", "true" },
		{ "Breaking.Name", "EBreakableActorState::Breaking" },
		{ "Broken.Name", "EBreakableActorState::Broken" },
		{ "Idle.Name", "EBreakableActorState::Idle" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBreakableActorState::Idle", (int64)EBreakableActorState::Idle },
		{ "EBreakableActorState::Active", (int64)EBreakableActorState::Active },
		{ "EBreakableActorState::Breaking", (int64)EBreakableActorState::Breaking },
		{ "EBreakableActorState::Broken", (int64)EBreakableActorState::Broken },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"EBreakableActorState",
	"EBreakableActorState",
	Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState()
{
	if (!Z_Registration_Info_UEnum_EBreakableActorState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBreakableActorState.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBreakableActorState.InnerSingleton;
}
// ********** End Enum EBreakableActorState ********************************************************

// ********** Begin Class ABreakableActor Function ActivateBreakable *******************************
struct Z_Construct_UFunction_ABreakableActor_ActivateBreakable_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ActivateBreakable constinit property declarations *********************
// ********** End Function ActivateBreakable constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_ActivateBreakable_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "ActivateBreakable", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_ActivateBreakable_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_ActivateBreakable_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ABreakableActor_ActivateBreakable()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_ActivateBreakable_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABreakableActor::execActivateBreakable)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ActivateBreakable();
	P_NATIVE_END;
}
// ********** End Class ABreakableActor Function ActivateBreakable *********************************

// ********** Begin Class ABreakableActor Function ApplyBreakableDamage ****************************
struct Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics
{
	struct BreakableActor_eventApplyBreakableDamage_Parms
	{
		float DamageAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyBreakableDamage constinit property declarations ******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyBreakableDamage constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyBreakableDamage Property Definitions *****************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BreakableActor_eventApplyBreakableDamage_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::PropPointers) < 2048);
// ********** End Function ApplyBreakableDamage Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "ApplyBreakableDamage", 	Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::BreakableActor_eventApplyBreakableDamage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::BreakableActor_eventApplyBreakableDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABreakableActor::execApplyBreakableDamage)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyBreakableDamage(Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class ABreakableActor Function ApplyBreakableDamage ******************************

// ********** Begin Class ABreakableActor Function BP_OnActivated **********************************
static FName NAME_ABreakableActor_BP_OnActivated = FName(TEXT("BP_OnActivated"));
void ABreakableActor::BP_OnActivated()
{
	UFunction* Func = FindFunctionChecked(NAME_ABreakableActor_BP_OnActivated);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ABreakableActor_BP_OnActivated_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnActivated constinit property declarations ************************
// ********** End Function BP_OnActivated constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_BP_OnActivated_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "BP_OnActivated", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_BP_OnActivated_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_BP_OnActivated_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ABreakableActor_BP_OnActivated()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_BP_OnActivated_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ABreakableActor Function BP_OnActivated ************************************

// ********** Begin Class ABreakableActor Function BP_OnBroken *************************************
static FName NAME_ABreakableActor_BP_OnBroken = FName(TEXT("BP_OnBroken"));
void ABreakableActor::BP_OnBroken()
{
	UFunction* Func = FindFunctionChecked(NAME_ABreakableActor_BP_OnBroken);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ABreakableActor_BP_OnBroken_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnBroken constinit property declarations ***************************
// ********** End Function BP_OnBroken constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_BP_OnBroken_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "BP_OnBroken", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_BP_OnBroken_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_BP_OnBroken_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ABreakableActor_BP_OnBroken()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_BP_OnBroken_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ABreakableActor Function BP_OnBroken ***************************************

// ********** Begin Class ABreakableActor Function BreakActor **************************************
struct Z_Construct_UFunction_ABreakableActor_BreakActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BreakActor constinit property declarations ****************************
// ********** End Function BreakActor constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_BreakActor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "BreakActor", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_BreakActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_BreakActor_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ABreakableActor_BreakActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_BreakActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABreakableActor::execBreakActor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BreakActor();
	P_NATIVE_END;
}
// ********** End Class ABreakableActor Function BreakActor ****************************************

// ********** Begin Class ABreakableActor Function IsActivated *************************************
struct Z_Construct_UFunction_ABreakableActor_IsActivated_Statics
{
	struct BreakableActor_eventIsActivated_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsActivated constinit property declarations ***************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsActivated constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsActivated Property Definitions **************************************
void Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BreakableActor_eventIsActivated_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BreakableActor_eventIsActivated_Parms), &Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::PropPointers) < 2048);
// ********** End Function IsActivated Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "IsActivated", 	Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::BreakableActor_eventIsActivated_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::BreakableActor_eventIsActivated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ABreakableActor_IsActivated()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_IsActivated_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABreakableActor::execIsActivated)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsActivated();
	P_NATIVE_END;
}
// ********** End Class ABreakableActor Function IsActivated ***************************************

// ********** Begin Class ABreakableActor Function IsBroken ****************************************
struct Z_Construct_UFunction_ABreakableActor_IsBroken_Statics
{
	struct BreakableActor_eventIsBroken_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
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
void Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((BreakableActor_eventIsBroken_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BreakableActor_eventIsBroken_Parms), &Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::PropPointers) < 2048);
// ********** End Function IsBroken Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "IsBroken", 	Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::BreakableActor_eventIsBroken_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::BreakableActor_eventIsBroken_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ABreakableActor_IsBroken()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_IsBroken_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABreakableActor::execIsBroken)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsBroken();
	P_NATIVE_END;
}
// ********** End Class ABreakableActor Function IsBroken ******************************************

// ********** Begin Class ABreakableActor Function ResetBreakable **********************************
struct Z_Construct_UFunction_ABreakableActor_ResetBreakable_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ResetBreakable constinit property declarations ************************
// ********** End Function ResetBreakable constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABreakableActor_ResetBreakable_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABreakableActor, nullptr, "ResetBreakable", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABreakableActor_ResetBreakable_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABreakableActor_ResetBreakable_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ABreakableActor_ResetBreakable()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABreakableActor_ResetBreakable_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABreakableActor::execResetBreakable)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetBreakable();
	P_NATIVE_END;
}
// ********** End Class ABreakableActor Function ResetBreakable ************************************

// ********** Begin Class ABreakableActor **********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ABreakableActor;
UClass* ABreakableActor::GetPrivateStaticClass()
{
	using TClass = ABreakableActor;
	if (!Z_Registration_Info_UClass_ABreakableActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BreakableActor"),
			Z_Registration_Info_UClass_ABreakableActor.InnerSingleton,
			StaticRegisterNativesABreakableActor,
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
	return Z_Registration_Info_UClass_ABreakableActor.InnerSingleton;
}
UClass* Z_Construct_UClass_ABreakableActor_NoRegister()
{
	return ABreakableActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ABreakableActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/BreakableActor.h" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "Breakable" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BreakableState_MetaData[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bActivated_MetaData[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBroken_MetaData[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDurability_MetaData[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentDurability_MetaData[] = {
		{ "Category", "Breakable" },
		{ "ModuleRelativePath", "Map/BreakableActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ABreakableActor constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FBytePropertyParams NewProp_BreakableState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_BreakableState;
	static void NewProp_bActivated_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActivated;
	static void NewProp_bBroken_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBroken;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxDurability;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentDurability;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ABreakableActor constinit property declarations ****************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ActivateBreakable"), .Pointer = &ABreakableActor::execActivateBreakable },
		{ .NameUTF8 = UTF8TEXT("ApplyBreakableDamage"), .Pointer = &ABreakableActor::execApplyBreakableDamage },
		{ .NameUTF8 = UTF8TEXT("BreakActor"), .Pointer = &ABreakableActor::execBreakActor },
		{ .NameUTF8 = UTF8TEXT("IsActivated"), .Pointer = &ABreakableActor::execIsActivated },
		{ .NameUTF8 = UTF8TEXT("IsBroken"), .Pointer = &ABreakableActor::execIsBroken },
		{ .NameUTF8 = UTF8TEXT("ResetBreakable"), .Pointer = &ABreakableActor::execResetBreakable },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ABreakableActor_ActivateBreakable, "ActivateBreakable" }, // 3241175096
		{ &Z_Construct_UFunction_ABreakableActor_ApplyBreakableDamage, "ApplyBreakableDamage" }, // 588591786
		{ &Z_Construct_UFunction_ABreakableActor_BP_OnActivated, "BP_OnActivated" }, // 1091599625
		{ &Z_Construct_UFunction_ABreakableActor_BP_OnBroken, "BP_OnBroken" }, // 476996480
		{ &Z_Construct_UFunction_ABreakableActor_BreakActor, "BreakActor" }, // 3201595023
		{ &Z_Construct_UFunction_ABreakableActor_IsActivated, "IsActivated" }, // 3858238200
		{ &Z_Construct_UFunction_ABreakableActor_IsBroken, "IsBroken" }, // 3761361663
		{ &Z_Construct_UFunction_ABreakableActor_ResetBreakable, "ResetBreakable" }, // 1237745608
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABreakableActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ABreakableActor_Statics

// ********** Begin Class ABreakableActor Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABreakableActor_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABreakableActor, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ABreakableActor_Statics::NewProp_BreakableState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ABreakableActor_Statics::NewProp_BreakableState = { "BreakableState", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABreakableActor, BreakableState), Z_Construct_UEnum_Claim_Of_Core_EBreakableActorState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BreakableState_MetaData), NewProp_BreakableState_MetaData) }; // 3267201018
void Z_Construct_UClass_ABreakableActor_Statics::NewProp_bActivated_SetBit(void* Obj)
{
	((ABreakableActor*)Obj)->bActivated = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABreakableActor_Statics::NewProp_bActivated = { "bActivated", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABreakableActor), &Z_Construct_UClass_ABreakableActor_Statics::NewProp_bActivated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bActivated_MetaData), NewProp_bActivated_MetaData) };
void Z_Construct_UClass_ABreakableActor_Statics::NewProp_bBroken_SetBit(void* Obj)
{
	((ABreakableActor*)Obj)->bBroken = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABreakableActor_Statics::NewProp_bBroken = { "bBroken", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABreakableActor), &Z_Construct_UClass_ABreakableActor_Statics::NewProp_bBroken_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBroken_MetaData), NewProp_bBroken_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABreakableActor_Statics::NewProp_MaxDurability = { "MaxDurability", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABreakableActor, MaxDurability), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDurability_MetaData), NewProp_MaxDurability_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABreakableActor_Statics::NewProp_CurrentDurability = { "CurrentDurability", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABreakableActor, CurrentDurability), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentDurability_MetaData), NewProp_CurrentDurability_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABreakableActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABreakableActor_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABreakableActor_Statics::NewProp_BreakableState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABreakableActor_Statics::NewProp_BreakableState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABreakableActor_Statics::NewProp_bActivated,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABreakableActor_Statics::NewProp_bBroken,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABreakableActor_Statics::NewProp_MaxDurability,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABreakableActor_Statics::NewProp_CurrentDurability,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABreakableActor_Statics::PropPointers) < 2048);
// ********** End Class ABreakableActor Property Definitions ***************************************
UObject* (*const Z_Construct_UClass_ABreakableActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABreakableActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ABreakableActor_Statics::ClassParams = {
	&ABreakableActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ABreakableActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ABreakableActor_Statics::PropPointers),
	0,
	0x009000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABreakableActor_Statics::Class_MetaDataParams), Z_Construct_UClass_ABreakableActor_Statics::Class_MetaDataParams)
};
void ABreakableActor::StaticRegisterNativesABreakableActor()
{
	UClass* Class = ABreakableActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ABreakableActor_Statics::Funcs));
}
UClass* Z_Construct_UClass_ABreakableActor()
{
	if (!Z_Registration_Info_UClass_ABreakableActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABreakableActor.OuterSingleton, Z_Construct_UClass_ABreakableActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ABreakableActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ABreakableActor);
ABreakableActor::~ABreakableActor() {}
// ********** End Class ABreakableActor ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h__Script_Claim_Of_Core_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBreakableActorState_StaticEnum, TEXT("EBreakableActorState"), &Z_Registration_Info_UEnum_EBreakableActorState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3267201018U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ABreakableActor, ABreakableActor::StaticClass, TEXT("ABreakableActor"), &Z_Registration_Info_UClass_ABreakableActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABreakableActor), 1115036268U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h__Script_Claim_Of_Core_2302973990{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h__Script_Claim_Of_Core_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h__Script_Claim_Of_Core_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
