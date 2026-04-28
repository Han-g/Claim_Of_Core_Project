// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/IceCave/IcicleActor.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeIcicleActor() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIcicleActor();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIcicleActor_NoRegister();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_EIcicleState();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EIcicleState **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EIcicleState;
static UEnum* EIcicleState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EIcicleState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EIcicleState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_EIcicleState, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("EIcicleState"));
	}
	return Z_Registration_Info_UEnum_EIcicleState.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EIcicleState>()
{
	return EIcicleState_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Broken.Name", "EIcicleState::Broken" },
		{ "Falling.Name", "EIcicleState::Falling" },
		{ "Idle.Name", "EIcicleState::Idle" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
		{ "Warning.Name", "EIcicleState::Warning" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EIcicleState::Idle", (int64)EIcicleState::Idle },
		{ "EIcicleState::Warning", (int64)EIcicleState::Warning },
		{ "EIcicleState::Falling", (int64)EIcicleState::Falling },
		{ "EIcicleState::Broken", (int64)EIcicleState::Broken },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"EIcicleState",
	"EIcicleState",
	Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_EIcicleState()
{
	if (!Z_Registration_Info_UEnum_EIcicleState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EIcicleState.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_EIcicleState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EIcicleState.InnerSingleton;
}
// ********** End Enum EIcicleState ****************************************************************

// ********** Begin Class AIcicleActor Function BP_OnBroken ****************************************
static FName NAME_AIcicleActor_BP_OnBroken = FName(TEXT("BP_OnBroken"));
void AIcicleActor::BP_OnBroken()
{
	UFunction* Func = FindFunctionChecked(NAME_AIcicleActor_BP_OnBroken);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AIcicleActor_BP_OnBroken_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnBroken constinit property declarations ***************************
// ********** End Function BP_OnBroken constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIcicleActor_BP_OnBroken_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIcicleActor, nullptr, "BP_OnBroken", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_BP_OnBroken_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIcicleActor_BP_OnBroken_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIcicleActor_BP_OnBroken()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIcicleActor_BP_OnBroken_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AIcicleActor Function BP_OnBroken ******************************************

// ********** Begin Class AIcicleActor Function BP_OnFallingStarted ********************************
static FName NAME_AIcicleActor_BP_OnFallingStarted = FName(TEXT("BP_OnFallingStarted"));
void AIcicleActor::BP_OnFallingStarted()
{
	UFunction* Func = FindFunctionChecked(NAME_AIcicleActor_BP_OnFallingStarted);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AIcicleActor_BP_OnFallingStarted_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnFallingStarted constinit property declarations *******************
// ********** End Function BP_OnFallingStarted constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIcicleActor_BP_OnFallingStarted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIcicleActor, nullptr, "BP_OnFallingStarted", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_BP_OnFallingStarted_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIcicleActor_BP_OnFallingStarted_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIcicleActor_BP_OnFallingStarted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIcicleActor_BP_OnFallingStarted_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AIcicleActor Function BP_OnFallingStarted **********************************

// ********** Begin Class AIcicleActor Function BP_OnWarningStarted ********************************
static FName NAME_AIcicleActor_BP_OnWarningStarted = FName(TEXT("BP_OnWarningStarted"));
void AIcicleActor::BP_OnWarningStarted()
{
	UFunction* Func = FindFunctionChecked(NAME_AIcicleActor_BP_OnWarningStarted);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AIcicleActor_BP_OnWarningStarted_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnWarningStarted constinit property declarations *******************
// ********** End Function BP_OnWarningStarted constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIcicleActor_BP_OnWarningStarted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIcicleActor, nullptr, "BP_OnWarningStarted", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_BP_OnWarningStarted_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIcicleActor_BP_OnWarningStarted_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIcicleActor_BP_OnWarningStarted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIcicleActor_BP_OnWarningStarted_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AIcicleActor Function BP_OnWarningStarted **********************************

// ********** Begin Class AIcicleActor Function OnIcicleHit ****************************************
struct Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics
{
	struct IcicleActor_eventOnIcicleHit_Parms
	{
		UPrimitiveComponent* HitComponent;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		FVector NormalImpulse;
		FHitResult Hit;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HitComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnIcicleHit constinit property declarations ***************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HitComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NormalImpulse;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Hit;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnIcicleHit constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnIcicleHit Property Definitions **************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_HitComponent = { "HitComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(IcicleActor_eventOnIcicleHit_Parms, HitComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HitComponent_MetaData), NewProp_HitComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(IcicleActor_eventOnIcicleHit_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(IcicleActor_eventOnIcicleHit_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_NormalImpulse = { "NormalImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(IcicleActor_eventOnIcicleHit_Parms, NormalImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_Hit = { "Hit", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(IcicleActor_eventOnIcicleHit_Parms, Hit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hit_MetaData), NewProp_Hit_MetaData) }; // 222120718
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_HitComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_NormalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::NewProp_Hit,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::PropPointers) < 2048);
// ********** End Function OnIcicleHit Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIcicleActor, nullptr, "OnIcicleHit", 	Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::IcicleActor_eventOnIcicleHit_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::IcicleActor_eventOnIcicleHit_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AIcicleActor_OnIcicleHit()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIcicleActor_OnIcicleHit_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIcicleActor::execOnIcicleHit)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComponent);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_STRUCT(FVector,Z_Param_NormalImpulse);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnIcicleHit(Z_Param_HitComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit);
	P_NATIVE_END;
}
// ********** End Class AIcicleActor Function OnIcicleHit ******************************************

// ********** Begin Class AIcicleActor Function StartFalling ***************************************
struct Z_Construct_UFunction_AIcicleActor_StartFalling_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartFalling constinit property declarations **************************
// ********** End Function StartFalling constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIcicleActor_StartFalling_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIcicleActor, nullptr, "StartFalling", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_StartFalling_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIcicleActor_StartFalling_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIcicleActor_StartFalling()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIcicleActor_StartFalling_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIcicleActor::execStartFalling)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartFalling();
	P_NATIVE_END;
}
// ********** End Class AIcicleActor Function StartFalling *****************************************

// ********** Begin Class AIcicleActor Function StartWarning ***************************************
struct Z_Construct_UFunction_AIcicleActor_StartWarning_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartWarning constinit property declarations **************************
// ********** End Function StartWarning constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AIcicleActor_StartWarning_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AIcicleActor, nullptr, "StartWarning", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AIcicleActor_StartWarning_Statics::Function_MetaDataParams), Z_Construct_UFunction_AIcicleActor_StartWarning_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AIcicleActor_StartWarning()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AIcicleActor_StartWarning_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AIcicleActor::execStartWarning)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartWarning();
	P_NATIVE_END;
}
// ********** End Class AIcicleActor Function StartWarning *****************************************

// ********** Begin Class AIcicleActor *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AIcicleActor;
UClass* AIcicleActor::GetPrivateStaticClass()
{
	using TClass = AIcicleActor;
	if (!Z_Registration_Info_UClass_AIcicleActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("IcicleActor"),
			Z_Registration_Info_UClass_AIcicleActor.InnerSingleton,
			StaticRegisterNativesAIcicleActor,
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
	return Z_Registration_Info_UClass_AIcicleActor.InnerSingleton;
}
UClass* Z_Construct_UClass_AIcicleActor_NoRegister()
{
	return AIcicleActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AIcicleActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/IceCave/IcicleActor.h" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "IcicleActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IcicleMesh_MetaData[] = {
		{ "Category", "IcicleActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningRange_MetaData[] = {
		{ "Category", "IcicleActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageCollision_MetaData[] = {
		{ "Category", "IcicleActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "Category", "Icicle" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarningTime_MetaData[] = {
		{ "Category", "Icicle" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Damage_MetaData[] = {
		{ "Category", "Icicle" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DestroyDelay_MetaData[] = {
		{ "Category", "Icicle" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDestroyAfterHitGround_MetaData[] = {
		{ "Category", "Icicle" },
		{ "ModuleRelativePath", "Map/IceCave/IcicleActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AIcicleActor constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_IcicleMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WarningRange;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DamageCollision;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WarningTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DestroyDelay;
	static void NewProp_bDestroyAfterHitGround_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDestroyAfterHitGround;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AIcicleActor constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnIcicleHit"), .Pointer = &AIcicleActor::execOnIcicleHit },
		{ .NameUTF8 = UTF8TEXT("StartFalling"), .Pointer = &AIcicleActor::execStartFalling },
		{ .NameUTF8 = UTF8TEXT("StartWarning"), .Pointer = &AIcicleActor::execStartWarning },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AIcicleActor_BP_OnBroken, "BP_OnBroken" }, // 252201500
		{ &Z_Construct_UFunction_AIcicleActor_BP_OnFallingStarted, "BP_OnFallingStarted" }, // 3237351311
		{ &Z_Construct_UFunction_AIcicleActor_BP_OnWarningStarted, "BP_OnWarningStarted" }, // 423257904
		{ &Z_Construct_UFunction_AIcicleActor_OnIcicleHit, "OnIcicleHit" }, // 3340342902
		{ &Z_Construct_UFunction_AIcicleActor_StartFalling, "StartFalling" }, // 1498502447
		{ &Z_Construct_UFunction_AIcicleActor_StartWarning, "StartWarning" }, // 4019629096
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AIcicleActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AIcicleActor_Statics

// ********** Begin Class AIcicleActor Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_IcicleMesh = { "IcicleMesh", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, IcicleMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IcicleMesh_MetaData), NewProp_IcicleMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_WarningRange = { "WarningRange", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, WarningRange), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningRange_MetaData), NewProp_WarningRange_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_DamageCollision = { "DamageCollision", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, DamageCollision), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageCollision_MetaData), NewProp_DamageCollision_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_CurrentState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, CurrentState), Z_Construct_UEnum_Claim_Of_Core_EIcicleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 2524465267
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_WarningTime = { "WarningTime", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, WarningTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarningTime_MetaData), NewProp_WarningTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, Damage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Damage_MetaData), NewProp_Damage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_DestroyDelay = { "DestroyDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AIcicleActor, DestroyDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DestroyDelay_MetaData), NewProp_DestroyDelay_MetaData) };
void Z_Construct_UClass_AIcicleActor_Statics::NewProp_bDestroyAfterHitGround_SetBit(void* Obj)
{
	((AIcicleActor*)Obj)->bDestroyAfterHitGround = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AIcicleActor_Statics::NewProp_bDestroyAfterHitGround = { "bDestroyAfterHitGround", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AIcicleActor), &Z_Construct_UClass_AIcicleActor_Statics::NewProp_bDestroyAfterHitGround_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDestroyAfterHitGround_MetaData), NewProp_bDestroyAfterHitGround_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AIcicleActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_IcicleMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_WarningRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_DamageCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_CurrentState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_CurrentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_WarningTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_Damage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_DestroyDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AIcicleActor_Statics::NewProp_bDestroyAfterHitGround,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIcicleActor_Statics::PropPointers) < 2048);
// ********** End Class AIcicleActor Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_AIcicleActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIcicleActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AIcicleActor_Statics::ClassParams = {
	&AIcicleActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AIcicleActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AIcicleActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AIcicleActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AIcicleActor_Statics::Class_MetaDataParams)
};
void AIcicleActor::StaticRegisterNativesAIcicleActor()
{
	UClass* Class = AIcicleActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AIcicleActor_Statics::Funcs));
}
UClass* Z_Construct_UClass_AIcicleActor()
{
	if (!Z_Registration_Info_UClass_AIcicleActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AIcicleActor.OuterSingleton, Z_Construct_UClass_AIcicleActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AIcicleActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AIcicleActor);
AIcicleActor::~AIcicleActor() {}
// ********** End Class AIcicleActor ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h__Script_Claim_Of_Core_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EIcicleState_StaticEnum, TEXT("EIcicleState"), &Z_Registration_Info_UEnum_EIcicleState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2524465267U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AIcicleActor, AIcicleActor::StaticClass, TEXT("AIcicleActor"), &Z_Registration_Info_UClass_AIcicleActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AIcicleActor), 1416107199U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h__Script_Claim_Of_Core_3470365715{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h__Script_Claim_Of_Core_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h__Script_Claim_Of_Core_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
