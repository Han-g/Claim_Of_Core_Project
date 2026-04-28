// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Sub/MyCharacter.h"

#ifdef CLAIM_OF_CORE_MyCharacter_generated_h
#error "MyCharacter.generated.h already included, missing '#pragma once' in MyCharacter.h"
#endif
#define CLAIM_OF_CORE_MyCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class ABaseItem;
class UPrimitiveComponent;
enum class ERecCharacterState : uint8;
enum class ERecRoleType : uint8;
enum class ERecStatusEffectType : uint8;
struct FHitResult;

// ********** Begin ScriptStruct FRoleVisualData ***************************************************
struct Z_Construct_UScriptStruct_FRoleVisualData_Statics;
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_46_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FRoleVisualData_Statics; \
	CLAIM_OF_CORE_API static class UScriptStruct* StaticStruct();


struct FRoleVisualData;
// ********** End ScriptStruct FRoleVisualData *****************************************************

// ********** Begin Class AMyCharacter *************************************************************
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void ServerActivateRoleSkill_Implementation(); \
	virtual void ServerCycleRole_Implementation(); \
	virtual void ServerResetHP_Implementation(); \
	virtual void ServerHeal_Implementation(int32 HealAmount); \
	virtual void ServerApplyDamage_Implementation(int32 DamageAmount); \
	DECLARE_FUNCTION(execGetNetworkAnimationNum); \
	DECLARE_FUNCTION(execOnRep_RoleSkillActive); \
	DECLARE_FUNCTION(execOnRep_RoleType); \
	DECLARE_FUNCTION(execOnRep_CharacterState); \
	DECLARE_FUNCTION(execOnRep_CurrentHP); \
	DECLARE_FUNCTION(execServerActivateRoleSkill); \
	DECLARE_FUNCTION(execServerCycleRole); \
	DECLARE_FUNCTION(execServerResetHP); \
	DECLARE_FUNCTION(execServerHeal); \
	DECLARE_FUNCTION(execServerApplyDamage); \
	DECLARE_FUNCTION(execAnimNotify_AttackHit); \
	DECLARE_FUNCTION(execDropCurrentItem); \
	DECLARE_FUNCTION(execEquipItem); \
	DECLARE_FUNCTION(execSetOverlappingItem); \
	DECLARE_FUNCTION(execOnAttackOverlap); \
	DECLARE_FUNCTION(execApplyKnockback); \
	DECLARE_FUNCTION(execCanReceiveStatusEffect); \
	DECLARE_FUNCTION(execIsStatusEffectImmune); \
	DECLARE_FUNCTION(execIsRoleSkillActive); \
	DECLARE_FUNCTION(execActivateRoleSkill); \
	DECLARE_FUNCTION(execGetRoleType); \
	DECLARE_FUNCTION(execIsDead); \
	DECLARE_FUNCTION(execGetCharacterState); \
	DECLARE_FUNCTION(execGetMaxHP); \
	DECLARE_FUNCTION(execGetCurrentHP); \
	DECLARE_FUNCTION(execResetHP); \
	DECLARE_FUNCTION(execHeal); \
	DECLARE_FUNCTION(execApplyDamage); \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_CALLBACK_WRAPPERS
struct Z_Construct_UClass_AMyCharacter_Statics;
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AMyCharacter_NoRegister();

#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyCharacter(); \
	friend struct ::Z_Construct_UClass_AMyCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CLAIM_OF_CORE_API UClass* ::Z_Construct_UClass_AMyCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AMyCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Claim_Of_Core"), Z_Construct_UClass_AMyCharacter_NoRegister) \
	DECLARE_SERIALIZER(AMyCharacter) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		RoleType=NETFIELD_REP_START, \
		CharacterState, \
		MaxHP, \
		CurrentHP, \
		bRoleSkillActive, \
		NETFIELD_REP_END=bRoleSkillActive	}; \
	DECLARE_VALIDATE_GENERATED_REP_ENUMS(NO_API)


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMyCharacter(AMyCharacter&&) = delete; \
	AMyCharacter(const AMyCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AMyCharacter) \
	NO_API virtual ~AMyCharacter();


#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_58_PROLOG
#define FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_CALLBACK_WRAPPERS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_INCLASS_NO_PURE_DECLS \
	FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h_61_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMyCharacter;

// ********** End Class AMyCharacter ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h

// ********** Begin Enum ERecCharacterState ********************************************************
#define FOREACH_ENUM_ERECCHARACTERSTATE(op) \
	op(ERecCharacterState::Alive) \
	op(ERecCharacterState::Dead) 

enum class ERecCharacterState : uint8;
template<> struct TIsUEnumClass<ERecCharacterState> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERecCharacterState>();
// ********** End Enum ERecCharacterState **********************************************************

// ********** Begin Enum ERecRoleType **************************************************************
#define FOREACH_ENUM_ERECROLETYPE(op) \
	op(ERecRoleType::Striker) \
	op(ERecRoleType::Guardian) \
	op(ERecRoleType::Manipulator) 

enum class ERecRoleType : uint8;
template<> struct TIsUEnumClass<ERecRoleType> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERecRoleType>();
// ********** End Enum ERecRoleType ****************************************************************

// ********** Begin Enum ERecStatusEffectType ******************************************************
#define FOREACH_ENUM_ERECSTATUSEFFECTTYPE(op) \
	op(ERecStatusEffectType::Slow) \
	op(ERecStatusEffectType::Stun) \
	op(ERecStatusEffectType::Knockback) 

enum class ERecStatusEffectType : uint8;
template<> struct TIsUEnumClass<ERecStatusEffectType> { enum { Value = true }; };
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERecStatusEffectType>();
// ********** End Enum ERecStatusEffectType ********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
