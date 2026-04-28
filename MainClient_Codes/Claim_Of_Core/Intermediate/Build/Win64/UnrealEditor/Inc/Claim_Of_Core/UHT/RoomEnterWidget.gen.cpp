// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RoomEnterWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeRoomEnterWidget() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URoomEnterWidget();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URoomEnterWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class URoomEnterWidget Function OnJoinButtonClicked ****************************
struct Z_Construct_UFunction_URoomEnterWidget_OnJoinButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "UI/RoomEnterWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnJoinButtonClicked constinit property declarations *******************
// ********** End Function OnJoinButtonClicked constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URoomEnterWidget_OnJoinButtonClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URoomEnterWidget, nullptr, "OnJoinButtonClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URoomEnterWidget_OnJoinButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_URoomEnterWidget_OnJoinButtonClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_URoomEnterWidget_OnJoinButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URoomEnterWidget_OnJoinButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URoomEnterWidget::execOnJoinButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnJoinButtonClicked();
	P_NATIVE_END;
}
// ********** End Class URoomEnterWidget Function OnJoinButtonClicked ******************************

// ********** Begin Class URoomEnterWidget *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_URoomEnterWidget;
UClass* URoomEnterWidget::GetPrivateStaticClass()
{
	using TClass = URoomEnterWidget;
	if (!Z_Registration_Info_UClass_URoomEnterWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("RoomEnterWidget"),
			Z_Registration_Info_UClass_URoomEnterWidget.InnerSingleton,
			StaticRegisterNativesURoomEnterWidget,
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
	return Z_Registration_Info_UClass_URoomEnterWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_URoomEnterWidget_NoRegister()
{
	return URoomEnterWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_URoomEnterWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\n */" },
#endif
		{ "IncludePath", "UI/RoomEnterWidget.h" },
		{ "ModuleRelativePath", "UI/RoomEnterWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomName_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RoomEnterWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerCounter_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RoomEnterWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JoinButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RoomEnterWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class URoomEnterWidget constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RoomName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerCounter;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JoinButton;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class URoomEnterWidget constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnJoinButtonClicked"), .Pointer = &URoomEnterWidget::execOnJoinButtonClicked },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URoomEnterWidget_OnJoinButtonClicked, "OnJoinButtonClicked" }, // 1073573901
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URoomEnterWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_URoomEnterWidget_Statics

// ********** Begin Class URoomEnterWidget Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URoomEnterWidget_Statics::NewProp_RoomName = { "RoomName", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URoomEnterWidget, RoomName), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomName_MetaData), NewProp_RoomName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URoomEnterWidget_Statics::NewProp_PlayerCounter = { "PlayerCounter", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URoomEnterWidget, PlayerCounter), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerCounter_MetaData), NewProp_PlayerCounter_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URoomEnterWidget_Statics::NewProp_JoinButton = { "JoinButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URoomEnterWidget, JoinButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JoinButton_MetaData), NewProp_JoinButton_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URoomEnterWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URoomEnterWidget_Statics::NewProp_RoomName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URoomEnterWidget_Statics::NewProp_PlayerCounter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URoomEnterWidget_Statics::NewProp_JoinButton,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URoomEnterWidget_Statics::PropPointers) < 2048);
// ********** End Class URoomEnterWidget Property Definitions **************************************
UObject* (*const Z_Construct_UClass_URoomEnterWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URoomEnterWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URoomEnterWidget_Statics::ClassParams = {
	&URoomEnterWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URoomEnterWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URoomEnterWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URoomEnterWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_URoomEnterWidget_Statics::Class_MetaDataParams)
};
void URoomEnterWidget::StaticRegisterNativesURoomEnterWidget()
{
	UClass* Class = URoomEnterWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_URoomEnterWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_URoomEnterWidget()
{
	if (!Z_Registration_Info_UClass_URoomEnterWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URoomEnterWidget.OuterSingleton, Z_Construct_UClass_URoomEnterWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URoomEnterWidget.OuterSingleton;
}
URoomEnterWidget::URoomEnterWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, URoomEnterWidget);
URoomEnterWidget::~URoomEnterWidget() {}
// ********** End Class URoomEnterWidget ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomEnterWidget_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URoomEnterWidget, URoomEnterWidget::StaticClass, TEXT("URoomEnterWidget"), &Z_Registration_Info_UClass_URoomEnterWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URoomEnterWidget), 1809532325U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomEnterWidget_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomEnterWidget_h__Script_Claim_Of_Core_541119085{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomEnterWidget_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomEnterWidget_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
