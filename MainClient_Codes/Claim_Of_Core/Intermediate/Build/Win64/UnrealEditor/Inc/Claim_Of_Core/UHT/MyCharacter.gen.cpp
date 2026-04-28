// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Sub/MyCharacter.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMyCharacter() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ABaseItem_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AMyCharacter();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AMyCharacter_NoRegister();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_ERecRoleType();
CLAIM_OF_CORE_API UEnum* Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType();
CLAIM_OF_CORE_API UScriptStruct* Z_Construct_UScriptStruct_FRoleVisualData();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UAnimInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTextRenderComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ERecCharacterState ********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ERecCharacterState;
static UEnum* ERecCharacterState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ERecCharacterState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ERecCharacterState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("ERecCharacterState"));
	}
	return Z_Registration_Info_UEnum_ERecCharacterState.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERecCharacterState>()
{
	return ERecCharacterState_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Alive.DisplayName", "Alive" },
		{ "Alive.Name", "ERecCharacterState::Alive" },
		{ "BlueprintType", "true" },
		{ "Dead.DisplayName", "Dead" },
		{ "Dead.Name", "ERecCharacterState::Dead" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ERecCharacterState::Alive", (int64)ERecCharacterState::Alive },
		{ "ERecCharacterState::Dead", (int64)ERecCharacterState::Dead },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"ERecCharacterState",
	"ERecCharacterState",
	Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState()
{
	if (!Z_Registration_Info_UEnum_ERecCharacterState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ERecCharacterState.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ERecCharacterState.InnerSingleton;
}
// ********** End Enum ERecCharacterState **********************************************************

// ********** Begin Enum ERecRoleType **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ERecRoleType;
static UEnum* ERecRoleType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ERecRoleType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ERecRoleType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_ERecRoleType, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("ERecRoleType"));
	}
	return Z_Registration_Info_UEnum_ERecRoleType.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERecRoleType>()
{
	return ERecRoleType_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Guardian.DisplayName", "Guardian" },
		{ "Guardian.Name", "ERecRoleType::Guardian" },
		{ "Manipulator.DisplayName", "Manipulator" },
		{ "Manipulator.Name", "ERecRoleType::Manipulator" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
		{ "Striker.DisplayName", "Striker" },
		{ "Striker.Name", "ERecRoleType::Striker" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ERecRoleType::Striker", (int64)ERecRoleType::Striker },
		{ "ERecRoleType::Guardian", (int64)ERecRoleType::Guardian },
		{ "ERecRoleType::Manipulator", (int64)ERecRoleType::Manipulator },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"ERecRoleType",
	"ERecRoleType",
	Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_ERecRoleType()
{
	if (!Z_Registration_Info_UEnum_ERecRoleType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ERecRoleType.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_ERecRoleType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ERecRoleType.InnerSingleton;
}
// ********** End Enum ERecRoleType ****************************************************************

// ********** Begin Enum ERecStatusEffectType ******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ERecStatusEffectType;
static UEnum* ERecStatusEffectType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ERecStatusEffectType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ERecStatusEffectType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("ERecStatusEffectType"));
	}
	return Z_Registration_Info_UEnum_ERecStatusEffectType.OuterSingleton;
}
template<> CLAIM_OF_CORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ERecStatusEffectType>()
{
	return ERecStatusEffectType_StaticEnum();
}
struct Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Knockback.DisplayName", "Knockback" },
		{ "Knockback.Name", "ERecStatusEffectType::Knockback" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
		{ "Slow.DisplayName", "Slow" },
		{ "Slow.Name", "ERecStatusEffectType::Slow" },
		{ "Stun.DisplayName", "Stun" },
		{ "Stun.Name", "ERecStatusEffectType::Stun" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ERecStatusEffectType::Slow", (int64)ERecStatusEffectType::Slow },
		{ "ERecStatusEffectType::Stun", (int64)ERecStatusEffectType::Stun },
		{ "ERecStatusEffectType::Knockback", (int64)ERecStatusEffectType::Knockback },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	"ERecStatusEffectType",
	"ERecStatusEffectType",
	Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType()
{
	if (!Z_Registration_Info_UEnum_ERecStatusEffectType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ERecStatusEffectType.InnerSingleton, Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ERecStatusEffectType.InnerSingleton;
}
// ********** End Enum ERecStatusEffectType ********************************************************

// ********** Begin ScriptStruct FRoleVisualData ***************************************************
struct Z_Construct_UScriptStruct_FRoleVisualData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FRoleVisualData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FRoleVisualData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "Category", "RoleVisualData" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimBPClass_MetaData[] = {
		{ "Category", "RoleVisualData" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackMontage_MetaData[] = {
		{ "Category", "RoleVisualData" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FRoleVisualData constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FClassPropertyParams NewProp_AnimBPClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackMontage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FRoleVisualData constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRoleVisualData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FRoleVisualData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FRoleVisualData;
class UScriptStruct* FRoleVisualData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FRoleVisualData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FRoleVisualData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRoleVisualData, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("RoleVisualData"));
	}
	return Z_Registration_Info_UScriptStruct_FRoleVisualData.OuterSingleton;
	}

// ********** Begin ScriptStruct FRoleVisualData Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FRoleVisualData_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x0114000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRoleVisualData, Mesh), Z_Construct_UClass_USkeletalMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UScriptStruct_FRoleVisualData_Statics::NewProp_AnimBPClass = { "AnimBPClass", nullptr, (EPropertyFlags)0x0014000000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRoleVisualData, AnimBPClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UAnimInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimBPClass_MetaData), NewProp_AnimBPClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FRoleVisualData_Statics::NewProp_AttackMontage = { "AttackMontage", nullptr, (EPropertyFlags)0x0114000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRoleVisualData, AttackMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackMontage_MetaData), NewProp_AttackMontage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRoleVisualData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoleVisualData_Statics::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoleVisualData_Statics::NewProp_AnimBPClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoleVisualData_Statics::NewProp_AttackMontage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoleVisualData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FRoleVisualData Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRoleVisualData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	&NewStructOps,
	"RoleVisualData",
	Z_Construct_UScriptStruct_FRoleVisualData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoleVisualData_Statics::PropPointers),
	sizeof(FRoleVisualData),
	alignof(FRoleVisualData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoleVisualData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRoleVisualData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FRoleVisualData()
{
	if (!Z_Registration_Info_UScriptStruct_FRoleVisualData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FRoleVisualData.InnerSingleton, Z_Construct_UScriptStruct_FRoleVisualData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FRoleVisualData.InnerSingleton);
}
// ********** End ScriptStruct FRoleVisualData *****************************************************

// ********** Begin Class AMyCharacter Function ActivateRoleSkill **********************************
struct Z_Construct_UFunction_AMyCharacter_ActivateRoleSkill_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RoleSkill" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ActivateRoleSkill constinit property declarations *********************
// ********** End Function ActivateRoleSkill constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ActivateRoleSkill_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ActivateRoleSkill", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ActivateRoleSkill_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ActivateRoleSkill_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_ActivateRoleSkill()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ActivateRoleSkill_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execActivateRoleSkill)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ActivateRoleSkill();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ActivateRoleSkill ************************************

// ********** Begin Class AMyCharacter Function AnimNotify_AttackHit *******************************
struct Z_Construct_UFunction_AMyCharacter_AnimNotify_AttackHit_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AnimNotify_AttackHit constinit property declarations ******************
// ********** End Function AnimNotify_AttackHit constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_AnimNotify_AttackHit_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "AnimNotify_AttackHit", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_AnimNotify_AttackHit_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_AnimNotify_AttackHit_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_AnimNotify_AttackHit()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_AnimNotify_AttackHit_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execAnimNotify_AttackHit)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AnimNotify_AttackHit();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function AnimNotify_AttackHit *********************************

// ********** Begin Class AMyCharacter Function ApplyDamage ****************************************
struct Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics
{
	struct MyCharacter_eventApplyDamage_Parms
	{
		int32 DamageAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyDamage constinit property declarations ***************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyDamage constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyDamage Property Definitions **************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventApplyDamage_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::PropPointers) < 2048);
// ********** End Function ApplyDamage Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ApplyDamage", 	Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::MyCharacter_eventApplyDamage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::MyCharacter_eventApplyDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_ApplyDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ApplyDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execApplyDamage)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyDamage(Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ApplyDamage ******************************************

// ********** Begin Class AMyCharacter Function ApplyKnockback *************************************
struct Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics
{
	struct MyCharacter_eventApplyKnockback_Parms
	{
		AActor* Attacker;
		float KnockbackStrength;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyKnockback constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Attacker;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_KnockbackStrength;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyKnockback constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyKnockback Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::NewProp_Attacker = { "Attacker", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventApplyKnockback_Parms, Attacker), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::NewProp_KnockbackStrength = { "KnockbackStrength", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventApplyKnockback_Parms, KnockbackStrength), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::NewProp_Attacker,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::NewProp_KnockbackStrength,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::PropPointers) < 2048);
// ********** End Function ApplyKnockback Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ApplyKnockback", 	Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::MyCharacter_eventApplyKnockback_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::MyCharacter_eventApplyKnockback_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_ApplyKnockback()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ApplyKnockback_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execApplyKnockback)
{
	P_GET_OBJECT(AActor,Z_Param_Attacker);
	P_GET_PROPERTY(FFloatProperty,Z_Param_KnockbackStrength);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyKnockback(Z_Param_Attacker,Z_Param_KnockbackStrength);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ApplyKnockback ***************************************

// ********** Begin Class AMyCharacter Function CanReceiveStatusEffect *****************************
struct Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics
{
	struct MyCharacter_eventCanReceiveStatusEffect_Parms
	{
		ERecStatusEffectType InStatusEffect;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Status" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CanReceiveStatusEffect constinit property declarations ****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_InStatusEffect_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_InStatusEffect;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CanReceiveStatusEffect constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CanReceiveStatusEffect Property Definitions ***************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_InStatusEffect_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_InStatusEffect = { "InStatusEffect", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventCanReceiveStatusEffect_Parms, InStatusEffect), Z_Construct_UEnum_Claim_Of_Core_ERecStatusEffectType, METADATA_PARAMS(0, nullptr) }; // 2446554896
void Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MyCharacter_eventCanReceiveStatusEffect_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyCharacter_eventCanReceiveStatusEffect_Parms), &Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_InStatusEffect_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_InStatusEffect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::PropPointers) < 2048);
// ********** End Function CanReceiveStatusEffect Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "CanReceiveStatusEffect", 	Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::MyCharacter_eventCanReceiveStatusEffect_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::MyCharacter_eventCanReceiveStatusEffect_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execCanReceiveStatusEffect)
{
	P_GET_ENUM(ERecStatusEffectType,Z_Param_InStatusEffect);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->CanReceiveStatusEffect(ERecStatusEffectType(Z_Param_InStatusEffect));
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function CanReceiveStatusEffect *******************************

// ********** Begin Class AMyCharacter Function DoJumpEnd ******************************************
struct Z_Construct_UFunction_AMyCharacter_DoJumpEnd_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpEnd constinit property declarations *****************************
// ********** End Function DoJumpEnd constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_DoJumpEnd_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "DoJumpEnd", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoJumpEnd_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_DoJumpEnd_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_DoJumpEnd()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_DoJumpEnd_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execDoJumpEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpEnd();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function DoJumpEnd ********************************************

// ********** Begin Class AMyCharacter Function DoJumpStart ****************************************
struct Z_Construct_UFunction_AMyCharacter_DoJumpStart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpStart constinit property declarations ***************************
// ********** End Function DoJumpStart constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_DoJumpStart_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "DoJumpStart", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoJumpStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_DoJumpStart_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_DoJumpStart()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_DoJumpStart_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execDoJumpStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpStart();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function DoJumpStart ******************************************

// ********** Begin Class AMyCharacter Function DoLook *********************************************
struct Z_Construct_UFunction_AMyCharacter_DoLook_Statics
{
	struct MyCharacter_eventDoLook_Parms
	{
		float Yaw;
		float Pitch;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DoLook constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Yaw;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Pitch;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoLook constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoLook Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCharacter_DoLook_Statics::NewProp_Yaw = { "Yaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventDoLook_Parms, Yaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCharacter_DoLook_Statics::NewProp_Pitch = { "Pitch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventDoLook_Parms, Pitch), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_DoLook_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_DoLook_Statics::NewProp_Yaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_DoLook_Statics::NewProp_Pitch,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoLook_Statics::PropPointers) < 2048);
// ********** End Function DoLook Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_DoLook_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "DoLook", 	Z_Construct_UFunction_AMyCharacter_DoLook_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoLook_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_DoLook_Statics::MyCharacter_eventDoLook_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoLook_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_DoLook_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_DoLook_Statics::MyCharacter_eventDoLook_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_DoLook()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_DoLook_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execDoLook)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Yaw);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Pitch);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoLook(Z_Param_Yaw,Z_Param_Pitch);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function DoLook ***********************************************

// ********** Begin Class AMyCharacter Function DoMove *********************************************
struct Z_Construct_UFunction_AMyCharacter_DoMove_Statics
{
	struct MyCharacter_eventDoMove_Parms
	{
		float Right;
		float Forward;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DoMove constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Right;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Forward;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoMove constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoMove Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCharacter_DoMove_Statics::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventDoMove_Parms, Right), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyCharacter_DoMove_Statics::NewProp_Forward = { "Forward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventDoMove_Parms, Forward), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_DoMove_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_DoMove_Statics::NewProp_Right,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_DoMove_Statics::NewProp_Forward,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoMove_Statics::PropPointers) < 2048);
// ********** End Function DoMove Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_DoMove_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "DoMove", 	Z_Construct_UFunction_AMyCharacter_DoMove_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoMove_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_DoMove_Statics::MyCharacter_eventDoMove_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DoMove_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_DoMove_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_DoMove_Statics::MyCharacter_eventDoMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_DoMove()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_DoMove_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execDoMove)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Right);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Forward);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoMove(Z_Param_Right,Z_Param_Forward);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function DoMove ***********************************************

// ********** Begin Class AMyCharacter Function DropCurrentItem ************************************
struct Z_Construct_UFunction_AMyCharacter_DropCurrentItem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DropCurrentItem constinit property declarations ***********************
// ********** End Function DropCurrentItem constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_DropCurrentItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "DropCurrentItem", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_DropCurrentItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_DropCurrentItem_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_DropCurrentItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_DropCurrentItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execDropCurrentItem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DropCurrentItem();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function DropCurrentItem **************************************

// ********** Begin Class AMyCharacter Function EquipItem ******************************************
struct Z_Construct_UFunction_AMyCharacter_EquipItem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function EquipItem constinit property declarations *****************************
// ********** End Function EquipItem constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_EquipItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "EquipItem", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_EquipItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_EquipItem_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_EquipItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_EquipItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execEquipItem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->EquipItem();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function EquipItem ********************************************

// ********** Begin Class AMyCharacter Function GetCharacterState **********************************
struct Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics
{
	struct MyCharacter_eventGetCharacterState_Parms
	{
		ERecCharacterState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "State" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCharacterState constinit property declarations *********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCharacterState constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCharacterState Property Definitions ********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventGetCharacterState_Parms, ReturnValue), Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState, METADATA_PARAMS(0, nullptr) }; // 1614730820
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::PropPointers) < 2048);
// ********** End Function GetCharacterState Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "GetCharacterState", 	Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::MyCharacter_eventGetCharacterState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::MyCharacter_eventGetCharacterState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_GetCharacterState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_GetCharacterState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execGetCharacterState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ERecCharacterState*)Z_Param__Result=P_THIS->GetCharacterState();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function GetCharacterState ************************************

// ********** Begin Class AMyCharacter Function GetCurrentHP ***************************************
struct Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics
{
	struct MyCharacter_eventGetCurrentHP_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentHP constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentHP constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentHP Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventGetCurrentHP_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentHP Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "GetCurrentHP", 	Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::MyCharacter_eventGetCurrentHP_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::MyCharacter_eventGetCurrentHP_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_GetCurrentHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_GetCurrentHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execGetCurrentHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCurrentHP();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function GetCurrentHP *****************************************

// ********** Begin Class AMyCharacter Function GetMaxHP *******************************************
struct Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics
{
	struct MyCharacter_eventGetMaxHP_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMaxHP constinit property declarations ******************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMaxHP constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMaxHP Property Definitions *****************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventGetMaxHP_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::PropPointers) < 2048);
// ********** End Function GetMaxHP Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "GetMaxHP", 	Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::MyCharacter_eventGetMaxHP_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::MyCharacter_eventGetMaxHP_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_GetMaxHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_GetMaxHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execGetMaxHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetMaxHP();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function GetMaxHP *********************************************

// ********** Begin Class AMyCharacter Function GetNetworkAnimationNum *****************************
struct Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics
{
	struct MyCharacter_eventGetNetworkAnimationNum_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Network|Animation" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetNetworkAnimationNum constinit property declarations ****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetNetworkAnimationNum constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetNetworkAnimationNum Property Definitions ***************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventGetNetworkAnimationNum_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::PropPointers) < 2048);
// ********** End Function GetNetworkAnimationNum Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "GetNetworkAnimationNum", 	Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::MyCharacter_eventGetNetworkAnimationNum_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::MyCharacter_eventGetNetworkAnimationNum_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execGetNetworkAnimationNum)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetNetworkAnimationNum();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function GetNetworkAnimationNum *******************************

// ********** Begin Class AMyCharacter Function GetRoleType ****************************************
struct Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics
{
	struct MyCharacter_eventGetRoleType_Parms
	{
		ERecRoleType ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Role" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRoleType constinit property declarations ***************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRoleType constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRoleType Property Definitions **************************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventGetRoleType_Parms, ReturnValue), Z_Construct_UEnum_Claim_Of_Core_ERecRoleType, METADATA_PARAMS(0, nullptr) }; // 3141253188
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::PropPointers) < 2048);
// ********** End Function GetRoleType Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "GetRoleType", 	Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::MyCharacter_eventGetRoleType_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::MyCharacter_eventGetRoleType_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_GetRoleType()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_GetRoleType_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execGetRoleType)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ERecRoleType*)Z_Param__Result=P_THIS->GetRoleType();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function GetRoleType ******************************************

// ********** Begin Class AMyCharacter Function Heal ***********************************************
struct Z_Construct_UFunction_AMyCharacter_Heal_Statics
{
	struct MyCharacter_eventHeal_Parms
	{
		int32 HealAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Heal constinit property declarations **********************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_HealAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Heal constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Heal Property Definitions *********************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_Heal_Statics::NewProp_HealAmount = { "HealAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventHeal_Parms, HealAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_Heal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_Heal_Statics::NewProp_HealAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_Heal_Statics::PropPointers) < 2048);
// ********** End Function Heal Property Definitions ***********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_Heal_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "Heal", 	Z_Construct_UFunction_AMyCharacter_Heal_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_Heal_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_Heal_Statics::MyCharacter_eventHeal_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_Heal_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_Heal_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_Heal_Statics::MyCharacter_eventHeal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_Heal()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_Heal_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execHeal)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_HealAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Heal(Z_Param_HealAmount);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function Heal *************************************************

// ********** Begin Class AMyCharacter Function IsDead *********************************************
struct Z_Construct_UFunction_AMyCharacter_IsDead_Statics
{
	struct MyCharacter_eventIsDead_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "State" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsDead constinit property declarations ********************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsDead constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsDead Property Definitions *******************************************
void Z_Construct_UFunction_AMyCharacter_IsDead_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MyCharacter_eventIsDead_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyCharacter_IsDead_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyCharacter_eventIsDead_Parms), &Z_Construct_UFunction_AMyCharacter_IsDead_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_IsDead_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_IsDead_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsDead_Statics::PropPointers) < 2048);
// ********** End Function IsDead Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_IsDead_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "IsDead", 	Z_Construct_UFunction_AMyCharacter_IsDead_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsDead_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_IsDead_Statics::MyCharacter_eventIsDead_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsDead_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_IsDead_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_IsDead_Statics::MyCharacter_eventIsDead_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_IsDead()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_IsDead_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execIsDead)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsDead();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function IsDead ***********************************************

// ********** Begin Class AMyCharacter Function IsRoleSkillActive **********************************
struct Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics
{
	struct MyCharacter_eventIsRoleSkillActive_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RoleSkill" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsRoleSkillActive constinit property declarations *********************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsRoleSkillActive constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsRoleSkillActive Property Definitions ********************************
void Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MyCharacter_eventIsRoleSkillActive_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyCharacter_eventIsRoleSkillActive_Parms), &Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::PropPointers) < 2048);
// ********** End Function IsRoleSkillActive Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "IsRoleSkillActive", 	Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::MyCharacter_eventIsRoleSkillActive_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::MyCharacter_eventIsRoleSkillActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execIsRoleSkillActive)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsRoleSkillActive();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function IsRoleSkillActive ************************************

// ********** Begin Class AMyCharacter Function IsStatusEffectImmune *******************************
struct Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics
{
	struct MyCharacter_eventIsStatusEffectImmune_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RoleSkill" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsStatusEffectImmune constinit property declarations ******************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsStatusEffectImmune constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsStatusEffectImmune Property Definitions *****************************
void Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MyCharacter_eventIsStatusEffectImmune_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyCharacter_eventIsStatusEffectImmune_Parms), &Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::PropPointers) < 2048);
// ********** End Function IsStatusEffectImmune Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "IsStatusEffectImmune", 	Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::MyCharacter_eventIsStatusEffectImmune_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::MyCharacter_eventIsStatusEffectImmune_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execIsStatusEffectImmune)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsStatusEffectImmune();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function IsStatusEffectImmune *********************************

// ********** Begin Class AMyCharacter Function OnAttackOverlap ************************************
struct Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics
{
	struct MyCharacter_eventOnAttackOverlap_Parms
	{
		UPrimitiveComponent* OverlappedComponent;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		int32 OtherBodyIndex;
		bool bFromSweep;
		FHitResult SweepResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnAttackOverlap constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static void NewProp_bFromSweep_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SweepResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnAttackOverlap constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnAttackOverlap Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OverlappedComponent = { "OverlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventOnAttackOverlap_Parms, OverlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlappedComponent_MetaData), NewProp_OverlappedComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventOnAttackOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventOnAttackOverlap_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventOnAttackOverlap_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_bFromSweep_SetBit(void* Obj)
{
	((MyCharacter_eventOnAttackOverlap_Parms*)Obj)->bFromSweep = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyCharacter_eventOnAttackOverlap_Parms), &Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventOnAttackOverlap_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SweepResult_MetaData), NewProp_SweepResult_MetaData) }; // 222120718
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OverlappedComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_OtherBodyIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_bFromSweep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::NewProp_SweepResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::PropPointers) < 2048);
// ********** End Function OnAttackOverlap Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "OnAttackOverlap", 	Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::MyCharacter_eventOnAttackOverlap_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::MyCharacter_eventOnAttackOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_OnAttackOverlap()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_OnAttackOverlap_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execOnAttackOverlap)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_GET_UBOOL(Z_Param_bFromSweep);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnAttackOverlap(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function OnAttackOverlap **************************************

// ********** Begin Class AMyCharacter Function OnRep_CharacterState *******************************
struct Z_Construct_UFunction_AMyCharacter_OnRep_CharacterState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_CharacterState constinit property declarations ******************
// ********** End Function OnRep_CharacterState constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_OnRep_CharacterState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "OnRep_CharacterState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_OnRep_CharacterState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_OnRep_CharacterState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_OnRep_CharacterState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_OnRep_CharacterState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execOnRep_CharacterState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_CharacterState();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function OnRep_CharacterState *********************************

// ********** Begin Class AMyCharacter Function OnRep_CurrentHP ************************************
struct Z_Construct_UFunction_AMyCharacter_OnRep_CurrentHP_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_CurrentHP constinit property declarations ***********************
// ********** End Function OnRep_CurrentHP constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_OnRep_CurrentHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "OnRep_CurrentHP", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_OnRep_CurrentHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_OnRep_CurrentHP_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_OnRep_CurrentHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_OnRep_CurrentHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execOnRep_CurrentHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_CurrentHP();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function OnRep_CurrentHP **************************************

// ********** Begin Class AMyCharacter Function OnRep_RoleSkillActive ******************************
struct Z_Construct_UFunction_AMyCharacter_OnRep_RoleSkillActive_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_RoleSkillActive constinit property declarations *****************
// ********** End Function OnRep_RoleSkillActive constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_OnRep_RoleSkillActive_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "OnRep_RoleSkillActive", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_OnRep_RoleSkillActive_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_OnRep_RoleSkillActive_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_OnRep_RoleSkillActive()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_OnRep_RoleSkillActive_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execOnRep_RoleSkillActive)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_RoleSkillActive();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function OnRep_RoleSkillActive ********************************

// ********** Begin Class AMyCharacter Function OnRep_RoleType *************************************
struct Z_Construct_UFunction_AMyCharacter_OnRep_RoleType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRep_RoleType constinit property declarations ************************
// ********** End Function OnRep_RoleType constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_OnRep_RoleType_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "OnRep_RoleType", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_OnRep_RoleType_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_OnRep_RoleType_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_OnRep_RoleType()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_OnRep_RoleType_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execOnRep_RoleType)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_RoleType();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function OnRep_RoleType ***************************************

// ********** Begin Class AMyCharacter Function ResetHP ********************************************
struct Z_Construct_UFunction_AMyCharacter_ResetHP_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ResetHP constinit property declarations *******************************
// ********** End Function ResetHP constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ResetHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ResetHP", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ResetHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ResetHP_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_ResetHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ResetHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execResetHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetHP();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ResetHP **********************************************

// ********** Begin Class AMyCharacter Function ServerActivateRoleSkill ****************************
static FName NAME_AMyCharacter_ServerActivateRoleSkill = FName(TEXT("ServerActivateRoleSkill"));
void AMyCharacter::ServerActivateRoleSkill()
{
	UFunction* Func = FindFunctionChecked(NAME_AMyCharacter_ServerActivateRoleSkill);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AMyCharacter_ServerActivateRoleSkill_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerActivateRoleSkill constinit property declarations ***************
// ********** End Function ServerActivateRoleSkill constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ServerActivateRoleSkill_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ServerActivateRoleSkill", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerActivateRoleSkill_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ServerActivateRoleSkill_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_ServerActivateRoleSkill()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ServerActivateRoleSkill_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execServerActivateRoleSkill)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerActivateRoleSkill_Implementation();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ServerActivateRoleSkill ******************************

// ********** Begin Class AMyCharacter Function ServerApplyDamage **********************************
struct MyCharacter_eventServerApplyDamage_Parms
{
	int32 DamageAmount;
};
static FName NAME_AMyCharacter_ServerApplyDamage = FName(TEXT("ServerApplyDamage"));
void AMyCharacter::ServerApplyDamage(int32 DamageAmount)
{
	MyCharacter_eventServerApplyDamage_Parms Parms;
	Parms.DamageAmount=DamageAmount;
	UFunction* Func = FindFunctionChecked(NAME_AMyCharacter_ServerApplyDamage);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerApplyDamage constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerApplyDamage constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerApplyDamage Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventServerApplyDamage_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::PropPointers) < 2048);
// ********** End Function ServerApplyDamage Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ServerApplyDamage", 	Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::PropPointers), 
sizeof(MyCharacter_eventServerApplyDamage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(MyCharacter_eventServerApplyDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_ServerApplyDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ServerApplyDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execServerApplyDamage)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerApplyDamage_Implementation(Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ServerApplyDamage ************************************

// ********** Begin Class AMyCharacter Function ServerCycleRole ************************************
static FName NAME_AMyCharacter_ServerCycleRole = FName(TEXT("ServerCycleRole"));
void AMyCharacter::ServerCycleRole()
{
	UFunction* Func = FindFunctionChecked(NAME_AMyCharacter_ServerCycleRole);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AMyCharacter_ServerCycleRole_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerCycleRole constinit property declarations ***********************
// ********** End Function ServerCycleRole constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ServerCycleRole_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ServerCycleRole", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerCycleRole_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ServerCycleRole_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_ServerCycleRole()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ServerCycleRole_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execServerCycleRole)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerCycleRole_Implementation();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ServerCycleRole **************************************

// ********** Begin Class AMyCharacter Function ServerHeal *****************************************
struct MyCharacter_eventServerHeal_Parms
{
	int32 HealAmount;
};
static FName NAME_AMyCharacter_ServerHeal = FName(TEXT("ServerHeal"));
void AMyCharacter::ServerHeal(int32 HealAmount)
{
	MyCharacter_eventServerHeal_Parms Parms;
	Parms.HealAmount=HealAmount;
	UFunction* Func = FindFunctionChecked(NAME_AMyCharacter_ServerHeal);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerHeal constinit property declarations ****************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_HealAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ServerHeal constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ServerHeal Property Definitions ***************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::NewProp_HealAmount = { "HealAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventServerHeal_Parms, HealAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::NewProp_HealAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::PropPointers) < 2048);
// ********** End Function ServerHeal Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ServerHeal", 	Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::PropPointers), 
sizeof(MyCharacter_eventServerHeal_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(MyCharacter_eventServerHeal_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_ServerHeal()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ServerHeal_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execServerHeal)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_HealAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerHeal_Implementation(Z_Param_HealAmount);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ServerHeal *******************************************

// ********** Begin Class AMyCharacter Function ServerResetHP **************************************
static FName NAME_AMyCharacter_ServerResetHP = FName(TEXT("ServerResetHP"));
void AMyCharacter::ServerResetHP()
{
	UFunction* Func = FindFunctionChecked(NAME_AMyCharacter_ServerResetHP);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AMyCharacter_ServerResetHP_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ServerResetHP constinit property declarations *************************
// ********** End Function ServerResetHP constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_ServerResetHP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "ServerResetHP", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_ServerResetHP_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_ServerResetHP_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMyCharacter_ServerResetHP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_ServerResetHP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execServerResetHP)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerResetHP_Implementation();
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function ServerResetHP ****************************************

// ********** Begin Class AMyCharacter Function SetOverlappingItem *********************************
struct Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics
{
	struct MyCharacter_eventSetOverlappingItem_Parms
	{
		ABaseItem* Item;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetOverlappingItem constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Item;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetOverlappingItem constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetOverlappingItem Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::NewProp_Item = { "Item", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyCharacter_eventSetOverlappingItem_Parms, Item), Z_Construct_UClass_ABaseItem_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::NewProp_Item,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::PropPointers) < 2048);
// ********** End Function SetOverlappingItem Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMyCharacter, nullptr, "SetOverlappingItem", 	Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::MyCharacter_eventSetOverlappingItem_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::MyCharacter_eventSetOverlappingItem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyCharacter_SetOverlappingItem()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyCharacter_SetOverlappingItem_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyCharacter::execSetOverlappingItem)
{
	P_GET_OBJECT(ABaseItem,Z_Param_Item);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetOverlappingItem(Z_Param_Item);
	P_NATIVE_END;
}
// ********** End Class AMyCharacter Function SetOverlappingItem ***********************************

// ********** Begin Class AMyCharacter *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMyCharacter;
UClass* AMyCharacter::GetPrivateStaticClass()
{
	using TClass = AMyCharacter;
	if (!Z_Registration_Info_UClass_AMyCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MyCharacter"),
			Z_Registration_Info_UClass_AMyCharacter.InnerSingleton,
			StaticRegisterNativesAMyCharacter,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AMyCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_AMyCharacter_NoRegister()
{
	return AMyCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMyCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Sub/MyCharacter.h" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HPTextComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoleTextComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathUITextComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseLookAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_KnockbackAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoleType_MetaData[] = {
		{ "Category", "Role" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterState_MetaData[] = {
		{ "Category", "State" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StrikerVisual_MetaData[] = {
		{ "Category", "Role|Visual" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GuardianVisual_MetaData[] = {
		{ "Category", "Role|Visual" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ManipulatorVisual_MetaData[] = {
		{ "Category", "Role|Visual" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlappingItem_MetaData[] = {
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentItem_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHP_MetaData[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "HP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseWalkSpeed_MetaData[] = {
		{ "Category", "Role" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseJumpMaxCount_MetaData[] = {
		{ "Category", "Role" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRoleSkillActive_MetaData[] = {
		{ "Category", "RoleSkill" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DashDuration_MetaData[] = {
		{ "Category", "RoleSkill|Striker" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DashSpeedMultiplier_MetaData[] = {
		{ "Category", "RoleSkill|Striker" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DashDamageMultiplier_MetaData[] = {
		{ "Category", "RoleSkill|Striker" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HardDuration_MetaData[] = {
		{ "Category", "RoleSkill|Guardian" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HardSpeedMultiplier_MetaData[] = {
		{ "Category", "RoleSkill|Guardian" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HardScaleMultiplier_MetaData[] = {
		{ "Category", "RoleSkill|Guardian" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HardDamageTakenMultiplier_MetaData[] = {
		{ "Category", "RoleSkill|Guardian" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DBJPDuration_MetaData[] = {
		{ "Category", "RoleSkill|Manipulator" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpectateMoveSpeed_MetaData[] = {
		{ "Category", "Spectate" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpectateVerticalSpeed_MetaData[] = {
		{ "Category", "Spectate" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpectateInputUnlockDelay_MetaData[] = {
		{ "Category", "Death" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpectatingUITextDuration_MetaData[] = {
		{ "Category", "Death" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPThreshold_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLowHPEffectActive_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPPostProcessBlendWeight_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPVignetteIntensity_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPSaturation_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPPulseSpeed_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPPulseVignetteAmplitude_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPPulseBlendAmplitude_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LowHPSceneTint_MetaData[] = {
		{ "Category", "LowHP" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathCameraTargetArmLength_MetaData[] = {
		{ "Category", "DeathCamera" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathCameraInterpSpeed_MetaData[] = {
		{ "Category", "DeathCamera" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathShakeDuration_MetaData[] = {
		{ "Category", "DeathCameraShake" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathShakeAmplitude_MetaData[] = {
		{ "Category", "DeathCameraShake" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathShakeFrequency_MetaData[] = {
		{ "Category", "DeathCameraShake" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDeathCameraShaking_MetaData[] = {
		{ "Category", "DeathCameraShake" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathShakeElapsed_MetaData[] = {
		{ "Category", "DeathCameraShake" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkAnimationNum_MetaData[] = {
		{ "Category", "Network|Animation" },
		{ "ModuleRelativePath", "Sub/MyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMyCharacter constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HPTextComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RoleTextComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DeathUITextComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MouseLookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_KnockbackAction;
	static const UECodeGen_Private::FBytePropertyParams NewProp_RoleType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_RoleType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CharacterState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CharacterState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StrikerVisual;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GuardianVisual;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ManipulatorVisual;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappingItem;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentItem;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxHP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseWalkSpeed;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BaseJumpMaxCount;
	static void NewProp_bRoleSkillActive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRoleSkillActive;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DashDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DashSpeedMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DashDamageMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HardDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HardSpeedMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HardScaleMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HardDamageTakenMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DBJPDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpectateMoveSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpectateVerticalSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpectateInputUnlockDelay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpectatingUITextDuration;
	static const UECodeGen_Private::FIntPropertyParams NewProp_LowHPThreshold;
	static void NewProp_bLowHPEffectActive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLowHPEffectActive;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LowHPPostProcessBlendWeight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LowHPVignetteIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LowHPSaturation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LowHPPulseSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LowHPPulseVignetteAmplitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LowHPPulseBlendAmplitude;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LowHPSceneTint;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathCameraTargetArmLength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathCameraInterpSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathShakeDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathShakeAmplitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathShakeFrequency;
	static void NewProp_bDeathCameraShaking_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDeathCameraShaking;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathShakeElapsed;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NetworkAnimationNum;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMyCharacter constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ActivateRoleSkill"), .Pointer = &AMyCharacter::execActivateRoleSkill },
		{ .NameUTF8 = UTF8TEXT("AnimNotify_AttackHit"), .Pointer = &AMyCharacter::execAnimNotify_AttackHit },
		{ .NameUTF8 = UTF8TEXT("ApplyDamage"), .Pointer = &AMyCharacter::execApplyDamage },
		{ .NameUTF8 = UTF8TEXT("ApplyKnockback"), .Pointer = &AMyCharacter::execApplyKnockback },
		{ .NameUTF8 = UTF8TEXT("CanReceiveStatusEffect"), .Pointer = &AMyCharacter::execCanReceiveStatusEffect },
		{ .NameUTF8 = UTF8TEXT("DoJumpEnd"), .Pointer = &AMyCharacter::execDoJumpEnd },
		{ .NameUTF8 = UTF8TEXT("DoJumpStart"), .Pointer = &AMyCharacter::execDoJumpStart },
		{ .NameUTF8 = UTF8TEXT("DoLook"), .Pointer = &AMyCharacter::execDoLook },
		{ .NameUTF8 = UTF8TEXT("DoMove"), .Pointer = &AMyCharacter::execDoMove },
		{ .NameUTF8 = UTF8TEXT("DropCurrentItem"), .Pointer = &AMyCharacter::execDropCurrentItem },
		{ .NameUTF8 = UTF8TEXT("EquipItem"), .Pointer = &AMyCharacter::execEquipItem },
		{ .NameUTF8 = UTF8TEXT("GetCharacterState"), .Pointer = &AMyCharacter::execGetCharacterState },
		{ .NameUTF8 = UTF8TEXT("GetCurrentHP"), .Pointer = &AMyCharacter::execGetCurrentHP },
		{ .NameUTF8 = UTF8TEXT("GetMaxHP"), .Pointer = &AMyCharacter::execGetMaxHP },
		{ .NameUTF8 = UTF8TEXT("GetNetworkAnimationNum"), .Pointer = &AMyCharacter::execGetNetworkAnimationNum },
		{ .NameUTF8 = UTF8TEXT("GetRoleType"), .Pointer = &AMyCharacter::execGetRoleType },
		{ .NameUTF8 = UTF8TEXT("Heal"), .Pointer = &AMyCharacter::execHeal },
		{ .NameUTF8 = UTF8TEXT("IsDead"), .Pointer = &AMyCharacter::execIsDead },
		{ .NameUTF8 = UTF8TEXT("IsRoleSkillActive"), .Pointer = &AMyCharacter::execIsRoleSkillActive },
		{ .NameUTF8 = UTF8TEXT("IsStatusEffectImmune"), .Pointer = &AMyCharacter::execIsStatusEffectImmune },
		{ .NameUTF8 = UTF8TEXT("OnAttackOverlap"), .Pointer = &AMyCharacter::execOnAttackOverlap },
		{ .NameUTF8 = UTF8TEXT("OnRep_CharacterState"), .Pointer = &AMyCharacter::execOnRep_CharacterState },
		{ .NameUTF8 = UTF8TEXT("OnRep_CurrentHP"), .Pointer = &AMyCharacter::execOnRep_CurrentHP },
		{ .NameUTF8 = UTF8TEXT("OnRep_RoleSkillActive"), .Pointer = &AMyCharacter::execOnRep_RoleSkillActive },
		{ .NameUTF8 = UTF8TEXT("OnRep_RoleType"), .Pointer = &AMyCharacter::execOnRep_RoleType },
		{ .NameUTF8 = UTF8TEXT("ResetHP"), .Pointer = &AMyCharacter::execResetHP },
		{ .NameUTF8 = UTF8TEXT("ServerActivateRoleSkill"), .Pointer = &AMyCharacter::execServerActivateRoleSkill },
		{ .NameUTF8 = UTF8TEXT("ServerApplyDamage"), .Pointer = &AMyCharacter::execServerApplyDamage },
		{ .NameUTF8 = UTF8TEXT("ServerCycleRole"), .Pointer = &AMyCharacter::execServerCycleRole },
		{ .NameUTF8 = UTF8TEXT("ServerHeal"), .Pointer = &AMyCharacter::execServerHeal },
		{ .NameUTF8 = UTF8TEXT("ServerResetHP"), .Pointer = &AMyCharacter::execServerResetHP },
		{ .NameUTF8 = UTF8TEXT("SetOverlappingItem"), .Pointer = &AMyCharacter::execSetOverlappingItem },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMyCharacter_ActivateRoleSkill, "ActivateRoleSkill" }, // 3537229730
		{ &Z_Construct_UFunction_AMyCharacter_AnimNotify_AttackHit, "AnimNotify_AttackHit" }, // 1609638898
		{ &Z_Construct_UFunction_AMyCharacter_ApplyDamage, "ApplyDamage" }, // 666109846
		{ &Z_Construct_UFunction_AMyCharacter_ApplyKnockback, "ApplyKnockback" }, // 2569617239
		{ &Z_Construct_UFunction_AMyCharacter_CanReceiveStatusEffect, "CanReceiveStatusEffect" }, // 2464014532
		{ &Z_Construct_UFunction_AMyCharacter_DoJumpEnd, "DoJumpEnd" }, // 988327275
		{ &Z_Construct_UFunction_AMyCharacter_DoJumpStart, "DoJumpStart" }, // 694861249
		{ &Z_Construct_UFunction_AMyCharacter_DoLook, "DoLook" }, // 481978328
		{ &Z_Construct_UFunction_AMyCharacter_DoMove, "DoMove" }, // 2599372898
		{ &Z_Construct_UFunction_AMyCharacter_DropCurrentItem, "DropCurrentItem" }, // 2533895883
		{ &Z_Construct_UFunction_AMyCharacter_EquipItem, "EquipItem" }, // 1018328333
		{ &Z_Construct_UFunction_AMyCharacter_GetCharacterState, "GetCharacterState" }, // 3454118103
		{ &Z_Construct_UFunction_AMyCharacter_GetCurrentHP, "GetCurrentHP" }, // 2733043168
		{ &Z_Construct_UFunction_AMyCharacter_GetMaxHP, "GetMaxHP" }, // 3810254293
		{ &Z_Construct_UFunction_AMyCharacter_GetNetworkAnimationNum, "GetNetworkAnimationNum" }, // 4035692722
		{ &Z_Construct_UFunction_AMyCharacter_GetRoleType, "GetRoleType" }, // 1709365993
		{ &Z_Construct_UFunction_AMyCharacter_Heal, "Heal" }, // 4188434684
		{ &Z_Construct_UFunction_AMyCharacter_IsDead, "IsDead" }, // 36366079
		{ &Z_Construct_UFunction_AMyCharacter_IsRoleSkillActive, "IsRoleSkillActive" }, // 2879766415
		{ &Z_Construct_UFunction_AMyCharacter_IsStatusEffectImmune, "IsStatusEffectImmune" }, // 176460120
		{ &Z_Construct_UFunction_AMyCharacter_OnAttackOverlap, "OnAttackOverlap" }, // 3281895323
		{ &Z_Construct_UFunction_AMyCharacter_OnRep_CharacterState, "OnRep_CharacterState" }, // 3623320751
		{ &Z_Construct_UFunction_AMyCharacter_OnRep_CurrentHP, "OnRep_CurrentHP" }, // 2187432755
		{ &Z_Construct_UFunction_AMyCharacter_OnRep_RoleSkillActive, "OnRep_RoleSkillActive" }, // 2291920985
		{ &Z_Construct_UFunction_AMyCharacter_OnRep_RoleType, "OnRep_RoleType" }, // 3261324005
		{ &Z_Construct_UFunction_AMyCharacter_ResetHP, "ResetHP" }, // 2649160694
		{ &Z_Construct_UFunction_AMyCharacter_ServerActivateRoleSkill, "ServerActivateRoleSkill" }, // 3919803770
		{ &Z_Construct_UFunction_AMyCharacter_ServerApplyDamage, "ServerApplyDamage" }, // 1217575186
		{ &Z_Construct_UFunction_AMyCharacter_ServerCycleRole, "ServerCycleRole" }, // 1186489623
		{ &Z_Construct_UFunction_AMyCharacter_ServerHeal, "ServerHeal" }, // 1654688610
		{ &Z_Construct_UFunction_AMyCharacter_ServerResetHP, "ServerResetHP" }, // 3156654722
		{ &Z_Construct_UFunction_AMyCharacter_SetOverlappingItem, "SetOverlappingItem" }, // 3213574543
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMyCharacter_Statics

// ********** Begin Class AMyCharacter Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_HPTextComponent = { "HPTextComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, HPTextComponent), Z_Construct_UClass_UTextRenderComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HPTextComponent_MetaData), NewProp_HPTextComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_RoleTextComponent = { "RoleTextComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, RoleTextComponent), Z_Construct_UClass_UTextRenderComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoleTextComponent_MetaData), NewProp_RoleTextComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathUITextComponent = { "DeathUITextComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DeathUITextComponent), Z_Construct_UClass_UTextRenderComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathUITextComponent_MetaData), NewProp_DeathUITextComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_MouseLookAction = { "MouseLookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, MouseLookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseLookAction_MetaData), NewProp_MouseLookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_AttackAction = { "AttackAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, AttackAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackAction_MetaData), NewProp_AttackAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_KnockbackAction = { "KnockbackAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, KnockbackAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_KnockbackAction_MetaData), NewProp_KnockbackAction_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_RoleType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_RoleType = { "RoleType", "OnRep_RoleType", (EPropertyFlags)0x0010000100020821, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, RoleType), Z_Construct_UEnum_Claim_Of_Core_ERecRoleType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoleType_MetaData), NewProp_RoleType_MetaData) }; // 3141253188
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_CharacterState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_CharacterState = { "CharacterState", "OnRep_CharacterState", (EPropertyFlags)0x0010000100020821, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, CharacterState), Z_Construct_UEnum_Claim_Of_Core_ERecCharacterState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterState_MetaData), NewProp_CharacterState_MetaData) }; // 1614730820
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_StrikerVisual = { "StrikerVisual", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, StrikerVisual), Z_Construct_UScriptStruct_FRoleVisualData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StrikerVisual_MetaData), NewProp_StrikerVisual_MetaData) }; // 2255437909
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_GuardianVisual = { "GuardianVisual", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, GuardianVisual), Z_Construct_UScriptStruct_FRoleVisualData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GuardianVisual_MetaData), NewProp_GuardianVisual_MetaData) }; // 2255437909
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_ManipulatorVisual = { "ManipulatorVisual", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, ManipulatorVisual), Z_Construct_UScriptStruct_FRoleVisualData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ManipulatorVisual_MetaData), NewProp_ManipulatorVisual_MetaData) }; // 2255437909
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_OverlappingItem = { "OverlappingItem", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, OverlappingItem), Z_Construct_UClass_ABaseItem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlappingItem_MetaData), NewProp_OverlappingItem_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_CurrentItem = { "CurrentItem", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, CurrentItem), Z_Construct_UClass_ABaseItem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentItem_MetaData), NewProp_CurrentItem_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_MaxHP = { "MaxHP", nullptr, (EPropertyFlags)0x0040000000010021, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, MaxHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHP_MetaData), NewProp_MaxHP_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_CurrentHP = { "CurrentHP", "OnRep_CurrentHP", (EPropertyFlags)0x0040000100020821, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_BaseWalkSpeed = { "BaseWalkSpeed", nullptr, (EPropertyFlags)0x0040000000020801, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, BaseWalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseWalkSpeed_MetaData), NewProp_BaseWalkSpeed_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_BaseJumpMaxCount = { "BaseJumpMaxCount", nullptr, (EPropertyFlags)0x0040000000020801, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, BaseJumpMaxCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseJumpMaxCount_MetaData), NewProp_BaseJumpMaxCount_MetaData) };
void Z_Construct_UClass_AMyCharacter_Statics::NewProp_bRoleSkillActive_SetBit(void* Obj)
{
	((AMyCharacter*)Obj)->bRoleSkillActive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_bRoleSkillActive = { "bRoleSkillActive", "OnRep_RoleSkillActive", (EPropertyFlags)0x0040000100020821, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMyCharacter), &Z_Construct_UClass_AMyCharacter_Statics::NewProp_bRoleSkillActive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRoleSkillActive_MetaData), NewProp_bRoleSkillActive_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DashDuration = { "DashDuration", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DashDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DashDuration_MetaData), NewProp_DashDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DashSpeedMultiplier = { "DashSpeedMultiplier", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DashSpeedMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DashSpeedMultiplier_MetaData), NewProp_DashSpeedMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DashDamageMultiplier = { "DashDamageMultiplier", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DashDamageMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DashDamageMultiplier_MetaData), NewProp_DashDamageMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardDuration = { "HardDuration", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, HardDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HardDuration_MetaData), NewProp_HardDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardSpeedMultiplier = { "HardSpeedMultiplier", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, HardSpeedMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HardSpeedMultiplier_MetaData), NewProp_HardSpeedMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardScaleMultiplier = { "HardScaleMultiplier", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, HardScaleMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HardScaleMultiplier_MetaData), NewProp_HardScaleMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardDamageTakenMultiplier = { "HardDamageTakenMultiplier", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, HardDamageTakenMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HardDamageTakenMultiplier_MetaData), NewProp_HardDamageTakenMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DBJPDuration = { "DBJPDuration", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DBJPDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DBJPDuration_MetaData), NewProp_DBJPDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectateMoveSpeed = { "SpectateMoveSpeed", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, SpectateMoveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpectateMoveSpeed_MetaData), NewProp_SpectateMoveSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectateVerticalSpeed = { "SpectateVerticalSpeed", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, SpectateVerticalSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpectateVerticalSpeed_MetaData), NewProp_SpectateVerticalSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectateInputUnlockDelay = { "SpectateInputUnlockDelay", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, SpectateInputUnlockDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpectateInputUnlockDelay_MetaData), NewProp_SpectateInputUnlockDelay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectatingUITextDuration = { "SpectatingUITextDuration", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, SpectatingUITextDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpectatingUITextDuration_MetaData), NewProp_SpectatingUITextDuration_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPThreshold = { "LowHPThreshold", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPThreshold_MetaData), NewProp_LowHPThreshold_MetaData) };
void Z_Construct_UClass_AMyCharacter_Statics::NewProp_bLowHPEffectActive_SetBit(void* Obj)
{
	((AMyCharacter*)Obj)->bLowHPEffectActive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_bLowHPEffectActive = { "bLowHPEffectActive", nullptr, (EPropertyFlags)0x0040000000020801, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMyCharacter), &Z_Construct_UClass_AMyCharacter_Statics::NewProp_bLowHPEffectActive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLowHPEffectActive_MetaData), NewProp_bLowHPEffectActive_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPostProcessBlendWeight = { "LowHPPostProcessBlendWeight", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPPostProcessBlendWeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPPostProcessBlendWeight_MetaData), NewProp_LowHPPostProcessBlendWeight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPVignetteIntensity = { "LowHPVignetteIntensity", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPVignetteIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPVignetteIntensity_MetaData), NewProp_LowHPVignetteIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPSaturation = { "LowHPSaturation", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPSaturation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPSaturation_MetaData), NewProp_LowHPSaturation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPulseSpeed = { "LowHPPulseSpeed", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPPulseSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPPulseSpeed_MetaData), NewProp_LowHPPulseSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPulseVignetteAmplitude = { "LowHPPulseVignetteAmplitude", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPPulseVignetteAmplitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPPulseVignetteAmplitude_MetaData), NewProp_LowHPPulseVignetteAmplitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPulseBlendAmplitude = { "LowHPPulseBlendAmplitude", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPPulseBlendAmplitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPPulseBlendAmplitude_MetaData), NewProp_LowHPPulseBlendAmplitude_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPSceneTint = { "LowHPSceneTint", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, LowHPSceneTint), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LowHPSceneTint_MetaData), NewProp_LowHPSceneTint_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathCameraTargetArmLength = { "DeathCameraTargetArmLength", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DeathCameraTargetArmLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathCameraTargetArmLength_MetaData), NewProp_DeathCameraTargetArmLength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathCameraInterpSpeed = { "DeathCameraInterpSpeed", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DeathCameraInterpSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathCameraInterpSpeed_MetaData), NewProp_DeathCameraInterpSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeDuration = { "DeathShakeDuration", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DeathShakeDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathShakeDuration_MetaData), NewProp_DeathShakeDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeAmplitude = { "DeathShakeAmplitude", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DeathShakeAmplitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathShakeAmplitude_MetaData), NewProp_DeathShakeAmplitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeFrequency = { "DeathShakeFrequency", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DeathShakeFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathShakeFrequency_MetaData), NewProp_DeathShakeFrequency_MetaData) };
void Z_Construct_UClass_AMyCharacter_Statics::NewProp_bDeathCameraShaking_SetBit(void* Obj)
{
	((AMyCharacter*)Obj)->bDeathCameraShaking = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_bDeathCameraShaking = { "bDeathCameraShaking", nullptr, (EPropertyFlags)0x0040000000020801, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMyCharacter), &Z_Construct_UClass_AMyCharacter_Statics::NewProp_bDeathCameraShaking_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDeathCameraShaking_MetaData), NewProp_bDeathCameraShaking_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeElapsed = { "DeathShakeElapsed", nullptr, (EPropertyFlags)0x0040000000020801, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, DeathShakeElapsed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathShakeElapsed_MetaData), NewProp_DeathShakeElapsed_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyCharacter_Statics::NewProp_NetworkAnimationNum = { "NetworkAnimationNum", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter, NetworkAnimationNum), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkAnimationNum_MetaData), NewProp_NetworkAnimationNum_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_HPTextComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_RoleTextComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathUITextComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_MouseLookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_AttackAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_KnockbackAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_RoleType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_RoleType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_CharacterState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_CharacterState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_StrikerVisual,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_GuardianVisual,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_ManipulatorVisual,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_OverlappingItem,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_CurrentItem,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_MaxHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_BaseWalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_BaseJumpMaxCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_bRoleSkillActive,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DashDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DashSpeedMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DashDamageMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardSpeedMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardScaleMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_HardDamageTakenMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DBJPDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectateMoveSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectateVerticalSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectateInputUnlockDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_SpectatingUITextDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_bLowHPEffectActive,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPostProcessBlendWeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPVignetteIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPSaturation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPulseSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPulseVignetteAmplitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPPulseBlendAmplitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_LowHPSceneTint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathCameraTargetArmLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathCameraInterpSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeAmplitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_bDeathCameraShaking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_DeathShakeElapsed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Statics::NewProp_NetworkAnimationNum,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Statics::PropPointers) < 2048);
// ********** End Class AMyCharacter Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_AMyCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyCharacter_Statics::ClassParams = {
	&AMyCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMyCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Statics::PropPointers),
	0,
	0x008000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyCharacter_Statics::Class_MetaDataParams)
};
void AMyCharacter::StaticRegisterNativesAMyCharacter()
{
	UClass* Class = AMyCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AMyCharacter_Statics::Funcs));
}
UClass* Z_Construct_UClass_AMyCharacter()
{
	if (!Z_Registration_Info_UClass_AMyCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyCharacter.OuterSingleton, Z_Construct_UClass_AMyCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyCharacter.OuterSingleton;
}
#if VALIDATE_CLASS_REPS
void AMyCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static FName Name_RoleType(TEXT("RoleType"));
	static FName Name_CharacterState(TEXT("CharacterState"));
	static FName Name_MaxHP(TEXT("MaxHP"));
	static FName Name_CurrentHP(TEXT("CurrentHP"));
	static FName Name_bRoleSkillActive(TEXT("bRoleSkillActive"));
	const bool bIsValid = true
		&& Name_RoleType == ClassReps[(int32)ENetFields_Private::RoleType].Property->GetFName()
		&& Name_CharacterState == ClassReps[(int32)ENetFields_Private::CharacterState].Property->GetFName()
		&& Name_MaxHP == ClassReps[(int32)ENetFields_Private::MaxHP].Property->GetFName()
		&& Name_CurrentHP == ClassReps[(int32)ENetFields_Private::CurrentHP].Property->GetFName()
		&& Name_bRoleSkillActive == ClassReps[(int32)ENetFields_Private::bRoleSkillActive].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AMyCharacter"));
}
#endif
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMyCharacter);
AMyCharacter::~AMyCharacter() {}
// ********** End Class AMyCharacter ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ERecCharacterState_StaticEnum, TEXT("ERecCharacterState"), &Z_Registration_Info_UEnum_ERecCharacterState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1614730820U) },
		{ ERecRoleType_StaticEnum, TEXT("ERecRoleType"), &Z_Registration_Info_UEnum_ERecRoleType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3141253188U) },
		{ ERecStatusEffectType_StaticEnum, TEXT("ERecStatusEffectType"), &Z_Registration_Info_UEnum_ERecStatusEffectType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2446554896U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FRoleVisualData::StaticStruct, Z_Construct_UScriptStruct_FRoleVisualData_Statics::NewStructOps, TEXT("RoleVisualData"),&Z_Registration_Info_UScriptStruct_FRoleVisualData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRoleVisualData), 2255437909U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyCharacter, AMyCharacter::StaticClass, TEXT("AMyCharacter"), &Z_Registration_Info_UClass_AMyCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyCharacter), 2317699722U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_155916941{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Sub_MyCharacter_h__Script_Claim_Of_Core_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
