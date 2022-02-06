// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealClient : ModuleRules
{
	public UnrealClient(ReadOnlyTargetRules Target) : base(Target)
	{
		// 언리얼은 각 기능을 모듈로 가지고 있음
		// 모든 기능을 전부 빌드하지 않고 필요한 기능만 빌드하여 사용함
		// 사용할 기능을 여기서 빌드에 포함시켜야 사용할 수 있음
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
