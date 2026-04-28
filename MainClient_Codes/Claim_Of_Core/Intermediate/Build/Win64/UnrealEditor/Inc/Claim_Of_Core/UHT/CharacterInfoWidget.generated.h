// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CharacterInfoWidget.h"

#ifdef CLAIM_OF_CORE_CharacterInfoWidget_generated_h
#error "CharacterInfoWidget.generated.h already included, missing '#pragma once' in CharacterInfoWidget.h"
#endif
#define CLAIM_OF_CORE_CharacterInfoWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FOnCharacterRoleSelected **********************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_14_DELEGATE \
CLAIM_OF_CORE_API void FOnCharacterRoleSelected_DelegateWrapper(const FMulticastScriptDelegate& OnCharacterRoleSelected, int32 SelectedRoleType);


// ********** End Delegate FOnCharacterRoleSelected ************************************************

// ********** Begin Class UCharacterInfoWidget *****************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnManipulatorClicked); \
	DECLARE_FUNCTION(execOnGuardianClicked); \
	DECLARE_FUNCTION(execOnStrikerClicked);


struct Z_Construct_UClass_UCharacterInfoWidget_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UCharacterInfoWidget_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCharacterInfoWidget(); \
	friend struct ::Z_Construct_UClass_UCharacterInfoWidget_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_UCharacterInfoWidget_NoRegister(); \
public: \
	DECLARE_CLASS2(UCharacterInfoWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_UCharacterInfoWidget_NoRegister) \
	DECLARE_SERIALIZER(UCharacterInfoWidget)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCharacterInfoWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCharacterInfoWidget(UCharacterInfoWidget&&) = delete; \
	UCharacterInfoWidget(const UCharacterInfoWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCharacterInfoWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCharacterInfoWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCharacterInfoWidget) \
	NO_API virtual ~UCharacterInfoWidget();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_16_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_19_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCharacterInfoWidget;

// ********** End Class UCharacterInfoWidget *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
