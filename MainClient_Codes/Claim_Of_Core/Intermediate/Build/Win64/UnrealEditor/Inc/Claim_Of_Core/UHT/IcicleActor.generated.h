// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Map/IceCave/IcicleActor.h"

#ifdef CLAIM_OF_CORE_IcicleActor_generated_h
#error "IcicleActor.generated.h already included, missing '#pragma once' in IcicleActor.h"
#endif
#define CLAIM_OF_CORE_IcicleActor_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;

// ********** Begin Class AIcicleActor *************************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execStartFalling); \
	DECLARE_FUNCTION(execStartWarning); \
	DECLARE_FUNCTION(execOnIcicleHit);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_CALLBACK_WRAPPERS
struct Z_Construct_UClass_AIcicleActor_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIcicleActor_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAIcicleActor(); \
	friend struct ::Z_Construct_UClass_AIcicleActor_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_AIcicleActor_NoRegister(); \
public: \
	DECLARE_CLASS2(AIcicleActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_AIcicleActor_NoRegister) \
	DECLARE_SERIALIZER(AIcicleActor)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AIcicleActor(AIcicleActor&&) = delete; \
	AIcicleActor(const AIcicleActor&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AIcicleActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AIcicleActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AIcicleActor) \
	NO_API virtual ~AIcicleActor();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_20_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AIcicleActor;

// ********** End Class AIcicleActor ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IcicleActor_h

// ********** Begin Enum EIcicleState **************************************************************
#define FOREACH_ENUM_EICICLESTATE(op) \
	op(EIcicleState::Idle) \
	op(EIcicleState::Warning) \
	op(EIcicleState::Falling) \
	op(EIcicleState::Broken) 

enum class EIcicleState : uint8;
template<> struct TIsUEnumClass<EIcicleState> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EIcicleState>();
// ********** End Enum EIcicleState ****************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
