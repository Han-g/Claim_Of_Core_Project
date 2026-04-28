// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Map/IceCave/IceFloorTile.h"

#ifdef CLAIM_OF_CORE_IceFloorTile_generated_h
#error "IceFloorTile.generated.h already included, missing '#pragma once' in IceFloorTile.h"
#endif
#define CLAIM_OF_CORE_IceFloorTile_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AIceFloorTile ************************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsBroken); \
	DECLARE_FUNCTION(execBreakFloor); \
	DECLARE_FUNCTION(execStartBreaking); \
	DECLARE_FUNCTION(execSetCracked);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_CALLBACK_WRAPPERS
struct Z_Construct_UClass_AIceFloorTile_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIceFloorTile_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAIceFloorTile(); \
	friend struct ::Z_Construct_UClass_AIceFloorTile_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_AIceFloorTile_NoRegister(); \
public: \
	DECLARE_CLASS2(AIceFloorTile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_AIceFloorTile_NoRegister) \
	DECLARE_SERIALIZER(AIceFloorTile)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AIceFloorTile(AIceFloorTile&&) = delete; \
	AIceFloorTile(const AIceFloorTile&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AIceFloorTile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AIceFloorTile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AIceFloorTile) \
	NO_API virtual ~AIceFloorTile();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_19_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AIceFloorTile;

// ********** End Class AIceFloorTile **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceFloorTile_h

// ********** Begin Enum EIceFloorState ************************************************************
#define FOREACH_ENUM_EICEFLOORSTATE(op) \
	op(EIceFloorState::Normal) \
	op(EIceFloorState::Cracked) \
	op(EIceFloorState::Breaking) \
	op(EIceFloorState::Broken) 

enum class EIceFloorState : uint8;
template<> struct TIsUEnumClass<EIceFloorState> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EIceFloorState>();
// ********** End Enum EIceFloorState **************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
