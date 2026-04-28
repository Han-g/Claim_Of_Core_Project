// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Map/BreakableActor.h"

#ifdef CLAIM_OF_CORE_BreakableActor_generated_h
#error "BreakableActor.generated.h already included, missing '#pragma once' in BreakableActor.h"
#endif
#define CLAIM_OF_CORE_BreakableActor_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ABreakableActor **********************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsActivated); \
	DECLARE_FUNCTION(execIsBroken); \
	DECLARE_FUNCTION(execBreakActor); \
	DECLARE_FUNCTION(execApplyBreakableDamage); \
	DECLARE_FUNCTION(execResetBreakable); \
	DECLARE_FUNCTION(execActivateBreakable);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ABreakableActor_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ABreakableActor_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABreakableActor(); \
	friend struct ::Z_Construct_UClass_ABreakableActor_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_ABreakableActor_NoRegister(); \
public: \
	DECLARE_CLASS2(ABreakableActor, AActor, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_ABreakableActor_NoRegister) \
	DECLARE_SERIALIZER(ABreakableActor)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ABreakableActor(ABreakableActor&&) = delete; \
	ABreakableActor(const ABreakableActor&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABreakableActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABreakableActor); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ABreakableActor) \
	NO_API virtual ~ABreakableActor();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_16_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ABreakableActor;

// ********** End Class ABreakableActor ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_BreakableActor_h

// ********** Begin Enum EBreakableActorState ******************************************************
#define FOREACH_ENUM_EBREAKABLEACTORSTATE(op) \
	op(EBreakableActorState::Idle) \
	op(EBreakableActorState::Active) \
	op(EBreakableActorState::Breaking) \
	op(EBreakableActorState::Broken) 

enum class EBreakableActorState : uint8;
template<> struct TIsUEnumClass<EBreakableActorState> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EBreakableActorState>();
// ********** End Enum EBreakableActorState ********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
