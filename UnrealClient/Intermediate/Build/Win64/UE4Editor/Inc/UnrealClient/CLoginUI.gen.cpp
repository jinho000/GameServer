// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealClient/Login/CLoginUI.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCLoginUI() {}
// Cross Module References
	UNREALCLIENT_API UClass* Z_Construct_UClass_UCLoginUI_NoRegister();
	UNREALCLIENT_API UClass* Z_Construct_UClass_UCLoginUI();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_UnrealClient();
// End Cross Module References
	DEFINE_FUNCTION(UCLoginUI::execLogin)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Login();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCLoginUI::execConnectServer)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ConnectServer();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCLoginUI::execResetConnectInfo)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ResetConnectInfo();
		P_NATIVE_END;
	}
	void UCLoginUI::StaticRegisterNativesUCLoginUI()
	{
		UClass* Class = UCLoginUI::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ConnectServer", &UCLoginUI::execConnectServer },
			{ "Login", &UCLoginUI::execLogin },
			{ "ResetConnectInfo", &UCLoginUI::execResetConnectInfo },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCLoginUI_ConnectServer_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCLoginUI_ConnectServer_Statics::Function_MetaDataParams[] = {
		{ "Category", "Login|Connect" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCLoginUI_ConnectServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCLoginUI, nullptr, "ConnectServer", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCLoginUI_ConnectServer_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCLoginUI_ConnectServer_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCLoginUI_ConnectServer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCLoginUI_ConnectServer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCLoginUI_Login_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCLoginUI_Login_Statics::Function_MetaDataParams[] = {
		{ "Category", "Login|Connect" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCLoginUI_Login_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCLoginUI, nullptr, "Login", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCLoginUI_Login_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCLoginUI_Login_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCLoginUI_Login()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCLoginUI_Login_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCLoginUI_ResetConnectInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCLoginUI_ResetConnectInfo_Statics::Function_MetaDataParams[] = {
		{ "Category", "Login|Connect" },
		{ "Comment", "// UFUNCTION: ????????\xc6\xae???? ?\xd4\xbc??? ?????\xcf\xb1? ???? ????\n" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
		{ "ToolTip", "UFUNCTION: ????????\xc6\xae???? ?\xd4\xbc??? ?????\xcf\xb1? ???? ????" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCLoginUI_ResetConnectInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCLoginUI, nullptr, "ResetConnectInfo", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCLoginUI_ResetConnectInfo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCLoginUI_ResetConnectInfo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCLoginUI_ResetConnectInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCLoginUI_ResetConnectInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCLoginUI_NoRegister()
	{
		return UCLoginUI::StaticClass();
	}
	struct Z_Construct_UClass_UCLoginUI_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IP_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_IP;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Port_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Port;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ID;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Password;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCLoginUI_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealClient,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCLoginUI_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCLoginUI_ConnectServer, "ConnectServer" }, // 2325214481
		{ &Z_Construct_UFunction_UCLoginUI_Login, "Login" }, // 2268909238
		{ &Z_Construct_UFunction_UCLoginUI_ResetConnectInfo, "ResetConnectInfo" }, // 1326170343
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCLoginUI_Statics::Class_MetaDataParams[] = {
		{ "Comment", "// UUserWidget ????????\xc6\xae \xc5\xac?????? ???\xd3\xb9???\n// ?? \xc5\xac?????? ????????\xc6\xae?? ??????\n// -> UI?? ?\xca\xbf??? ?????? ?\xd4\xbc? ?????? ????????\n// \n// UCLASS ?\xf0\xb8\xae\xbe? ?????? ?????????? ?????\xcf\xb1? ???? \xc5\xb0????\n" },
		{ "IncludePath", "Login/CLoginUI.h" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
		{ "ToolTip", "UUserWidget ????????\xc6\xae \xc5\xac?????? ???\xd3\xb9???\n?? \xc5\xac?????? ????????\xc6\xae?? ??????\n-> UI?? ?\xca\xbf??? ?????? ?\xd4\xbc? ?????? ????????\n\nUCLASS ?\xf0\xb8\xae\xbe? ?????? ?????????? ?????\xcf\xb1? ???? \xc5\xb0????" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCLoginUI_Statics::NewProp_IP_MetaData[] = {
		{ "Category", "ConnectInfo" },
		{ "Comment", "// UPROPERTY: ????????\xc6\xae???? ?????\xcf\xb1? ???? ????\n" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
		{ "ToolTip", "UPROPERTY: ????????\xc6\xae???? ?????\xcf\xb1? ???? ????" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCLoginUI_Statics::NewProp_IP = { "IP", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCLoginUI, IP), METADATA_PARAMS(Z_Construct_UClass_UCLoginUI_Statics::NewProp_IP_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCLoginUI_Statics::NewProp_IP_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCLoginUI_Statics::NewProp_Port_MetaData[] = {
		{ "Category", "ConnectInfo" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCLoginUI_Statics::NewProp_Port = { "Port", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCLoginUI, Port), METADATA_PARAMS(Z_Construct_UClass_UCLoginUI_Statics::NewProp_Port_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCLoginUI_Statics::NewProp_Port_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCLoginUI_Statics::NewProp_ID_MetaData[] = {
		{ "Category", "ConnectInfo" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCLoginUI_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCLoginUI, ID), METADATA_PARAMS(Z_Construct_UClass_UCLoginUI_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCLoginUI_Statics::NewProp_ID_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCLoginUI_Statics::NewProp_Password_MetaData[] = {
		{ "Category", "ConnectInfo" },
		{ "ModuleRelativePath", "Login/CLoginUI.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCLoginUI_Statics::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCLoginUI, Password), METADATA_PARAMS(Z_Construct_UClass_UCLoginUI_Statics::NewProp_Password_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCLoginUI_Statics::NewProp_Password_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCLoginUI_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCLoginUI_Statics::NewProp_IP,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCLoginUI_Statics::NewProp_Port,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCLoginUI_Statics::NewProp_ID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCLoginUI_Statics::NewProp_Password,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCLoginUI_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCLoginUI>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCLoginUI_Statics::ClassParams = {
		&UCLoginUI::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCLoginUI_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCLoginUI_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCLoginUI_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCLoginUI_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCLoginUI()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCLoginUI_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCLoginUI, 2480374620);
	template<> UNREALCLIENT_API UClass* StaticClass<UCLoginUI>()
	{
		return UCLoginUI::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCLoginUI(Z_Construct_UClass_UCLoginUI, &UCLoginUI::StaticClass, TEXT("/Script/UnrealClient"), TEXT("UCLoginUI"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCLoginUI);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
