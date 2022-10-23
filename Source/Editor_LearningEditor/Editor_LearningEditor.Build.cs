// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Editor_LearningEditor : ModuleRules
{
	public Editor_LearningEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { });

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore" ,
			"Editor_Learning",
			"Slate",
			"SlateCore",
		});
	}
}
