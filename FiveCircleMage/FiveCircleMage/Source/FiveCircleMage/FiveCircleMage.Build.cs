// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FiveCircleMage : ModuleRules
{
	public FiveCircleMage(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "PreCompiled.h";
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseUnity = true;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "AIModule",
            "GameplayTasks",
            "AnimGraphRuntime",
            "Niagara",
            "UMG",
            "NavigationSystem",
        });

        PublicIncludePaths.Add(ModuleDirectory);

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
