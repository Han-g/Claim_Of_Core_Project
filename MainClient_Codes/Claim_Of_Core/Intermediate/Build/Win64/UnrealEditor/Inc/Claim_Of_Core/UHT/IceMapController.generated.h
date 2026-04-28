// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Map/IceCave/IceMapController.h"

#ifdef CLAIM_OF_CORE_IceMapController_generated_h
#error "IceMapController.generated.h already included, missing '#pragma once' in IceMapController.h"
#endif
#define CLAIM_OF_CORE_IceMapController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EIceMapPhase : uint8;

// ********** Begin Class AIceMapController ********************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execStartIceMap);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_CALLBACK_WRAPPERS
struct Z_Construct_UClass_AIceMapController_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AIceMapController_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAIceMapController(); \
	friend struct ::Z_Construct_UClass_AIceMapController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_AIceMapController_NoRegister(); \
public: \
	DECLARE_CLASS2(AIceMapController, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_AIceMapController_NoRegister) \
	DECLARE_SERIALIZER(AIceMapController)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AIceMapController(AIceMapController&&) = delete; \
	AIceMapController(const AIceMapController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AIceMapController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AIceMapController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AIceMapController) \
	NO_API virtual ~AIceMapController();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_18_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AIceMapController;

// ********** End Class AIceMapController **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_IceCave_IceMapController_h

// ********** Begin Enum EIceMapPhase **************************************************************
#define FOREACH_ENUM_EICEMAPPHASE(op) \
	op(EIceMapPhase::Phase1) \
	op(EIceMapPhase::Phase2) \
	op(EIceMapPhase::Phase3) 

enum class EIceMapPhase : uint8;
template<> struct TIsUEnumClass<EIceMapPhase> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EIceMapPhase>();
// ********** End Enum EIceMapPhase ****************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
