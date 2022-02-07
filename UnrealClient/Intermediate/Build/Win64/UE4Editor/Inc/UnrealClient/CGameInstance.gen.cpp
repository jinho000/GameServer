// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealClient/Global/CGameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCGameInstance() {}
// Cross Module References
	UNREALCLIENT_API UClass* Z_Construct_UClass_UCGameInstance_NoRegister();
	UNREALCLIENT_API UClass* Z_Construct_UClass_UCGameInstance();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_UnrealClient();
// End Cross Module References
	void UCGameInstance::StaticRegisterNativesUCGameInstance()
	{
	}
	UClass* Z_Construct_UClass_UCGameInstance_NoRegister()
	{
		return UCGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_UCGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealClient,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCGameInstance_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */// ???? ???\xdb\xba??? ?????\xc3\xb1??? ?????\xd6\xb4? \xc5\xac????\n// ?????? ?\xd9\xb2\xf0\xb6\xa7\xbf??? ???? ?????? \xc3\xb3??\n" },
		{ "IncludePath", "Global/CGameInstance.h" },
		{ "ModuleRelativePath", "Global/CGameInstance.h" },
		{ "ToolTip", "// ???? ???\xdb\xba??? ?????\xc3\xb1??? ?????\xd6\xb4? \xc5\xac????\n// ?????? ?\xd9\xb2\xf0\xb6\xa7\xbf??? ???? ?????? \xc3\xb3??" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCGameInstance>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCGameInstance_Statics::ClassParams = {
		&UCGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UCGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCGameInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCGameInstance_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCGameInstance, 3144617627);
	template<> UNREALCLIENT_API UClass* StaticClass<UCGameInstance>()
	{
		return UCGameInstance::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCGameInstance(Z_Construct_UClass_UCGameInstance, &UCGameInstance::StaticClass, TEXT("/Script/UnrealClient"), TEXT("UCGameInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCGameInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
