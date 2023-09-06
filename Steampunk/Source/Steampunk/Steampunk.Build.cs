// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Steampunk : ModuleRules
{
	public Steampunk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
			{ 
				"Steampunk/Public/Player", 
				"Steampunk/Public/Components", 
				"Steampunk/Public/Dev", 
				"Steampunk/Public/Weapon",
				"Steampunk/Public/UI",
				"Steampunk/Public/Animations",
				"Steampunk/Public/Pickups",
				"Steampunk/Public/Weapon/Components",
				"Steampunk/Public/AI",
				"Steampunk/Public/AI/Tasks",
				"Steampunk/Public/AI/Services",
				"Steampunk/Public/AI/EQS",
				"Steampunk/Public/AI/Decorators",
				"Steampunk/Public/Menu",
				"Steampunk/Public/Menu/UI"
			});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
