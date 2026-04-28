// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NetworkInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNetworkInstance() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_AMyCharacter_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UNetworkInstance();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UNetworkInstance_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URoomWidget_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
ENGINE_API UClass* Z_Construct_UClass_UWorld_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UNetworkInstance Function SelectCharacterAndReady ************************
struct Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics
{
	struct NetworkInstance_eventSelectCharacterAndReady_Parms
	{
		int32 SelectedRoleType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Network|Room" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SelectCharacterAndReady constinit property declarations ***************
	static const UECodeGen_Private::FIntPropertyParams NewProp_SelectedRoleType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SelectCharacterAndReady constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SelectCharacterAndReady Property Definitions **************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::NewProp_SelectedRoleType = { "SelectedRoleType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkInstance_eventSelectCharacterAndReady_Parms, SelectedRoleType), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::NewProp_SelectedRoleType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::PropPointers) < 2048);
// ********** End Function SelectCharacterAndReady Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNetworkInstance, nullptr, "SelectCharacterAndReady", 	Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::NetworkInstance_eventSelectCharacterAndReady_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::NetworkInstance_eventSelectCharacterAndReady_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkInstance::execSelectCharacterAndReady)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_SelectedRoleType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SelectCharacterAndReady(Z_Param_SelectedRoleType);
	P_NATIVE_END;
}
// ********** End Class UNetworkInstance Function SelectCharacterAndReady **************************

// ********** Begin Class UNetworkInstance Function ShowLoginHUD ***********************************
struct Z_Construct_UFunction_UNetworkInstance_ShowLoginHUD_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Network|UI" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShowLoginHUD constinit property declarations **************************
// ********** End Function ShowLoginHUD constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkInstance_ShowLoginHUD_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UNetworkInstance, nullptr, "ShowLoginHUD", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkInstance_ShowLoginHUD_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkInstance_ShowLoginHUD_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UNetworkInstance_ShowLoginHUD()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkInstance_ShowLoginHUD_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkInstance::execShowLoginHUD)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowLoginHUD();
	P_NATIVE_END;
}
// ********** End Class UNetworkInstance Function ShowLoginHUD *************************************

// ********** Begin Class UNetworkInstance *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UNetworkInstance;
UClass* UNetworkInstance::GetPrivateStaticClass()
{
	using TClass = UNetworkInstance;
	if (!Z_Registration_Info_UClass_UNetworkInstance.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NetworkInstance"),
			Z_Registration_Info_UClass_UNetworkInstance.InnerSingleton,
			StaticRegisterNativesUNetworkInstance,
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
	return Z_Registration_Info_UClass_UNetworkInstance.InnerSingleton;
}
UClass* Z_Construct_UClass_UNetworkInstance_NoRegister()
{
	return UNetworkInstance::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UNetworkInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\n */" },
#endif
		{ "IncludePath", "UI/NetworkInstance.h" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoginWidgetClass_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Widget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Getter Function For Accessing Widget from External\n" },
#endif
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Getter Function For Accessing Widget from External" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoginWidgetInstance_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LobbyWidgetClass_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Widget" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LobbyWidgetInstance_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomWidgetClass_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Widget" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomWidgetInstance_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerIPAddress_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Getter Function For Server Connection\n" },
#endif
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Getter Function For Server Connection" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InGameLevel_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Level" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Getter Function For Map Control \n" },
#endif
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Getter Function For Map Control" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RemoteCharacterClass_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Network|Remote" },
		{ "ModuleRelativePath", "UI/NetworkInstance.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNetworkInstance constinit property declarations *************************
	static const UECodeGen_Private::FClassPropertyParams NewProp_LoginWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoginWidgetInstance;
	static const UECodeGen_Private::FClassPropertyParams NewProp_LobbyWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LobbyWidgetInstance;
	static const UECodeGen_Private::FClassPropertyParams NewProp_RoomWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RoomWidgetInstance;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerIPAddress;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_InGameLevel;
	static const UECodeGen_Private::FClassPropertyParams NewProp_RemoteCharacterClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNetworkInstance constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("SelectCharacterAndReady"), .Pointer = &UNetworkInstance::execSelectCharacterAndReady },
		{ .NameUTF8 = UTF8TEXT("ShowLoginHUD"), .Pointer = &UNetworkInstance::execShowLoginHUD },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNetworkInstance_SelectCharacterAndReady, "SelectCharacterAndReady" }, // 1368340714
		{ &Z_Construct_UFunction_UNetworkInstance_ShowLoginHUD, "ShowLoginHUD" }, // 1461944764
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNetworkInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UNetworkInstance_Statics

// ********** Begin Class UNetworkInstance Property Definitions ************************************
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LoginWidgetClass = { "LoginWidgetClass", nullptr, (EPropertyFlags)0x0044000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, LoginWidgetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoginWidgetClass_MetaData), NewProp_LoginWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LoginWidgetInstance = { "LoginWidgetInstance", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, LoginWidgetInstance), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoginWidgetInstance_MetaData), NewProp_LoginWidgetInstance_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LobbyWidgetClass = { "LobbyWidgetClass", nullptr, (EPropertyFlags)0x0044000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, LobbyWidgetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LobbyWidgetClass_MetaData), NewProp_LobbyWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LobbyWidgetInstance = { "LobbyWidgetInstance", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, LobbyWidgetInstance), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LobbyWidgetInstance_MetaData), NewProp_LobbyWidgetInstance_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_RoomWidgetClass = { "RoomWidgetClass", nullptr, (EPropertyFlags)0x0044000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, RoomWidgetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_URoomWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomWidgetClass_MetaData), NewProp_RoomWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_RoomWidgetInstance = { "RoomWidgetInstance", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, RoomWidgetInstance), Z_Construct_UClass_URoomWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomWidgetInstance_MetaData), NewProp_RoomWidgetInstance_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_ServerIPAddress = { "ServerIPAddress", nullptr, (EPropertyFlags)0x0040000000004000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, ServerIPAddress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerIPAddress_MetaData), NewProp_ServerIPAddress_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_InGameLevel = { "InGameLevel", nullptr, (EPropertyFlags)0x0044000000000005, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, InGameLevel), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InGameLevel_MetaData), NewProp_InGameLevel_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UNetworkInstance_Statics::NewProp_RemoteCharacterClass = { "RemoteCharacterClass", nullptr, (EPropertyFlags)0x0044000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkInstance, RemoteCharacterClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_AMyCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RemoteCharacterClass_MetaData), NewProp_RemoteCharacterClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNetworkInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LoginWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LoginWidgetInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LobbyWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_LobbyWidgetInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_RoomWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_RoomWidgetInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_ServerIPAddress,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_InGameLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkInstance_Statics::NewProp_RemoteCharacterClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkInstance_Statics::PropPointers) < 2048);
// ********** End Class UNetworkInstance Property Definitions **************************************
UObject* (*const Z_Construct_UClass_UNetworkInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNetworkInstance_Statics::ClassParams = {
	&UNetworkInstance::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UNetworkInstance_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkInstance_Statics::PropPointers),
	0,
	0x009000ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UNetworkInstance_Statics::Class_MetaDataParams)
};
void UNetworkInstance::StaticRegisterNativesUNetworkInstance()
{
	UClass* Class = UNetworkInstance::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UNetworkInstance_Statics::Funcs));
}
UClass* Z_Construct_UClass_UNetworkInstance()
{
	if (!Z_Registration_Info_UClass_UNetworkInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNetworkInstance.OuterSingleton, Z_Construct_UClass_UNetworkInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNetworkInstance.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNetworkInstance);
UNetworkInstance::~UNetworkInstance() {}
// ********** End Class UNetworkInstance ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_NetworkInstance_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNetworkInstance, UNetworkInstance::StaticClass, TEXT("UNetworkInstance"), &Z_Registration_Info_UClass_UNetworkInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNetworkInstance), 2363827742U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_NetworkInstance_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_NetworkInstance_h__Script_Claim_Of_Core_2104200288{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_NetworkInstance_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_NetworkInstance_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
