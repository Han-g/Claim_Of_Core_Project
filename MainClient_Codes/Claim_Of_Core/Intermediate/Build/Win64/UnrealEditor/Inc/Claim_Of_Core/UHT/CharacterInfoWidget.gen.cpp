// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CharacterInfoWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeCharacterInfoWidget() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UCharacterInfoWidget();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_UCharacterInfoWidget_NoRegister();
CLAIM_OF_CORE_API UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnCharacterRoleSelected **********************************************
struct Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics
{
	struct _Script_Claim_Of_Core_eventOnCharacterRoleSelected_Parms
	{
		int32 SelectedRoleType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnCharacterRoleSelected constinit property declarations **************
	static const UECodeGen_Private::FIntPropertyParams NewProp_SelectedRoleType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnCharacterRoleSelected constinit property declarations ****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnCharacterRoleSelected Property Definitions *************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::NewProp_SelectedRoleType = { "SelectedRoleType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_Claim_Of_Core_eventOnCharacterRoleSelected_Parms, SelectedRoleType), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::NewProp_SelectedRoleType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnCharacterRoleSelected Property Definitions ***************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Claim_Of_Core, nullptr, "OnCharacterRoleSelected__DelegateSignature", 	Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnCharacterRoleSelected_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::_Script_Claim_Of_Core_eventOnCharacterRoleSelected_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnCharacterRoleSelected_DelegateWrapper(const FMulticastScriptDelegate& OnCharacterRoleSelected, int32 SelectedRoleType)
{
	struct _Script_Claim_Of_Core_eventOnCharacterRoleSelected_Parms
	{
		int32 SelectedRoleType;
	};
	_Script_Claim_Of_Core_eventOnCharacterRoleSelected_Parms Parms;
	Parms.SelectedRoleType=SelectedRoleType;
	OnCharacterRoleSelected.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnCharacterRoleSelected ************************************************

// ********** Begin Class UCharacterInfoWidget Function OnGuardianClicked **************************
struct Z_Construct_UFunction_UCharacterInfoWidget_OnGuardianClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnGuardianClicked constinit property declarations *********************
// ********** End Function OnGuardianClicked constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCharacterInfoWidget_OnGuardianClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCharacterInfoWidget, nullptr, "OnGuardianClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCharacterInfoWidget_OnGuardianClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCharacterInfoWidget_OnGuardianClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCharacterInfoWidget_OnGuardianClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCharacterInfoWidget_OnGuardianClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCharacterInfoWidget::execOnGuardianClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnGuardianClicked();
	P_NATIVE_END;
}
// ********** End Class UCharacterInfoWidget Function OnGuardianClicked ****************************

// ********** Begin Class UCharacterInfoWidget Function OnManipulatorClicked ***********************
struct Z_Construct_UFunction_UCharacterInfoWidget_OnManipulatorClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnManipulatorClicked constinit property declarations ******************
// ********** End Function OnManipulatorClicked constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCharacterInfoWidget_OnManipulatorClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCharacterInfoWidget, nullptr, "OnManipulatorClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCharacterInfoWidget_OnManipulatorClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCharacterInfoWidget_OnManipulatorClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCharacterInfoWidget_OnManipulatorClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCharacterInfoWidget_OnManipulatorClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCharacterInfoWidget::execOnManipulatorClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnManipulatorClicked();
	P_NATIVE_END;
}
// ********** End Class UCharacterInfoWidget Function OnManipulatorClicked *************************

// ********** Begin Class UCharacterInfoWidget Function OnStrikerClicked ***************************
struct Z_Construct_UFunction_UCharacterInfoWidget_OnStrikerClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnStrikerClicked constinit property declarations **********************
// ********** End Function OnStrikerClicked constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCharacterInfoWidget_OnStrikerClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCharacterInfoWidget, nullptr, "OnStrikerClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCharacterInfoWidget_OnStrikerClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCharacterInfoWidget_OnStrikerClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCharacterInfoWidget_OnStrikerClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCharacterInfoWidget_OnStrikerClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCharacterInfoWidget::execOnStrikerClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnStrikerClicked();
	P_NATIVE_END;
}
// ********** End Class UCharacterInfoWidget Function OnStrikerClicked *****************************

// ********** Begin Class UCharacterInfoWidget *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UCharacterInfoWidget;
UClass* UCharacterInfoWidget::GetPrivateStaticClass()
{
	using TClass = UCharacterInfoWidget;
	if (!Z_Registration_Info_UClass_UCharacterInfoWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("CharacterInfoWidget"),
			Z_Registration_Info_UClass_UCharacterInfoWidget.InnerSingleton,
			StaticRegisterNativesUCharacterInfoWidget,
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
	return Z_Registration_Info_UClass_UCharacterInfoWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UCharacterInfoWidget_NoRegister()
{
	return UCharacterInfoWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCharacterInfoWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "CharacterInfoWidget.h" },
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnCharacterRoleSelected_MetaData[] = {
		{ "Category", "Character" },
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StrikerButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GuardianButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ManipulatorButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectedRoleType_MetaData[] = {
		{ "Category", "Character" },
		{ "ModuleRelativePath", "CharacterInfoWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UCharacterInfoWidget constinit property declarations *********************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCharacterRoleSelected;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StrikerButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GuardianButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ManipulatorButton;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SelectedRoleType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UCharacterInfoWidget constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnGuardianClicked"), .Pointer = &UCharacterInfoWidget::execOnGuardianClicked },
		{ .NameUTF8 = UTF8TEXT("OnManipulatorClicked"), .Pointer = &UCharacterInfoWidget::execOnManipulatorClicked },
		{ .NameUTF8 = UTF8TEXT("OnStrikerClicked"), .Pointer = &UCharacterInfoWidget::execOnStrikerClicked },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCharacterInfoWidget_OnGuardianClicked, "OnGuardianClicked" }, // 1552609540
		{ &Z_Construct_UFunction_UCharacterInfoWidget_OnManipulatorClicked, "OnManipulatorClicked" }, // 4242968774
		{ &Z_Construct_UFunction_UCharacterInfoWidget_OnStrikerClicked, "OnStrikerClicked" }, // 775579709
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCharacterInfoWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UCharacterInfoWidget_Statics

// ********** Begin Class UCharacterInfoWidget Property Definitions ********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_OnCharacterRoleSelected = { "OnCharacterRoleSelected", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterInfoWidget, OnCharacterRoleSelected), Z_Construct_UDelegateFunction_Claim_Of_Core_OnCharacterRoleSelected__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnCharacterRoleSelected_MetaData), NewProp_OnCharacterRoleSelected_MetaData) }; // 458062957
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_StrikerButton = { "StrikerButton", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterInfoWidget, StrikerButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StrikerButton_MetaData), NewProp_StrikerButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_GuardianButton = { "GuardianButton", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterInfoWidget, GuardianButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GuardianButton_MetaData), NewProp_GuardianButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_ManipulatorButton = { "ManipulatorButton", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterInfoWidget, ManipulatorButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ManipulatorButton_MetaData), NewProp_ManipulatorButton_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_SelectedRoleType = { "SelectedRoleType", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterInfoWidget, SelectedRoleType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectedRoleType_MetaData), NewProp_SelectedRoleType_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCharacterInfoWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_OnCharacterRoleSelected,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_StrikerButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_GuardianButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_ManipulatorButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterInfoWidget_Statics::NewProp_SelectedRoleType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterInfoWidget_Statics::PropPointers) < 2048);
// ********** End Class UCharacterInfoWidget Property Definitions **********************************
UObject* (*const Z_Construct_UClass_UCharacterInfoWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterInfoWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCharacterInfoWidget_Statics::ClassParams = {
	&UCharacterInfoWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UCharacterInfoWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterInfoWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterInfoWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UCharacterInfoWidget_Statics::Class_MetaDataParams)
};
void UCharacterInfoWidget::StaticRegisterNativesUCharacterInfoWidget()
{
	UClass* Class = UCharacterInfoWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UCharacterInfoWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_UCharacterInfoWidget()
{
	if (!Z_Registration_Info_UClass_UCharacterInfoWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCharacterInfoWidget.OuterSingleton, Z_Construct_UClass_UCharacterInfoWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCharacterInfoWidget.OuterSingleton;
}
UCharacterInfoWidget::UCharacterInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UCharacterInfoWidget);
UCharacterInfoWidget::~UCharacterInfoWidget() {}
// ********** End Class UCharacterInfoWidget *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCharacterInfoWidget, UCharacterInfoWidget::StaticClass, TEXT("UCharacterInfoWidget"), &Z_Registration_Info_UClass_UCharacterInfoWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCharacterInfoWidget), 2592725982U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h__Script_Claim_Of_Core_1701841650{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_CharacterInfoWidget_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
