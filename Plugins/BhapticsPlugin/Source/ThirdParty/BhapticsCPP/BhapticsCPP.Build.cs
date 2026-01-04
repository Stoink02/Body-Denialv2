//Copyright bHaptics Inc. All Rights Reserved 2022~

using System.IO;
using UnrealBuildTool;

public class BhapticsCPP : ModuleRules
{
	public BhapticsCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicSystemIncludePaths.Add("$(ModuleDir)/Public");
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "bhaptics_library.lib"));
			PublicDelayLoadDLLs.Add("bhaptics_library.dll");
			
			string runtimeDependencyPath;
			if (IsGamePlugin(Target))
			{
				string pluginRootDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../.."));
				string pluginFolderName = Path.GetFileName(pluginRootDir);
				
				runtimeDependencyPath = $"$(ProjectDir)/Plugins/{pluginFolderName}/Source/ThirdParty/BhapticsCPP/Win64/bhaptics_library.dll";
			}
			else
			{
				runtimeDependencyPath = "$(PluginDir)/Source/ThirdParty/BhapticsCPP/Win64/bhaptics_library.dll";
			}
			RuntimeDependencies.Add(runtimeDependencyPath);
		}
	}
	private bool IsGamePlugin(ReadOnlyTargetRules Target)
	{
		string projectDirectory = Path.GetDirectoryName(Target.ProjectFile.ToString());
		string normalizedPluginBaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../")).Replace("\\", "/");
		string normalizedProjectDirectory = projectDirectory.Replace("\\", "/").ToLower();
		return normalizedPluginBaseDirectory.ToLower().StartsWith(normalizedProjectDirectory);
	}
}