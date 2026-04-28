// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Sub/HPComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeHPComponent() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UHPComponent();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UHPComponent_NoRegister();
CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature();
CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnHPChangedSignature *************************************************
struct Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics
{
	struct _Script_Claim_Of_Core_eventOnHPChangedSignature_Parms
	{
		int32 NewHP;
		int32 OldHP;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnHPChangedSignature constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_NewHP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OldHP;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnHPChangedSignature constinit property declarations *******************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnHPChangedSignature Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::NewProp_NewHP = { "NewHP", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_Claim_Of_Core_eventOnHPChangedSignature_Parms, NewHP), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::NewProp_OldHP = { "OldHP", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_Claim_Of_Core_eventOnHPChangedSignature_Parms, OldHP), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::NewProp_NewHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::NewProp_OldHP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnHPChangedSignature Property Definitions ******************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core, nullptr, "OnHPChangedSignature__DelegateSignature", 	Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnHPChangedSignature_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnHPChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnHPChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnHPChangedSignature, int32 NewHP, int32 OldHP)
{
	struct _Script_Claim_Of_Core_eventOnHPChangedSignature_Parms
	{
		int32 NewHP;
		int32 OldHP;
	};
	_Script_Claim_Of_Core_eventOnHPChangedSignature_Parms Parms;
	Parms.NewHP=NewHP;
	Parms.OldHP=OldHP;
	OnHPChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnHPChangedSignature ***************************************************

// ********** Begin Delegate FOnHPZeroSignature ****************************************************
struct Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnHPZeroSignature constinit property declarations ********************
// ********** End Delegate FOnHPZeroSignature constinit property declarations **********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core, nullptr, "OnHPZeroSignature__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnHPZeroSignature_DelegateWrapper(const FMulticastScriptDelegate& OnHPZeroSignature)
{
	OnHPZeroSignature.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnHPZeroSignature ******************************************************

// ********** Begin Class UHPComponent Function ApplyDamage ****************************************
struct Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics
{
	struct HPComponent_eventApplyDamage_Parms
	{
		int32 DamageAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyDamage constinit property declarations ***************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyDamage constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyDamage Property Definitions **************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventApplyDamage_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::PropPointers) < 2048);
// ********** End Function ApplyDamage Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "ApplyDamage", 	Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::HPComponent_eventApplyDamage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::HPComponent_eventApplyDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_ApplyDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_ApplyDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execApplyDamage)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyDamage(Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function ApplyDamage ******************************************

// ********** Begin Class UHPComponent Function GetCurrentHP ***************************************
struct Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics
{
	struct HPComponent_eventGetCurrentHP_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentHP constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentHP constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentHP Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventGetCurrentHP_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentHP Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "GetCurrentHP", 	Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::HPComponent_eventGetCurrentHP_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::HPComponent_eventGetCurrentHP_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_GetCurrentHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_GetCurrentHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execGetCurrentHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCurrentHP();
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function GetCurrentHP *****************************************

// ********** Begin Class UHPComponent Function GetHPPercent ***************************************
struct Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics
{
	struct HPComponent_eventGetHPPercent_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetHPPercent constinit property declarations **************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetHPPercent constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetHPPercent Property Definitions *************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventGetHPPercent_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::PropPointers) < 2048);
// ********** End Function GetHPPercent Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "GetHPPercent", 	Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::HPComponent_eventGetHPPercent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::HPComponent_eventGetHPPercent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_GetHPPercent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_GetHPPercent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execGetHPPercent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetHPPercent();
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function GetHPPercent *****************************************

// ********** Begin Class UHPComponent Function GetMaxHP *******************************************
struct Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics
{
	struct HPComponent_eventGetMaxHP_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMaxHP constinit property declarations ******************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMaxHP constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMaxHP Property Definitions *****************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventGetMaxHP_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::PropPointers) < 2048);
// ********** End Function GetMaxHP Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "GetMaxHP", 	Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::HPComponent_eventGetMaxHP_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::HPComponent_eventGetMaxHP_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_GetMaxHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_GetMaxHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execGetMaxHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetMaxHP();
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function GetMaxHP *********************************************

// ********** Begin Class UHPComponent Function Heal ***********************************************
struct Z_Construct_UFunction_UHPComponent_Heal_Statics
{
	struct HPComponent_eventHeal_Parms
	{
		int32 HealAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Heal constinit property declarations **********************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_HealAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Heal constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Heal Property Definitions *********************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHPComponent_Heal_Statics::NewProp_HealAmount = { "HealAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventHeal_Parms, HealAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_Heal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_Heal_Statics::NewProp_HealAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_Heal_Statics::PropPointers) < 2048);
// ********** End Function Heal Property Definitions ***********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_Heal_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "Heal", 	Z_Construct_UFunction_UHPComponent_Heal_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_Heal_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHPComponent_Heal_Statics::HPComponent_eventHeal_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_Heal_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_Heal_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHPComponent_Heal_Statics::HPComponent_eventHeal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_Heal()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_Heal_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execHeal)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_HealAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Heal(Z_Param_HealAmount);
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function Heal *************************************************

// ********** Begin Class UHPComponent Function IsDead *********************************************
struct Z_Construct_UFunction_UHPComponent_IsDead_Statics
{
	struct HPComponent_eventIsDead_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsDead constinit property declarations ********************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsDead constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsDead Property Definitions *******************************************
void Z_Construct_UFunction_UHPComponent_IsDead_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((HPComponent_eventIsDead_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHPComponent_IsDead_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HPComponent_eventIsDead_Parms), &Z_Construct_UFunction_UHPComponent_IsDead_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_IsDead_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_IsDead_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_IsDead_Statics::PropPointers) < 2048);
// ********** End Function IsDead Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_IsDead_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "IsDead", 	Z_Construct_UFunction_UHPComponent_IsDead_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_IsDead_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHPComponent_IsDead_Statics::HPComponent_eventIsDead_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_IsDead_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_IsDead_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHPComponent_IsDead_Statics::HPComponent_eventIsDead_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_IsDead()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_IsDead_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execIsDead)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsDead();
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function IsDead ***********************************************

// ********** Begin Class UHPComponent Function OnRep_CurrentHP ************************************
struct Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics
{
	struct HPComponent_eventOnRep_CurrentHP_Parms
	{
		int32 OldHP;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_CurrentHP constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_OldHP;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnRep_CurrentHP constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnRep_CurrentHP Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::NewProp_OldHP = { "OldHP", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventOnRep_CurrentHP_Parms, OldHP), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::NewProp_OldHP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::PropPointers) < 2048);
// ********** End Function OnRep_CurrentHP Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "OnRep_CurrentHP", 	Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::HPComponent_eventOnRep_CurrentHP_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::HPComponent_eventOnRep_CurrentHP_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execOnRep_CurrentHP)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_OldHP);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_CurrentHP(Z_Param_OldHP);
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function OnRep_CurrentHP **************************************

// ********** Begin Class UHPComponent Function ResetHP ********************************************
struct Z_Construct_UFunction_UHPComponent_ResetHP_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ResetHP constinit property declarations *******************************
// ********** End Function ResetHP constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_ResetHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "ResetHP", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ResetHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_ResetHP_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UHPComponent_ResetHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_ResetHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execResetHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetHP();
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function ResetHP **********************************************

// ********** Begin Class UHPComponent Function ServerApplyDamage **********************************
struct HPComponent_eventServerApplyDamage_Parms
{
	int32 DamageAmount;
};
static FName NAME_UHPComponent_ServerApplyDamage = FName(TEXT("ServerApplyDamage"));
void UHPComponent::ServerApplyDamage(int32 DamageAmount)
{
	HPComponent_eventServerApplyDamage_Parms Parms;
	Parms.DamageAmount=DamageAmount;
	UFunction* Func = FindFunctionChecked(NAME_UHPComponent_ServerApplyDamage);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerApplyDamage constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerApplyDamage constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerApplyDamage Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventServerApplyDamage_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::PropPointers) < 2048);
// ********** End Function ServerApplyDamage Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "ServerApplyDamage", 	Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::PropPointers), 
sizeof(HPComponent_eventServerApplyDamage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00280CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(HPComponent_eventServerApplyDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_ServerApplyDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_ServerApplyDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execServerApplyDamage)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerApplyDamage_Implementation(Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function ServerApplyDamage ************************************

// ********** Begin Class UHPComponent Function ServerHeal *****************************************
struct HPComponent_eventServerHeal_Parms
{
	int32 HealAmount;
};
static FName NAME_UHPComponent_ServerHeal = FName(TEXT("ServerHeal"));
void UHPComponent::ServerHeal(int32 HealAmount)
{
	HPComponent_eventServerHeal_Parms Parms;
	Parms.HealAmount=HealAmount;
	UFunction* Func = FindFunctionChecked(NAME_UHPComponent_ServerHeal);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UHPComponent_ServerHeal_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerHeal constinit property declarations ****************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_HealAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerHeal constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerHeal Property Definitions ***************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::NewProp_HealAmount = { "HealAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HPComponent_eventServerHeal_Parms, HealAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::NewProp_HealAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::PropPointers) < 2048);
// ********** End Function ServerHeal Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "ServerHeal", 	Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::PropPointers), 
sizeof(HPComponent_eventServerHeal_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00280CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(HPComponent_eventServerHeal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHPComponent_ServerHeal()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_ServerHeal_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execServerHeal)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_HealAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerHeal_Implementation(Z_Param_HealAmount);
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function ServerHeal *******************************************

// ********** Begin Class UHPComponent Function ServerResetHP **************************************
static FName NAME_UHPComponent_ServerResetHP = FName(TEXT("ServerResetHP"));
void UHPComponent::ServerResetHP()
{
	UFunction* Func = FindFunctionChecked(NAME_UHPComponent_ServerResetHP);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_UHPComponent_ServerResetHP_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerResetHP constinit property declarations *************************
// ********** End Function ServerResetHP constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHPComponent_ServerResetHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHPComponent, nullptr, "ServerResetHP", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHPComponent_ServerResetHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHPComponent_ServerResetHP_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UHPComponent_ServerResetHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHPComponent_ServerResetHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHPComponent::execServerResetHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerResetHP_Implementation();
	P_NATIVE_END;
}
// ********** End Class UHPComponent Function ServerResetHP ****************************************

// ********** Begin Class UHPComponent *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UHPComponent;
UClass* UHPComponent::GetPrivateStaticClass()
{
	using TClass = UHPComponent;
	if (!Z_Registration_Info_UClass_UHPComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("HPComponent"),
			Z_Registration_Info_UClass_UHPComponent.InnerSingleton,
			StaticRegisterNativesUHPComponent,
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
	return Z_Registration_Info_UClass_UHPComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UHPComponent_NoRegister()
{
	return UHPComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UHPComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Sub/HPComponent.h" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHP_MetaData[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnHPChanged_MetaData[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnHPZero_MetaData[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/HPComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UHPComponent constinit property declarations *****************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxHP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnHPChanged;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnHPZero;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UHPComponent constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyDamage"), .Pointer = &UHPComponent::execApplyDamage },
		{ .NameUTF8 = UTF8TEXT("GetCurrentHP"), .Pointer = &UHPComponent::execGetCurrentHP },
		{ .NameUTF8 = UTF8TEXT("GetHPPercent"), .Pointer = &UHPComponent::execGetHPPercent },
		{ .NameUTF8 = UTF8TEXT("GetMaxHP"), .Pointer = &UHPComponent::execGetMaxHP },
		{ .NameUTF8 = UTF8TEXT("Heal"), .Pointer = &UHPComponent::execHeal },
		{ .NameUTF8 = UTF8TEXT("IsDead"), .Pointer = &UHPComponent::execIsDead },
		{ .NameUTF8 = UTF8TEXT("OnRep_CurrentHP"), .Pointer = &UHPComponent::execOnRep_CurrentHP },
		{ .NameUTF8 = UTF8TEXT("ResetHP"), .Pointer = &UHPComponent::execResetHP },
		{ .NameUTF8 = UTF8TEXT("ServerApplyDamage"), .Pointer = &UHPComponent::execServerApplyDamage },
		{ .NameUTF8 = UTF8TEXT("ServerHeal"), .Pointer = &UHPComponent::execServerHeal },
		{ .NameUTF8 = UTF8TEXT("ServerResetHP"), .Pointer = &UHPComponent::execServerResetHP },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UHPComponent_ApplyDamage, "ApplyDamage" }, // 1305769978
		{ &Z_Construct_UFunction_UHPComponent_GetCurrentHP, "GetCurrentHP" }, // 3842540783
		{ &Z_Construct_UFunction_UHPComponent_GetHPPercent, "GetHPPercent" }, // 2568241662
		{ &Z_Construct_UFunction_UHPComponent_GetMaxHP, "GetMaxHP" }, // 467800365
		{ &Z_Construct_UFunction_UHPComponent_Heal, "Heal" }, // 3691372621
		{ &Z_Construct_UFunction_UHPComponent_IsDead, "IsDead" }, // 1409588390
		{ &Z_Construct_UFunction_UHPComponent_OnRep_CurrentHP, "OnRep_CurrentHP" }, // 1357188983
		{ &Z_Construct_UFunction_UHPComponent_ResetHP, "ResetHP" }, // 902187311
		{ &Z_Construct_UFunction_UHPComponent_ServerApplyDamage, "ServerApplyDamage" }, // 1968378071
		{ &Z_Construct_UFunction_UHPComponent_ServerHeal, "ServerHeal" }, // 999999168
		{ &Z_Construct_UFunction_UHPComponent_ServerResetHP, "ServerResetHP" }, // 2905537744
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHPComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UHPComponent_Statics

// ********** Begin Class UHPComponent Property Definitions ****************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHPComponent_Statics::NewProp_MaxHP = { "MaxHP", nullptr, (EPropertyFlags)0x0010000000010035, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHPComponent, MaxHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHP_MetaData), NewProp_MaxHP_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHPComponent_Statics::NewProp_CurrentHP = { "CurrentHP", "OnRep_CurrentHP", (EPropertyFlags)0x0010000100000034, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHPComponent, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UHPComponent_Statics::NewProp_OnHPChanged = { "OnHPChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHPComponent, OnHPChanged), Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnHPChanged_MetaData), NewProp_OnHPChanged_MetaData) }; // 1990099325
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UHPComponent_Statics::NewProp_OnHPZero = { "OnHPZero", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHPComponent, OnHPZero), Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnHPZero_MetaData), NewProp_OnHPZero_MetaData) }; // 2206951305
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHPComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHPComponent_Statics::NewProp_MaxHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHPComponent_Statics::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHPComponent_Statics::NewProp_OnHPChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHPComponent_Statics::NewProp_OnHPZero,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHPComponent_Statics::PropPointers) < 2048);
// ********** End Class UHPComponent Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_UHPComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHPComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHPComponent_Statics::ClassParams = {
	&UHPComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UHPComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UHPComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHPComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UHPComponent_Statics::Class_MetaDataParams)
};
void UHPComponent::StaticRegisterNativesUHPComponent()
{
	UClass* Class = UHPComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UHPComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UHPComponent()
{
	if (!Z_Registration_Info_UClass_UHPComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHPComponent.OuterSingleton, Z_Construct_UClass_UHPComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHPComponent.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void UHPComponent::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_MaxHP(TEXT("MaxHP"));
	static FName Name_CurrentHP(TEXT("CurrentHP"));
	const bool bIsValid = true
		&& Name_MaxHP == ClassReps[(int32)ENetFields_Private::MaxHP].Property->GetFName()
		&& Name_CurrentHP == ClassReps[(int32)ENetFields_Private::CurrentHP].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UHPComponent"));
}
#endif
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UHPComponent);
UHPComponent::~UHPComponent() {}
// ********** End Class UHPComponent ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHPComponent, UHPComponent::StaticClass, TEXT("UHPComponent"), &Z_Registration_Info_UClass_UHPComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHPComponent), 3236481599U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h__Script_Claim_Of_Core_2541871243{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
