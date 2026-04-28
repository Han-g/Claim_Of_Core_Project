// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameState/InGame_GameState.h"

#ifdef CLAIM_OF_CORE_InGame_GameState_generated_h
#error "InGame_GameState.generated.h already included, missing '#pragma once' in InGame_GameState.h"
#endif
#define CLAIM_OF_CORE_InGame_GameState_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AInGame_GameState ********************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetElapsedPlayTime); \
	DECLARE_FUNCTION(execUpdatePhase);


struct Z_Construct_UClass_AInGame_GameState_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AInGame_GameState_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInGame_GameState(); \
	friend struct ::Z_Construct_UClass_AInGame_GameState_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_AInGame_GameState_NoRegister(); \
public: \
	DECLARE_CLASS2(AInGame_GameState, AGameStateBase, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_AInGame_GameState_NoRegister) \
	DECLARE_SERIALIZER(AInGame_GameState) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		RoundState=NETFIELD_REP_START, \
		ReadyTime, \
		GameTime, \
		CurrentPhase, \
		Phase1Time, \
		Phase2Time, \
		Phase3Time, \
		CurrentReadyTime, \
		CurrentGameTime, \
		NETFIELD_REP_END=CurrentGameTime	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInGame_GameState(AInGame_GameState&&) = delete; \
	AInGame_GameState(const AInGame_GameState&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInGame_GameState); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInGame_GameState); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AInGame_GameState) \
	NO_API virtual ~AInGame_GameState();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_25_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_28_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInGame_GameState;

// ********** End Class AInGame_GameState **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_GameState_InGame_GameState_h

// ********** Begin Enum ERoundState ***************************************************************
#define FOREACH_ENUM_EROUNDSTATE(op) \
	op(ERoundState::Waiting) \
	op(ERoundState::Playing) \
	op(ERoundState::Finished) 

enum class ERoundState : uint8;
template<> struct TIsUEnumClass<ERoundState> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERoundState>();
// ********** End Enum ERoundState *****************************************************************

// ********** Begin Enum EMapPhase *****************************************************************
#define FOREACH_ENUM_EMAPPHASE(op) \
	op(EMapPhase::None) \
	op(EMapPhase::Phase1) \
	op(EMapPhase::Phase2) \
	op(EMapPhase::Phase3) \
	op(EMapPhase::End) 

enum class EMapPhase : uint8;
template<> struct TIsUEnumClass<EMapPhase> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMapPhase>();
// ********** End Enum EMapPhase *******************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
