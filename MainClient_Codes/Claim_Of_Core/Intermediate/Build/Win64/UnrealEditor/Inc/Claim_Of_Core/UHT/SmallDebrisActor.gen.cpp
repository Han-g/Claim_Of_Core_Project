// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Map/Building/SmallDebrisActor.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeSmallDebrisActor() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ASmallDebrisActor();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ASmallDebrisActor_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASmallDebrisActor Function DestroySelf ***********************************
struct Z_Construct_UFunction_ASmallDebrisActor_DestroySelf_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DestroySelf constinit property declarations ***************************
// ********** End Function DestroySelf constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASmallDebrisActor_DestroySelf_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASmallDebrisActor, nullptr, "DestroySelf", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASmallDebrisActor_DestroySelf_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASmallDebrisActor_DestroySelf_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ASmallDebrisActor_DestroySelf()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASmallDebrisActor_DestroySelf_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASmallDebrisActor::execDestroySelf)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DestroySelf();
	P_NATIVE_END;
}
// ********** End Class ASmallDebrisActor Function DestroySelf *************************************

// ********** Begin Class ASmallDebrisActor Function OnDebrisHit ***********************************
struct Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics
{
	struct SmallDebrisActor_eventOnDebrisHit_Parms
	{
		UPrimitiveComponent* HitComponent;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		FVector NormalImpulse;
		FHitResult Hit;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HitComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnDebrisHit constinit property declarations ***************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HitComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NormalImpulse;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Hit;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnDebrisHit constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnDebrisHit Property Definitions **************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_HitComponent = { "HitComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SmallDebrisActor_eventOnDebrisHit_Parms, HitComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HitComponent_MetaData), NewProp_HitComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SmallDebrisActor_eventOnDebrisHit_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SmallDebrisActor_eventOnDebrisHit_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_NormalImpulse = { "NormalImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SmallDebrisActor_eventOnDebrisHit_Parms, NormalImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_Hit = { "Hit", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SmallDebrisActor_eventOnDebrisHit_Parms, Hit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hit_MetaData), NewProp_Hit_MetaData) }; // 222120718
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_HitComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_NormalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::NewProp_Hit,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::PropPointers) < 2048);
// ********** End Function OnDebrisHit Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASmallDebrisActor, nullptr, "OnDebrisHit", 	Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::SmallDebrisActor_eventOnDebrisHit_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::SmallDebrisActor_eventOnDebrisHit_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASmallDebrisActor::execOnDebrisHit)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComponent);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_STRUCT(FVector,Z_Param_NormalImpulse);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnDebrisHit(Z_Param_HitComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit);
	P_NATIVE_END;
}
// ********** End Class ASmallDebrisActor Function OnDebrisHit *************************************

// ********** Begin Class ASmallDebrisActor ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ASmallDebrisActor;
UClass* ASmallDebrisActor::GetPrivateStaticClass()
{
	using TClass = ASmallDebrisActor;
	if (!Z_Registration_Info_UClass_ASmallDebrisActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("SmallDebrisActor"),
			Z_Registration_Info_UClass_ASmallDebrisActor.InnerSingleton,
			StaticRegisterNativesASmallDebrisActor,
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
	return Z_Registration_Info_UClass_ASmallDebrisActor.InnerSingleton;
}
UClass* Z_Construct_UClass_ASmallDebrisActor_NoRegister()
{
	return ASmallDebrisActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASmallDebrisActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Map/Building/SmallDebrisActor.h" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionComp_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshComp_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Damage_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DestroyDelayAfterHitGround_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDestroyOnPlayerHit_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasHitSomething_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasDamagedPlayer_MetaData[] = {
		{ "Category", "Debris" },
		{ "ModuleRelativePath", "Map/Building/SmallDebrisActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ASmallDebrisActor constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollisionComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshComp;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DestroyDelayAfterHitGround;
	static void NewProp_bDestroyOnPlayerHit_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDestroyOnPlayerHit;
	static void NewProp_bHasHitSomething_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasHitSomething;
	static void NewProp_bHasDamagedPlayer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasDamagedPlayer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASmallDebrisActor constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DestroySelf"), .Pointer = &ASmallDebrisActor::execDestroySelf },
		{ .NameUTF8 = UTF8TEXT("OnDebrisHit"), .Pointer = &ASmallDebrisActor::execOnDebrisHit },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASmallDebrisActor_DestroySelf, "DestroySelf" }, // 1067831497
		{ &Z_Construct_UFunction_ASmallDebrisActor_OnDebrisHit, "OnDebrisHit" }, // 3104569882
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASmallDebrisActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ASmallDebrisActor_Statics

// ********** Begin Class ASmallDebrisActor Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASmallDebrisActor, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_CollisionComp = { "CollisionComp", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASmallDebrisActor, CollisionComp), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionComp_MetaData), NewProp_CollisionComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_MeshComp = { "MeshComp", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASmallDebrisActor, MeshComp), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshComp_MetaData), NewProp_MeshComp_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASmallDebrisActor, Damage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Damage_MetaData), NewProp_Damage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_DestroyDelayAfterHitGround = { "DestroyDelayAfterHitGround", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASmallDebrisActor, DestroyDelayAfterHitGround), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DestroyDelayAfterHitGround_MetaData), NewProp_DestroyDelayAfterHitGround_MetaData) };
void Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bDestroyOnPlayerHit_SetBit(void* Obj)
{
	((ASmallDebrisActor*)Obj)->bDestroyOnPlayerHit = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bDestroyOnPlayerHit = { "bDestroyOnPlayerHit", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASmallDebrisActor), &Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bDestroyOnPlayerHit_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDestroyOnPlayerHit_MetaData), NewProp_bDestroyOnPlayerHit_MetaData) };
void Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasHitSomething_SetBit(void* Obj)
{
	((ASmallDebrisActor*)Obj)->bHasHitSomething = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasHitSomething = { "bHasHitSomething", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASmallDebrisActor), &Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasHitSomething_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasHitSomething_MetaData), NewProp_bHasHitSomething_MetaData) };
void Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasDamagedPlayer_SetBit(void* Obj)
{
	((ASmallDebrisActor*)Obj)->bHasDamagedPlayer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasDamagedPlayer = { "bHasDamagedPlayer", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASmallDebrisActor), &Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasDamagedPlayer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasDamagedPlayer_MetaData), NewProp_bHasDamagedPlayer_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASmallDebrisActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_CollisionComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_MeshComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_Damage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_DestroyDelayAfterHitGround,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bDestroyOnPlayerHit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasHitSomething,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmallDebrisActor_Statics::NewProp_bHasDamagedPlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASmallDebrisActor_Statics::PropPointers) < 2048);
// ********** End Class ASmallDebrisActor Property Definitions *************************************
UObject* (*const Z_Construct_UClass_ASmallDebrisActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASmallDebrisActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASmallDebrisActor_Statics::ClassParams = {
	&ASmallDebrisActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ASmallDebrisActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ASmallDebrisActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASmallDebrisActor_Statics::Class_MetaDataParams), Z_Construct_UClass_ASmallDebrisActor_Statics::Class_MetaDataParams)
};
void ASmallDebrisActor::StaticRegisterNativesASmallDebrisActor()
{
	UClass* Class = ASmallDebrisActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ASmallDebrisActor_Statics::Funcs));
}
UClass* Z_Construct_UClass_ASmallDebrisActor()
{
	if (!Z_Registration_Info_UClass_ASmallDebrisActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASmallDebrisActor.OuterSingleton, Z_Construct_UClass_ASmallDebrisActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASmallDebrisActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASmallDebrisActor);
ASmallDebrisActor::~ASmallDebrisActor() {}
// ********** End Class ASmallDebrisActor **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_SmallDebrisActor_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASmallDebrisActor, ASmallDebrisActor::StaticClass, TEXT("ASmallDebrisActor"), &Z_Registration_Info_UClass_ASmallDebrisActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASmallDebrisActor), 3678266260U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_SmallDebrisActor_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_SmallDebrisActor_h__Script_Claim_Of_Core_3962253242{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_SmallDebrisActor_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Map_Building_SmallDebrisActor_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
