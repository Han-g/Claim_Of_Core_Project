// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Map/PreFracturedActor.h"

#ifdef CLAIM_OF_CORE_PreFracturedActor_generated_h
#error "PreFracturedActor.generated.h already included, missing '#pragma once' in PreFracturedActor.h"
#endif
#define CLAIM_OF_CORE_PreFracturedActor_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FPreFracturedChunkData ********************************************
struct Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics;
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_13_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FPreFracturedChunkData_Statics; \
	CLAIM_OF_CORE_API static class UScriptStruct* StaticStruct();


struct FPreFracturedChunkData;
// ********** End ScriptStruct FPreFracturedChunkData **********************************************

// ********** Begin Class APreFracturedActor *******************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execBreakChunk); \
	DECLARE_FUNCTION(execApplyDamageToChunk); \
	DECLARE_FUNCTION(execPrepareFracture);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_CALLBACK_WRAPPERS
struct Z_Construct_UClass_APreFracturedActor_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_APreFracturedActor_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPreFracturedActor(); \
	friend struct ::Z_Construct_UClass_APreFracturedActor_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_APreFracturedActor_NoRegister(); \
public: \
	DECLARE_CLASS2(APreFracturedActor, ABreakableActor, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_APreFracturedActor_NoRegister) \
	DECLARE_SERIALIZER(APreFracturedActor)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APreFracturedActor(APreFracturedActor&&) = delete; \
	APreFracturedActor(const APreFracturedActor&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APreFracturedActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APreFracturedActor); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(APreFracturedActor) \
	NO_API virtual ~APreFracturedActor();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_34_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h_37_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APreFracturedActor;

// ********** End Class APreFracturedActor *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_PreFracturedActor_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
