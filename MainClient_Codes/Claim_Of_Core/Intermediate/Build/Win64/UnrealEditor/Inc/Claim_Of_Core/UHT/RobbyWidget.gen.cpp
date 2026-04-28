// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RobbyWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeRobbyWidget() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URobbyWidget();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URobbyWidget_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URoomEnterWidget_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UScrollBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class URobbyWidget Function OnCreateButtonClicked ******************************
struct Z_Construct_UFunction_URobbyWidget_OnCreateButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "UI/RobbyWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnCreateButtonClicked constinit property declarations *****************
// ********** End Function OnCreateButtonClicked constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URobbyWidget_OnCreateButtonClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URobbyWidget, nullptr, "OnCreateButtonClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URobbyWidget_OnCreateButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_URobbyWidget_OnCreateButtonClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_URobbyWidget_OnCreateButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URobbyWidget_OnCreateButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URobbyWidget::execOnCreateButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnCreateButtonClicked();
	P_NATIVE_END;
}
// ********** End Class URobbyWidget Function OnCreateButtonClicked ********************************

// ********** Begin Class URobbyWidget Function OnStartButtonClicked *******************************
struct Z_Construct_UFunction_URobbyWidget_OnStartButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "UI/RobbyWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnStartButtonClicked constinit property declarations ******************
// ********** End Function OnStartButtonClicked constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URobbyWidget_OnStartButtonClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URobbyWidget, nullptr, "OnStartButtonClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URobbyWidget_OnStartButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_URobbyWidget_OnStartButtonClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_URobbyWidget_OnStartButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URobbyWidget_OnStartButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URobbyWidget::execOnStartButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnStartButtonClicked();
	P_NATIVE_END;
}
// ********** End Class URobbyWidget Function OnStartButtonClicked *********************************

// ********** Begin Class URobbyWidget *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_URobbyWidget;
UClass* URobbyWidget::GetPrivateStaticClass()
{
	using TClass = URobbyWidget;
	if (!Z_Registration_Info_UClass_URobbyWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("RobbyWidget"),
			Z_Registration_Info_UClass_URobbyWidget.InnerSingleton,
			StaticRegisterNativesURobbyWidget,
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
	return Z_Registration_Info_UClass_URobbyWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_URobbyWidget_NoRegister()
{
	return URobbyWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_URobbyWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\n */" },
#endif
		{ "IncludePath", "UI/RobbyWidget.h" },
		{ "ModuleRelativePath", "UI/RobbyWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CreateButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RobbyWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RobbyWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomScrollBox_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RobbyWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomEntryClass_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "UI/RobbyWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class URobbyWidget constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CreateButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StartButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RoomScrollBox;
	static const UECodeGen_Private::FClassPropertyParams NewProp_RoomEntryClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class URobbyWidget constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnCreateButtonClicked"), .Pointer = &URobbyWidget::execOnCreateButtonClicked },
		{ .NameUTF8 = UTF8TEXT("OnStartButtonClicked"), .Pointer = &URobbyWidget::execOnStartButtonClicked },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URobbyWidget_OnCreateButtonClicked, "OnCreateButtonClicked" }, // 353098017
		{ &Z_Construct_UFunction_URobbyWidget_OnStartButtonClicked, "OnStartButtonClicked" }, // 2186878461
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URobbyWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_URobbyWidget_Statics

// ********** Begin Class URobbyWidget Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URobbyWidget_Statics::NewProp_CreateButton = { "CreateButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URobbyWidget, CreateButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CreateButton_MetaData), NewProp_CreateButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URobbyWidget_Statics::NewProp_StartButton = { "StartButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URobbyWidget, StartButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartButton_MetaData), NewProp_StartButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URobbyWidget_Statics::NewProp_RoomScrollBox = { "RoomScrollBox", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URobbyWidget, RoomScrollBox), Z_Construct_UClass_UScrollBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomScrollBox_MetaData), NewProp_RoomScrollBox_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_URobbyWidget_Statics::NewProp_RoomEntryClass = { "RoomEntryClass", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URobbyWidget, RoomEntryClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_URoomEnterWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomEntryClass_MetaData), NewProp_RoomEntryClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URobbyWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URobbyWidget_Statics::NewProp_CreateButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URobbyWidget_Statics::NewProp_StartButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URobbyWidget_Statics::NewProp_RoomScrollBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URobbyWidget_Statics::NewProp_RoomEntryClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URobbyWidget_Statics::PropPointers) < 2048);
// ********** End Class URobbyWidget Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_URobbyWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URobbyWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URobbyWidget_Statics::ClassParams = {
	&URobbyWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URobbyWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URobbyWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URobbyWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_URobbyWidget_Statics::Class_MetaDataParams)
};
void URobbyWidget::StaticRegisterNativesURobbyWidget()
{
	UClass* Class = URobbyWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_URobbyWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_URobbyWidget()
{
	if (!Z_Registration_Info_UClass_URobbyWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URobbyWidget.OuterSingleton, Z_Construct_UClass_URobbyWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URobbyWidget.OuterSingleton;
}
URobbyWidget::URobbyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, URobbyWidget);
URobbyWidget::~URobbyWidget() {}
// ********** End Class URobbyWidget ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RobbyWidget_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URobbyWidget, URobbyWidget::StaticClass, TEXT("URobbyWidget"), &Z_Registration_Info_UClass_URobbyWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URobbyWidget), 917444841U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RobbyWidget_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RobbyWidget_h__Script_Claim_Of_Core_2168477151{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RobbyWidget_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RobbyWidget_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
