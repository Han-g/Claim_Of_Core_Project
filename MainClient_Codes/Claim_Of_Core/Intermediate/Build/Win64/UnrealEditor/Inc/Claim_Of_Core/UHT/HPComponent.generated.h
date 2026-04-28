// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Sub/HPComponent.h"

#ifdef CLAIM_OF_CORE_HPComponent_generated_h
#error "HPComponent.generated.h already included, missing '#pragma once' in HPComponent.h"
#endif
#define CLAIM_OF_CORE_HPComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FOnHPChangedSignature *************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_7_DELEGATE \
CLAIM_OF_CORE_API void FOnHPChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnHPChangedSignature, int32 NewHP, int32 OldHP);


// ********** End Delegate FOnHPChangedSignature ***************************************************

// ********** Begin Delegate FOnHPZeroSignature ****************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_8_DELEGATE \
CLAIM_OF_CORE_API void FOnHPZeroSignature_DelegateWrapper(const FMulticastScriptDelegate& OnHPZeroSignature);


// ********** End Delegate FOnHPZeroSignature ******************************************************

// ********** Begin Class UHPComponent *************************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ServerHeal_Implementation(int32 HealAmount); \
	virtual void ServerApplyDamage_Implementation(int32 DamageAmount); \
	virtual void ServerResetHP_Implementation(); \
	DECLARE_FUNCTION(execServerHeal); \
	DECLARE_FUNCTION(execServerApplyDamage); \
	DECLARE_FUNCTION(execOnRep_CurrentHP); \
	DECLARE_FUNCTION(execIsDead); \
	DECLARE_FUNCTION(execGetHPPercent); \
	DECLARE_FUNCTION(execGetMaxHP); \
	DECLARE_FUNCTION(execGetCurrentHP); \
	DECLARE_FUNCTION(execServerResetHP); \
	DECLARE_FUNCTION(execResetHP); \
	DECLARE_FUNCTION(execHeal); \
	DECLARE_FUNCTION(execApplyDamage);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_CALLBACK_WRAPPERS
struct Z_Construct_UClass_UHPComponent_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UHPComponent_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHPComponent(); \
	friend struct ::Z_Construct_UClass_UHPComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_UHPComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UHPComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_UHPComponent_NoRegister) \
	DECLARE_SERIALIZER(UHPComponent) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		MaxHP=NETFIELD_REP_START, \
		CurrentHP, \
		NETFIELD_REP_END=CurrentHP	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UHPComponent(UHPComponent&&) = delete; \
	UHPComponent(const UHPComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHPComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHPComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHPComponent) \
	NO_API virtual ~UHPComponent();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_10_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UHPComponent;

// ********** End Class UHPComponent ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_HPComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
