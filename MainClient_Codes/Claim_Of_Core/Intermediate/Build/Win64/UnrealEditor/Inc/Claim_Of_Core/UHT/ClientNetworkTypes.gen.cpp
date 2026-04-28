// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ClientNetworkTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeClientNetworkTypes() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UScriptStruct* Z_Construct_UScriptStruct_FRoomInfoData();
CLAIM_OF_CORE_API UScriptStruct* Z_Construct_UScriptStruct_FRoomMemberInfo();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FRoomInfoData *****************************************************
struct Z_Construct_UScriptStruct_FRoomInfoData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FRoomInfoData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FRoomInfoData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============================================================\n// USTRUCTs (for UMG / Blueprint)\n// ============================================================\n" },
#endif
		{ "ModuleRelativePath", "Networking/ClientNetworkTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "USTRUCTs (for UMG / Blueprint)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomID_MetaData[] = {
		{ "Category", "RoomInfoData" },
		{ "ModuleRelativePath", "Networking/ClientNetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomName_MetaData[] = {
		{ "Category", "RoomInfoData" },
		{ "ModuleRelativePath", "Networking/ClientNetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentPlayers_MetaData[] = {
		{ "Category", "RoomInfoData" },
		{ "ModuleRelativePath", "Networking/ClientNetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPlayers_MetaData[] = {
		{ "Category", "RoomInfoData" },
		{ "ModuleRelativePath", "Networking/ClientNetworkTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FRoomInfoData constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_RoomID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RoomName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentPlayers;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxPlayers;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FRoomInfoData constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRoomInfoData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FRoomInfoData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FRoomInfoData;
class UScriptStruct* FRoomInfoData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FRoomInfoData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FRoomInfoData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRoomInfoData, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("RoomInfoData"));
	}
	return Z_Registration_Info_UScriptStruct_FRoomInfoData.OuterSingleton;
	}

// ********** Begin ScriptStruct FRoomInfoData Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_RoomID = { "RoomID", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRoomInfoData, RoomID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomID_MetaData), NewProp_RoomID_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_RoomName = { "RoomName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRoomInfoData, RoomName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomName_MetaData), NewProp_RoomName_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_CurrentPlayers = { "CurrentPlayers", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRoomInfoData, CurrentPlayers), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentPlayers_MetaData), NewProp_CurrentPlayers_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_MaxPlayers = { "MaxPlayers", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRoomInfoData, MaxPlayers), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPlayers_MetaData), NewProp_MaxPlayers_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRoomInfoData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_RoomID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_RoomName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_CurrentPlayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewProp_MaxPlayers,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomInfoData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FRoomInfoData Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRoomInfoData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	&NewStructOps,
	"RoomInfoData",
	Z_Construct_UScriptStruct_FRoomInfoData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomInfoData_Statics::PropPointers),
	sizeof(FRoomInfoData),
	alignof(FRoomInfoData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomInfoData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRoomInfoData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FRoomInfoData()
{
	if (!Z_Registration_Info_UScriptStruct_FRoomInfoData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FRoomInfoData.InnerSingleton, Z_Construct_UScriptStruct_FRoomInfoData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FRoomInfoData.InnerSingleton);
}
// ********** End ScriptStruct FRoomInfoData *******************************************************

// ********** Begin ScriptStruct FRoomMemberInfo ***************************************************
struct Z_Construct_UScriptStruct_FRoomMemberInfo_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FRoomMemberInfo); }
	static inline consteval int16 GetStructAlignment() { return alignof(FRoomMemberInfo); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Networking/ClientNetworkTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FRoomMemberInfo constinit property declarations *******************
// ********** End ScriptStruct FRoomMemberInfo constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRoomMemberInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FRoomMemberInfo_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FRoomMemberInfo;
class UScriptStruct* FRoomMemberInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FRoomMemberInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FRoomMemberInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRoomMemberInfo, (UObject*)Z_Construct_UPackage__Script_Claim_Of_Core(), TEXT("RoomMemberInfo"));
	}
	return Z_Registration_Info_UScriptStruct_FRoomMemberInfo.OuterSingleton;
	}
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRoomMemberInfo_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
	nullptr,
	&NewStructOps,
	"RoomMemberInfo",
	nullptr,
	0,
	sizeof(FRoomMemberInfo),
	alignof(FRoomMemberInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomMemberInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRoomMemberInfo_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FRoomMemberInfo()
{
	if (!Z_Registration_Info_UScriptStruct_FRoomMemberInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FRoomMemberInfo.InnerSingleton, Z_Construct_UScriptStruct_FRoomMemberInfo_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FRoomMemberInfo.InnerSingleton);
}
// ********** End ScriptStruct FRoomMemberInfo *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Networking_ClientNetworkTypes_h__Script_Claim_Of_Core_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FRoomInfoData::StaticStruct, Z_Construct_UScriptStruct_FRoomInfoData_Statics::NewStructOps, TEXT("RoomInfoData"),&Z_Registration_Info_UScriptStruct_FRoomInfoData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRoomInfoData), 1489542110U) },
		{ FRoomMemberInfo::StaticStruct, Z_Construct_UScriptStruct_FRoomMemberInfo_Statics::NewStructOps, TEXT("RoomMemberInfo"),&Z_Registration_Info_UScriptStruct_FRoomMemberInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRoomMemberInfo), 646677467U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Networking_ClientNetworkTypes_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Networking_ClientNetworkTypes_h__Script_Claim_Of_Core_4009582814{
	TEXT("/Script/Claim_Of_Core"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Networking_ClientNetworkTypes_h__Script_Claim_Of_Core_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_Networking_ClientNetworkTypes_h__Script_Claim_Of_Core_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
