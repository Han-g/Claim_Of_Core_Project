// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LoginWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeLoginWidget() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ULoginWidget();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_ULoginWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UEditableTextBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ULoginWidget Function HidePopup ******************************************
struct Z_Construct_UFunction_ULoginWidget_HidePopup_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HidePopup constinit property declarations *****************************
// ********** End Function HidePopup constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULoginWidget_HidePopup_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ULoginWidget, nullptr, "HidePopup", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULoginWidget_HidePopup_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULoginWidget_HidePopup_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ULoginWidget_HidePopup()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULoginWidget_HidePopup_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULoginWidget::execHidePopup)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HidePopup();
	P_NATIVE_END;
}
// ********** End Class ULoginWidget Function HidePopup ********************************************

// ********** Begin Class ULoginWidget Function OnLoginClicked *************************************
struct Z_Construct_UFunction_ULoginWidget_OnLoginClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnLoginClicked constinit property declarations ************************
// ********** End Function OnLoginClicked constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULoginWidget_OnLoginClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ULoginWidget, nullptr, "OnLoginClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULoginWidget_OnLoginClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULoginWidget_OnLoginClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ULoginWidget_OnLoginClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULoginWidget_OnLoginClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULoginWidget::execOnLoginClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnLoginClicked();
	P_NATIVE_END;
}
// ********** End Class ULoginWidget Function OnLoginClicked ***************************************

// ********** Begin Class ULoginWidget Function OnRegisterCliecked *********************************
struct Z_Construct_UFunction_ULoginWidget_OnRegisterCliecked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnRegisterCliecked constinit property declarations ********************
// ********** End Function OnRegisterCliecked constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULoginWidget_OnRegisterCliecked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ULoginWidget, nullptr, "OnRegisterCliecked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULoginWidget_OnRegisterCliecked_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULoginWidget_OnRegisterCliecked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ULoginWidget_OnRegisterCliecked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULoginWidget_OnRegisterCliecked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULoginWidget::execOnRegisterCliecked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRegisterCliecked();
	P_NATIVE_END;
}
// ********** End Class ULoginWidget Function OnRegisterCliecked ***********************************

// ********** Begin Class ULoginWidget *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ULoginWidget;
UClass* ULoginWidget::GetPrivateStaticClass()
{
	using TClass = ULoginWidget;
	if (!Z_Registration_Info_UClass_ULoginWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("LoginWidget"),
			Z_Registration_Info_UClass_ULoginWidget.InnerSingleton,
			StaticRegisterNativesULoginWidget,
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
	return Z_Registration_Info_UClass_ULoginWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_ULoginWidget_NoRegister()
{
	return ULoginWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ULoginWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UI/LoginWidget.h" },
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ID_BOX_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PW_BOX_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RegisterButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoginButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FailLoginPopUp_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/LoginWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ULoginWidget constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ID_BOX;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PW_BOX;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RegisterButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoginButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FailLoginPopUp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ULoginWidget constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("HidePopup"), .Pointer = &ULoginWidget::execHidePopup },
		{ .NameUTF8 = UTF8TEXT("OnLoginClicked"), .Pointer = &ULoginWidget::execOnLoginClicked },
		{ .NameUTF8 = UTF8TEXT("OnRegisterCliecked"), .Pointer = &ULoginWidget::execOnRegisterCliecked },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ULoginWidget_HidePopup, "HidePopup" }, // 3735252346
		{ &Z_Construct_UFunction_ULoginWidget_OnLoginClicked, "OnLoginClicked" }, // 3208787549
		{ &Z_Construct_UFunction_ULoginWidget_OnRegisterCliecked, "OnRegisterCliecked" }, // 1702722836
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULoginWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ULoginWidget_Statics

// ********** Begin Class ULoginWidget Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULoginWidget_Statics::NewProp_ID_BOX = { "ID_BOX", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULoginWidget, ID_BOX), Z_Construct_UClass_UEditableTextBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ID_BOX_MetaData), NewProp_ID_BOX_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULoginWidget_Statics::NewProp_PW_BOX = { "PW_BOX", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULoginWidget, PW_BOX), Z_Construct_UClass_UEditableTextBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PW_BOX_MetaData), NewProp_PW_BOX_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULoginWidget_Statics::NewProp_RegisterButton = { "RegisterButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULoginWidget, RegisterButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RegisterButton_MetaData), NewProp_RegisterButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULoginWidget_Statics::NewProp_LoginButton = { "LoginButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULoginWidget, LoginButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoginButton_MetaData), NewProp_LoginButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULoginWidget_Statics::NewProp_FailLoginPopUp = { "FailLoginPopUp", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULoginWidget, FailLoginPopUp), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FailLoginPopUp_MetaData), NewProp_FailLoginPopUp_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULoginWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULoginWidget_Statics::NewProp_ID_BOX,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULoginWidget_Statics::NewProp_PW_BOX,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULoginWidget_Statics::NewProp_RegisterButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULoginWidget_Statics::NewProp_LoginButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULoginWidget_Statics::NewProp_FailLoginPopUp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULoginWidget_Statics::PropPointers) < 2048);
// ********** End Class ULoginWidget Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_ULoginWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULoginWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULoginWidget_Statics::ClassParams = {
	&ULoginWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ULoginWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ULoginWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULoginWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_ULoginWidget_Statics::Class_MetaDataParams)
};
void ULoginWidget::StaticRegisterNativesULoginWidget()
{
	UClass* Class = ULoginWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ULoginWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_ULoginWidget()
{
	if (!Z_Registration_Info_UClass_ULoginWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULoginWidget.OuterSingleton, Z_Construct_UClass_ULoginWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULoginWidget.OuterSingleton;
}
ULoginWidget::ULoginWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ULoginWidget);
ULoginWidget::~ULoginWidget() {}
// ********** End Class ULoginWidget ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_LoginWidget_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULoginWidget, ULoginWidget::StaticClass, TEXT("ULoginWidget"), &Z_Registration_Info_UClass_ULoginWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULoginWidget), 305683488U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_LoginWidget_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_LoginWidget_h__Script_Claim_Of_Core_2530354629{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_LoginWidget_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_LoginWidget_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
