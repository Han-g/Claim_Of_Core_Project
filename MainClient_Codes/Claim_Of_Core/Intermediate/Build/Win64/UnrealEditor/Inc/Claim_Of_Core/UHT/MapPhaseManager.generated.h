// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Map/MapPhaseManager.h"

#ifdef CLAIM_OF_CORE_MapPhaseManager_generated_h
#error "MapPhaseManager.generated.h already included, missing '#pragma once' in MapPhaseManager.h"
#endif
#define CLAIM_OF_CORE_MapPhaseManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AInGame_GameState;
enum class EMapPhase : uint8;
enum class ERoundState : uint8;

// ********** Begin Delegate FOnMapPhaseChangedSignature *******************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_8_DELEGATE \
CLAIM_OF_CORE_API void FOnMapPhaseChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnMapPhaseChangedSignature, EMapPhase NewPhase);


// ********** End Delegate FOnMapPhaseChangedSignature *********************************************

// ********** Begin Delegate FOnRoundStateChangedSignature *****************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_9_DELEGATE \
CLAIM_OF_CORE_API void FOnRoundStateChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnRoundStateChangedSignature, ERoundState NewRoundState);


// ********** End Delegate FOnRoundStateChangedSignature *******************************************

// ********** Begin Class AMapPhaseManager *********************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsRoundPlaying); \
	DECLARE_FUNCTION(execGetCurrentRoundState); \
	DECLARE_FUNCTION(execGetCurrentMapPhase); \
	DECLARE_FUNCTION(execGetInGameGameState); \
	DECLARE_FUNCTION(execInitializeFromGameState);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_CALLBACK_WRAPPERS
struct Z_Construct_UClass_AMapPhaseManager_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AMapPhaseManager_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMapPhaseManager(); \
	friend struct ::Z_Construct_UClass_AMapPhaseManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_AMapPhaseManager_NoRegister(); \
public: \
	DECLARE_CLASS2(AMapPhaseManager, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_AMapPhaseManager_NoRegister) \
	DECLARE_SERIALIZER(AMapPhaseManager)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMapPhaseManager(AMapPhaseManager&&) = delete; \
	AMapPhaseManager(const AMapPhaseManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMapPhaseManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMapPhaseManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMapPhaseManager) \
	NO_API virtual ~AMapPhaseManager();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_11_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMapPhaseManager;

// ********** End Class AMapPhaseManager ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_MapPhaseManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
