// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/PreFracturedActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodePreFracturedActor() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ABreakableActor();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AInGame_GameState_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_APreFracturedActor();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_APreFracturedActor_NoRegister();
CLAIM_OF_CORE_API UScriptStruct* Z_Construct_UScriptStruct_FPreFracturedChunkData();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FPreFracturedChunkData ********************************************
struct Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FPreFracturedChunkData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FPreFracturedChunkData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkIndex_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Neighbors_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentDamage_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BreakThreshold_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBroken_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAnchored_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FPreFracturedChunkData constinit property declarations ************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChunkIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Neighbors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Neighbors;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentDamage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BreakThreshold;
	static void NewProp_bBroken_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBroken;
	static void NewProp_bAnchored_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAnchored;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FPreFracturedChunkData constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPreFracturedChunkData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FPreFracturedChunkData;
class UScriptStruct* FPreFracturedChunkData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FPreFracturedChunkData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FPreFracturedChunkData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPreFracturedChunkData, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("PreFracturedChunkData"));
	}
	return Z_Registration_Info_UScriptStruct_FPreFracturedChunkData.OuterSingleton;
	}

// ********** Begin ScriptStruct FPreFracturedChunkData Property Definitions ***********************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_ChunkIndex = { "ChunkIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPreFracturedChunkData, ChunkIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkIndex_MetaData), NewProp_ChunkIndex_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_Neighbors_Inner = { "Neighbors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_Neighbors = { "Neighbors", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPreFracturedChunkData, Neighbors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Neighbors_MetaData), NewProp_Neighbors_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_CurrentDamage = { "CurrentDamage", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPreFracturedChunkData, CurrentDamage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentDamage_MetaData), NewProp_CurrentDamage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_BreakThreshold = { "BreakThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPreFracturedChunkData, BreakThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BreakThreshold_MetaData), NewProp_BreakThreshold_MetaData) };
void Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bBroken_SetBit(void* Obj)
{
	((FPreFracturedChunkData*)Obj)->bBroken = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bBroken = { "bBroken", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FPreFracturedChunkData), &Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bBroken_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBroken_MetaData), NewProp_bBroken_MetaData) };
void Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bAnchored_SetBit(void* Obj)
{
	((FPreFracturedChunkData*)Obj)->bAnchored = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bAnchored = { "bAnchored", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FPreFracturedChunkData), &Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bAnchored_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAnchored_MetaData), NewProp_bAnchored_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_ChunkIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_Neighbors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_Neighbors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_CurrentDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_BreakThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bBroken,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewProp_bAnchored,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FPreFracturedChunkData Property Definitions *************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	&NewStructOps,
	"PreFracturedChunkData",
	Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::PropPointers),
	sizeof(FPreFracturedChunkData),
	alignof(FPreFracturedChunkData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FPreFracturedChunkData()
{
	if (!Z_Registration_Info_UScriptStruct_FPreFracturedChunkData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FPreFracturedChunkData.InnerSingleton, Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FPreFracturedChunkData.InnerSingleton);
}
// ********** End ScriptStruct FPreFracturedChunkData **********************************************

// ********** Begin Class APreFracturedActor Function ApplyDamageToChunk ***************************
struct Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics
{
	struct PreFracturedActor_eventApplyDamageToChunk_Parms
	{
		int32 ChunkIndex;
		float DamageAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyDamageToChunk constinit property declarations ********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChunkIndex;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyDamageToChunk constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyDamageToChunk Property Definitions *******************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::NewProp_ChunkIndex = { "ChunkIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PreFracturedActor_eventApplyDamageToChunk_Parms, ChunkIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PreFracturedActor_eventApplyDamageToChunk_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::NewProp_ChunkIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::PropPointers) < 2048);
// ********** End Function ApplyDamageToChunk Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APreFracturedActor, nullptr, "ApplyDamageToChunk", 	Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::PreFracturedActor_eventApplyDamageToChunk_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::Function_MetaDataParams), Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::PreFracturedActor_eventApplyDamageToChunk_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APreFracturedActor::execApplyDamageToChunk)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ChunkIndex);
	P_GET_PROPERTY(FFloatProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyDamageToChunk(Z_Param_ChunkIndex,Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class APreFracturedActor Function ApplyDamageToChunk *****************************

// ********** Begin Class APreFracturedActor Function BP_OnChainReactionFinished *******************
static FName NAME_APreFracturedActor_BP_OnChainReactionFinished = FName(TEXT("BP_OnChainReactionFinished"));
void APreFracturedActor::BP_OnChainReactionFinished()
{
	UFunction* Func = FindFunctionChecked(NAME_APreFracturedActor_BP_OnChainReactionFinished);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_APreFracturedActor_BP_OnChainReactionFinished_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnChainReactionFinished constinit property declarations ************
// ********** End Function BP_OnChainReactionFinished constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APreFracturedActor_BP_OnChainReactionFinished_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APreFracturedActor, nullptr, "BP_OnChainReactionFinished", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_BP_OnChainReactionFinished_Statics::Function_MetaDataParams), Z_Construct_UFunction_APreFracturedActor_BP_OnChainReactionFinished_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_APreFracturedActor_BP_OnChainReactionFinished()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APreFracturedActor_BP_OnChainReactionFinished_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class APreFracturedActor Function BP_OnChainReactionFinished *********************

// ********** Begin Class APreFracturedActor Function BP_OnChunkBroken *****************************
struct PreFracturedActor_eventBP_OnChunkBroken_Parms
{
	int32 BrokenChunkIndex;
};
static FName NAME_APreFracturedActor_BP_OnChunkBroken = FName(TEXT("BP_OnChunkBroken"));
void APreFracturedActor::BP_OnChunkBroken(int32 BrokenChunkIndex)
{
	PreFracturedActor_eventBP_OnChunkBroken_Parms Parms;
	Parms.BrokenChunkIndex=BrokenChunkIndex;
	UFunction* Func = FindFunctionChecked(NAME_APreFracturedActor_BP_OnChunkBroken);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnChunkBroken constinit property declarations **********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_BrokenChunkIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnChunkBroken constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnChunkBroken Property Definitions *********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::NewProp_BrokenChunkIndex = { "BrokenChunkIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PreFracturedActor_eventBP_OnChunkBroken_Parms, BrokenChunkIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::NewProp_BrokenChunkIndex,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::PropPointers) < 2048);
// ********** End Function BP_OnChunkBroken Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APreFracturedActor, nullptr, "BP_OnChunkBroken", 	Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::PropPointers), 
sizeof(PreFracturedActor_eventBP_OnChunkBroken_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::Function_MetaDataParams), Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(PreFracturedActor_eventBP_OnChunkBroken_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class APreFracturedActor Function BP_OnChunkBroken *******************************

// ********** Begin Class APreFracturedActor Function BreakChunk ***********************************
struct Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics
{
	struct PreFracturedActor_eventBreakChunk_Parms
	{
		int32 ChunkIndex;
		bool bFromImpact;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Fracture" },
		{ "CPP_Default_bFromImpact", "false" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BreakChunk constinit property declarations ****************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChunkIndex;
	static void NewProp_bFromImpact_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromImpact;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BreakChunk constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BreakChunk Property Definitions ***************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::NewProp_ChunkIndex = { "ChunkIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PreFracturedActor_eventBreakChunk_Parms, ChunkIndex), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::NewProp_bFromImpact_SetBit(void* Obj)
{
	((PreFracturedActor_eventBreakChunk_Parms*)Obj)->bFromImpact = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::NewProp_bFromImpact = { "bFromImpact", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(PreFracturedActor_eventBreakChunk_Parms), &Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::NewProp_bFromImpact_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::NewProp_ChunkIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::NewProp_bFromImpact,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::PropPointers) < 2048);
// ********** End Function BreakChunk Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APreFracturedActor, nullptr, "BreakChunk", 	Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::PreFracturedActor_eventBreakChunk_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::Function_MetaDataParams), Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::PreFracturedActor_eventBreakChunk_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APreFracturedActor_BreakChunk()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APreFracturedActor_BreakChunk_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APreFracturedActor::execBreakChunk)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ChunkIndex);
	P_GET_UBOOL(Z_Param_bFromImpact);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BreakChunk(Z_Param_ChunkIndex,Z_Param_bFromImpact);
	P_NATIVE_END;
}
// ********** End Class APreFracturedActor Function BreakChunk *************************************

// ********** Begin Class APreFracturedActor Function PrepareFracture ******************************
struct Z_Construct_UFunction_APreFracturedActor_PrepareFracture_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PrepareFracture constinit property declarations ***********************
// ********** End Function PrepareFracture constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APreFracturedActor_PrepareFracture_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APreFracturedActor, nullptr, "PrepareFracture", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APreFracturedActor_PrepareFracture_Statics::Function_MetaDataParams), Z_Construct_UFunction_APreFracturedActor_PrepareFracture_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_APreFracturedActor_PrepareFracture()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APreFracturedActor_PrepareFracture_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APreFracturedActor::execPrepareFracture)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PrepareFracture();
	P_NATIVE_END;
}
// ********** End Class APreFracturedActor Function PrepareFracture ********************************

// ********** Begin Class APreFracturedActor *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_APreFracturedActor;
UClass* APreFracturedActor::GetPrivateStaticClass()
{
	using TClass = APreFracturedActor;
	if (!Z_Registration_Info_UClass_APreFracturedActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("PreFracturedActor"),
			Z_Registration_Info_UClass_APreFracturedActor.InnerSingleton,
			StaticRegisterNativesAPreFracturedActor,
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
	return Z_Registration_Info_UClass_APreFracturedActor.InnerSingleton;
}
UClass* Z_Construct_UClass_APreFracturedActor_NoRegister()
{
	return APreFracturedActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APreFracturedActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/PreFracturedActor.h" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkMeshes_MetaData[] = {
		{ "Category", "Fracture" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkData_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChainScatterImpulse_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFreezeAfterChainReaction_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FreezeDelay_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeighborDamageRatio_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkTag_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoBuildGraph_MetaData[] = {
		{ "Category", "Fracture|AutoGraph" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeighborDistanceThreshold_MetaData[] = {
		{ "Category", "Fracture|AutoGraph" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoSetAnchored_MetaData[] = {
		{ "Category", "Fracture|AutoGraph" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnchorBottomTolerance_MetaData[] = {
		{ "Category", "Fracture|AutoGraph" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedGameState_MetaData[] = {
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFractureRuntimeActivated_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Map/PreFracturedActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class APreFracturedActor constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChunkMeshes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ChunkMeshes;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ChunkData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ChunkData;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ChainScatterImpulse;
	static void NewProp_bFreezeAfterChainReaction_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFreezeAfterChainReaction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FreezeDelay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NeighborDamageRatio;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ChunkTag;
	static void NewProp_bAutoBuildGraph_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoBuildGraph;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NeighborDistanceThreshold;
	static void NewProp_bAutoSetAnchored_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoSetAnchored;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AnchorBottomTolerance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedGameState;
	static void NewProp_bFractureRuntimeActivated_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFractureRuntimeActivated;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class APreFracturedActor constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyDamageToChunk"), .Pointer = &APreFracturedActor::execApplyDamageToChunk },
		{ .NameUTF8 = UTF8TEXT("BreakChunk"), .Pointer = &APreFracturedActor::execBreakChunk },
		{ .NameUTF8 = UTF8TEXT("PrepareFracture"), .Pointer = &APreFracturedActor::execPrepareFracture },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APreFracturedActor_ApplyDamageToChunk, "ApplyDamageToChunk" }, // 2502436703
		{ &Z_Construct_UFunction_APreFracturedActor_BP_OnChainReactionFinished, "BP_OnChainReactionFinished" }, // 2524390768
		{ &Z_Construct_UFunction_APreFracturedActor_BP_OnChunkBroken, "BP_OnChunkBroken" }, // 2947641562
		{ &Z_Construct_UFunction_APreFracturedActor_BreakChunk, "BreakChunk" }, // 2803713162
		{ &Z_Construct_UFunction_APreFracturedActor_PrepareFracture, "PrepareFracture" }, // 3036068719
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APreFracturedActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_APreFracturedActor_Statics

// ********** Begin Class APreFracturedActor Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkMeshes_Inner = { "ChunkMeshes", nullptr, (EPropertyFlags)0x01040000000a0008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkMeshes = { "ChunkMeshes", nullptr, (EPropertyFlags)0x012408800002001d, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, ChunkMeshes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkMeshes_MetaData), NewProp_ChunkMeshes_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkData_Inner = { "ChunkData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FPreFracturedChunkData, METADATA_PARAMS(0, nullptr) }; // 2247896100
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkData = { "ChunkData", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, ChunkData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkData_MetaData), NewProp_ChunkData_MetaData) }; // 2247896100
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChainScatterImpulse = { "ChainScatterImpulse", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, ChainScatterImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChainScatterImpulse_MetaData), NewProp_ChainScatterImpulse_MetaData) };
void Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFreezeAfterChainReaction_SetBit(void* Obj)
{
	((APreFracturedActor*)Obj)->bFreezeAfterChainReaction = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFreezeAfterChainReaction = { "bFreezeAfterChainReaction", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(APreFracturedActor), &Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFreezeAfterChainReaction_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFreezeAfterChainReaction_MetaData), NewProp_bFreezeAfterChainReaction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_FreezeDelay = { "FreezeDelay", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, FreezeDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FreezeDelay_MetaData), NewProp_FreezeDelay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_NeighborDamageRatio = { "NeighborDamageRatio", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, NeighborDamageRatio), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeighborDamageRatio_MetaData), NewProp_NeighborDamageRatio_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkTag = { "ChunkTag", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, ChunkTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkTag_MetaData), NewProp_ChunkTag_MetaData) };
void Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoBuildGraph_SetBit(void* Obj)
{
	((APreFracturedActor*)Obj)->bAutoBuildGraph = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoBuildGraph = { "bAutoBuildGraph", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(APreFracturedActor), &Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoBuildGraph_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoBuildGraph_MetaData), NewProp_bAutoBuildGraph_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_NeighborDistanceThreshold = { "NeighborDistanceThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, NeighborDistanceThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeighborDistanceThreshold_MetaData), NewProp_NeighborDistanceThreshold_MetaData) };
void Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoSetAnchored_SetBit(void* Obj)
{
	((APreFracturedActor*)Obj)->bAutoSetAnchored = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoSetAnchored = { "bAutoSetAnchored", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(APreFracturedActor), &Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoSetAnchored_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoSetAnchored_MetaData), NewProp_bAutoSetAnchored_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_AnchorBottomTolerance = { "AnchorBottomTolerance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, AnchorBottomTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnchorBottomTolerance_MetaData), NewProp_AnchorBottomTolerance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_CachedGameState = { "CachedGameState", nullptr, (EPropertyFlags)0x0124080000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APreFracturedActor, CachedGameState), Z_Construct_UClass_AInGame_GameState_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedGameState_MetaData), NewProp_CachedGameState_MetaData) };
void Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFractureRuntimeActivated_SetBit(void* Obj)
{
	((APreFracturedActor*)Obj)->bFractureRuntimeActivated = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFractureRuntimeActivated = { "bFractureRuntimeActivated", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(APreFracturedActor), &Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFractureRuntimeActivated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFractureRuntimeActivated_MetaData), NewProp_bFractureRuntimeActivated_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APreFracturedActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkMeshes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkMeshes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChainScatterImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFreezeAfterChainReaction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_FreezeDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_NeighborDamageRatio,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_ChunkTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoBuildGraph,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_NeighborDistanceThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bAutoSetAnchored,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_AnchorBottomTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_CachedGameState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APreFracturedActor_Statics::NewProp_bFractureRuntimeActivated,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APreFracturedActor_Statics::PropPointers) < 2048);
// ********** End Class APreFracturedActor Property Definitions ************************************
UObject* (*const Z_Construct_UClass_APreFracturedActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ABreakableActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APreFracturedActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APreFracturedActor_Statics::ClassParams = {
	&APreFracturedActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APreFracturedActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APreFracturedActor_Statics::PropPointers),
	0,
	0x009000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APreFracturedActor_Statics::Class_MetaDataParams), Z_Construct_UClass_APreFracturedActor_Statics::Class_MetaDataParams)
};
void APreFracturedActor::StaticRegisterNativesAPreFracturedActor()
{
	UClass* Class = APreFracturedActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_APreFracturedActor_Statics::Funcs));
}
UClass* Z_Construct_UClass_APreFracturedActor()
{
	if (!Z_Registration_Info_UClass_APreFracturedActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APreFracturedActor.OuterSingleton, Z_Construct_UClass_APreFracturedActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APreFracturedActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, APreFracturedActor);
APreFracturedActor::~APreFracturedActor() {}
// ********** End Class APreFracturedActor *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h__Script_Claim_Of_Core_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FPreFracturedChunkData::StaticStruct, Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics::NewStructOps, TEXT("PreFracturedChunkData"),&Z_Registration_Info_UScriptStruct_FPreFracturedChunkData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPreFracturedChunkData), 2247896100U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APreFracturedActor, APreFracturedActor::StaticClass, TEXT("APreFracturedActor"), &Z_Registration_Info_UClass_APreFracturedActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APreFracturedActor), 46127979U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h__Script_Claim_Of_Core_17819802{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h__Script_Claim_Of_Core_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h__Script_Claim_Of_Core_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h__Script_Claim_Of_Core_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
