// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RoomWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeRoomWidget() {}

// ********** Begin Cross Module References ********************************************************
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URoomMemberWidget_NoRegister();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URoomWidget();
CLAIM_OF_CORE_API UClass* Z_Construct_UClass_URoomWidget_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUniformGridPanel_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Claim_Of_Core();
// ********** End Cross Module References **********************************************************

// ********** Begin Class URoomWidget Function OnStartButtonClicked ********************************
struct Z_Construct_UFunction_URoomWidget_OnStartButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "UI/RoomWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnStartButtonClicked constinit property declarations ******************
// ********** End Function OnStartButtonClicked constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URoomWidget_OnStartButtonClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URoomWidget, nullptr, "OnStartButtonClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URoomWidget_OnStartButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_URoomWidget_OnStartButtonClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_URoomWidget_OnStartButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URoomWidget_OnStartButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URoomWidget::execOnStartButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnStartButtonClicked();
	P_NATIVE_END;
}
// ********** End Class URoomWidget Function OnStartButtonClicked **********************************

// ********** Begin Class URoomWidget **************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_URoomWidget;
UClass* URoomWidget::GetPrivateStaticClass()
{
	using TClass = URoomWidget;
	if (!Z_Registration_Info_UClass_URoomWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("RoomWidget"),
			Z_Registration_Info_UClass_URoomWidget.InnerSingleton,
			StaticRegisterNativesURoomWidget,
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
	return Z_Registration_Info_UClass_URoomWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_URoomWidget_NoRegister()
{
	return URoomWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_URoomWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\n */" },
#endif
		{ "IncludePath", "UI/RoomWidget.h" },
		{ "ModuleRelativePath", "UI/RoomWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MemberList_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RoomWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MemberCount_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RoomWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "UI/RoomWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MemberWidgetClass_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "UI/RoomWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class URoomWidget constinit property declarations ******************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MemberList;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MemberCount;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StartButton;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MemberWidgetClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class URoomWidget constinit property declarations ********************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnStartButtonClicked"), .Pointer = &URoomWidget::execOnStartButtonClicked },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URoomWidget_OnStartButtonClicked, "OnStartButtonClicked" }, // 2652123509
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URoomWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_URoomWidget_Statics

// ********** Begin Class URoomWidget Property Definitions *****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URoomWidget_Statics::NewProp_MemberList = { "MemberList", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URoomWidget, MemberList), Z_Construct_UClass_UUniformGridPanel_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MemberList_MetaData), NewProp_MemberList_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URoomWidget_Statics::NewProp_MemberCount = { "MemberCount", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URoomWidget, MemberCount), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MemberCount_MetaData), NewProp_MemberCount_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URoomWidget_Statics::NewProp_StartButton = { "StartButton", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URoomWidget, StartButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartButton_MetaData), NewProp_StartButton_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_URoomWidget_Statics::NewProp_MemberWidgetClass = { "MemberWidgetClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URoomWidget, MemberWidgetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_URoomMemberWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MemberWidgetClass_MetaData), NewProp_MemberWidgetClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URoomWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URoomWidget_Statics::NewProp_MemberList,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URoomWidget_Statics::NewProp_MemberCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URoomWidget_Statics::NewProp_StartButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URoomWidget_Statics::NewProp_MemberWidgetClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URoomWidget_Statics::PropPointers) < 2048);
// ********** End Class URoomWidget Property Definitions *******************************************
UObject* (*const Z_Construct_UClass_URoomWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Claim_Of_Core,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URoomWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URoomWidget_Statics::ClassParams = {
	&URoomWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URoomWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URoomWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URoomWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_URoomWidget_Statics::Class_MetaDataParams)
};
void URoomWidget::StaticRegisterNativesURoomWidget()
{
	UClass* Class = URoomWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_URoomWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_URoomWidget()
{
	if (!Z_Registration_Info_UClass_URoomWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URoomWidget.OuterSingleton, Z_Construct_UClass_URoomWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URoomWidget.OuterSingleton;
}
URoomWidget::URoomWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, URoomWidget);
URoomWidget::~URoomWidget() {}
// ********** End Class URoomWidget ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomWidget_h__Script_Claim_Of_Core_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URoomWidget, URoomWidget::StaticClass, TEXT("URoomWidget"), &Z_Registration_Info_UClass_URoomWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URoomWidget), 459760806U) },
	};
}; // Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomWidget_h__Script_Claim_Of_Core_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomWidget_h__Script_Claim_Of_Core_2500734335{
	TEXT("/Script/Claim_Of_Core"),
	Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomWidget_h__Script_Claim_Of_Core_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Download_Claim_Of_Core_Project_MainClient_Claim_Of_Core_Project_MainClient_MainClient_Codes_Claim_Of_Core_Source_Claim_Of_Core_UI_RoomWidget_h__Script_Claim_Of_Core_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
