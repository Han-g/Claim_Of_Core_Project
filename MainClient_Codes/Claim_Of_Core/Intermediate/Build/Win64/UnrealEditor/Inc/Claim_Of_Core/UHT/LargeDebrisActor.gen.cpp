// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/Building/LargeDebrisActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeLargeDebrisActor() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ALargeDebrisActor();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ALargeDebrisActor_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_APreFracturedActor();
NIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ALargeDebrisActor Function ActivateDebris ********************************
struct Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics
{
	struct LargeDebrisActor_eventActivateDebris_Parms
	{
		float InitialImpulseStrength;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Debris" },
		{ "CPP_Default_InitialImpulseStrength", "0.000000" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ActivateDebris constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialImpulseStrength;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ActivateDebris constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ActivateDebris Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::NewProp_InitialImpulseStrength = { "InitialImpulseStrength", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LargeDebrisActor_eventActivateDebris_Parms, InitialImpulseStrength), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::NewProp_InitialImpulseStrength,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::PropPointers) < 2048);
// ********** End Function ActivateDebris Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ALargeDebrisActor, nullptr, "ActivateDebris", 	Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::LargeDebrisActor_eventActivateDebris_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::LargeDebrisActor_eventActivateDebris_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALargeDebrisActor::execActivateDebris)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InitialImpulseStrength);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ActivateDebris(Z_Param_InitialImpulseStrength);
	P_NATIVE_END;
}
// ********** End Class ALargeDebrisActor Function ActivateDebris **********************************

// ********** Begin Class ALargeDebrisActor Function BP_OnDebrisActivated **************************
static FName NAME_ALargeDebrisActor_BP_OnDebrisActivated = FName(TEXT("BP_OnDebrisActivated"));
void ALargeDebrisActor::BP_OnDebrisActivated()
{
	UFunction* Func = FindFunctionChecked(NAME_ALargeDebrisActor_BP_OnDebrisActivated);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisActivated_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnDebrisActivated constinit property declarations ******************
// ********** End Function BP_OnDebrisActivated constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisActivated_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ALargeDebrisActor, nullptr, "BP_OnDebrisActivated", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisActivated_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisActivated_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisActivated()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisActivated_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ALargeDebrisActor Function BP_OnDebrisActivated ****************************

// ********** Begin Class ALargeDebrisActor Function BP_OnDebrisLanded *****************************
static FName NAME_ALargeDebrisActor_BP_OnDebrisLanded = FName(TEXT("BP_OnDebrisLanded"));
void ALargeDebrisActor::BP_OnDebrisLanded()
{
	UFunction* Func = FindFunctionChecked(NAME_ALargeDebrisActor_BP_OnDebrisLanded);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisLanded_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnDebrisLanded constinit property declarations *********************
// ********** End Function BP_OnDebrisLanded constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisLanded_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ALargeDebrisActor, nullptr, "BP_OnDebrisLanded", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisLanded_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisLanded_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisLanded()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisLanded_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ALargeDebrisActor Function BP_OnDebrisLanded *******************************

// ********** Begin Class ALargeDebrisActor Function IsDebrisActivated *****************************
struct Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics
{
	struct LargeDebrisActor_eventIsDebrisActivated_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsDebrisActivated constinit property declarations *********************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsDebrisActivated constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsDebrisActivated Property Definitions ********************************
void Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((LargeDebrisActor_eventIsDebrisActivated_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(LargeDebrisActor_eventIsDebrisActivated_Parms), &Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::PropPointers) < 2048);
// ********** End Function IsDebrisActivated Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ALargeDebrisActor, nullptr, "IsDebrisActivated", 	Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::LargeDebrisActor_eventIsDebrisActivated_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::LargeDebrisActor_eventIsDebrisActivated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALargeDebrisActor::execIsDebrisActivated)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsDebrisActivated();
	P_NATIVE_END;
}
// ********** End Class ALargeDebrisActor Function IsDebrisActivated *******************************

// ********** Begin Class ALargeDebrisActor Function IsLanded **************************************
struct Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics
{
	struct LargeDebrisActor_eventIsLanded_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsLanded constinit property declarations ******************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsLanded constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsLanded Property Definitions *****************************************
void Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((LargeDebrisActor_eventIsLanded_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(LargeDebrisActor_eventIsLanded_Parms), &Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::PropPointers) < 2048);
// ********** End Function IsLanded Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ALargeDebrisActor, nullptr, "IsLanded", 	Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::LargeDebrisActor_eventIsLanded_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::LargeDebrisActor_eventIsLanded_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ALargeDebrisActor_IsLanded()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALargeDebrisActor_IsLanded_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALargeDebrisActor::execIsLanded)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsLanded();
	P_NATIVE_END;
}
// ********** End Class ALargeDebrisActor Function IsLanded ****************************************

// ********** Begin Class ALargeDebrisActor Function PrepareDebris *********************************
struct Z_Construct_UFunction_ALargeDebrisActor_PrepareDebris_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PrepareDebris constinit property declarations *************************
// ********** End Function PrepareDebris constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeDebrisActor_PrepareDebris_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ALargeDebrisActor, nullptr, "PrepareDebris", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeDebrisActor_PrepareDebris_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALargeDebrisActor_PrepareDebris_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ALargeDebrisActor_PrepareDebris()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALargeDebrisActor_PrepareDebris_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALargeDebrisActor::execPrepareDebris)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PrepareDebris();
	P_NATIVE_END;
}
// ********** End Class ALargeDebrisActor Function PrepareDebris ***********************************

// ********** Begin Class ALargeDebrisActor ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ALargeDebrisActor;
UClass* ALargeDebrisActor::GetPrivateStaticClass()
{
	using TClass = ALargeDebrisActor;
	if (!Z_Registration_Info_UClass_ALargeDebrisActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("LargeDebrisActor"),
			Z_Registration_Info_UClass_ALargeDebrisActor.InnerSingleton,
			StaticRegisterNativesALargeDebrisActor,
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
	return Z_Registration_Info_UClass_ALargeDebrisActor.InnerSingleton;
}
UClass* Z_Construct_UClass_ALargeDebrisActor_NoRegister()
{
	return ALargeDebrisActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ALargeDebrisActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/Building/LargeDebrisActor.h" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkBreakEffect_MetaData[] = {
		{ "Category", "Debris|VFX" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LandingDustEffect_MetaData[] = {
		{ "Category", "Debris|VFX" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DebrisEffectScale_MetaData[] = {
		{ "Category", "Debris|VFX" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseActorFall_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GravityAcceleration_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxFallSpeed_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundZ_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundOffset_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinBreakSpeed_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpeedToDamageScale_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxInitialBreakCount_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BottomChunkTolerance_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDebrisActivated_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLanded_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentFallSpeed_MetaData[] = {
		{ "Category", "Debris|Fall" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SequentialBreakInterval_MetaData[] = {
		{ "Category", "Debris|SequentialBreak" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd8\xb1\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd8\xb1\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SequentialBreakBatchSize_MetaData[] = {
		{ "Category", "Debris|SequentialBreak" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PendingBreakChunks_MetaData[] = {
		{ "Category", "Debris|SequentialBreak" },
		{ "ModuleRelativePath", "Map/Building/LargeDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ALargeDebrisActor constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChunkBreakEffect;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LandingDustEffect;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DebrisEffectScale;
	static void NewProp_bUseActorFall_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseActorFall;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GravityAcceleration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxFallSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundZ;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinBreakSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpeedToDamageScale;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxInitialBreakCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BottomChunkTolerance;
	static void NewProp_bDebrisActivated_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDebrisActivated;
	static void NewProp_bLanded_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLanded;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentFallSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SequentialBreakInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SequentialBreakBatchSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PendingBreakChunks_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PendingBreakChunks;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ALargeDebrisActor constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ActivateDebris"), .Pointer = &ALargeDebrisActor::execActivateDebris },
		{ .NameUTF8 = UTF8TEXT("IsDebrisActivated"), .Pointer = &ALargeDebrisActor::execIsDebrisActivated },
		{ .NameUTF8 = UTF8TEXT("IsLanded"), .Pointer = &ALargeDebrisActor::execIsLanded },
		{ .NameUTF8 = UTF8TEXT("PrepareDebris"), .Pointer = &ALargeDebrisActor::execPrepareDebris },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ALargeDebrisActor_ActivateDebris, "ActivateDebris" }, // 2637137923
		{ &Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisActivated, "BP_OnDebrisActivated" }, // 2688708834
		{ &Z_Construct_UFunction_ALargeDebrisActor_BP_OnDebrisLanded, "BP_OnDebrisLanded" }, // 1652404259
		{ &Z_Construct_UFunction_ALargeDebrisActor_IsDebrisActivated, "IsDebrisActivated" }, // 1237778032
		{ &Z_Construct_UFunction_ALargeDebrisActor_IsLanded, "IsLanded" }, // 1943373311
		{ &Z_Construct_UFunction_ALargeDebrisActor_PrepareDebris, "PrepareDebris" }, // 2751121141
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALargeDebrisActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ALargeDebrisActor_Statics

// ********** Begin Class ALargeDebrisActor Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_ChunkBreakEffect = { "ChunkBreakEffect", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, ChunkBreakEffect), Z_Construct_UClass_UNiagaraSystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkBreakEffect_MetaData), NewProp_ChunkBreakEffect_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_LandingDustEffect = { "LandingDustEffect", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, LandingDustEffect), Z_Construct_UClass_UNiagaraSystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LandingDustEffect_MetaData), NewProp_LandingDustEffect_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_DebrisEffectScale = { "DebrisEffectScale", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, DebrisEffectScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DebrisEffectScale_MetaData), NewProp_DebrisEffectScale_MetaData) };
void Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bUseActorFall_SetBit(void* Obj)
{
	((ALargeDebrisActor*)Obj)->bUseActorFall = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bUseActorFall = { "bUseActorFall", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALargeDebrisActor), &Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bUseActorFall_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseActorFall_MetaData), NewProp_bUseActorFall_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_GravityAcceleration = { "GravityAcceleration", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, GravityAcceleration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GravityAcceleration_MetaData), NewProp_GravityAcceleration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_MaxFallSpeed = { "MaxFallSpeed", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, MaxFallSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxFallSpeed_MetaData), NewProp_MaxFallSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_GroundZ = { "GroundZ", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, GroundZ), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundZ_MetaData), NewProp_GroundZ_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_GroundOffset = { "GroundOffset", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, GroundOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundOffset_MetaData), NewProp_GroundOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_MinBreakSpeed = { "MinBreakSpeed", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, MinBreakSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinBreakSpeed_MetaData), NewProp_MinBreakSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_SpeedToDamageScale = { "SpeedToDamageScale", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, SpeedToDamageScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpeedToDamageScale_MetaData), NewProp_SpeedToDamageScale_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_MaxInitialBreakCount = { "MaxInitialBreakCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, MaxInitialBreakCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxInitialBreakCount_MetaData), NewProp_MaxInitialBreakCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_BottomChunkTolerance = { "BottomChunkTolerance", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, BottomChunkTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BottomChunkTolerance_MetaData), NewProp_BottomChunkTolerance_MetaData) };
void Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bDebrisActivated_SetBit(void* Obj)
{
	((ALargeDebrisActor*)Obj)->bDebrisActivated = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bDebrisActivated = { "bDebrisActivated", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALargeDebrisActor), &Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bDebrisActivated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDebrisActivated_MetaData), NewProp_bDebrisActivated_MetaData) };
void Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bLanded_SetBit(void* Obj)
{
	((ALargeDebrisActor*)Obj)->bLanded = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bLanded = { "bLanded", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALargeDebrisActor), &Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bLanded_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLanded_MetaData), NewProp_bLanded_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_CurrentFallSpeed = { "CurrentFallSpeed", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, CurrentFallSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentFallSpeed_MetaData), NewProp_CurrentFallSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_SequentialBreakInterval = { "SequentialBreakInterval", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, SequentialBreakInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SequentialBreakInterval_MetaData), NewProp_SequentialBreakInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_SequentialBreakBatchSize = { "SequentialBreakBatchSize", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, SequentialBreakBatchSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SequentialBreakBatchSize_MetaData), NewProp_SequentialBreakBatchSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_PendingBreakChunks_Inner = { "PendingBreakChunks", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_PendingBreakChunks = { "PendingBreakChunks", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALargeDebrisActor, PendingBreakChunks), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PendingBreakChunks_MetaData), NewProp_PendingBreakChunks_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALargeDebrisActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_ChunkBreakEffect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_LandingDustEffect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_DebrisEffectScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bUseActorFall,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_GravityAcceleration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_MaxFallSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_GroundZ,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_GroundOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_MinBreakSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_SpeedToDamageScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_MaxInitialBreakCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_BottomChunkTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bDebrisActivated,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_bLanded,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_CurrentFallSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_SequentialBreakInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_SequentialBreakBatchSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_PendingBreakChunks_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeDebrisActor_Statics::NewProp_PendingBreakChunks,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisActor_Statics::PropPointers) < 2048);
// ********** End Class ALargeDebrisActor Property Definitions *************************************
UObject* (*const Z_Construct_UClass_ALargeDebrisActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APreFracturedActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALargeDebrisActor_Statics::ClassParams = {
	&ALargeDebrisActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ALargeDebrisActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALargeDebrisActor_Statics::Class_MetaDataParams), Z_Construct_UClass_ALargeDebrisActor_Statics::Class_MetaDataParams)
};
void ALargeDebrisActor::StaticRegisterNativesALargeDebrisActor()
{
	UClass* Class = ALargeDebrisActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ALargeDebrisActor_Statics::Funcs));
}
UClass* Z_Construct_UClass_ALargeDebrisActor()
{
	if (!Z_Registration_Info_UClass_ALargeDebrisActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALargeDebrisActor.OuterSingleton, Z_Construct_UClass_ALargeDebrisActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALargeDebrisActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ALargeDebrisActor);
ALargeDebrisActor::~ALargeDebrisActor() {}
// ********** End Class ALargeDebrisActor **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisActor_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALargeDebrisActor, ALargeDebrisActor::StaticClass, TEXT("ALargeDebrisActor"), &Z_Registration_Info_UClass_ALargeDebrisActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALargeDebrisActor), 1876423835U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisActor_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisActor_h__Script_Claim_Of_Core_1300274692{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisActor_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_LargeDebrisActor_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
