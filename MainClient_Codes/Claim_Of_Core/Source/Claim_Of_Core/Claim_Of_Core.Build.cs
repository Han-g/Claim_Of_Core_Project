// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Claim_Of_Core : ModuleRules
{
	public Claim_Of_Core(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Claim_Of_Core",
			"Claim_Of_Core/Variant_Platforming",
			"Claim_Of_Core/Variant_Platforming/Animation",
			"Claim_Of_Core/Variant_Combat",
			"Claim_Of_Core/Variant_Combat/AI",
			"Claim_Of_Core/Variant_Combat/Animation",
			"Claim_Of_Core/Variant_Combat/Gameplay",
			"Claim_Of_Core/Variant_Combat/Interfaces",
			"Claim_Of_Core/Variant_Combat/UI",
			"Claim_Of_Core/Variant_SideScrolling",
			"Claim_Of_Core/Variant_SideScrolling/AI",
			"Claim_Of_Core/Variant_SideScrolling/Gameplay",
			"Claim_Of_Core/Variant_SideScrolling/Interfaces",
			"Claim_Of_Core/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
