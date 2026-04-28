// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeClaim_Of_Core_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature();
	CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature();
	CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature();
	CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature();
	CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Claim_Of_Core;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Claim_Of_Core()
	{
		if (!Z_Registration_Info_UPackage__Script_Claim_Of_Core.OuterSingleton)
		{
		static UObject* (*const SingletonFuncArray[])() = {
			(UObject* (*)())Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPChangedSignature__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_Claim_Of_Core_OnHPZeroSignature__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_Claim_Of_Core_OnMapPhaseChangedSignature__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_Claim_Of_Core_OnRoundStateChangedSignature__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/Claim_Of_Core",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x0E7B38D0,
			0xF2CB5525,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Claim_Of_Core.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_Claim_Of_Core.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Claim_Of_Core(Z_Construct_UPackage__Script_Claim_Of_Core, TEXT("/Script/Claim_Of_Core"), Z_Registration_Info_UPackage__Script_Claim_Of_Core, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x0E7B38D0, 0xF2CB5525));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
